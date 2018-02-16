#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QVector>
#include "source/ProcessManager/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/ProcessManager/report.h"
#include "source/ProcessManager/processitem.h"



class ProcessManager
{
public:
    ProcessManager();

    bool m_processFinished;

    QVector<ProcessItem*> m_processItems;
    QVector<NutilProcess*> m_processes;

    Counter m_mainCounter;
    QColor m_background = QColor(255,255,255,255);

    virtual bool Build(LSheet* m_sheet) = 0;
    virtual void Execute() = 0;
    virtual void ReadHeader(LSheet* m_sheet) { }

    virtual bool Verify() = 0;
//    void ExecuteAutoContrast(QString compression, QColor background);

    void ClearProcesses();
    void ClearItems();
};






#endif // PROCESSMANAGER_H
