program xformat

use libxl

type(BookHandle) book
type(SheetHandle) sheet, nullSheet
type(FormatHandle) format1, nullFormat
type(FontHandle) font1, nullFont
integer i
   
book = xlCreateBook()
if(book%point.ne.0) then
    font1 = xlBookAddFont(book, nullFont)
    i = xlFontSetName(font1, "Impact")
    call xlFontSetSize(font1, 36)

    format1 = xlBookAddFormat(book, nullFormat)
    call xlFormatSetAlignH(format1, ALIGNH_CENTER)
    call xlFormatSetBorder(format1, BORDERSTYLE_MEDIUMDASHDOTDOT)
    call xlFormatSetBorderColor(format1, COLOR_RED)
    i=xlFormatSetFont(format1, font1)

    sheet = xlBookAddSheet(book, "Custom", nullSheet)
    if(sheet%point.ne.0) then 
        i = xlSheetWriteStr(sheet, 2, 1, "Format", format1)
        i = xlSheetSetCol(sheet, 1, 1, 25, nullFormat, 0)
    end if

    i = xlBookSave(book, "format.xls");
end if

end program xformat