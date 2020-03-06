#include "lbookcsv.h"
#include <QTextStream>
#include "source/data.h"

QString &LSheetCSV::get(int j, int i) {
//    qDebug() << "LBookCSV::get";
    int idx = i+j*m_width;


    if (idx<m_data.count()) {
//        return m_data[idx];
        bool isOk = false;
        double someVal = m_data[idx].toFloat(&isOk);
        if (isOk) {
            if ((someVal-floor(someVal)) ==0.0)
                m_data[idx] = QString::number((int)someVal,10);

        }
        return m_data[idx];
    }
    return none;

}

void LSheetCSV::set(int j, int i, QString val) {
    if (j>=m_height) {
        m_height = j+1;
        m_data.resize(m_height*m_width);

    }
    m_data[i+j*m_width] = val;
}

void LSheetCSV::Save(QString basename)
{
//    qDebug() << "LBookCSV::save";
    QString separator="_";
    if (m_name=="") separator="";
    QString fn = Util::RemoveFinalFiletype(basename) + separator + m_name + ".csv";
 //   qDebug() << "Report output filename :" << fn;

    if (QFile::exists(fn))
        QFile::remove(fn);

    QFile file(fn);
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


void LSheetCSV::SaveAsHTML(QString basename)
{
//    qDebug() << "LBookCSV::save";
    QString separator="_";
    if (m_name=="") separator="";
    QString fn = Util::RemoveFinalFiletype(basename) + separator + m_name + ".html";
//    qDebug() << "Report output filename :" << fn;

    if (QFile::exists(fn))
        QFile::remove(fn);

    QFile file(fn);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream << "<html>\n";
    stream << "<table>\n";


    for (int j=0;j<m_height;j++) {
        QString str = "<tr>";
        for (int i=0;i<m_width;i++) {
            str=str+"<td>"+get(j,i) + "</td>";
        }
        str = str + "</tr>";
        stream << str << "\n";

    }

    stream << "</table>\n";
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


void LSheetCSV::Set(int i, int j, float val)
{
    set(i,j,QString::number(val,'f'));
}

void LSheetCSV::Set(int i, int j, QString val)
{
    set(i,j,val);
}

void LBookCSV::RemoveSheet(int index)
{
    m_sheets.remove(index);
}

void LBookCSV::Load(QString filename)
{

}

void LBookCSV::Save(QString filename)
{

    filename = QDir::fromNativeSeparators(filename);

    QString dir = Util::RemoveFinalFiletype(filename);

    QString base = dir.split("/").last();
    if (!QDir().exists(dir))
        QDir().mkdir(dir);

    filename = dir + "/" + base + ".xslx";



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
