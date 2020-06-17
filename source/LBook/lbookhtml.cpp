#include "lbookhtml.h"

LBookHTML::LBookHTML()
{

}


void LBookHTML::Save(QString filename)
{
    filename = QDir::fromNativeSeparators(filename);

    QString dir = Util::RemoveFinalFiletype(filename);

    QString base = dir.split("/").last();
    if (!QDir().exists(dir))
        QDir().mkdir(dir);

    filename = dir + "/" + base + ".xslx";



    for (auto l: m_sheets)
        qSharedPointerDynamicCast<LSheetCSV>(l)->SaveAsHTML(filename);

}

