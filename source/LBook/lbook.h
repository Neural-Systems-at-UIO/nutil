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
#ifndef LBOOK_H
#define LBOOK_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QColor>
#include "source/util/util.h"
#include <QVector3D>
#include "source/util/lmessage.h"

class LSheet
{
public:
    QString m_name;
    LSheet();


    virtual double readNum(int i, int j) = 0;
    virtual long readLong(int i, int j) = 0;
    virtual QString readStr(int i, int j) = 0;
    virtual void Set(int i,int j, double val, int dec=-1) = 0;
        //added support for defining no. of decimal places
    virtual void Set(int i,int j, QString val) = 0;
    virtual void Set(int i,int j, long val) = 0;
    virtual void Set(int i,int j, int val) = 0;

    void writeStr(int i, int j, QString val) {
        Set(i,j,val);
    }
    void writeNum(int i, int j, float val) {
        Set(i,j,val);
    }
    virtual void setName(QString name) {
        m_name = name;
    }

    QColor readCol(int i, int j);


};

class LBook
{
public:
    LBook();

    QVector<QSharedPointer<LSheet>> m_sheets;

    virtual QStringList sheet_titles() = 0;
    bool m_ignoreColors = false;
    QChar m_separator = ';';
    virtual void RemoveSheet(int index) = 0;
    virtual void Load(QString filename) = 0;
    virtual void Save(QString filename) = 0;
    virtual QSharedPointer<LSheet> CreateSheet(QString sheetName) = 0;
    virtual QSharedPointer<LSheet> GetSheet(int idx) = 0;
    virtual QSharedPointer<LSheet> GetSheet(QString sheetName) = 0;

    QSharedPointer<LSheet> getSheetIndex(int idx);
    void Release();


};


#endif // LBOOK_H
