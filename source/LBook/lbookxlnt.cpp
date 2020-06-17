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

QSharedPointer<LSheet> LBookXlnt::CreateSheet(QString sheetName)
{
    QString org = sheetName;
    for (QSharedPointer<LSheet> s : m_sheets)
        if (s->m_name == sheetName) {
            LMessage::lMessage.Error("Two excel sheets are identical, ignoring creating last sheet: '" + sheetName + "'");
            return nullptr;
        }
//    m_book.create_sheet();
//    QSharedPointer<LSheet> l = new LSheetXlnt(m_book.copy_sheet(m_book.sheet_by_index(0)));
    QSharedPointer<LSheet> l = QSharedPointer<LSheetXlnt>(new LSheetXlnt(this));
    xlnt::worksheet* sheet =  qSharedPointerDynamicCast<LSheetXlnt>(l)->m_sheet;

    sheet->rows().clear_cells();
        // Create sheet CRASHES
//    QSharedPointer<LSheet> l = new LSheetXlnt(m_book.create_sheet());
    if (sheetName.count()>22) sheetName = sheetName.left(24);
   // qDebug() << sheetName;
    for (QSharedPointer<LSheet> s : m_sheets)
        if (s->m_name == sheetName) {
            sheetName = QString::number(m_book.sheet_count()+1) + sheetName;
            LMessage::lMessage.Message("Two excel sheets are identical, ignoring '"+org+"' and creating based on count: "+sheetName);
            break;
        }

    l->setName(sheetName);

    m_sheets.append(l);
    return l;
}

QSharedPointer<LSheet> LBookXlnt::GetSheet(int idx)
{
    QSharedPointer<LSheet> l = getSheetIndex(idx);
    if (l!=nullptr)
        return l;

    l = QSharedPointer<LSheetXlnt>(new LSheetXlnt(m_book.sheet_by_index(idx)));
    m_sheets.append(l);
    return l;
}

QSharedPointer<LSheet> LBookXlnt::GetSheet(QString name)
{
    if (!m_book.contains(name.toStdString()))
        return nullptr;
    QSharedPointer<LSheetXlnt> lx = QSharedPointer<LSheetXlnt>(new LSheetXlnt(m_book.sheet_by_title(name.toStdString())));
    m_sheets.append(lx);
    return lx;
}

QStringList LBookXlnt::sheet_titles()
{
    QStringList l;
    for (std::string s: m_book.sheet_titles())
        l << QString::fromStdString(s);
    l.removeAll("Nutil_info");
    return l;
}

void LBookXlnt::RemoveSheet(int index)
{
//    m_book.remove_sheet()
    m_book.remove_sheet(m_book.sheet_by_id(index));
}



LSheetXlnt::LSheetXlnt(xlnt::worksheet sheet)
{
    m_sheet = new xlnt::worksheet();
    *m_sheet = sheet;
}

double LSheetXlnt::readNum(int i, int j)
{
//    qDebug() << m_sheet->cell(Util::c2x(i,j));
    if (m_sheet->cell(Util::c2x(i,j)).data_type() != xlnt::cell::type::number) {
        //qDebug() << "ERROR: Cell " << i << ", " << j << "does not contain number";
        return 0;
    }
    return m_sheet->cell(Util::c2x(i,j)).value<double>();
}

long LSheetXlnt::readLong(int i, int j)
{
//    qDebug() << m_sheet->cell(Util::c2x(i,j));
    if (m_sheet->cell(Util::c2x(i,j)).data_type() != xlnt::cell::type::number) {
        //qDebug() << "ERROR: Cell " << i << ", " << j << "does not contain number";
        return 0;
    }
    return m_sheet->cell(Util::c2x(i,j)).value<int>();
}

QString LSheetXlnt::readStr(int i, int j)
{
    return QString::fromStdString(m_sheet->cell(Util::c2x(i,j)).value<string>());
}


void LSheetXlnt::Set(int i, int j, double val, int dec)
{
    if (val!=val)
        val=0;
    m_sheet->cell(Util::c2x(i,j)).value(val);
}

void LSheetXlnt::Set(int i, int j, int val)
{
    if (val!=val)
        val=0;
    m_sheet->cell(Util::c2x(i,j)).value(val);

}

void LSheetXlnt::Set(int i, int j, long val)
{
    if (val!=val)
        val=0;
    m_sheet->cell(Util::c2x(i,j)).value((double)val);

}

void LSheetXlnt::Set(int i, int j, QString val)
{
    m_sheet->cell(Util::c2x(i,j)).value(val.toStdString());
}
