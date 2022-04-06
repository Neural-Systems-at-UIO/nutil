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
#ifndef LBOOKCSV_H
#define LBOOKCSV_H


#include "lbook.h"
#include "source/util/util.h"
#include "source/util/lmessage.h"
#include <QDebug>

#include <QMap>

class LSheetCSV;


class LBookCSV  : public LBook
{
public:
    LBookCSV() {
        CreateSheet("");
    }

   ~LBookCSV() {
        Release();
    }

    void RemoveSheet(int index) override ;

//    QVector<QSheetLSheetCSV> m_sheets;
    QStringList m_titles;
    void Load(QString filename) override;
    void Save(QString filename) override;
    QSharedPointer<LSheet> CreateSheet(QString sheetName) override;
    QSharedPointer<LSheet> GetSheet(int idx) override;
    QSharedPointer<LSheet> GetSheet(QString name) override;
    QStringList sheet_titles() override;

};

class LSheetCSV : public LSheet
{
public:

  //  xlnt::worksheet* m_sheet;

    QVector<QString> m_data;
    int m_width = 128;
    int m_height = 0;

    QString& get(int i, int j);
    void set(int i, int j, QString val);
    QString none="0";


    void Save(QString basename);
    void SaveAsHTML(QString basename);
    QString m_name;
//    LSheetXlnt(xlnt::worksheet sheet);
    LSheetCSV() {}
    double readNum(int i, int j) override;
    long readLong(int i, int j) override;
    QString readStr(int i, int j) override;

    void Set(int i,int j, double val, int dec=-1) override;
    void Set(int i,int j, long val) override;
    void Set(int i,int j, int val) override;
    void Set(int i,int j, QString val) override;

    void setName(QString name) override {
        LSheet::setName(name);
        m_name = name;
    }


};
#endif // LBOOKCSV_H
