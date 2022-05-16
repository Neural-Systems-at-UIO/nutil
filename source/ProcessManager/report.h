/*
Nutil - Neuroimaging utilities - aims to both simplify and streamline the mechanism of
pre-and-post processing 2D brain image data. Nutil is developed as a stand-alone application
that runs on all operating systems with a minimalistic user interface requiring little-to-no
experience to execute.

Copyright (C) 2020 nicolaas.groeneboom@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef REPORT_H
#define REPORT_H
#include <QString>
#include <QVector>
#include <QColor>
#include "source/data.h"
#include "source/ProcessManager/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/LBook/lbookxlnt.h"
#include "source/util/counter.h"
#include "source/ProcessManager/processitem.h"
#include "source/LBook/lbookfactory.h"
#include "source/util/coordinatetransform.h"

class Report {
public:
    QString m_filename;
    QColor m_color = QColor(255,0,0);
    QVector<long> m_IDs;
    QVector<Area*> m_areasOfInterest;
    QString m_unit;
    double m_totalPixelArea = 0;
    double m_totalArea = 0;
    double m_regionPixelArea = 0;
    double m_regionArea = 0;

    Report() {}
    Report(QString filename, QStringList& ids, QColor c) {
        m_filename = filename;
        m_color = c;
        for (QString s : ids) {
            bool ok;
            long l = (long)s.simplified().toLong(&ok);
/*            if (l>100000)
                qDebug() << "FOUND " << l;
            if (!ok) {
                qDebug() << "NOT OK: " <<s.simplified() << " " << l;
            }*/
            m_IDs.push_back( l);
        }
    }

    void FindAreasOfInterest(QVector<QSharedPointer<NutilProcess>>& processes);
    void GenerateSheet(LBook* b, QString units);

};


class Reports {
public:

    LBook* m_book;
    QString m_filename;
    QVector<Report> m_reports;
    QVector<QVector<long>> getList();

    void Calculate(AtlasLabels* atlasLabels);
    void CreateBook(QString filename, QString type);
    void CreateSheets( QVector<QSharedPointer<NutilProcess>>& processes,AtlasLabels* atlasLabels, QString unit, bool hasAreaSplitting);
    void CreateSummary(AtlasLabels* atlasLabels);
    void CreateRefAtlasRegions( QString filename, AtlasLabels* atlasLabels,QVector<QSharedPointer<NutilProcess>> processes,QVector<QSharedPointer<ProcessItem>> items, QString units, QString bookType);
    void CreateRefAtlasRegionsSlices( QString filename, AtlasLabels* atlasLabels,QVector<QSharedPointer<NutilProcess>> processes,QVector<QSharedPointer<ProcessItem>> items, QString units, QString bookType, bool displayID);
    void CreateSliceReports(QString filename,  QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items,AtlasLabels* labels, QString units, QString bType, bool displayID);
    void CreateCustomRegions(QString filename,  QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items,AtlasLabels* labels, QString bType);

    void Create3DSummary(QString filename , QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items, float xyzSize, double spread);
    void Create3DSummaryJson(QString filename , QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items, float xyzSize, double spread, QString atlasType);
    void Create3DSliceJson(QString filename , QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items, float xyzSize, double spread);

    void CreateNifti(QString filename , QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items, int size);

    QVector3D InvProject(QPointF p, Area* a, double rndSpread, QVector3D invCenter, QVector3D* altPoint, CoordinateTransform* transform);
    QVector3D InvProject(QPointF p, Area* a, double rndSpread, CoordinateTransform* transform) {
        return InvProject(p,a,rndSpread,QVector3D(0,0,0), nullptr, transform);
    }




};


#endif // REPORT_H
