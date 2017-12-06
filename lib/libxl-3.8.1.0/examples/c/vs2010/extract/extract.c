#include <stdio.h>
#include <conio.h>
#include "libxl.h"

int main()
{
    BookHandle book = xlCreateBook();
    if(book) 
    {
        if(xlBookLoad(book, L"example.xls")) 
        {
            SheetHandle sheet = xlBookGetSheet(book, 0);
            if(sheet)
            {
                double d;
                const wchar_t* s = xlSheetReadStr(sheet, 2, 1, 0);

                if(s) wprintf(L"%s\n", s);

                d = xlSheetReadNum(sheet, 3, 1, 0);
                printf("%g\n", d);
            }
        }     
       
        xlBookRelease(book);
    }

    printf("\nPress any key to exit...");
    _getch();

    return 0;
}
