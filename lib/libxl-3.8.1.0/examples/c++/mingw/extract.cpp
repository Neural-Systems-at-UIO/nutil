#include <iostream>
#include <conio.h>
#include "libxl.h"

using namespace libxl;

int main() 
{
    Book* book = xlCreateBook();
    if(book)
    {
        if(book->load("example.xls"))
        {
            Sheet* sheet = book->getSheet(0);
            if(sheet)
            {
                const char* s = sheet->readStr(2, 1);
                if(s) std::cout << s << std::endl;

                double d = sheet->readNum(3, 1);
                std::cout << d << std::endl;
            }
        }

        book->release();
    }

    std::cout << "\nPress any key to exit...";
    _getch();

    return 0;
}

