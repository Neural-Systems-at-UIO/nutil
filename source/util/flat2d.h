#ifndef FLAT2D_H
#define FLAT2D_H

#include <QString>
#include <QImage>

#include "source/util/atlaslabel.h"


class Flat2D
{
public:

    unsigned int *m_data = nullptr;
    unsigned int m_width, m_height;

    bool Load(QString filename);


    Flat2D();
    ~Flat2D();

    void Release();

    QImage* toImage(AtlasLabels& labels);

    unsigned int width() const;
    unsigned int height() const;
    unsigned int pixel(int i, int j);
};

#endif // FLAT2D_H
