#ifndef LIMAGE_H
#define LIMAGE_H

#include <QImage>
#include <QString>
#include <QVector>
#include <QDebug>

#include "source/util/area.h"
#include "source/util/atlaslabel.h"
#include "libxl.h"
#include "source/util/counter.h"

using namespace libxl;

class LImage
{

private:
    //unsigned char* m_data;
    //unsigned int m_width, m_height;

    QImage m_image;
    QImage m_index;
//    QVector<Area> m_areas;

    QColor unset = QColor(0,0,0,255);
    QColor set = QColor(255,255,255,255);


public:

    void Load(QString filename);

    void FindAreas(QColor color, Counter* counter, QVector<Area>* areas);

    void FillArea(Area& area, int i, int j, QColor& testColor);
//    void GenerateAreaReport(QString outExcelFile,Counter *counter);

    void SaveAreasImage(QString filename,Counter *counter, QVector<Area>* areas);
    //void RenderAreas(QImage& image, QColor color);
    LImage() {}
    LImage(QString f) {
        Load(f);
    }

    void Anchor(QString filenameStripped, QString atlasDir, QString labelFile, AtlasLabels& label,Counter *counter,QVector<Area>* areas);
    QImage& image();
};

#endif // LIMAGE_H
