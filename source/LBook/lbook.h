#ifndef LBOOK_H
#define LBOOK_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QColor>


class LSheet
{
public:
    QString m_name;
    LSheet();
    virtual float readNum(int i, int j) = 0;
    virtual QString readStr(int i, int j) = 0;
    virtual QColor readCol(int i, int j) = 0;
    virtual void Set(int i,int j, float val) = 0;
    virtual void Set(int i,int j, QString val) = 0;

    void writeStr(int i, int j, QString val) {
        Set(i,j,val);
    }
    void writeNum(int i, int j, float val) {
        Set(i,j,val);
    }
    virtual void setName(QString name) {
        m_name = name;
    }


};

class LBook
{
public:
    LBook();

    QVector<LSheet*> m_sheets;

    virtual QStringList sheet_titles() = 0;

    virtual void Load(QString filename) = 0;
    virtual void Save(QString filename) = 0;
    virtual LSheet* CreateSheet(QString sheetName) = 0;
    virtual LSheet* GetSheet(int idx) = 0;

    LSheet* getSheetIndex(int idx);
    void Release();


};


#endif // LBOOK_H
