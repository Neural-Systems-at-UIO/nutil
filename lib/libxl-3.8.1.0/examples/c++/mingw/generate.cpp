#include <iostream>
#include <conio.h>
#include "libxl.h"

using namespace libxl;

int main() 
{	
    Book* book = xlCreateBook();
    if(book)
    {
        Sheet* sheet = book->addSheet("Sheet1");
        if(sheet)
        {
            sheet->writeStr(2, 1, "Hello, World !");
            sheet->writeNum(3, 1, 1000);

            Format* dateFormat = book->addFormat();
            dateFormat->setNumFormat(NUMFORMAT_DATE);
            sheet->writeNum(4, 1, book->datePack(2008, 4, 29), dateFormat);

            sheet->setCol(1, 1, 12);
        }

        if(book->save("example.xls")) std::cout << "\nFile example.xls has been created." << std::endl;
        book->release();		
    } 

    std::cout << "\nPress any key to exit...";
    _getch();
	
    return 0;
}
