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
        qDebug() << "Added " << inFile << " to " << outFile;
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
        qDebug() << "Added " << inFile << " for PCounting";
    }
    return true;

}

void ProcessManagerPCounter::Execute()
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

        m_processes[i]->PCounter(m_inputDir+  pi->m_inFile +".png", m_background);
        pi->m_infoText = "Anchoring areas";
        m_processes[i]->lImage.Anchor(pi->m_inFile, m_atlasDir, m_labelFile);
        pi->m_infoText = "Generating Excel report";
        m_processes[i]->lImage.GenerateAreaReport(pi->m_outFile);
        pi->m_infoText = "Saving test png file";

        m_processes[i]->lImage.SaveAreasImage(m_outputDir + pi->m_inFile + ".png");
        m_mainCounter.Tick();
    }
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

}
