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
#ifndef NLIMAGETIFF_H
#define NLIMAGETIFF_H

#include <QImage>
//#include <QRGB>
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
        if (!QFile::exists(filename)) {
            qDebug() << "NLIQImage::Load : Could not find file: " << filename;
            return false;
        }
        m_image = QImage();
        m_image.load(filename);
        if (m_image.format()!=QImage::Format_RGB32) {
            //qDebug() << "Converting";
            m_image = m_image.convertToFormat(QImage::Format_RGB32);
  //          m_image = img;
        }

//        qDebug() << "SIZE " << m_image.width();

        return true;

    }

    void FractalAnalyze();
    QPointF BoxCount(int boxSize, QColor searchColor);

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
