#include "processmanager.h"

ProcessManager::ProcessManager()
{

}

void ProcessManager::StartTimer()
{
    m_timer.restart();
}

void ProcessManager::EndTimer(QString text)
{
    QString t = Util::MilisecondToString(m_timer.elapsed());
    LMessage::lMessage.Message(text + " process time: <font color=\"#7FFF7F\">"+t+"</font>");
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








