#include "processmanagerautocontrast.h"

bool ProcessManagerAutoContrast::Build(LSheet *m_sheet)
{
    bool ok = false;
    int y = 10;
    int x = 2;

    m_processItems.clear();
    QDir directory(m_inputDir);
    QStringList images = directory.entryList(QStringList() << "*.tif" << "*.tiff",QDir::Files);
    for (QString filename: images) {
        QStringList inFileSplit = filename.split("/");
        QString inFile = (inFileSplit[inFileSplit.count()-1]);
        QFile test(m_inputDir+inFile);
        if(!test.exists()) {
            LMessage::lMessage.Error("Could not find file '" + inFile + "' for processing. Please fix input data and try again.");
            //m_status = Status::Idle;
            return false;
        }
        QString outFile = inFile;
        float scale = 1;//QString::fromWCharArray(m_sheet->readStr(y,x+3)).toFloat();

        m_processItems.append(new ProcessItem(m_inputDir+  inFile, m_outputDir+ outFile, 0, 1, outFile, m_outputDir));
        y++;
//        return true;
    }
    if (!Verify()) {
        m_processItems.clear();
        return false;
    }


//    m_pm.ExecuteTransform(m_compression, m_background, m_autoClip.toLower()=="yes", m_thumbnailSize, m_thumbType);

    return true;
}

void ProcessManagerAutoContrast::Execute()
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
        m_processes[i]->AutoContrast(pi->m_inFile, pi->m_outFile, m_compression, m_background);
        m_mainCounter.Tick();
    }
    m_processFinished = true;

}

void ProcessManagerAutoContrast::ReadHeader(LSheet *m_sheet)
{
    ProcessManager::ReadHeader(m_sheet);

    m_compression = m_sheet->readStr(2,1);
    m_inputDir = m_sheet->readStr(4,1);
    m_outputDir = m_sheet->readStr(5,1);
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);
    m_background = QColor(col_r, col_g, col_b);

 //   LMessage::lMessage.Message("Input dir: " + m_inputDir);

}
