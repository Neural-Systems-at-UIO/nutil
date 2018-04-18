#ifndef NLIMAGETIFF_H
#define NLIMAGETIFF_H

#include <QImage>
#include <QRGB>
#include "source/ltiff/ltiff.h"
#include <QFile>

class NLIParent
{
public:

    NLIParent() {}
//    NLIParent(int x, int y);



    virtual bool Load(QString filename) = 0;

    virtual QRgb getPixel(int x, int y) = 0;
    virtual void setPixel(int x, int y, QRgb col) = 0;
    virtual int width() = 0;
    virtual int height() = 0;
    virtual void Release() = 0;
    virtual void fill(QColor col) = 0;
    virtual void Save(QString filename) = 0;
    virtual void NewFrom(NLIParent* p) = 0;
};


class NLIQImage : public NLIParent {
public:
    QImage m_image;
    NLIQImage() {}
    NLIQImage(int x, int y) {
        m_image = QImage(x,y,QImage::Format_RGB32);
    }

    bool Load(QString filename) override {
        if (!QFile::exists(filename))
            return false;
        m_image.load(filename);
        return true;

    }


    void Save(QString filename) override {
        m_image.save(filename);
    }
    void fill(QColor r) {
        m_image.fill(r);
    }

    QRgb getPixel(int x, int y) override {
        return m_image.pixel(x,y);
    }

    void setPixel(int x, int y, QRgb col) override {
        m_image.setPixel(x,y, col);
    }

    void Release() override {
        m_image = QImage();
    }

    int width() {
        return m_image.width();
    }

    int height() {
        return m_image.height();
    }
    void NewFrom(NLIParent* p) override {
        NLIQImage* qi = dynamic_cast<NLIQImage*>(p);
        if (qi!=nullptr) {
            m_image = QImage(qi->width(),qi->height(),QImage::Format_RGB32);

        }

    }


};


/*class NLITiff : public NLIParent {
public:
    LTiff m_image;
    NLITiff() {}
    NLITiff(int x, int y) {
        //m_image = QImage(x,y,QImage::Format_RGB32)
//        m_image.New();
    }


    void NewFrom(NLIParent* p) override {
        NLITiff* qi = dynamic_cast<NLITiff*>(p);
        if (qi!=nullptr) {
            LTiff* t = &qi->m_image;
            m_image.CreateFromMeta(*t,t->  );

        }

    }


    bool Load(QString filename) override {
        if (!QFile::exists(filename))
            return false;
        m_image.load(filename);
        return true;

    }


    void Save(QString filename) override {
        m_image.save(filename);
    }
    void fill(QColor r) {
        m_image.fill(r);
    }

    QRgb getPixel(int x, int y) override {
        return m_image.pixel(x,y);
    }

    void setPixel(int x, int y, QRgb col) override {
        m_image.setPixel(x,y, col);
    }

    void Release() override {
        m_image = QImage();
    }

    int width() {
        return m_image.width();
    }

    int height() {
        return m_image.height();
    }


};
*/

#endif // NLIMAGETIFF_H
