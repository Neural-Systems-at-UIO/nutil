#ifndef FLAT2D_H
#define FLAT2D_H

#include <QString>
#include <QImage>
#include <QByteArray>
#include "source/util/atlaslabel.h"


class Flat2D
{
public:

    unsigned int *m_data_i = nullptr;
    unsigned short *m_data_s = nullptr;
//    unsigned char *m_data_b = nullptr;
    QByteArray m_data_b;

    unsigned int m_width, m_height;
    unsigned char m_bpp;

    bool m_newFormat = false;

    bool Load(QString filename);

//    void CreateFake(QString filename, int w, int h,short val);

    Flat2D();
    ~Flat2D();

    void Release();

    QImage* toImage(AtlasLabels& labels);



    unsigned int width() const;
    unsigned int height() const;
    unsigned int pixel(int i, int j);
};

#endif // FLAT2D_H
