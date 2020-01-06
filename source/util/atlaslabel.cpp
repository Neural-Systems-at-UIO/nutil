#include "atlaslabel.h"
#include <QDebug>

AtlasLabel::AtlasLabel()
{

}

AtlasLabel *AtlasLabels::get(long index, bool format)
{
    //if (index==182305705)
    //    qDebug()<< "CONTAINS: " <<indexedID.contains(index);
    if (format==true) {
        if (index<atlases.count())
            return atlases[index];
        else {
//            qDebug() << "Trying to access atlas index : "<< index << " which is above " <<atlases.count();
            LMessage::lMessage.Error("Trying to access atlas index : "+ QString::number(index) +
                                     " which is above " +QString::number(atlases.count()) +
                                     ".<br>Please make sure that you are using the correct atlas label file (i.e. the same version as was used with QuickNII).");
        }
    }

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

        if (!line.startsWith("#")) {
            QStringList fields = line.simplified().split(' ');
            AtlasLabel* al = new AtlasLabel(fields);
            atlases.append(al);
        }

    }
    file.close();
    BuildDictionary();
}

void AtlasLabels::LoadFake()
{
    QString data =  "1   255   255   255        1  1  0    \"All\"";
    QStringList fields = data.simplified().split(' ');
    AtlasLabel* al = new AtlasLabel(fields);
    atlases.append(al);
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
