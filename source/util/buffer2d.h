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
#pragma once

#include <QVector>
#include <QVector3D>
#include <QImage>
#include <QRgb>



#ifdef USE_HEALPIX
#include <healpix_map.h>
#endif


class Buffer2DShort {


    void Load(QString fname) {
/*    QFile file(fname);
      if (!file.open(QIODevice::ReadOnly))
          return;

      QByteArray compressed = file.readAll();
      qDebug() << "Compresed=" << compressed.size();

      QByteArray uncompressed = qUncompress(compressed); // HERE I GET: qUncompress: Input data is corrupted
      qDebug() << "UnCompresed=" << uncompressed.size();

*/
    }

};

class Buffer2D
{
    QVector<QVector3D> m_buffer;
    int m_size;

    QColor PostProcess(const QVector3D& v, float exposure, float gamma, float saturation);

public:
    ~Buffer2D();
    Buffer2D();
    Buffer2D(int size);
    void Initialize(int size);

    void Set(const int i, const int j, const QVector3D& v);
    void Set(const int i, const QVector3D& v);
    QVector3D Get(const int i, const int j);
    QVector3D Get(const int i);

    void DrawBox(Buffer2D* backImage, const int i, const int j, const int size, QVector3D val);
    void ToColorBuffer(QImage* image, QImage* shadowImage, float exposure, float gamma, float saturation);
    void ToColorBuffer(QImage* image, float exposure, float gamma, float saturation);
    void fill(const QVector3D v);
    void SaveFits(QString filename);
    void RenderStars(int noStars, int baseSize, int sizeSpread, float strength);
    QByteArray* toQByteArray(int no);

#ifdef USE_HEALPIX
    void MollweideProjection(Healpix_Map<float>& map);
#endif

    void Add(Buffer2D* other);
    void CopyTo(Buffer2D* to);

    void RenderGaussian(int i, int j, int w, QVector3D cs);


    int size() const;
};

