program extract

use libxl

interface
    subroutine convert(i,buff)
    !DEC$ ATTRIBUTES C :: convert
    !DEC$ ATTRIBUTES reference :: buff
    character(*) buff
    integer i
    end subroutine
end interface

type(BookHandle) book
type(SheetHandle) sheet
type(FormatHandle) nullFormat
integer i
double precision d
character(25) buff
 
book = xlCreateBook()
if(book%point.ne.0) then
    if(xlBookLoad(book, "..\generate\example.xls").ne.0) then
        sheet = xlBookGetSheet(book, 0)
        if(sheet%point.ne.0) then
            i = xlSheetReadStr(sheet, 2, 1, nullFormat)
            call convert(i,buff)

            if(buff.ne.'') print *,buff

            d = xlSheetReadNum(sheet, 3, 1, nullFormat)
            print *,d
        end if
    end if        
    call xlBookRelease(book)
end if
    
end program extract