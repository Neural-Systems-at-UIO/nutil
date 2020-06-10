#include "processmanager.h"

ProcessManager::ProcessManager()
{

}


void ProcessManager::ClearProcesses()
{
/*    for (QSharedPointer<NutilProcess> np: m_processes)
        if (np)
            delete np;


  */
    m_processes.clear();
}

void ProcessManager::SetParameters()
{
    for (QSharedPointer<NutilProcess> np:m_processes) {
        np->m_parameters = &m_parameters;
    }
}








