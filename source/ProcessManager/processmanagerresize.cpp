#include "processmanagerresize.h"

ProcessManagerResize::ProcessManagerResize()
{

}

void ProcessManagerResize::Execute()
{
    if (!QDir(m_outputDir).exists())
        QDir().mkdir(m_outputDir);

    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(new NutilProcess());
    }
    SetParameters();

    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();

    m_mainCounter = Counter(m_processes.length(),"",false);

#pragma omp parallel for

    for (int i=0;i<m_processes.length();i++) {
        QImage img;
        ProcessItem* pi = m_processItems[i];
        img.load(pi->m_inFile);

        float w = img.width();

        float newWidth = m_tileSize;
        float scale = newWidth/w;
        float newHeight = img.height()*scale;

        if (m_isPercent) {
            float p = m_tileSize/100.0;
            newWidth = img.width()*p;
            newHeight = img.height()*p;

        }

        img = img.scaled(newWidth,newHeight);

        pi->m_outFile = Util::RemoveFinalFiletype(pi->m_outFile) + ".png";
        img.save(pi->m_outFile);
        //m_processes[i]->AutoContrast(pi->m_inFile, pi->m_outFile, m_compression, m_background, m_outputDir);
        m_mainCounter.Tick();
    }
    m_processFinished = true;

}

void ProcessManagerResize::ReadHeader(NutilTemplate* data)
{
    ProcessManager::ReadHeader(data);
    m_compression = data->Get("resize_output_compression");
    m_inputDir = data->Get("resize_input_dir")+"/";
    m_outputDir = data->Get("resize_output_dir")+"/";
    m_tileSize = data->Get("resize_size").toFloat();
    m_isPercent = data->Get("resize_type").toLower().trimmed()=="percent";

}
