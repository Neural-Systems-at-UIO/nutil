#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QVector>
#include "source/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/LBook/lbookxlnt.h".h"

class ProcessItem {
public:
    QString m_inFile;
    QString m_outFile;

    QString m_outFolder;
    QString m_outFileSingle;

//    QString m_infoText;

    float m_angle;
    float m_scale;

    ProcessItem() {

    }

    ProcessItem(QString inFile, QString outFile, float angle, float scale, QString outFileSingle, QString outFolder) {
        m_inFile = inFile;
        m_outFile = outFile;
        m_angle = angle;
        m_scale = scale;
        m_outFolder = outFolder;
        m_outFileSingle = outFileSingle;
    }


};

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

//    void ExecuteAutoContrast(QString compression, QColor background);

    void ClearProcesses();
    void ClearItems();
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

};

class Report {
public:
    QString m_filename;
    QVector<long> m_IDs;
    QVector<Area*> m_areasOfInterest;
    float m_totalPixelArea;
    float m_regionPixelArea;

    Report() {}
    Report(QString filename, QStringList& ids) {
        m_filename = filename;
        for (QString s : ids) {
            bool ok;
            long l = s.simplified().toDouble(&ok);
            m_IDs.push_back( l);
        }
    }

    void FindAreasOfInterest(QVector<NutilProcess*>& processes);
    void GenerateSheet(LBook* b);
};


class Reports {
public:

    LBook* m_book;
    QString m_filename;
    QVector<Report> m_reports;
    QVector<QVector<long>> getList();

    void Calculate(AtlasLabels* atlasLabels);
    void CreateBook(QString filename );
    void CreateSheets( QVector<NutilProcess*>& processes,AtlasLabels* atlasLabels);
    void CreateSummary(AtlasLabels* atlasLabels);

};

class ProcessManagerPCounter : public ProcessManager {

public:

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir;
    QString m_atlasDir;
    QString m_labelFile;

    int m_pixelCutoff;

    Reports reports;


    bool Build(LSheet* m_sheet) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet) override;

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
