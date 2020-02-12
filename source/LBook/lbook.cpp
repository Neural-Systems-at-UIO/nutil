#include "lbook.h"

LBook::LBook()
{

}


LSheet *LBook::getSheetIndex(int idx)
{
    if (idx>=m_sheets.count())
        return nullptr;

    return m_sheets[idx];

}

void LBook::Release()
{
    for (int i=0;i<m_sheets.count();i++)
        delete m_sheets[i];

    m_sheets.clear();

}

LSheet::LSheet()
{

}

QColor LSheet::readCol(int i, int j)
{
    QString val = readStr(i,j);
    if (val.toLower().startsWith("col")) {
        QStringList valSplit = val.split(':');
        QString ij = QString::number(i) + ", " + QString::number(j);
        if (valSplit[0].toLower()!="col" || valSplit.count()!=2) {
            LMessage::lMessage.Error("Value at " +ij+ " not a color" );
            return QColor(0,0,0);
        }
        QStringList colList = valSplit[1].split(',');

        if (colList.length()!=3) {
            LMessage::lMessage.Error("Value at " +ij + " has incorrect color format 'r;g;b'");
            return QColor(0,0,0);
        }
        return QColor(colList[0].toInt(),colList[1].toInt(),colList[2].toInt());
    }
    QStringList sl = readStr(i,j).split(";");

    QVector3D col = QVector3D(0,0,0);
    if (sl.count()==3)
        col = QVector3D(sl[0].toFloat(), sl[1].toFloat(),sl[2].toFloat());
    else
        LMessage::lMessage.Error("Error when reading colour data in sheet '" + m_name +"' : " + readStr(i,j) + " (" +QString::number(readNum(i,j)) +")" + " is not correct colour format. ");
//    QVector3D col = Util::vecFromString();
    return QColor(col.x(), col.y(), col.z());

}
