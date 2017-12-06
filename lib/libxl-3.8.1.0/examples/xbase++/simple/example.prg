#include "ot4xb.ch"

DLL libxl.dll IMPORT createXMLBook AS int;
SYMBOL xlCreateXMLBookCW

DLL libxl.dll IMPORT addSheet AS int;
PARAM handle AS int,;
PARAM name AS LPSTR,;
PARAM initSheet AS int;
SYMBOL xlBookAddSheetW

DLL libxl.dll IMPORT writeNum AS int;
PARAM handle AS int,;
PARAM row AS int,;
PARAM col AS int,;
PARAM value AS Double,;
PARAM format AS int;
SYMBOL xlSheetWriteNumW

DLL libxl.dll IMPORT writeStr AS int;
PARAM handle AS int,;
PARAM row AS int,;
PARAM col AS int,;
PARAM value AS LPSTR,;
PARAM format AS int;
SYMBOL xlSheetWriteStrW

DLL libxl.dll IMPORT saveBook AS int;
PARAM handle AS int,;
PARAM name AS LPSTR;
SYMBOL xlBookSaveW

DLL libxl.dll IMPORT releaseXMLBook AS void;
PARAM handle AS int;
SYMBOL xlBookReleaseW


proc main()

  local book, sheet

  book := createXMLBook()
  sheet := addSheet(book, Str2Unicode("Sheet1"), 0)
  writeNum(sheet, 5, 1, 95.7699, 0)
  writeStr(sheet, 7, 1, Str2Unicode("hello world !"), 0)
  saveBook(book, Str2Unicode("example.xlsx"))  
  releaseXMLBook(book)

return


