#include "processmanagertransform.h"
#include "source/data.h"
bool ProcessManagerTransform::Build(NutilTemplate* data)
{
    bool ok = false;
    int y = 10;
    int x = 0;

    m_processItems.clear();
    QString dt = data->m_items["transform_files"]->m_value;
//    dt = dt.replace("#NNN","\n");
    QStringList dataList =dt.split(",");
//    //while (!ok)

    QStringList full;

    int width = data->m_items["transform_files"]->m_matrixFieldWidth;
    for (int i=0;i<dataList.count()/width;i++) {
        QString cur = "";
        for (int j=0;j<width;j++) {
            cur += dataList[i*width+j].trimmed() + ",";
        }
        cur.remove(cur.length()-1,1);
        full.append(cur);
    }


    for (QString f : full)
    {
//        qDebug() << f;
        QStringList d = f.simplified().trimmed().split(",");
        QString inFile = d[0];
        if (inFile == "") {
            ok = true;
            break;
        }
        QString searchFile = Util::findFileInSubDirectories(inFile,m_inputDir,"");


        LMessage::lMessage.Log("Transform found file: " + searchFile);
//        qDebug() << "Found: " << searchFile;
        if (searchFile=="" || !searchFile.contains(".tif")) {
            LMessage::lMessage.Error("Could not find any file '"+inFile+"' in subdirectories.");
            return false;
        }
        inFile = searchFile;

//        qDebug() << inFile;

        QFile test(inFile);
        if(!test.exists()) {
            LMessage::lMessage.Error("Could not find file '" + inFile + "' for processing. Please fix input data and try again.");
            //m_status = Status::Idle;
            return false;
        }

        QString outFile = d[1].trimmed() + ".tif";
        if (outFile==".tif") {

            LMessage::lMessage.Error("Output file not specified for : '"+inFile+"'.");
            return false;
        }

        float angle = d[2].toFloat();

        angle = angle/360*(2*M_PI);

        float scaleX = d[3].toFloat();//m_sheet->readNum(y,x+3);
        float scaleY = d[4].toFloat();//m_sheet->readNum(y,x+4);
        if (scaleX==0)
            scaleX = 1;
        if (scaleY==0)
            scaleY = 1;

//        qDebug() << "Scales : " << scaleX << scaleY;

        QPointF scale(scaleX, scaleY);
        m_processItems.append(QSharedPointer<ProcessItem>(new ProcessItem(inFile, m_outputDir+ outFile, angle, scale, outFile, m_outputDir)));
        y++;
//        return true;
    }
    if (!Verify()) {
        m_processItems.clear();
        return false;
    }


    if (!QDir(m_outputDir).exists())
        QDir().mkdir(m_outputDir);


    return true;
//    m_pm.ExecuteTransform(m_compression, m_background, m_autoClip.toLower()=="yes", m_thumbnailSize, m_thumbType);

}

void ProcessManagerTransform::Execute()
{
    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(QSharedPointer<NutilProcess>(new NutilProcess()));
    }
    SetParameters();


    QFile::copy(m_excelInputFilename, m_outputDir + "/" + m_excelInputFilename.split("/").last());

    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();
    m_mainCounter = Counter(m_processes.length(),"",false);

#pragma omp parallel for num_threads(m_numProcessors)

    for (int i=0;i<m_processes.length();i++) {
        QSharedPointer<ProcessItem> pi = m_processItems[i];

        //m_processes[i]->InitializeCounter(pi->m_inFile, m_autoClip, m_thumbnailSize);

        if (!m_onlyThumbs) {

            m_processes[i]->TransformTiff(pi->m_inFile, pi->m_outFile, m_compression, pi->m_angle, pi->m_scale, m_background, m_colorSpread, m_autoClip.toLower()=="yes");
            if (Data::data.abort || Util::CancelSignal) {
                LMessage::lMessage.Log("User aborting!");
                //break;
            }
        }
        if (m_thumbnailSize>0) {
            QString tfolder = pi->m_outFolder + "/thumbnails/";
            if (!QDir(tfolder).exists())
               QDir().mkdir(tfolder);


            QString thumbOut = tfolder + pi->m_outFileSingle.split('.')[0] + "_thumbnail." + m_thumbType;
//            qDebug() <<"*** : "<< pi->m_outFileSingle;

            if (m_thumbnailSize!=0) {

            if (!m_onlyThumbs)
                m_processes[i]->GenerateThumbnail(pi->m_outFile, thumbOut,m_thumbnailSize);
            else
                m_processes[i]->GenerateThumbnail(pi->m_inFile, thumbOut,m_thumbnailSize);

            }
            }
        m_mainCounter.Tick();
    }
    m_processFinished = true;

}

void ProcessManagerTransform::ReadHeader(NutilTemplate* data)
{

    m_compression = data->Get("output_compression");
    m_inputDir = Util::fixFolder(data->Get("transform_input_dir"));
    m_outputDir = Util::fixFolder(data->Get("transform_output_dir"));
    m_background =  NutilTemplateItem::StringToColor(data->Get("transform_background_color"));

    m_colorSpread = data->Get("transform_color_spread").toFloat();
    if (m_colorSpread==0) m_colorSpread=1;
    m_autoClip = data->Get("auto_crop");
    m_onlyThumbs = (data->Get("only_thumbnails").toLower()=="yes");


    m_thumbnailSize = data->Get("transform_thumbnail_size").toFloat();

//    qDebug() << m_thumbnailSize;
  //  exit(1);

    m_thumbType = "png";

    LMessage::lMessage.Message("Input dir: " + m_inputDir);
}

bool ProcessManagerTransform::Verify()
{
    // Verify that output files are NOT identical
    for (int i=0;i<m_processItems.count();i++) {
        QString testFile = m_processItems[i]->m_outFile;
        for (int j=i+1;j<m_processItems.count();j++) {
            if (testFile.toLower() == m_processItems[j]->m_outFile) {
                LMessage::lMessage.Error("ERROR: Output filenams are identical: " + testFile);
                return false;
            }
        }
    }

    return true;
}
