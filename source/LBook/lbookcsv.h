#ifndef LBOOKCSV_H
#define LBOOKCSV_H


#include "lbook.h"

#include <QMap>

class LBookCSV  : public LBook
{
public:
    LBookCSV() {}

//    xlnt::workbook m_book;


    void Load(QString filename) override;
    void Save(QString filename) override;
    LSheet* CreateSheet(QString sheetName) override;
    LSheet* GetSheet(int idx) override;
    LSheet* GetSheet(QString name) override;
    QStringList sheet_titles() override;



};

class LSheetCSV : public LSheet
{
public:

  //  xlnt::worksheet* m_sheet;
    QMap<int, QMap<int, QString>> m_csv;
    QString m_name;
//    LSheetXlnt(xlnt::worksheet sheet);
    LSheetCSV() {}
    double readNum(int i, int j) override;
    long readLong(int i, int j) override;
    QString readStr(int i, int j) override;
    QColor readCol(int i, int j) override;

    void Set(int i,int j, float val) override;
    void Set(int i,int j, QString val) override;

    void setName(QString name) override {
        LSheet::setName(name);
        m_name = name;
    }


};
#endif // LBOOKCSV_H
