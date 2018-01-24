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

bool ProcessManagerTransform::Build(Sheet *m_sheet)
{
    bool ok = false;
    int y = 10;
    int x = 2;

    m_processItems.clear();


    while (!ok) {
        QString inFile = QString::fromWCharArray(m_sheet->readStr(y,x));
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

        QString outFile = QString::fromWCharArray(m_sheet->readStr(y,x+1)) + ".tif";
        float angle = m_sheet->readNum(y,x+2);

        angle = angle/360*(2*M_PI);

        float scale = 1;//QString::fromWCharArray(m_sheet->readStr(y,x+3)).toFloat();
        m_processItems.append(new ProcessItem(m_inputDir+  inFile, m_outputDir+ outFile, angle, scale, outFile, m_outputDir));
        y++;
        return true;
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

void ProcessManagerTransform::ReadHeader(Sheet* m_sheet)
{
    ProcessManager::ReadHeader(m_sheet);

    m_compression = QString::fromWCharArray(m_sheet->readStr(2,1));
    m_inputDir = QString::fromWCharArray(m_sheet->readStr(4,1));
    m_outputDir = QString::fromWCharArray(m_sheet->readStr(5,1));
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);
    m_autoClip = QString::fromWCharArray(m_sheet->readStr(7,1));
    m_thumbnailSize = m_sheet->readNum(6,1);
    m_thumbType = QString::fromWCharArray(m_sheet->readStr(6,2));
    m_background = QColor(col_r, col_g, col_b);

    LMessage::lMessage.Message("Input dir: " + m_inputDir);

}


bool ProcessManagerPCounter::Build(Sheet* m_sheet)
{
    m_processItems.clear();
    QDirIterator it(m_inputDir, QStringList() << "*.png", QDir::Files);
    while (it.hasNext()) {
        QString inFileFull = it.next();
        QStringList l = inFileFull.split('/');
        QString inFile = l[l.length()-1];
        QString inFileSingle = inFile.split('.')[0];
        m_processItems.append(new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xls", 0, 0, inFileSingle, m_outputDir));
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
#pragma omp parallel for
    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];

        //qDebug() << "Executing on " <<m_inputDir+  pi->m_inFile +".png";
        m_processes[i]->PCounter(m_inputDir+  pi->m_inFile +".png", m_background, &m_processes[i]->m_areas);
        m_processes[i]->m_infoText = "Anchoring areas";
        // Find atlas file:

        QString atlasFile = Util::findFileInDirectory(pi->m_inFile.split('_')[3] + "_Segmentation", m_atlasDir, "png");

        m_processes[i]->lImage.Anchor(pi->m_inFile, atlasFile, m_labelFile, m_labels, &m_processes[i]->m_counter, &m_processes[i]->m_areas);
/*        m_processes[i]->m_infoText = "Generating Excel report";
        m_processes[i]->lImage.GenerateAreaReport(pi->m_outFile,&m_processes[i]->m_counter, &m_processes[i]->m_areas);
        m_processes[i]->m_infoText = "Saving test png file";
*/
        m_processes[i]->lImage.SaveAreasImage(m_outputDir + pi->m_inFile + ".png",&m_processes[i]->m_counter, &m_processes[i]->m_areas);
        m_mainCounter.Tick();
        m_processes[i]->m_counter.m_progress = 100;
    }

    reports.CreateBook(m_outputDir + "Report.xls");
    reports.CreateSheets(m_processes);

    m_processFinished = true;

}

void ProcessManagerPCounter::ReadHeader(Sheet *m_sheet)
{
    ProcessManager::ReadHeader(m_sheet);
    m_inputDir = QString::fromWCharArray(m_sheet->readStr(4,1));
    m_outputDir = QString::fromWCharArray(m_sheet->readStr(5,1));
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);
    m_background = QColor(col_r, col_g, col_b);
    m_atlasDir = QString::fromWCharArray(m_sheet->readStr(6,1));
    m_labelFile = QString::fromWCharArray(m_sheet->readStr(7,1));

    bool found = false;
    int i = 4;
    while ((i<1000) && (found==false)) {
        i++;
        QString t = QString::fromWCharArray(m_sheet->readStr(i,1));
        if (t.simplified().toLower() == "hierarchy analysis list") {
            found = true;
            break;
        }
    }
    i++;
    bool hasNext = true;
    while (hasNext) {
        QString excelName = QString::fromWCharArray(m_sheet->readStr(i,1));
        if (excelName.simplified()!="") {
            QStringList ids = QString::fromWCharArray(m_sheet->readStr(i,3)).split(',');
            reports.m_reports.push_back(Report(excelName, ids));
            //qDebug() << excelName << " , " << ids;
        }
        else hasNext = false;
        i++;
    }


}

void Report::GenerateSheet(Book* book)
{
    wchar_t* wname = Util::QStringToWchar(m_filename);
    Sheet* sheet = book->addSheet(wname);
    qDebug() << "Inserting sheet: " << QString::fromWCharArray(wname);
    delete[] wname;

    if(sheet)
    {
        sheet->writeStr(1,0, L"Pixel count");
        sheet->writeStr(1,1, L"Area (not yet defined)");

        sheet->writeStr(1, 2, L"object_area_units");
        sheet->writeStr(1, 3, L"Center X");
        sheet->writeStr(1, 4, L"Center Y");
        sheet->writeStr(1, 5, L"Area ID");
        sheet->writeStr(1, 6, L"Area name");
        for (int i=0;i<m_areasOfInterest.count();i++) {
            sheet->writeNum(2+i,0, m_areasOfInterest[i]->m_pixelArea);
            sheet->writeNum(2+i,3, m_areasOfInterest[i]->m_center.x());
            sheet->writeNum(2+i,4, m_areasOfInterest[i]->m_center.y());
            sheet->writeNum(2+i,5, m_areasOfInterest[i]->atlasLabel->index);
            wchar_t* arr = Util::QStringToWchar(m_areasOfInterest[i]->atlasLabel->name);
            sheet->writeStr(2+i,6, arr);
            delete[] arr;
        }

    }
}

void Report::FindAreasOfInterest(QVector<NutilProcess *>& processes)
{
    m_areasOfInterest.clear();
    for (int i : m_IDs) {
        qDebug() << "Checking for: " << i;
        for (NutilProcess* np : processes)
            for (Area& a: np->m_areas)
                if (a.atlasLabel->index == i)
                    m_areasOfInterest.append(&a);


    }
    qDebug() << "Found amount: " << m_areasOfInterest.count();
}

void Reports::CreateBook(QString filename)
{
    m_book = xlCreateBook(); // xlCreateXMLBook() for xlsx
    //m_book = xlCreateXMLBook();// for xlsx
    m_filename = filename;
}

void Reports::CreateSheets(QVector<NutilProcess*>& processes)
{
    if(m_book)
        for (Report& r: m_reports) {
            r.FindAreasOfInterest(processes);
            r.GenerateSheet(m_book);
        }

    wchar_t* arr = Util::QStringToWchar(m_filename);
    m_book->save(arr);
    qDebug() << QString::fromWCharArray(arr);
    delete[] arr;
    m_book->release();

}
