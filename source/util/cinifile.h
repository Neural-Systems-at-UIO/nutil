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
//#include "cutil.h"
#include <string>
#include <vector>
#include <iostream>
#include <QString>
#include <QDebug>


#ifndef CINIFILE_H
#define CINIFILE_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QVector3D>
#include <QColor>

class CItem {
public:
    QString name, strval;
    QStringList lst;
    double dval;
    QVector3D vec;
};

class CIniFile  {
public:
    QString filename;

    QVector<CItem> items;

    CIniFile() {}

    void Save() {
        Save(filename);
    }

    bool contains(QString name) {
        for (int i=0;i<items.size();i++)
            if (items[i].name==name.toLower().trimmed())
                return true;

       return false;

    }

    QString getString(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed())
                return items[i].strval;
        }
        return "";
    }


    QVector3D getVec(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed())
                return items[i].vec;
        }
        return QVector3D(0,0,0);
    }
    QColor getColor(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                QColor c;
                c.setRed(items[i].vec.x());
                c.setGreen(items[i].vec.y());
                c.setBlue(items[i].vec.z());
                return c;
            }
        }
        return QColor(0,0,0);
    }

    QStringList nullList;
    QStringList& getStringList(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed())
                return items[i].lst;
        }
        return nullList;
    }

    void setString(QString name, QString val) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                items[i].strval = val;
                return;
            }

        }
        CItem i;
        i.name = name;
        i.strval  = val;
        items.append(i);

    }

    void setFloat(QString name, float val) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                items[i].dval = val;
                items[i].strval = "";
                return;
            }

        }
        CItem i;
        i.name = name;
        i.dval  = val;
        i.strval = "";
        items.append(i);

    }


    void setVec(QString name, QVector3D val) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                items[i].vec = val;
                return;
            }

        }
        CItem i;
        i.name = name;
        i.vec  = val;
        items.append(i);

    }

    void addStringList(QString name, QString val, bool isUnique) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                if (isUnique)
                    AddUniqueString(&items[i], val);
                else
                    items[i].lst<<val;
                return;
            }

        }
        CItem i;
        i.name = name;
//        if (isUnique)
  //          AddUniqueString(&items[i], val);

        i.lst<<val;
        items.append(i);

    }

    void setStringList(QString name, QStringList val) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                items[i].lst = val;
                return;
            }

        }
        CItem i;
        i.name = name;
//        if (isUnique)
  //          AddUniqueString(&items[i], val);

        i.lst = val;
        items.append(i);

    }



    void removeFromList(QString name, QString val) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                items[i].lst.removeAll(val);
                return;
            }

        }

    }

    void AddUniqueString(CItem* it,QString str) {
        it->lst.removeAll(str);
        it->lst.insert(0, str);
    }

    bool getBool(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed()) {
                if (items[i].strval=="true")
                    return true;
                return false;
            }
        }
        qDebug() << "CIniFile: Could not find parameter " + name;
    }

    int getInt(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed())
                return (int)items[i].dval;
        }
        qDebug() << "CIniFile: Could not find parameter " + name;
    }

    double getdouble(QString name) {
        for (int i=0;i<items.size();i++) {
            if (items[i].name==name.toLower().trimmed())
                return items[i].dval;
        }
        qDebug() << "CIniFile: Could not find parameter " + name;
    }

/*    bool find(QString key, QString value) {
        QQString actualValue = QQString::fromStdQString(getQString(key.toLower().toStdQString()));
        return value.toLower().compare(actualValue) == 0;
    }
    bool find(QString key, int value) {
        return getint(key.toStdQString()) == value;
    }
    bool find(QString key, bool value) {
        return getbool(key.toStdQString()) == value;
    }*/





void Load(QString fname) {

    filename = fname;
    if (!QFile::exists(fname)) {
        qDebug() << "Could not find file " << fname;
        return;
    }
//    qDebug() << fname << "exists";

    QFile file(fname);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream f(&file);

    while(!f.atEnd()) {

        QString line = f.readLine();



        QStringList tok = line.split("=");
        if (tok.size()==2) {
            CItem it;
            it.dval = -1;
            it.name = tok[0].toLower().trimmed();
            it.strval = tok[1].trimmed();
            bool ok;
            it.dval  = tok[1].toFloat(&ok);
            if (ok) {
                it.strval="";
            }
            else it.dval = 0;

            if (tok[1].split(":").count()==3) {
                QStringList v = tok[1].split(":");
                it.vec.setX( v[0].toFloat());
                it.vec.setY( v[1].toFloat());
                it.vec.setZ( v[2].toFloat());
            }


            if (tok[1].split(",").count()!=1) {
                it.strval = "";
                it.dval = -1;
                it.lst = tok[1].split(",");
                it.lst.removeFirst();
                for (QString& s : it.lst) {
                    s = s.trimmed();
                 //   qDebug() << s;
                }
            }
            items.push_back(it);
        }
    }
    file.close();
}

void Save(QString fname)
{
    if (QFile::exists(fname)) {
        QFile::remove(fname);
    }

    QFile file(fname);
    file.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream f(&file);
    for (CItem i: items) {
//          qDebug() << i.name << " " << QString::number(i.dval) << ", " << i.strval << "\n";
        f << i.name << " = ";
        if (i.strval!="")
           f << i.strval << "\n";
        else
          if (i.lst.count()!=0) {
              f<<",";
              for (int j=0;j<i.lst.count();j++) {
                  f<<i.lst[j];
                 // qDebug() << " << " << i.lst[j];
                  if (j!=i.lst.count()-1)
                      f<<", ";
              }
            f<<"\n";
          }
          else
              if (i.vec.length()!=0) {
                  f<<QString::number(i.vec.x()) << ":";
                  f<<QString::number(i.vec.y()) << ":";
                  f<<QString::number(i.vec.z()) << "\n";
              }

              else {
            f << QString::number(i.dval) << "\n";
          //  qDebug() << QString::number(i.dval) << "\n";
              }

    }
    file.close();

}

};
#endif // CINIFILE_H
