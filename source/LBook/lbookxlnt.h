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
#ifndef LBOOKXLNT_H
#define LBOOKXLNT_H

#include <QString>
#include <xlnt/xlnt.hpp>
#include "source/LBook/lbook.h"
#include "source/util/util.h"
#include <QVector>
#include <QDebug>
#include <QStringList>

class LBookXlnt  : public LBook
{
public:
    LBookXlnt() {}

    xlnt::workbook m_book;


    void Load(QString filename) override;
    void Save(QString filename) override;
    QSharedPointer<LSheet> CreateSheet(QString sheetName) override;
    QSharedPointer<LSheet> GetSheet(int idx) override;
    QSharedPointer<LSheet> GetSheet(QString name) override;
    QStringList sheet_titles() override;

    void RemoveSheet(int index);


};

class LSheetXlnt : public LSheet
{
public:

    xlnt::worksheet* m_sheet = nullptr;
    xlnt::worksheet m_sheetO;

    LSheetXlnt(xlnt::worksheet sheet);
    LSheetXlnt(LBookXlnt* book) {
        m_sheetO = book->m_book.create_sheet();
        m_sheet = &m_sheetO;
        m_sheet->title(("t_"+QString::number(rand()%100)).toStdString());
    }
    double readNum(int i, int j) override;
    long readLong(int i, int j) override;
    QString readStr(int i, int j) override;
//    QColor readCol(int i, int j) override;

    void Set(int i,int j, double val,int dec=-1) override;
    void Set(int i,int j, int val) override;
    void Set(int i,int j, long val) override;
    void Set(int i,int j, QString val) override;

    void setName(QString name) override {
        LSheet::setName(name);
        if (m_sheet != nullptr) {
            m_sheet->title(name.toStdString());
        }
    }


};



#endif // LBOOKXLNT_H
