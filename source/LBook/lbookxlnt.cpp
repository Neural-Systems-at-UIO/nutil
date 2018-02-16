#include "source/LBook/lbookxlnt.h"
#include <QLockFile>
#include "source/util/lmessage.h"

void LBookXlnt::Load(QString filename)
{
    m_book.load(filename.toStdString());
}

void LBookXlnt::Save(QString filename)
{
   // QFileInfo()
    if (!QFile(filename).open(QIODevice::WriteOnly)) {
        LMessage::lMessage.Error("Report files are open in Excel! Please close all files before proceeding.");
        return;
    }

    if (QFile::exists(filename))
        QFile::remove(filename);

    m_book.save(filename.toStdString());
}

LSheet* LBookXlnt::CreateSheet(QString sheetName)
{
    LSheet* l = new LSheetXlnt(m_book.create_sheet());
    l->setName(sheetName);

    m_sheets.append(l);
    return l;
}

LSheet* LBookXlnt::GetSheet(int idx)
{
    LSheet* l = getSheetIndex(idx);
    if (l!=nullptr)
        return l;

    l = new LSheetXlnt(m_book.sheet_by_index(idx));
    m_sheets.append(l);
    return l;
}

QStringList LBookXlnt::sheet_titles()
{
    QStringList l;
    for (std::string s: m_book.sheet_titles())
        l << QString::fromStdString(s);
    return l;
}



LSheetXlnt::LSheetXlnt(xlnt::worksheet sheet)
{
    m_sheet = new xlnt::worksheet();
    *m_sheet = sheet;
}

float LSheetXlnt::readNum(int i, int j)
{
//    qDebug() << m_sheet->cell(Util::c2x(i,j));
    if (m_sheet->cell(Util::c2x(i,j)).data_type() != xlnt::cell::type::number) {
        //qDebug() << "ERROR: Cell " << i << ", " << j << "does not contain number";
        return 0;
    }
    return m_sheet->cell(Util::c2x(i,j)).value<float>();
}

QString LSheetXlnt::readStr(int i, int j)
{
    return QString::fromStdString(m_sheet->cell(Util::c2x(i,j)).value<string>());
}

QColor LSheetXlnt::readCol(int i, int j)
{
    QString val = QString::fromStdString(m_sheet->cell(Util::c2x(i,j)).value<string>());
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

void LSheetXlnt::Set(int i, int j, float val)
{
    m_sheet->cell(Util::c2x(i,j)).value(val);
}

void LSheetXlnt::Set(int i, int j, QString val)
{
    m_sheet->cell(Util::c2x(i,j)).value(val.toStdString());
}
