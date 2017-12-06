#COMPILE EXE
#DIM ALL
#TOOLS ON

#INCLUDE "libxl.inc"

    GLOBAL maxCol, maxRow AS LONG


FUNCTION makestring () AS STRING
    DIM s AS STRING
    DIM N%
    s = "00000000"
    FOR N% = 1 TO 8 STEP 1
       ASC(s, N%) = RND(33,126)
    NEXT N%
    FUNCTION = s
END FUNCTION

FUNCTION test (number AS LONG) AS LONG
    DIM book AS BookHandle
    DIM sheet AS SheetHandle
    DIM t1#
    DIM t2#
    DIM d#
    DIM n#
    DIM row%
    DIM col%
    DIM s$

    s$ = "---------------------------------------"+ $CRLF
    IF(number = 1) THEN
        s$ = s$ + "              strings                  "+ $CRLF
    ELSE
        s$ = s$ + "              numbers                  "+ $CRLF
    END IF
    s$ = s$ + "---------------------------------------" + $CRLF

    book = xlCreateBook()
    IF(book) THEN
        sheet = xlBookAddSheet(book, "Sheet1", 0)
        IF(sheet) THEN
            MSGBOX(s$ + "writing " + STR$( (maxRow - 1) * maxCol,0) + " cells...")
            t1 = TIMER
            IF(number = 1) THEN
                FOR row% = 1 TO maxRow STEP 1
                    FOR col% = 0 TO maxCol STEP 1
                        n# = xlSheetWriteStr(sheet, row%, col%, makestring(), 0)
                    NEXT col%
                NEXT row%
            ELSE
                FOR row% = 1 TO maxRow STEP 1
                    FOR col% = 0 TO maxCol STEP 1
                        n# = xlSheetWriteNum(sheet, row%, col%, CDBL(row% * col%), 0)
                    NEXT col%
                NEXT row%
            END IF
            t2 = TIMER
            d = t2 - t1
            IF(d > 0) THEN
                MSGBOX(s$+ "time:  " + STR$(d,6) + "sec"+ $CRLF +"speed: " + STR$((maxRow-1)* maxCol / d, 6) + " cells/sec" )
            END IF
            MSGBOX(s$ + "saving...")
            t1 = TIMER
            IF(number = 1) THEN
                xlBookSave(book, "perfstr.xls")
            ELSE
                xlBookSave(book, "perfnum.xls")
            END IF
            t2 = TIMER
            d = t2 - t1
            IF(d > 0) THEN
                MSGBOX(s$+ "time:  " + STR$(d,6) + "sec"+ $CRLF +"speed: " + STR$((maxRow-1)* maxCol / d, 6) + " cells/sec" )
            END IF
        END IF
    xlBookRelease(book)
    END IF

END FUNCTION



FUNCTION PBMAIN () AS LONG
    maxCol = 256
    maxRow = 20000
    test(0)
    test(1)

END FUNCTION
