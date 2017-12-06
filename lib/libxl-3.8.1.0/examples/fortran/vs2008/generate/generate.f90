program generate

use libxl

type(BookHandle) book
type(SheetHandle) sheet, nullSheet
type(FormatHandle) nullFormat
integer i

book = xlCreateBook()

if(book%point.ne.0) then
    sheet = xlBookAddSheet(book, "Sheet1", nullSheet)
    if(sheet%point.ne.0) then
        i=xlSheetWriteStr(sheet, 2, 1, "Hello, World !", nullFormat);
        i=xlSheetWriteNum(sheet, 3, 1, 1000, nullFormat);
    end if
    i=xlBookSave(book, 'example.xls')
    call xlBookRelease(book)
end if
    
end program generate