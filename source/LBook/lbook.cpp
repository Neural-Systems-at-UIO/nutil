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

    QVector3D col = Util::vecFromString(readStr(i,j));
    return QColor(col.x(), col.y(), col.z());

}
