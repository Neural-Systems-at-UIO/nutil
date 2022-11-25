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
    QString m_atlas; // Present in .seg only

    unsigned int m_width, m_height;
    unsigned char m_bpp;

    bool m_newFormat = false;

    bool Load(QString filename);
    bool LoadFromSeg(QFile& file);

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
