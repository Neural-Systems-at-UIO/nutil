#include "processmanager.h".|
#include <omp.h>

ProcessManager::ProcessManager()
{

}


/*void ProcessManager::ExecuteAutoContrast(QString compression, QColor background)
{
    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(new NutilProcess());
    }


    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();
    m_mainCounter = Counter(m_processes.length(),"",false);
#pragma omp parallel for
    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];
        m_processes[i]->AutoContrast(pi->m_inFile, pi->m_outFile, compression, background);
        m_mainCounter.Tick();
    }
    m_processFinished = true;

}
*/
void ProcessManager::ClearProcesses()
{
    for (NutilProcess* np: m_processes)
        if (np)
            delete np;

    m_processes.clear();
}

bool ProcessManagerTransform::Build(LSheet *m_sheet)
{
    bool ok = false;
    int y = 10;
    int x = 2;

    m_processItems.clear();



    while (!ok) {
        QString inFile = m_sheet->readStr(y,x);
        if (inFile == "") {
            ok = true;
            break;
        }
        inFile += ".tif";

        QFile test(m_inputDir+inFile);
        if(!test.exists()) {
            LMessage::lMessage.Error("Could not find file '" + inFile + "' for processing. Please fix input data and try again.");
            //m_status = Status::Idle;
            return false;
        }

        QString outFile = m_sheet->readStr(y,x+1) + ".tif";
        float angle = m_sheet->readNum(y,x+2);

        angle = angle/360*(2*M_PI);

        float scale = 1;//QString::fromWCharArray(m_sheet->readStr(y,x+3)).toFloat();
        m_processItems.append(new ProcessItem(m_inputDir+  inFile, m_outputDir+ outFile, angle, scale, outFile, m_outputDir));
        y++;
//        return true;
    }
    if (!Verify()) {
        m_processItems.clear();
        return false;
    }


//    m_pm.ExecuteTransform(m_compression, m_background, m_autoClip.toLower()=="yes", m_thumbnailSize, m_thumbType);

}

void ProcessManagerTransform::Execute()
{
    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(new NutilProcess());
    }


    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();
    m_mainCounter = Counter(m_processes.length(),"",false);

#pragma omp parallel for

    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];
        //m_processes[i]->InitializeCounter(pi->m_inFile, m_autoClip, m_thumbnailSize);
        m_processes[i]->TransformTiff(pi->m_inFile, pi->m_outFile, m_compression, pi->m_angle, pi->m_scale, m_background, m_autoClip.toLower()=="yes");
        if (m_thumbnailSize>0) {
            QString tfolder = pi->m_outFolder + "/thumbnails/";
            if (!QDir(tfolder).exists())
               QDir().mkdir(tfolder);

            QString thumbOut = tfolder + pi->m_outFileSingle.split('.')[0] + "_thumbnail." + m_thumbType;

            m_processes[i]->GenerateThumbnail(pi->m_outFile, thumbOut,m_thumbnailSize);
        }
        m_mainCounter.Tick();
    }
    m_processFinished = true;

}

void ProcessManagerTransform::ReadHeader(LSheet* m_sheet)
{
    ProcessManager::ReadHeader(m_sheet);

    m_compression = m_sheet->readStr(2,1);
    m_inputDir = m_sheet->readStr(4,1);
    m_outputDir = m_sheet->readStr(5,1);
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);
    m_autoClip = m_sheet->readStr(7,1);
    m_thumbnailSize = m_sheet->readNum(6,1);
    m_thumbType = m_sheet->readStr(6,2);
    m_background = QColor(col_r, col_g, col_b);

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



bool ProcessManagerPCounter::Build(LSheet* m_sheet)
{
    m_processItems.clear();
    /*QDirIterator it(m_inputDir, QStringList() << "*.png", QDir::Files);
    while (it.hasNext()) {
        QString inFileFull = it.next();
        QStringList l = inFileFull.split('/');
        QString inFile = l[l.length()-1];
        QString inFileSingle = inFile.split('.')[0];
        m_processItems.append(new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx", 0, 0, inFileSingle, m_outputDir));
//        break;

    }*/
    int x = 1;
    int y = 12;
    bool done = false;
    while (!done) {
        QString name = m_sheet->readStr(y,x);
        if (name!="") {
            QString inFileFull = Util::findFileInDirectory(name,m_inputDir,"png");
            if (inFileFull=="") {
                LMessage::lMessage.Error("Error: Could not find file that contains: " + name);
                m_processItems.clear();
                return false;
            }
            QString inFlatFull = Util::findFileInDirectory(name,m_atlasDir,"flat");
            if (inFlatFull=="") {
                LMessage::lMessage.Error("Error: Could not find FLAT files that contains: " + name + ". Did you remember to run the java binary file converter?");
                m_processItems.clear();
                return false;
            }

            QStringList l = inFileFull.split('/');
            QString inFile = l[l.length()-1];
            QString inFileSingle = inFile.split('.')[0];
            ProcessItem* pi = new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx", 0, 0, inFileSingle, m_outputDir);
            pi->m_pixelAreaScale = m_areaScale*m_sheet->readNum(y,x+1);
            pi->m_id = name;
            m_processItems.append(pi);
        }
        else {
            done = true;
        }
        y++;

    }


    return true;

}

