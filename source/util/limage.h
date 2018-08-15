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

#include <QRgb>
#include "source/util/nlimagetiff.h"

class NLImage
{

private:
    //unsigned char* m_data;
    //unsigned int m_width, m_height;

/*    QImage m_image;
    QImage m_index;*/

    enum Type{TIFF, OTHER};

    Type m_type = Type::OTHER;


    NLIParent* m_image=nullptr;
    NLIParent* m_index=nullptr;
//    QVector<Area> m_areas;

    QColor unset = QColor(0,0,0,255);
    QColor set = QColor(255,255,255,255);

    QImage* m_testImage = nullptr;
    int scale = 1;


public:

    NLIParent* createImage(int w, int h) {
//        if (m_type==TIFF)
//            return new NLImageTiff();
        if (m_type==OTHER)
            return new NLIQImage(w,h);

        return nullptr;
    }

    void Load(QString filename);

    void Release();
    void FindAreas(QColor color, Counter* counter, QVector<Area>* areas, int pixelCutoff, int pMax);

    void FillArea(Area& area, const int i, const int j, const QColor& testColor, int pMax);
//    void GenerateAreaReport(QString outExcelFile,Counter *counter);

    void CountAtlasArea(Flat2D& refImage, AtlasLabels& labels, float scale, float areaScale);
    void SaveAreasImage(QString filename,Counter *counter, QVector<Area>* areas, QVector<QVector<long>>, QVector<QColor> cols);
    //void RenderAreas(QImage& image, QColor color);
    NLImage() {}
    NLImage(QString f) {
        Load(f);
    }

    void Anchor(QString filenameStripped, QString atlasDir, QString labelFile, AtlasLabels& label,Counter *counter,QVector<Area>* areas, float pixelAreaScale);
    NLIParent* image();
};

#endif // LIMAGE_H
