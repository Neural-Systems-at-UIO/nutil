#include <iostream>
#include <windows.h>
#include "libxl.h"

using namespace libxl;

int main() 
{	
    Book* book = xlCreateBook();
    if(book)
    {
        Sheet* sheet = book->addSheet(L"Sheet1");
        if(sheet)
        {
            sheet->writeStr(2, 1, L"Hello, World !");
            sheet->writeNum(4, 1, 1000);
            sheet->writeNum(5, 1, 2000);
            
            Font* font = book->addFont();            
            font->setColor(COLOR_RED);
            font->setBold(true);
            Format* boldFormat = book->addFormat();
            boldFormat->setFont(font);
            sheet->writeFormula(6, 1, L"SUM(B5:B6)", boldFormat);

            Format* dateFormat = book->addFormat();
            dateFormat->setNumFormat(NUMFORMAT_DATE);
            sheet->writeNum(8, 1, book->datePack(2008, 4, 29), dateFormat);

            sheet->setCol(1, 1, 12);
        }

        if(book->save(L"example.xls")) 
        {
            ::ShellExecute(NULL, L"open", L"example.xls", NULL, NULL, SW_SHOW);        
        }
        else
        {
            std::cout << book->errorMessage() << std::endl;
        }

        book->release();		
    } 
   
    return 0;
}
