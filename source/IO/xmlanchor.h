#ifndef XMLANCHOR_H
#define XMLANCHOR_H

#include <QXmlSimpleReader>
#include <QVector3D>
#include <QXmlAttributes>
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

class XMLAnchor
{
public:
    XMLAnchor();
    QVector<XMLData> m_data;

    XMLData findData(QString filename);

    void Load(QString file);
};

#endif // XMLANCHOR_H
