program custom

use libxl

type(BookHandle) book
type(SheetHandle) sheet, nullSheet
type(FormatHandle) f(6), nullFormat
integer c(6), i

book = xlCreateBook()

c(1) = xlBookAddCustomNumFormat(book, "0.0")
c(2) = xlBookAddCustomNumFormat(book, "0.00")
c(3) = xlBookAddCustomNumFormat(book, "0.000")
c(4) = xlBookAddCustomNumFormat(book, "0.0000")
c(5) = xlBookAddCustomNumFormat(book, "#,###.00 $")
c(6) = xlBookAddCustomNumFormat(book, "#,###.00 $[Black][<1000];#,###.00 $[Red][>=1000]")

do i = 1, 6  
  f(i) = xlBookAddFormat(book, nullFormat)
  call xlFormatSetNumFormat(f(i), c(i))
end do

sheet = xlBookAddSheet(book, "Custom formats", nullSheet)
    
i = xlSheetSetCol(sheet, 0, 0, 20, nullFormat, 0);
i = xlSheetWriteNum(sheet, 2, 0, 25.718, f(1));
i = xlSheetWriteNum(sheet, 3, 0, 25.718, f(2));
i = xlSheetWriteNum(sheet, 4, 0, 25.718, f(3));
i = xlSheetWriteNum(sheet, 5, 0, 25.718, f(4));

i = xlSheetWriteNum(sheet, 7, 0, 1800.5, f(5));

i = xlSheetWriteNum(sheet, 9, 0, 500, f(6));
i = xlSheetWriteNum(sheet, 10, 0, 1600, f(6));
    
i = xlBookSave(book, 'custom.xls')

call xlBookRelease(book)
    
end program custom