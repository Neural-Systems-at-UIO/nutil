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
#ifndef NLIMAGE_H
#define NLIMAGE_H

#include <QImage>
#include <QString>
#include <QVector>
#include <QDebug>

#include "source/util/area.h"
#include "source/util/atlaslabel.h"


#ifndef TARGET_OS_MAC
#include "xlnt/xlnt.hpp"
#else
//#include "/usr/local/include/xlnt/xlnt.hpp"
#include "xlnt/xlnt.hpp"
#endif


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
    float scale = 1.0;


public:

    int m_totalPixelArea;

    NLIParent* createImage(int w, int h) {
//        if (m_type==TIFF)
//            return new NLImageTiff();
        if (m_type==OTHER)
            return new NLIQImage(w,h);

        return nullptr;
    }

    void Load(QString filename);

    void ApplyMask(QString maskFile, QVector3D useColor, QColor background);

    void Release();
    void FractalAnalyze();
    void FindAreas(QColor color, QVector3D colorWidth,Counter* counter, QVector<Area>* areas, int pixelCutoff, int pMax);

    void FillAreaDFS(Area& area, const int i, const int j, const QColor& testColor, const QVector3D& spread,int pMax);
    void FillAreaBFS(Area& area, const int i, const int j, const QColor& testColor, const QVector3D& spread,int pMax);
//    void GenerateAreaReport(QString outExcelFile,Counter *counter);

    void CountAtlasArea(Flat2D& refImage, AtlasLabels& labels, double scale, double areaScale, int slice, QString maskFile, QVector3D maskColor);
    void SaveAreasImage(QString filename,Counter *counter, QVector<Area>* areas, QVector<QVector<long>>, QVector<QColor> cols, QString maskFile,QColor m_customMaskInclusionColors,bool outputRegionID, bool displayID);
    //void RenderAreas(QImage& image, QColor color);
    NLImage() {}
    NLImage(QString f) {
        Load(f);
    }

    void AnchorSingle(QString filenameStripped, QString atlasDir, QString labelFile, AtlasLabels& label,Counter *counter,QVector<Area>* areas, float pixelAreaScale, int slice, QString maskFile, QVector3D maskColor);
    void AnchorSplitting(QString filenameStripped, QString atlasDir, QString labelFile, AtlasLabels& label,Counter *counter,QVector<Area>* areas, double pixelAreaScale, int slice, QString maskFile, QVector3D maskColor);
    NLIParent* image();
};

#endif // LIMAGE_H
