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
#ifndef ATLASLABEL_H
#define ATLASLABEL_H

#include <QString>
#include <QVector3D>
#include <QStringList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "source/util/lmessage.h"
#include <QDebug>


class AtlasLabel
{
public:
    AtlasLabel();

    QString name;
    long index;
    QVector3D color;
    QVector3D extra;
    QVector3D extra2;
    bool toggle = false;
    double maxval = 0;
    int count = 0;

    QMap<int, double> sliceArea;
    QMap<int, double> sliceAreaScaled;


    double area = 0.0;
    double areaScaled = 0.0;
    double areaSum = 0.0;


    AtlasLabel (QStringList& s)
    {
        index = s[0].toLong();
        color.setX(s[1].toFloat());
        color.setY(s[2].toFloat());
        color.setZ(s[3].toFloat());


        extra.setX(s[4].toFloat());
        extra.setY(s[5].toFloat());
        extra.setZ(s[6].toFloat());
        name = "";
        for (int i=7;i<s.count();i++)
            name = name + s[i] + " ";

        name = name.replace("\"","");
        name = name.trimmed();
        toggle = true;
        area = 0.0;
        areaScaled = 0.0;
        areaSum = 0.0;
    }
};


class AtlasLabels {
private:
    QMap<long, AtlasLabel*> indexedID;

public:
    //QMap<QVector3D, AtlasLabel*> indexedColor;
    QVector<AtlasLabel*> atlases;

    AtlasLabels() {

    }

    AtlasLabel* get(long index, bool newFormat);

    AtlasLabels(QString filename) {
        Load(filename);
    }
    void Load(QString filename);
    void LoadFake();
    void BuildDictionary();
    QVector<AtlasLabel*> getFromColor(QVector3D col);

    void Clear();

    ~AtlasLabels() {
        Clear();
    }

};

#endif // ATLASLABEL_H
