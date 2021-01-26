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
#ifndef XMLANCHOR_H
#define XMLANCHOR_H

//#include <QXmlSimpleReader>
#include <QVector3D>
//#include <QXmlAttributes>
#include <QVector>
#include <QDebug>

class XMLData {
public:
    QString m_filename;
    int m_nr;
    int m_width;
    int m_height;
    QVector3D m_o;
    QVector3D m_u;
    QVector3D m_v;

    XMLData() {}

    float* toMatrix() {
        return new float[16] {
                m_u.x(),m_u.y(),m_u.z(),0,
                m_v.x(),m_v.y(),m_v.z(),0,
                m_o.x(),m_o.y(),m_o.z(),0,
                0,0,0,1
    };
    }

    XMLData(QString filename, int nr, int width, int height, float ox, float oy, float oz, float ux, float uy, float uz, float vx, float vy, float vz) {
        m_filename = filename;
        m_nr = nr;
        m_width = width;
        m_height=height;
        m_o=QVector3D(ox,oy,oz);
        m_u=QVector3D(ux,uy,uz);
        m_v=QVector3D(vx,vy,vz);
    }
};


class AbstractAnchor {
public:
    //AbstractAnchor()  {}

    //  XMLAnchor();
    QVector<XMLData> m_data;

    XMLData findData(QString filename);

    virtual void Load(QString file) = 0;

};


class XMLAnchor : public AbstractAnchor
{
public:

    void Load(QString file);
};


class JSONAnchor : public AbstractAnchor
{
public:

    void Load(QString file);
};

class AnchorFactory {
public:
    static AbstractAnchor* Load(QString file) {

        AbstractAnchor* anchor = nullptr;
        if (file.toLower().endsWith(".xml"))
            anchor = new XMLAnchor();
        if (file.toLower().endsWith(".json"))
            anchor = new JSONAnchor();
        if (anchor==nullptr) {
            qDebug() << "ERROR: Unknown file type when loading anchor (not xml/json).";
            return nullptr;
        }
        anchor->Load(file);
        return anchor;
    }
};

#endif // XMLANCHOR_H
