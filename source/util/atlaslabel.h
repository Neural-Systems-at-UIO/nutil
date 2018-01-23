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
    int index;
    QVector3D color;
    QVector3D extra;
    bool toggle;
    float maxval;

    AtlasLabel (QStringList& s)
    {
        index = s[0].toInt();
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

    }
};


class AtlasLabels {
public:
    QMap<int, AtlasLabel*> indexedID;
    //QMap<QVector3D, AtlasLabel*> indexedColor;
    QVector<AtlasLabel*> atlases;

    AtlasLabels() {

    }

    AtlasLabels(QString filename) {
        Load(filename);
    }
    void Load(QString filename);
    void BuildDictionary();
    AtlasLabel* getFromColor(QVector3D col);

    void Clear();

    ~AtlasLabels() {
        Clear();
    }

};

#endif // ATLASLABEL_H
