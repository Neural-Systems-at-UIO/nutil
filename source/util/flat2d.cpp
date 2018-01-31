#include "flat2d.h"
#include "source/util/lmessage.h"
#include <QFile>
#include <QDebug>
#include <QColor>
#include <QRgb>

unsigned int Flat2D::width() const
{
    return m_width;
}

unsigned int Flat2D::height() const
{
    return m_height;
}

unsigned int Flat2D::pixel(int i, int j)
{
    if (i<0 || i>=m_width)
        return 0;
    if (j<0 || j>=m_height)
        return 0;
    return m_data[i+ j*m_width];
}

bool Flat2D::Load(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        LMessage::lMessage.Error("Could not open flat file: "  + filename);
        return false;
    }
    file.read((char*)&m_width,4);
    file.read((char*)&m_height,4);
    m_data = new unsigned int[m_width*m_height];
    file.read((char*)m_data, m_width*m_height*4);
    file.close();
    return true;
}

Flat2D::Flat2D()
{

}

Flat2D::~Flat2D()
{
    Release();
}

void Flat2D::Release()
{
    if (m_data!=nullptr)
        delete[] m_data;

    m_data = nullptr;
}

QImage *Flat2D::toImage(AtlasLabels &labels)
{
    QImage* img = new QImage(m_width, m_height, QImage::Format_ARGB32);

    for (unsigned int i=0;i<m_width;i++)
        for (unsigned int j=0;j<m_height;j++) {
            long idx = pixel(i,j);
            AtlasLabel* al = labels.get(idx);
            if (al!=nullptr)
                img->setPixel(i,j, QColor(al->color.x(), al->color.y(),al->color.z()).rgba());
        }

    return img;
}
