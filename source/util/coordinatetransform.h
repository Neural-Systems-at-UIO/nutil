#ifndef COORDINATETRANSFORM_H
#define COORDINATETRANSFORM_H

#include <QMatrix4x4>

class CoordinateTransform
{
public:

    CoordinateTransform();

    static QVector3D Linear(QVector3D& p, QMatrix4x4& mat)
    {
        return p*mat;

    }

    void Setup(QMatrix4x4 &mat, QVector<QVector4D>& marks, int m_height, int m_width) {
        // Sets up and stores transformation data in class members
    }


    QVector3D NonLinear(QVector3D& p)
    {
        // performs a 2d -> 3d transform using the current setup
        return p;

    }

};

#endif // COORDINATETRANSFORM_H
