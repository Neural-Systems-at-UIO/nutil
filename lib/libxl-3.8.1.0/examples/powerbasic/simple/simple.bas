#COMPILE EXE
#DIM ALL

#INCLUDE "libxlw.inc"


FUNCTION PBMAIN () AS LONG
    DIM book AS BookHandle
    book = xlCreateBook()

    IF(book) THEN
        DIM sheet AS SheetHandle
        sheet = xlBookAddSheet(book, UCODE$("sheet1") , 0)
    END IF
        'if(sheet)
        '{
            xlSheetWriteStr(sheet, 2, 2, UCODE$("AEHello, World !"), 0)
            xlSheetWriteNum(sheet, 3, 1, 1000, 0)
        '}




    xlBookSave(book, UCODE$("example.xls"))
	MSGBOX("File Written")
    xlBookRelease(book)



END FUNCTION
