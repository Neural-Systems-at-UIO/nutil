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


QVector<QVector<long> > Reports::getList()
{
    QVector<QVector<long>> list;
    for (Report& r: m_reports) {
        list.append(r.m_IDs);
    }
    return list;
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

            QStringList l = inFileFull.split('/');
            QString inFile = l[l.length()-1];
            QString inFileSingle = inFile.split('.')[0];
            ProcessItem* pi = new ProcessItem(inFileSingle, m_outputDir+ inFileSingle + ".xlsx", 0, 0, inFileSingle, m_outputDir);
            pi->m_pixelAreaScale = m_areaScale*m_sheet->readNum(y,x+1);
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

    while (hasNext) {

        QString excelName = m_sheet->readStr(i,x);
        qDebug() << excelName << i << " " << x;
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
            qDebug() << excelName;
            qDebug() << ids;


            reports.m_reports.push_back(Report(excelName, ids));
            //qDebug() << excelName << " , " << ids;

        }
        else hasNext = false;
        x++;
    }

}

void Report::GenerateSheet(LBook* book)
{
    LSheet* sheet = book->CreateSheet(m_filename);

    if(sheet)
    {
        sheet->writeStr(0,0, "Pixel count");
        sheet->writeStr(0,1, "Area");

        sheet->writeStr(0, 2, "object_area_units");
        sheet->writeStr(0, 3, "Center X");
        sheet->writeStr(0, 4, "Center Y");
        sheet->writeStr(0, 5, "Area ID");
        sheet->writeStr(0, 6, "Area name");
        for (int i=0;i<m_areasOfInterest.count();i++) {
            sheet->writeNum(1+i,0, m_areasOfInterest[i]->m_pixelArea);
            sheet->writeNum(1+i,1, m_areasOfInterest[i]->m_area);
            sheet->writeNum(1+i,3, m_areasOfInterest[i]->m_center.x());
            sheet->writeNum(1+i,4, m_areasOfInterest[i]->m_center.y());
            sheet->writeNum(1+i,5, m_areasOfInterest[i]->atlasLabel->index);
            sheet->writeStr(1+i,6, m_areasOfInterest[i]->atlasLabel->name);
        }

    }
}

void Reports::CreateSummary(AtlasLabels* atlasLabels)
{
    LSheet* sheet = m_book->CreateSheet("Summary");
    Calculate(atlasLabels);

    if (sheet) {

        sheet->writeStr(0,0, "Region name");
        sheet->writeStr(0,1, "reg_idx_full");
        sheet->writeStr(0,2, "reg_idx");
        sheet->writeStr(0,3, "Region pixel area");
        sheet->writeStr(0,4, "Region area");
        sheet->writeStr(0,5, "Area unit");
        sheet->writeStr(0,6, "Object count");
        sheet->writeStr(0,7, "Object region count ratio");
        sheet->writeStr(0,8, "Object pixel");
        sheet->writeStr(0,9, "Object area");
        sheet->writeStr(0,10, "Object area unit");
        sheet->writeStr(0,11, "Object area ratio");

        int i = 1;
        for (Report& r : m_reports) {
            sheet->writeStr(i,0, r.m_filename);
            sheet->writeNum(i,3, r.m_regionPixelArea);
            sheet->writeNum(i,4, r.m_regionArea);
            sheet->writeNum(i,6, r.m_areasOfInterest.count());
            sheet->writeNum(i,8, r.m_totalPixelArea);
            sheet->writeNum(i,9, r.m_totalArea);
            sheet->writeNum(i,11, r.m_totalPixelArea/(float)r.m_regionPixelArea);



            i++;
        }

    }

}

void Report::FindAreasOfInterest(QVector<NutilProcess *>& processes)
{
    m_areasOfInterest.clear();
    for (long i : m_IDs) {
        for (NutilProcess* np : processes)
            for (Area& a: np->m_areas)
                if (a.atlasLabel!=nullptr)
                    if (a.atlasLabel->index == i)
                        m_areasOfInterest.append(&a);


    }
    qDebug() << "Found amount: " << m_areasOfInterest.count();

}

void Reports::Calculate(AtlasLabels* atlasLabels)
{
    for (Report& r: m_reports) {
        r.m_totalPixelArea = 0;
        r.m_regionPixelArea = 0;
        r.m_totalArea = 0;
        r.m_regionArea = 0;
        for (Area* a: r.m_areasOfInterest) {
            r.m_totalPixelArea+=a->m_pixelArea;
            r.m_totalArea +=a->m_area;
        }
        for (int i: r.m_IDs) {
            AtlasLabel* al = atlasLabels->get(i);
            if (al!=nullptr) {
                r.m_regionPixelArea += al->area;
                r.m_regionArea += al->areaScaled;
            }
        }

    }
}

void Reports::CreateBook(QString filename)
{
    m_book = new LBookXlnt();
    //m_book = xlCreateXMLBook();// for xlsx
    m_filename = filename;

}

void Reports::CreateSheets(QVector<NutilProcess*>& processes,AtlasLabels* atlasLabels)
{
    if (!m_book)
        return;
    for (Report& r: m_reports)
            r.FindAreasOfInterest(processes);

    qDebug() << "Creating summary ";
    CreateSummary(atlasLabels);

    qDebug() << "Generating sheets ";

    for (Report& r: m_reports) {
        r.GenerateSheet(m_book);
    }
    qDebug() << "Saving to " << m_filename;
    m_book->Save(m_filename);

    qDebug() << "Releasing " << m_filename;
    m_book->Release();

}






