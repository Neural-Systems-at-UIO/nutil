#include "flat2d.h"
#include "source/util/lmessage.h"
#include <QFile>
#include <QDebug>
#include <QColor>
#include <QRgb>
#include <QtEndian>

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

    if (m_bpp==4)
        return m_data_i[i+ j*m_width];
    if (m_bpp==2)
        return m_data_s[i+ j*m_width];

    if (m_bpp==1) {
        return m_data_b[i+j*m_width];
    }
    return 0;
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
    m_bpp = 4;
    if (file.size()!=(m_width*m_height*4 + 8)) {
//        exit(1);
        file.close();
        //file = QFile(filename);
        file.open(QIODevice::ReadOnly);
        file.read((char*)&m_bpp,1);
        file.read((char*)&m_width,4);
        file.read((char*)&m_height,4);
        m_width = qFromBigEndian<int>((char*)&m_width);
        m_height = qFromBigEndian<int>((char*)&m_height);
//        qDebug() << "BPP IS : "<< m_bpp << QString::number(m_width) << QString::number(m_height);
//        qDebug() << "Width height: " << m_width << m_height << m_bpp;
  //      exit(1);
        m_newFormat = true;
    }


    if (m_bpp==4) {
        m_data_i = new unsigned int[m_width*m_height];
        file.read((char*)m_data_i, m_width*m_height*4);
        if (m_newFormat)
            for (int i=0;i<m_width*m_height;i++) m_data_i[i] = qFromBigEndian<int>((char*)&m_data_i[i]);

    }
    if (m_bpp==2) {
        m_data_s = new unsigned short[m_width*m_height];
        file.read((char*)m_data_s, m_width*m_height*2);
        for (int i=0;i<m_width*m_height;i++) m_data_s[i] = qFromBigEndian<unsigned short>((char*)&m_data_s[i]);
    }
    if (m_bpp==1) {
        m_data_b = file.read(m_width*m_height);
    }
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
    if (m_data_s!=nullptr)
        delete[] m_data_s;

//    if (m_data_b!=nullptr)
  //      delete[] m_data_b;

    if (m_data_i!=nullptr)
        delete[] m_data_i;

    m_data_s = nullptr;
    m_data_i = nullptr;
    m_data_b = nullptr;
}

QImage *Flat2D::toImage(AtlasLabels &labels)
{
    QImage* img = new QImage(m_width, m_height, QImage::Format_ARGB32);
    for (unsigned int i=0;i<m_width;i++)
        for (unsigned int j=0;j<m_height;j++) {
           unsigned int idx = pixel(i,j);
           AtlasLabel* al = labels.get(idx, m_newFormat);//
           if (al!=nullptr)
                img->setPixel(i,j, QColor(al->color.x(), al->color.y(),al->color.z()).rgba());

        }
    return img;
}
