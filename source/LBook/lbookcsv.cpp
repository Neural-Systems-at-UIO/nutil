#include "lbookcsv.h"
#include <QTextStream>

QString &LSheetCSV::get(int j, int i) {
//    qDebug() << "LBookCSV::get";
    int idx = i+j*m_width;
    if (idx<m_data.count())
        return m_data[idx];
    return none;

}

void LSheetCSV::set(int j, int i, QString val) {
  //  qDebug() << "LSheetCSV " << m_name<<QString::number(i)<<QString::number(j);
    if (j>=m_height) {
        m_height = j+1;
        m_data.resize(m_height*m_width);
//        qDebug() << "Resizing to height " << QString::number(m_height);

    }
    m_data[i+j*m_width] = val;
 //   qDebug() << "Done!";
}

void LSheetCSV::Save(QString basename)
{
//    qDebug() << "LBookCSV::save";
    QString separator="_";
    if (m_name=="") separator="";
    QString fn = basename.split(".").first() + separator + m_name + ".csv";
    QFile file(fn);
    if (QFile::exists(fn))
        QFile::remove(fn);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    for (int j=0;j<m_height;j++) {
        QString s;
        for (int i=0;i<m_width;i++) {
            s=s+get(j,i)+";";
        }
        s = s.remove(s.length()-1,1);
        stream<< s << "\n";
    }


    file.close();
}

double LSheetCSV::readNum(int i, int j)
{
    return get(i,j).toFloat();
}

long LSheetCSV::readLong(int i, int j)
{
    return get(i,j).toLong();
}

QString LSheetCSV::readStr(int i, int j)
{
    return get(i,j);
}

QColor LSheetCSV::readCol(int i, int j)
{
    QString val = get(i,j);
    QStringList valSplit = val.split(':');
    QString ij = QString::number(i) + ", " + QString::number(j);
    if (valSplit[0].toLower()!="col" || valSplit.count()!=2) {
        LMessage::lMessage.Error("Value at " +ij+ " not a color" );
        return QColor(0,0,0);
    }
    QStringList colList = valSplit[1].split(',');

    if (colList.length()!=3) {
        LMessage::lMessage.Error("Value at " +ij + " has incorrect color format 'col:r,g,b'");
        return QColor(0,0,0);
    }
    return QColor(colList[0].toInt(),colList[1].toInt(),colList[2].toInt());

}

void LSheetCSV::Set(int i, int j, float val)
{
    set(i,j,QString::number(val));
}

void LSheetCSV::Set(int i, int j, QString val)
{
    set(i,j,val);
}

void LBookCSV::Load(QString filename)
{

}

void LBookCSV::Save(QString filename)
{
    for (auto l: m_sheets)
        dynamic_cast<LSheetCSV*>(l)->Save(filename);

}

LSheet *LBookCSV::CreateSheet(QString sheetName)
{
    LSheetCSV* ls = new LSheetCSV();
    ls->m_name = sheetName;
    m_sheets.append(ls);
    m_titles.append(sheetName);
    return ls;

}

LSheet *LBookCSV::GetSheet(int idx)
{
    if (idx<m_sheets.count())
        return m_sheets[idx];

    return nullptr;
}

LSheet *LBookCSV::GetSheet(QString name)
{
    for (auto l: m_sheets)
        if (l->m_name==name)
            return l;

    return nullptr;
}


QStringList LBookCSV::sheet_titles()
{
    return m_titles;
}
