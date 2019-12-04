#include "lbookhtml.h"

LBookHTML::LBookHTML()
{

}


void LBookHTML::Save(QString filename)
{
    for (auto l: m_sheets)
        dynamic_cast<LSheetCSV*>(l)->SaveAsHTML(filename);

}

