#ifndef AREA_H
#define AREA_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QPoint>
#include "source/util/atlaslabel.h"
#include <QColor>
class Area
{
public:
    Area();
    QVector<QPointF> m_points;
    QPointF m_center;
    double m_pixelArea=0;
    QMatrix4x4 m_mat;
    double m_area=0;
    double m_areaScale = 0;
    double m_width,m_height;
    QColor color;
    AtlasLabel* atlasLabel = nullptr;

    void CalculateStatistics();

    bool operator<(const Area& rhs) const {
        return rhs.m_pixelArea<m_pixelArea;


    }
};

#endif // AREA_H