void ProcessManagerPCounter::Execute()
{

    m_labels.Load(m_labelFile);
    if (m_labels.atlases.count()==0) {
        LMessage::lMessage.Error("Incorrect label file. Please check parameters in excel sheet.");
        return;
    }


    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(new NutilProcess());
    }

    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();
    m_mainCounter = Counter(m_processes.length(),"",false);

    qDebug()<<"Number reports found: " << reports.m_reports.count();


#pragma omp parallel for
    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];


//        qDebug() << "Executing on " <<m_inputDir+  pi->m_inFile +".png";
        m_processes[i]->PCounter(m_inputDir+  pi->m_inFile +".png", m_background, &m_processes[i]->m_areas, m_pixelCutoff);
        m_processes[i]->m_infoText = "Anchoring areas";
        // Find atlas file:

        QString atlasFile = Util::findFileInDirectory(pi->m_inFile.split('_')[3] + "_Segmentation", m_atlasDir, "flat");

        m_processes[i]->lImage.Anchor(pi->m_inFile, atlasFile, m_outputDir + pi->m_inFile + "_test.png", m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas, pi->m_pixelAreaScale);
/*        m_processes[i]->m_infoText = "Generating Excel report";
        m_processes[i]->lImage.GenerateAreaReport(pi->m_outFile,&m_processes[i]->m_counter, &m_processes[i]->m_areas);
        m_processes[i]->m_infoText = "Saving test png file";
*/
        m_processes[i]->lImage.SaveAreasImage(m_outputDir + pi->m_inFile + ".png",&m_processes[i]->m_counter, &m_processes[i]->m_areas, reports.getList());
        m_mainCounter.Tick();
        m_processes[i]->m_counter.m_progress = 100;
    }

    reports.CreateBook(m_outputDir + "Report.xls");
    reports.CreateSheets(m_processes, &m_labels);
    reports.CreateSliceReports(m_outputDir + "Report_slices.xls", m_processes, m_processItems);


    m_processFinished = true;



}




void ProcessManagerPCounter::ReadHeader(LSheet *m_sheet)
{
    ProcessManager::ReadHeader(m_sheet);
    m_inputDir = m_sheet->readStr(4,1);
    m_outputDir = m_sheet->readStr(5,1);
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);

    m_background = QColor(col_r, col_g, col_b);
    m_atlasDir = m_sheet->readStr(6,1);
    m_labelFile = m_sheet->readStr(7,1);
    m_pixelCutoff = m_sheet->readNum(9,1);
    m_areaScale = m_sheet->readNum(10,1);

    GenerateReports(m_sheet);

}

void ProcessManagerPCounter::GenerateReports(LSheet *m_sheet)
{
    bool found = false;
    int i = 4;
    // Find hierarchy analysis list
    while ((i<1000) && (found==false)) {
        i++;
        QString t = m_sheet->readStr(i,1);
        if (t.simplified().toLower() == "hierarchy analysis list") {
            found = true;
            break;
        }
    }
    i++;
    bool hasNext = true;
    int x = 1;
    // As long as a next one exist (x-axis reports)
    while (hasNext) {

        QString excelName = m_sheet->readStr(i,x);
//        qDebug() << excelName << i << " " << x;
        if (excelName.simplified()!="") {
            QStringList ids;// = QString::fromWCharArray(m_sheet->readStr(i,3)).split(',');
            bool done = false;
            int j=i+1;
            while (!done) {
                double num = m_sheet->readNum(j,x);
                QString s = QString::number(num);
                if (s!="" && s!="0" && j<1024)
                    ids<<s;
                else
                    done = true;
                j++;
            }
//            qDebug() << excelName;
//            qDebug() << ids;


            reports.m_reports.push_back(Report(excelName, ids));
            //qDebug() << excelName << " , " << ids;

        }
        else hasNext = false;
        x++;
    }

}



