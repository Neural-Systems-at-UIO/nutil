#include "processmanager.h".|
#include <omp.h>

ProcessManager::ProcessManager()
{

}


void ProcessManager::ClearProcesses()
{
    for (NutilProcess* np: m_processes)
        if (np)
            delete np;

    m_processes.clear();
}







