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
    LSheet* CreateSheet(QString sheetName) override;
    LSheet* GetSheet(int idx) override;
    LSheet* GetSheet(QString name) override;
    QStringList sheet_titles() override;

    void RemoveSheet(int index);


};

class LSheetXlnt : public LSheet
{
public:

    xlnt::worksheet* m_sheet;

    LSheetXlnt(xlnt::worksheet sheet);
    LSheetXlnt() {}
    double readNum(int i, int j) override;
    long readLong(int i, int j) override;
    QString readStr(int i, int j) override;
    QColor readCol(int i, int j) override;

    void Set(int i,int j, float val) override;
    void Set(int i,int j, QString val) override;

    void setName(QString name) override {
        LSheet::setName(name);
        if (m_sheet != nullptr) {
            m_sheet->title(name.toStdString());
        }
    }


};



#endif // LBOOKXLNT_H
