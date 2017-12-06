program edit

use libxl

type(BookHandle) book
type(SheetHandle) sheet
type(FormatHandle) nullFormat
integer i
double precision d
    
book = xlCreateBook()
if(book%point.ne.0) then
    if(xlBookLoad(book, "..\generate\example.xls").ne.0) then
        sheet = xlBookGetSheet(book, 0)
        if(sheet%point.ne.0) then
            d = xlSheetReadNum(sheet, 3, 1, nullFormat)
            i=xlSheetWriteNum(sheet, 3, 1, d * 2, nullFormat)
            i=xlSheetWriteStr(sheet, 4, 1, "new string", nullFormat)
        end if
        i=xlBookSave(book, "..\generate\example.xls")
    end if
    call xlBookRelease(book)
end if

end program edit