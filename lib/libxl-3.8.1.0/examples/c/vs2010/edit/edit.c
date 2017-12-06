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
                double d = xlSheetReadNum(sheet, 3, 1, 0);
                xlSheetWriteNum(sheet, 3, 1, d * 2, 0);
                xlSheetWriteStr(sheet, 4, 1, L"new string", 0);     
            }

            if(xlBookSave(book, L"example.xls")) printf("\nFile example.xls has been modified.\n");
        } 

        xlBookRelease(book);
    }

    printf("\nPress any key to exit...");
    _getch();

    return 0;
}
