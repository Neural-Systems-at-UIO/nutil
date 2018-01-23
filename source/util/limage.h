#ifndef LIMAGE_H
#define LIMAGE_H

#include <QImage>
#include <QString>
#include <QVector>
#include <QDebug>

#include "source/util/area.h"
#include "source/util/atlaslabel.h"
#include "libxl.h"
using namespace libxl;

class LImage
{

private:
    //unsigned char* m_data;
    //unsigned int m_width, m_height;

    QImage m_image;
    QImage m_index;
    QVector<Area> m_areas;

    QColor unset = QColor(0,0,0,255);
    QColor set = QColor(255,255,255,255);

    AtlasLabels labels;

public:

    void Load(QString filename);

    void FindAreas(QColor color);

    void FillArea(Area& area, int i, int j, QColor& testColor);
    void GenerateAreaReport(QString outExcelFile);

    void SaveAreasImage(QString filename);
    //void RenderAreas(QImage& image, QColor color);
    LImage() {}
    LImage(QString f) {
        Load(f);
    }

    void Anchor(QString filenameStripped, QString atlasDir, QString labelFile);
    QImage& image();
    QVector<Area>& areas();
};

#endif // LIMAGE_H
