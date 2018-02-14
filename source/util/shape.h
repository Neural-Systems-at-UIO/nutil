#ifndef SHAPE_H
#define SHAPE_H

#include "source/util/area.h"
#include <QPointF>

class Shape
{
public:
    Area* m_area = nullptr;
    QPointF m_center;

    Shape(Area* area);

    virtual void Fit() = 0;

};


class ShapeCircle: public Shape {
public:

    ShapeCircle(Area* area):Shape(area) {

    }

    void Fit() override;

};


#endif // SHAPE_H
