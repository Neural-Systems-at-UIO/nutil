#include "processmanager.h"
#include <omp.h>

ProcessManager::ProcessManager()
{

}



void ProcessManager::ExecuteTransform(QString compression, QColor background)
{
    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(new NutilProcess());
    }

    Util::globalTimer.restart();

#pragma omp parallel for
    for (int i=0;i<m_processes.length();i++) {
        ProcessItem* pi = m_processItems[i];
        m_processes[i]->TransformTiff(pi->m_inFile, pi->m_outFile, compression, pi->m_angle, pi->m_scale, background);
    }
    m_processFinished = true;

}

void ProcessManager::ClearProcesses()
{
    for (NutilProcess* np: m_processes)
        if (np)
            delete np;

    m_processes.clear();
}
