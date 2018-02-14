#ifndef REPORT_H
#define REPORT_H
#include <QString>
#include <QVector>
#include "source/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/LBook/lbookxlnt.h".h"

#include "source/processitem.h"


class Report {
public:
    QString m_filename;
    QVector<long> m_IDs;
    QVector<Area*> m_areasOfInterest;
    float m_totalPixelArea = 0;
    float m_totalArea = 0;
    float m_regionPixelArea = 0;
    float m_regionArea = 0;

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
    void CreateSliceReports(QString filename, QVector<NutilProcess*> processes, QVector<ProcessItem*> items);

};


#endif // REPORT_H
