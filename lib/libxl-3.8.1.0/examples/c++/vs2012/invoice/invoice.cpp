#include <iostream>
#include <windows.h>
#include "libxl.h"

using namespace libxl;

int main()
{
    Book* book = xlCreateXMLBook();
    if(book) 
    {   
        Font* boldFont = book->addFont();
        boldFont->setBold();

        Font* titleFont = book->addFont();
        titleFont->setName(L"Arial Black");
        titleFont->setSize(16);

        Format* titleFormat = book->addFormat();
        titleFormat->setFont(titleFont);

        Format* headerFormat = book->addFormat();
        headerFormat->setAlignH(ALIGNH_CENTER);
        headerFormat->setBorder(BORDERSTYLE_THIN);
        headerFormat->setFont(boldFont);        
        headerFormat->setFillPattern(FILLPATTERN_SOLID);
        headerFormat->setPatternForegroundColor(COLOR_TAN);

        Format* descriptionFormat = book->addFormat();
        descriptionFormat->setBorderLeft(BORDERSTYLE_THIN);

        Format* amountFormat = book->addFormat();
        amountFormat->setNumFormat(NUMFORMAT_CURRENCY_NEGBRA);
        amountFormat->setBorderLeft(BORDERSTYLE_THIN);
        amountFormat->setBorderRight(BORDERSTYLE_THIN);
                
        Format* totalLabelFormat = book->addFormat();
        totalLabelFormat->setBorderTop(BORDERSTYLE_THIN);
        totalLabelFormat->setAlignH(ALIGNH_RIGHT);
        totalLabelFormat->setFont(boldFont);

        Format* totalFormat = book->addFormat();
        totalFormat->setNumFormat(NUMFORMAT_CURRENCY_NEGBRA);
        totalFormat->setBorder(BORDERSTYLE_THIN);
        totalFormat->setFont(boldFont);
        totalFormat->setFillPattern(FILLPATTERN_SOLID);
        totalFormat->setPatternForegroundColor(COLOR_YELLOW);

        Format* signatureFormat = book->addFormat();
        signatureFormat->setAlignH(ALIGNH_CENTER);
        signatureFormat->setBorderTop(BORDERSTYLE_THIN);
             
        Sheet* sheet = book->addSheet(L"Invoice");
        if(sheet)
        {
            sheet->writeStr(2, 1, L"Invoice No. 3568", titleFormat);

            sheet->writeStr(4, 1, L"Name: John Smith");
            sheet->writeStr(5, 1, L"Address: San Ramon, CA 94583 USA");

            sheet->writeStr(7, 1, L"Description", headerFormat);
            sheet->writeStr(7, 2, L"Amount", headerFormat);

            sheet->writeStr(8, 1, L"Ball-Point Pens", descriptionFormat);
            sheet->writeNum(8, 2, 85, amountFormat);
            sheet->writeStr(9, 1, L"T-Shirts", descriptionFormat);
            sheet->writeNum(9, 2, 150, amountFormat);
            sheet->writeStr(10, 1, L"Tea cups", descriptionFormat);
            sheet->writeNum(10, 2, 45, amountFormat);

            sheet->writeStr(11, 1, L"Total:", totalLabelFormat);
            sheet->writeFormula(11, 2, L"=SUM(C9:C11)", totalFormat);

            sheet->writeStr(14, 2, L"Signature", signatureFormat);

            sheet->setCol(1, 1, 40);
            sheet->setCol(2, 2, 15);
          }

          if(book->save(L"invoice.xlsx")) 
          {
            ::ShellExecute(NULL, L"open", L"invoice.xlsx", NULL, NULL, SW_SHOW);
          }

          book->release();   
    }

    return 0;
}
