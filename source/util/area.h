#ifndef AREA_H
#define AREA_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QPoint>
#include "source/util/atlaslabel.h"

class Area
{
public:
    Area();
    QVector<QPointF> m_points;
    QPointF m_center;
    double m_pixelArea=0;
    double m_area=0;
    QVector3D color;
    AtlasLabel* atlasLabel = nullptr;

    void CalculateStatistics();

    bool operator<(const Area& rhs) const {
        return rhs.m_pixelArea<m_pixelArea;


    }
};

#endif // AREA_H
