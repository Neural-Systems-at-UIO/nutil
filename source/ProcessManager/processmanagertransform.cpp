#include "processmanagertransform.h"
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

        float scale = m_sheet->readNum(y,x+3);
        if (scale==0)
            scale = 1;
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
    m_inputDir = Util::fixFolder(m_sheet->readStr(4,1));
    m_outputDir = Util::fixFolder(m_sheet->readStr(5,1));
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
