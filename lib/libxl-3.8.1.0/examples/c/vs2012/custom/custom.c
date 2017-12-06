#include <stdio.h>
#include <conio.h>
#include "libxl.h"

int main()
{
    BookHandle book = xlCreateBook();
    if(book) 
    {	
        int i, f[6];
        FormatHandle format[6];
        SheetHandle sheet;		

        f[0] = xlBookAddCustomNumFormat(book, L"0.0");
        f[1] = xlBookAddCustomNumFormat(book, L"0.00");
        f[2] = xlBookAddCustomNumFormat(book, L"0.000");
        f[3] = xlBookAddCustomNumFormat(book, L"0.0000");
        f[4] = xlBookAddCustomNumFormat(book, L"#,###.00 $");
        f[5] = xlBookAddCustomNumFormat(book, L"#,###.00 $[Black][<1000];#,###.00 $[Red][>=1000]");

        for(i = 0; i < 6; ++i) {
            format[i] = xlBookAddFormat(book, 0);
            xlFormatSetNumFormat(format[i], f[i]);
        }
	
        sheet = xlBookAddSheet(book, L"Custom formats", 0);
        if(sheet) 
        {
            xlSheetSetCol(sheet, 0, 0, 20, 0, 0);
            xlSheetWriteNum(sheet, 2, 0, 25.718, format[0]);
            xlSheetWriteNum(sheet, 3, 0, 25.718, format[1]);
            xlSheetWriteNum(sheet, 4, 0, 25.718, format[2]);
            xlSheetWriteNum(sheet, 5, 0, 25.718, format[3]);

            xlSheetWriteNum(sheet, 7, 0, 1800.5, format[4]);

            xlSheetWriteNum(sheet, 9, 0, 500, format[5]);
            xlSheetWriteNum(sheet, 10, 0, 1600, format[5]);            
        }

        if(xlBookSave(book, L"custom.xls")) printf("\nFile custom.xls has been created.\n");
        xlBookRelease(book);
    }

    printf("\nPress any key to exit...");
    _getch();

    return 0;
}
