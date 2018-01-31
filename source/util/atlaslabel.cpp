#include "atlaslabel.h"
#include <QDebug>
AtlasLabel::AtlasLabel()
{

}

AtlasLabel *AtlasLabels::get(long index)
{
    if (indexedID.contains(index))
        return indexedID[index];
    return nullptr;
}

void AtlasLabels::Load(QString filename)
{
    Clear();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        LMessage::lMessage.Error("Could not open label file '" + filename + "'");
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();

        if (line[0]!='#') {
            QStringList fields = line.simplified().split(' ');
            AtlasLabel* al = new AtlasLabel(fields);
            atlases.append(al);
        }

    }
    file.close();
    BuildDictionary();
}

void AtlasLabels::BuildDictionary()
{
    indexedID.clear();
    //indexedColor.clear();
    for (AtlasLabel* al : atlases) {
        indexedID.insert(al->index, al);
//        indexedColor.insert(al->color, al);
    }
}

QVector<AtlasLabel*> AtlasLabels::getFromColor(QVector3D col)
{
    QVector<AtlasLabel*> labels;
    for (AtlasLabel* al: atlases)
        if ((al->color-col).length()<0.001)
            labels.append(al);

//            return al;

    return labels;
}

void AtlasLabels::Clear()
{
    for (int i=0;i<atlases.length();i++)
        delete atlases[i];
    atlases.clear();
}
