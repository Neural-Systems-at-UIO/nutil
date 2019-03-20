#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QVector>
#include "source/ProcessManager/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/ProcessManager/report.h"
#include "source/ProcessManager/processitem.h"
#include "source/util/lparameter.h"


class ProcessManager
{
public:
    ProcessManager();
    LParameter m_parameters;
    bool m_processFinished;

    QVector<ProcessItem*> m_processItems;
    QVector<NutilProcess*> m_processes;

    Counter m_mainCounter;
    QColor m_background = QColor(255,255,255,255);

    int m_numProcessors = -1;

 //   QString m_globalMessage = "";

    virtual bool Build(LSheet* m_sheet) = 0;
    virtual void Execute() = 0;
    virtual void ReadHeader(LSheet* m_sheet, LBook* book) { }

    virtual bool Verify() = 0;
//    void ExecuteAutoContrast(QString compression, QColor background);

    void ClearProcesses();
    void ClearItems();
    void SetParameters();


    void Abort() {
        ClearProcesses();
        ClearItems();

    }

};






#endif // PROCESSMANAGER_H
