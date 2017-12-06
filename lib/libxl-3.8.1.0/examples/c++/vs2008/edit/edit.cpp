#include <iostream>
#include <windows.h>
#include <conio.h>
#include "libxl.h"

using namespace libxl;

int main() 
{
    Book* book = xlCreateBook();
    if(book) 
    {                
        if(book->load(L"..\\generate\\example.xls"))
        {
            Sheet* sheet = book->getSheet(0);
            if(sheet) 
            {   
                double d = sheet->readNum(4, 1);
                sheet->writeNum(4, 1, d * 2);
                sheet->writeStr(10, 1, L"new string !");
            }

            if(book->save(L"..\\generate\\example.xls")) 
            {
                std::cout << "\nFile example.xls has been modified." << std::endl;
                ::ShellExecute(NULL, L"open", L"..\\generate\\example.xls", NULL, NULL, SW_SHOW);
            }
            else
            {
                std::cout << book->errorMessage() << std::endl;
            }
        }
        else
        {
            std::cout << "At first run generate !" << std::endl;
        }

        book->release();   
    }

    std::cout << "\nPress any key to exit...";
    _getch();
   
    return 0;
}
