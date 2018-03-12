#ifndef NLIMAGE_H
#define NLIMAGE_H

#include <QImage>
#include <QString>
#include <QVector>
#include <QDebug>

#include "source/util/area.h"
#include "source/util/atlaslabel.h"
#include "xlnt/xlnt.hpp"
#include "source/util/counter.h"
#include "source/util/flat2d.h"

//using namespace libxl;

class NLImage
{

private:
    //unsigned char* m_data;
    //unsigned int m_width, m_height;

    QImage m_image;
    QImage m_index;
//    QVector<Area> m_areas;

    QColor unset = QColor(0,0,0,255);
    QColor set = QColor(255,255,255,255);

    QImage* m_testImage = nullptr;
    int scale = 2;


public:

    void Load(QString filename);
    void Release();
    void FindAreas(QColor color, Counter* counter, QVector<Area>* areas, int pixelCutoff);

    void FillArea(Area& area, int i, int j, QColor& testColor);
//    void GenerateAreaReport(QString outExcelFile,Counter *counter);

    void CountAtlasArea(Flat2D& refImage, AtlasLabels& labels, float scale, float areaScale);
    void SaveAreasImage(QString filename,Counter *counter, QVector<Area>* areas, QVector<QVector<long>>, QVector<QColor> cols);
    //void RenderAreas(QImage& image, QColor color);
    NLImage() {}
    NLImage(QString f) {
        Load(f);
    }

    void Anchor(QString filenameStripped, QString atlasDir, QString labelFile, AtlasLabels& label,Counter *counter,QVector<Area>* areas, float pixelAreaScale);
    QImage& image();
};

#endif // LIMAGE_H
