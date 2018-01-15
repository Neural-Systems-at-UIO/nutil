#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QVector>
#include "source/nutilprocess.h"

class ProcessItem {
public:
    QString m_inFile;
    QString m_outFile;
    QString m_infoText;
    float m_angle;
    float m_scale;


    ProcessItem() {

    }

    ProcessItem(QString inFile, QString outFile, float angle, float scale) {
        m_inFile = inFile;
        m_outFile = outFile;
        m_angle = angle;
        m_scale = scale;
    }


};

class ProcessManager
{
public:
    ProcessManager();

    bool m_processFinished;

    QVector<ProcessItem*> m_processItems;
    QVector<NutilProcess*> m_processes;

    void ExecuteTransform(QString compression, QColor background);

    void ClearProcesses();
    void ClearItems();
};

#endif // PROCESSMANAGER_H
