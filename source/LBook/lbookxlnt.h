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

    void Set(int i,int j, double val) override;
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
