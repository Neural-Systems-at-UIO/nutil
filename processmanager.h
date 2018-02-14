#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QVector>
#include "source/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/report.h"
#include "source/processitem.h"



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

class ProcessManagerAutoContrast : public ProcessManager {
public:
    QString m_inputDir, m_outputDir;
    QString m_compression = "jpg";

    bool Build(LSheet* m_sheet) override {return true;}
    void Execute() override {  } //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet) override {return;}
    bool Verify() override { return true; }

};


class ProcessManagerTransform : public ProcessManager {

public:

    QString m_inputDir, m_outputDir;
    QString m_compression = "jpg";
    QString m_thumbType;
    QString m_autoClip;

    int m_thumbnailSize;

    bool Build(LSheet* m_sheet) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet) override;
    bool Verify() override;

};

class ProcessManagerPCounter : public ProcessManager {

public:

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir;
    QString m_atlasDir;
    QString m_labelFile;

    int m_pixelCutoff;
    float m_areaScale = 1;

    Reports reports;


    bool Build(LSheet* m_sheet) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet) override;

    void GenerateReports(LSheet* m_sheet);
    bool Verify() override { return true; }

};


class ProcessManagerFactory {
public:
    static ProcessManager* CreateProcessManager(QString pm_type) {
        if (pm_type.toLower() == "rotation")
            return new ProcessManagerTransform();
        if (pm_type.toLower() == "pcounter")
            return new ProcessManagerPCounter();

        return nullptr;
    }


};

#endif // PROCESSMANAGER_H
