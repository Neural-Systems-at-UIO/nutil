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

    QVector<LSheetCSV*> m_sheets;
    QStringList m_titles;
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

    QVector<QString> m_data;
    int m_width = 24;
    int m_height = 0;

    QString& get(int i, int j);
    void set(int i, int j, QString val);
    QString none="";

    void Save(QString basename);
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
