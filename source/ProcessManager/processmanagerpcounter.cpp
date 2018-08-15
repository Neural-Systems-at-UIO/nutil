#include "processmanagerpcounter.h"
#include <QStringList>
#include "source/data.h"


void ProcessManagerPCounter::LoadXML()
{


    if (QFile::exists(m_anchorFile))
        m_xmlAnchor.Load(m_anchorFile);
    else {
        LMessage::lMessage.Message("Could not find anchor file: " + m_anchorFile + ". Please specify in the input xml file!" );
        Data::data.abort = true;
    }

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
    int y = 16;
    Data::data.abort = false;

    LoadXML();

    bool done = false;
    while (!done) {
        QString name = m_sheet->readStr(y,x);
        if (name!="") {
            bool isTiff = false;
            QString inFileFull = Util::findFileInDirectory(name,m_inputDir,"png");
            if (inFileFull=="") {
                inFileFull = Util::findFileInDirectory(name,m_inputDir,"tif");
                if (inFileFull!="")
                    isTiff = true;
            }



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
            ProcessItem* pi = new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx",0, QPointF(1,1), inFileSingle, m_outputDir);
            pi->m_pixelAreaScale = m_areaScale*m_sheet->readNum(y,x+1);
            //qDebug() << name;
            pi->m_xmlData =m_xmlAnchor.findData(name);
            pi->m_id = name;
            if (isTiff)
                pi->m_filetype = "tif";
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

//    qDebug()<<"Number reports found: " << reports.m_reports.count();


    QVector<QColor> cols;
    for (int i=0;i<reports.m_reports.count();i++)
        cols.append(reports.m_reports[i].m_color);


#pragma omp parallel for num_threads(m_numProcessors)
    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];


        qDebug() << "Pcounter: " << pi->m_inFile;

        QMatrix4x4 mat(m_processItems[i]->m_xmlData.toMatrix());

        m_processes[i]->PCounter(m_inputDir+  pi->m_inFile +"."+pi->m_filetype, m_background, &m_processes[i]->m_areas, m_pixelCutoff);
        qDebug() << "PCounter done";
        for (Area&a : m_processes[i]->m_areas)
            a.m_mat = mat;
        m_processes[i]->m_infoText = "Anchoring areas";
        // Find atlas file:
        QString atlasFile = Util::findFileInDirectory(pi->m_id,m_atlasDir,"flat");


        if (atlasFile=="") {
            LMessage::lMessage.Error("Could not find any atlas flat file!");
            Data::data.abort = true;
        }
        if (Data::data.abort)
            break;

        qDebug() << "Anchor: " << pi->m_inFile;
        m_processes[i]->lImage.Anchor(pi->m_inFile, atlasFile, m_outputDir + pi->m_inFile + "_test.png", m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas, pi->m_pixelAreaScale);

        qDebug() << "Save: " << pi->m_inFile;
        m_processes[i]->lImage.SaveAreasImage(m_outputDir + pi->m_inFile + ".png",&m_processes[i]->m_counter, &m_processes[i]->m_areas, reports.getList(),cols);
        m_mainCounter.Tick();
        m_processes[i]->m_counter.m_progress = 100;
        qDebug() << "Release: " << pi->m_inFile;

// 37 49 71


        m_processes[i]->ReleasePCounter();
    }

    reports.CreateBook(m_outputDir + "Report.xlsx");
    reports.CreateSheets(m_processes, &m_labels);
    reports.CreateSliceReports(m_outputDir + "Report_slices.xlsx", m_processes, m_processItems);
    reports.CreateCombinedList(m_outputDir + "Report_combined.xlsx", &m_labels,m_processes, m_processItems);
    if (m_niftiSize!=0) {
        reports.Create3DSummary(m_outputDir + "3D_combined.txt", m_processes, m_processItems, m_xyzScale);
        reports.CreateNifti(m_outputDir + "test.nii", m_processes, m_processItems, m_niftiSize);
    }
    m_processFinished = true;



}




void ProcessManagerPCounter::ReadHeader(LSheet *m_sheet)
{
    ProcessManager::ReadHeader(m_sheet);
    m_inputDir = Util::fixFolder(m_sheet->readStr(4,1));
    m_outputDir = Util::fixFolder(m_sheet->readStr(5,1));
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);

    m_background = QColor(col_r, col_g, col_b);
    m_atlasDir = m_sheet->readStr(6,1);
    m_labelFile = m_sheet->readStr(7,1);
    m_pixelCutoff = m_sheet->readNum(9,1);
    m_areaScale = m_sheet->readNum(10,1);
    m_anchorFile = m_sheet->readStr(11,1);
    m_niftiSize = m_sheet->readNum(12,1);
    m_xyzScale = m_sheet->readNum(13,1);

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
            QColor reportColor = m_sheet->readCol(i+1,x);

            QStringList ids;// = QString::fromWCharArray(m_sheet->readStr(i,3)).split(',');
            bool done = false;
            int j=i+2;
            while (!done) {
                long num = m_sheet->readNum(j,x);
                QString s = QString::number(num);
                if (s!="" && s!="0" && j<1024)
                    ids<<s;
                else
                    done = true;
                j++;
            }
//            qDebug() << excelName;
//            qDebug() << ids;


            reports.m_reports.push_back(Report(excelName, ids,reportColor));
            //qDebug() << excelName << " , " << ids;

        }
        else hasNext = false;
        x++;
    }

}


