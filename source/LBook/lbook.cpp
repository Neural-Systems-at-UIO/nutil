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
