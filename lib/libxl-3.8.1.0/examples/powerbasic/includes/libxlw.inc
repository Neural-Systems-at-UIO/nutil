#INCLUDE THIS ONCE

#INCLUDE ONCE "enum.inc"

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''Book function declarations'''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

DECLARE FUNCTION xlCreateBook               LIB "libxl.dll" CDECL ALIAS "xlCreateBookCW"     _
                            () AS BookHandle
DECLARE FUNCTION xlCreateXMLBook            LIB "libxl.dll" CDECL ALIAS "xlCreateXMLBookCW"  _
                            () AS BookHandle

DECLARE FUNCTION xlBookLoad                 LIB "libxl.dll" CDECL ALIAS "xlBookLoadW"        _
                            (BYVAL book AS BookHandle, BYREF fileName AS STRINGZ) AS LONG
DECLARE FUNCTION xlBookSave                 LIB "libxl.dll" CDECL ALIAS "xlBookSaveW"        _
                            (BYVAL book AS BookHandle, BYREF fileName AS STRINGZ) AS LONG
DECLARE FUNCTION xlBookLoadRaw              LIB "libxl.dll" CDECL ALIAS "xlBookLoadRawW"     _
                            (BYVAL book AS BookHandle, BYREF fileData AS STRINGZ, BYVAL fileSize AS LONG) AS LONG
DECLARE FUNCTION xlBookSaveRaw              LIB "libxl.dll" CDECL ALIAS "xlBookSaveRawW"     _
                            (BYVAL book AS BookHandle, BYVAL fileData AS STRINGZ PTR, BYVAL fileSize AS LONG PTR) AS LONG

DECLARE FUNCTION xlBookAddSheet             LIB "libxl.dll" CDECL ALIAS "xlBookAddSheetW"    _
                            (BYVAL book AS BookHandle, BYREF sheetName AS STRINGZ, BYVAL initSheet AS SheetHandle) AS SheetHandle
DECLARE FUNCTION xlBookInsertSheet          LIB "libxl.dll" CDECL ALIAS "xlBookInsertSheetW" _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG, BYREF sheetName AS STRINGZ, BYVAL initSheet AS SheetHandle) AS SheetHandle
DECLARE FUNCTION xlBookGetSheet             LIB "libxl.dll" CDECL ALIAS "xlBookGetSheetW"    _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG) AS SheetHandle
DECLARE FUNCTION xlBookSheetType            LIB "libxl.dll" CDECL ALIAS "xlBookSheetTypeW"   _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG) AS LONG
DECLARE FUNCTION xlBookDelSheet             LIB "libxl.dll" CDECL ALIAS "xlBookDelSheetW"    _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG) AS LONG
DECLARE FUNCTION xlBookSheetCount           LIB "libxl.dll" CDECL ALIAS "xlBookSheetCountW"  _
                            (BYVAL book AS BookHandle) AS LONG

DECLARE FUNCTION xlBookAddFormat            LIB "libxl.dll" CDECL ALIAS "xlBookAddFormatW"          _
                            (BYVAL book AS BookHandle, BYVAL initFormat AS FormatHandle) AS FormatHandle
DECLARE FUNCTION xlBookAddFont              LIB "libxl.dll" CDECL ALIAS "xlBookAddFontW"            _
                            (BYVAL book AS BookHandle, BYVAL initFont AS FontHandle) AS FontHandle
DECLARE FUNCTION xlBookAddCustomNumFormat   LIB "libxl.dll" CDECL ALIAS "xlBookAddCustomNumFormatW" _
                            (BYVAL book AS BookHandle, BYREF customNumFormat AS STRINGZ) AS LONG
DECLARE FUNCTION xlBookCustomNumFormat LIB "libxl.dll" CDECL ALIAS "xlBookCustomNumFormatW"         _                     'check this function for sure
                            (BYVAL book AS BookHandle, BYVAL format AS LONG) AS DWORD

DECLARE FUNCTION xlBookFormat               LIB "libxl.dll" CDECL ALIAS "xlBookFormatW"      _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG) AS FormatHandle
DECLARE FUNCTION xlBookFormatSize           LIB "libxl.dll" CDECL ALIAS "xlBookFormatSizeW"  _
                            (BYVAL book AS BookHandle) AS LONG

DECLARE FUNCTION xlBookFont                 LIB "libxl.dll" CDECL ALIAS "xlBookFontW"        _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG) AS FontHandle
DECLARE FUNCTION xlBookFontSize             LIB "libxl.dll" CDECL ALIAS "xlBookFontSizeW"    _
                            (BYVAL book AS BookHandle) AS LONG

DECLARE FUNCTION xlBookDatePack             LIB "libxl.dll" CDECL ALIAS "xlBookDatePackW"    _
                            (BYVAL book AS BookHandle, BYVAL year AS LONG, BYVAL month AS LONG, BYVAL day AS LONG, BYVAL hour AS LONG, BYVAL minute AS LONG, BYVAL second AS LONG, BYVAL millisecond AS LONG) AS DOUBLE
DECLARE FUNCTION xlBookDateUnpack           LIB "libxl.dll" CDECL ALIAS "xlBookDateUnpackW"  _
                            (BYVAL book AS BookHandle, BYVAL value AS DOUBLE, BYVAL year AS LONG PTR, BYVAL month AS LONG PTR, BYVAL day AS LONG PTR, _
                             BYVAL hour AS LONG PTR, BYVAL minute AS LONG PTR, BYVAL second AS LONG PTR, BYVAL millisecond AS LONG PTR) AS LONG

DECLARE FUNCTION xlBookColorPack            LIB "libxl.dll" CDECL ALIAS "xlBookColorPackW"    _
                            (BYVAL book AS BookHandle, BYVAL red AS LONG, BYVAL green AS LONG, BYVAL blue AS LONG) AS LONG
DECLARE FUNCTION xlBookColorUnpack          LIB "libxl.dll" CDECL ALIAS "xlBookColorUnpackW"  _
                            (BYVAL book AS BookHandle, BYVAL value AS LONG, BYVAL red AS LONG PTR, BYVAL green AS LONG PTR, BYVAL blue AS LONG PTR) AS LONG

DECLARE FUNCTION xlBookActiveSheet          LIB "libxl.dll" CDECL ALIAS "xlBookActiveSheetW"    _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookSetActiveSheet       LIB "libxl.dll" CDECL ALIAS "xlBookSetActiveSheetW" _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG) AS LONG

DECLARE FUNCTION xlBookPictureSize          LIB "libxl.dll" CDECL ALIAS "xlBookPictureSizeW"  _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookGetPicture           LIB "libxl.dll" CDECL ALIAS "xlBookGetPictureW"   _
                            (BYVAL book AS BookHandle, BYVAL index AS LONG, BYVAL picData AS STRINGZ PTR, BYVAL picSize AS LONG PTR) AS LONG

DECLARE FUNCTION xlBookAddPicture           LIB "libxl.dll" CDECL ALIAS "xlBookAddPictureW"   _
                            (BYVAL book AS BookHandle, BYREF filename AS STRINGZ) AS LONG
DECLARE FUNCTION xlBookAddPicture2          LIB "libxl.dll" CDECL ALIAS "xlBookAddPicture2W"  _
                            (BYVAL book AS BookHandle, BYREF picData AS STRINGZ, BYVAL picSize AS LONG) AS LONG

DECLARE FUNCTION xlBookDefaultFont          LIB "libxl.dll" CDECL ALIAS "xlBookDefaultFontW"    _                         'check this function for sure
                            (BYVAL book AS BookHandle, BYVAL fontSize AS LONG PTR) AS DWORD
DECLARE FUNCTION xlBookSetDefaultFont       LIB "libxl.dll" CDECL ALIAS "xlBookSetDefaultFontW" _
                            (BYVAL book AS BookHandle, BYREF fontName AS STRINGZ, BYVAL fontSize AS LONG) AS LONG

DECLARE FUNCTION xlBookRefR1C1              LIB "libxl.dll" CDECL ALIAS "xlBookRefR1C1W"      _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookSetRefR1C1           LIB "libxl.dll" CDECL ALIAS "xlBookSetRefR1C1W"   _
                            (BYVAL book AS BookHandle, BYVAL refR1C1 AS LONG) AS LONG

DECLARE FUNCTION xlBookSetKey               LIB "libxl.dll" CDECL ALIAS "xlBookSetKeyW"       _
                            (BYVAL book AS BookHandle, BYREF keyname AS STRINGZ, BYREF key AS STRINGZ) AS LONG

DECLARE FUNCTION xlBookRgbMode              LIB "libxl.dll" CDECL ALIAS "xlBookRgbModeW"      _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookSetRgbMode           LIB "libxl.dll" CDECL ALIAS "xlBookSetRgbModeW"   _
                            (BYVAL book AS BookHandle, BYVAL rgbMode AS LONG) AS LONG

DECLARE FUNCTION xlBookVersion              LIB "libxl.dll" CDECL ALIAS "xlBookVersionW"      _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookBiffVersion          LIB "libxl.dll" CDECL ALIAS "xlBookBiffVersionW"  _
                            (BYVAL book AS BookHandle) AS LONG

DECLARE FUNCTION xlBookIsDate1904           LIB "libxl.dll" CDECL ALIAS "xlBookIsDate1904W"   _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookSetDate1904          LIB "libxl.dll" CDECL ALIAS "xlBookSetDate1904W"  _
                            (BYVAL book AS BookHandle, BYVAL date1904 AS LONG) AS LONG

DECLARE FUNCTION xlBookIsTemplate           LIB "libxl.dll" CDECL ALIAS "xlBookIsTemplateW"   _
                            (BYVAL book AS BookHandle) AS LONG
DECLARE FUNCTION xlBookSetTemplate          LIB "libxl.dll" CDECL ALIAS "xlBookSetTemplateW"  _
                            (BYVAL book AS BookHandle, BYVAL tmpl AS LONG) AS LONG

DECLARE FUNCTION xlBookSetLocale            LIB "libxl.dll" CDECL ALIAS "xlBookSetLocaleW"    _
                            (BYVAL book AS BookHandle, BYREF tmpl AS STRINGZ) AS LONG
DECLARE FUNCTION xlBookErrorMessage         LIB "libxl.dll" CDECL ALIAS "xlBookErrorMessageW" _                          'check this function for sure
                            (BYVAL book AS BookHandle) AS DWORD

DECLARE FUNCTION xlBookRelease              LIB "libxl.dll" CDECL ALIAS "xlBookReleaseW"      _
                            (BYVAL book AS BookHandle) AS LONG

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''Sheet function declarations''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                                                                                         '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
                                                                                                         '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

DECLARE FUNCTION xlSheetCellType      LIB "libxl.dll" CDECL ALIAS "xlSheetCellTypeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG
DECLARE FUNCTION xlSheetIsFormula      LIB "libxl.dll" CDECL ALIAS "xlSheetIsFormulaW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG

DECLARE FUNCTION xlSheetCellFormat      LIB "libxl.dll" CDECL ALIAS "xlSheetCellFormatW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS FormatHandle
DECLARE FUNCTION xlSheetSetCellFormat      LIB "libxl.dll" CDECL ALIAS "xlSheetSetCellFormatW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle) AS LONG

DECLARE FUNCTION xlSheetReadStr      LIB "libxl.dll" CDECL ALIAS "xlSheetReadStrW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle POINTER) AS DWORD
DECLARE FUNCTION xlSheetWriteStr      LIB "libxl.dll" CDECL ALIAS "xlSheetWriteStrW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYREF value AS STRINGZ, BYVAL format AS FormatHandle) AS LONG


DECLARE FUNCTION xlSheetReadNum      LIB "libxl.dll" CDECL ALIAS "xlSheetReadNumW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle POINTER) AS DOUBLE
DECLARE FUNCTION xlSheetWriteNum      LIB "libxl.dll" CDECL ALIAS "xlSheetWriteNumW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL value AS DOUBLE, BYVAL format AS FormatHandle) AS LONG


DECLARE FUNCTION xlSheetReadBool      LIB "libxl.dll" CDECL ALIAS "xlSheetReadBoolW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle POINTER) AS LONG
DECLARE FUNCTION xlSheetWriteBool      LIB "libxl.dll" CDECL ALIAS "xlSheetWriteBoolW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL value AS LONG, BYVAL format AS FormatHandle ) AS LONG


DECLARE FUNCTION xlSheetReadBlank      LIB "libxl.dll" CDECL ALIAS "xlSheetReadBlankW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle POINTER) AS LONG
DECLARE FUNCTION xlSheetWriteBlank      LIB "libxl.dll" CDECL ALIAS "xlSheetWriteBlankW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle) AS LONG


DECLARE FUNCTION xlSheetReadFormula      LIB "libxl.dll" CDECL ALIAS "xlSheetReadFormulaW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL format AS FormatHandle POINTER) AS DWORD
DECLARE FUNCTION xlSheetWriteFormula      LIB "libxl.dll" CDECL ALIAS "xlSheetWriteFormulaW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYREF value AS STRINGZ, BYVAL format AS FormatHandle POINTER) AS LONG


DECLARE FUNCTION xlSheetReadComment      LIB "libxl.dll" CDECL ALIAS "xlSheetReadCommentW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS DWORD
DECLARE FUNCTION xlSheetWriteComment      LIB "libxl.dll" CDECL ALIAS "xlSheetWriteCommentW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYREF value AS STRINGZ, BYREF author AS STRINGZ, BYVAL width_ AS LONG, BYVAL height_ AS LONG) AS LONG


DECLARE FUNCTION xlSheetIsDate      LIB "libxl.dll" CDECL ALIAS "xlSheetIsDateW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG
DECLARE FUNCTION xlSheetReadError      LIB "libxl.dll" CDECL ALIAS "xlSheetReadErrorW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG


DECLARE FUNCTION xlSheetColWidth      LIB "libxl.dll" CDECL ALIAS "xlSheetColWidthW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS DOUBLE
DECLARE FUNCTION xlSheetRowHeight      LIB "libxl.dll" CDECL ALIAS "xlSheetRowHeightW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS DOUBLE


DECLARE FUNCTION xlSheetSetCol      LIB "libxl.dll" CDECL ALIAS "xlSheetSetColW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL colFirst AS LONG, BYVAL colLast AS LONG, BYVAL format AS FormatHandle, BYVAL hidden_ AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetRow      LIB "libxl.dll" CDECL ALIAS "xlSheetSetRowW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL height AS DOUBLE, BYVAL format AS FormatHandle, BYVAL hidden_ AS LONG) AS LONG


DECLARE FUNCTION xlSheetRowHidden      LIB "libxl.dll" CDECL ALIAS "xlSheetRowHiddenW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetRowHidden      LIB "libxl.dll" CDECL ALIAS "xlSheetSetRowHiddenW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL hidden_ AS LONG) AS LONG


DECLARE FUNCTION xlSheetColHidden      LIB "libxl.dll" CDECL ALIAS "xlSheetColHiddenW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL col AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetColHidden      LIB "libxl.dll" CDECL ALIAS "xlSheetSetColHiddenW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL col AS LONG, BYVAL hidden AS LONG) AS LONG


DECLARE FUNCTION xlSheetGetMerge      LIB "libxl.dll" CDECL ALIAS "xlSheetGetMergeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL rowFirst AS LONG PTR, BYVAL rowLast AS LONG PTR, BYVAL colFirst AS LONG PTR, BYVAL colLast AS LONG PTR) AS LONG
DECLARE FUNCTION xlSheetSetMerge      LIB "libxl.dll" CDECL ALIAS "xlSheetSetMergeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG
DECLARE FUNCTION xlSheetDelMerge      LIB "libxl.dll" CDECL ALIAS "xlSheetDelMergeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG


DECLARE FUNCTION xlSheetMergeSize      LIB "libxl.dll" CDECL ALIAS "xlSheetMergeSizeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetMerge      LIB "libxl.dll" CDECL ALIAS "xlSheetMergeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG, BYVAL rowFirst AS LONG PTR, BYVAL rowLast AS LONG PTR, BYVAL colFirst AS LONG PTR, BYVAL colLast AS LONG PTR) AS LONG
DECLARE FUNCTION xlSheetDelMergeByIndex      LIB "libxl.dll" CDECL ALIAS "xlSheetDelMergeByIndexW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG) AS LONG


DECLARE FUNCTION xlSheetPictureSize      LIB "libxl.dll" CDECL ALIAS "xlSheetPictureSizeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetGetPicture      LIB "libxl.dll" CDECL ALIAS "xlSheetGetPictureW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG, BYVAL rowTop AS LONG PTR, BYVAL colLeft AS LONG PTR, BYVAL rowBottom AS LONG PTR, BYVAL colRight AS LONG PTR _
                                                                             , BYVAL width AS LONG PTR , BYVAL height AS LONG PTR , BYVAL offset_x AS LONG PTR , BYVAL offset_y AS LONG PTR) AS LONG
DECLARE FUNCTION xlSheetSetPicture      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPictureW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL pictureId AS LONG, BYVAL scale AS DOUBLE, BYVAL offset_x AS LONG, BYVAL offset_y AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetPicture2      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPicture2W"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL pictureId AS LONG, BYVAL width AS LONG, BYVAL height AS LONG, BYVAL offset_x AS LONG, BYVAL offset_y AS LONG) AS LONG


DECLARE FUNCTION xlSheetGetHorPageBreak      LIB "libxl.dll" CDECL ALIAS "xlSheetGetHorPageBreakW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG) AS LONG
DECLARE FUNCTION xlSheetGetHorPageBreakSize      LIB "libxl.dll" CDECL ALIAS "xlSheetGetHorPageBreakSizeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG


DECLARE FUNCTION xlSheetGetVerPageBreak      LIB "libxl.dll" CDECL ALIAS "xlSheetGetVerPageBreakW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG) AS LONG
DECLARE FUNCTION xlSheetGetVerPageBreakSize      LIB "libxl.dll" CDECL ALIAS "xlSheetGetVerPageBreakSizeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG


DECLARE FUNCTION xlSheetSetHorPageBreak      LIB "libxl.dll" CDECL ALIAS "xlSheetSetHorPageBreakW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL pageBreak AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetVerPageBreak      LIB "libxl.dll" CDECL ALIAS "xlSheetSetVerPageBreakW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL col AS LONG, BYVAL pageBreak AS LONG) AS LONG


DECLARE FUNCTION xlSheetSplit      LIB "libxl.dll" CDECL ALIAS "xlSheetSplitW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG
DECLARE FUNCTION xlSheetSplitInfo      LIB "libxl.dll" CDECL ALIAS "xlSheetSplitInfoW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG PTR, BYVAL col AS LONG PTR) AS LONG


DECLARE FUNCTION xlSheetGroupRows      LIB "libxl.dll" CDECL ALIAS "xlSheetGroupRowsW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG, BYVAL collapsed AS LONG) AS LONG
DECLARE FUNCTION xlSheetGroupCols      LIB "libxl.dll" CDECL ALIAS "xlSheetGroupColsW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL colFirst AS LONG, BYVAL colLast AS LONG, BYVAL collapsed AS LONG) AS LONG


DECLARE FUNCTION xlSheetGroupSummaryBelow      LIB "libxl.dll" CDECL ALIAS "xlSheetGroupSummaryBelowW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetGroupSummaryBelow      LIB "libxl.dll" CDECL ALIAS "xlSheetSetGroupSummaryBelowW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL below AS LONG) AS LONG


DECLARE FUNCTION xlSheetGroupSummaryRight      LIB "libxl.dll" CDECL ALIAS "xlSheetGroupSummaryRightW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetGroupSummaryRight      LIB "libxl.dll" CDECL ALIAS "xlSheetSetGroupSummaryRightW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL right AS LONG) AS LONG


DECLARE FUNCTION xlSheetClear      LIB "libxl.dll" CDECL ALIAS "xlSheetClearW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG


DECLARE FUNCTION xlSheetInsertCol      LIB "libxl.dll" CDECL ALIAS "xlSheetInsertColW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG
DECLARE FUNCTION xlSheetInsertRow      LIB "libxl.dll" CDECL ALIAS "xlSheetInsertRowW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG) AS LONG
DECLARE FUNCTION xlSheetRemoveCol      LIB "libxl.dll" CDECL ALIAS "xlSheetRemoveColW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG
DECLARE FUNCTION xlSheetRemoveRow      LIB "libxl.dll" CDECL ALIAS "xlSheetRemoveRowW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL colLast AS LONG) AS LONG


DECLARE FUNCTION xlSheetCopyCell      LIB "libxl.dll" CDECL ALIAS "xlSheetCopyCellW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowSrc AS LONG, BYVAL colSrc AS LONG, BYVAL rowDst AS LONG, BYVAL colDst AS LONG) AS LONG


DECLARE FUNCTION xlSheetFirstRow      LIB "libxl.dll" CDECL ALIAS "xlSheetFirstRowW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetLastRow      LIB "libxl.dll" CDECL ALIAS "xlSheetLastRowW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetFirstCol      LIB "libxl.dll" CDECL ALIAS "xlSheetFirstColW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetLastCol      LIB "libxl.dll" CDECL ALIAS "xlSheetLastColW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG


DECLARE FUNCTION xlSheetDisplayGridlines      LIB "libxl.dll" CDECL ALIAS "xlSheetDisplayGridlinesW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetDisplayGridlines      LIB "libxl.dll" CDECL ALIAS "xlSheetSetDisplayGridlinesW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL show AS LONG) AS LONG


DECLARE FUNCTION xlSheetPrintGridlines      LIB "libxl.dll" CDECL ALIAS "xlSheetPrintGridlinesW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetPrintGridlines      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintGridlinesW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL print AS LONG) AS LONG


DECLARE FUNCTION xlSheetZoom      LIB "libxl.dll" CDECL ALIAS "xlSheetZoomW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetZoom      LIB "libxl.dll" CDECL ALIAS "xlSheetSetZoomW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL zoom AS LONG) AS LONG


DECLARE FUNCTION xlSheetPrintZoom      LIB "libxl.dll" CDECL ALIAS "xlSheetPrintZoomW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetPrintZoom      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintZoomW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL zoom AS LONG) AS LONG


DECLARE FUNCTION xlSheetGetPrintFit      LIB "libxl.dll" CDECL ALIAS "xlSheetGetPrintFitW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL wPages AS LONG PTR, BYVAL hPages AS LONG PTR) AS LONG
DECLARE FUNCTION xlSheetSetPrintFit      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintFitW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL wPages AS LONG, BYVAL hPages AS LONG) AS LONG


DECLARE FUNCTION xlSheetLandscape      LIB "libxl.dll" CDECL ALIAS "xlSheetLandscapeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetLandscape      LIB "libxl.dll" CDECL ALIAS "xlSheetSetLandscapeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL landscape AS LONG) AS LONG


DECLARE FUNCTION xlSheetPaper      LIB "libxl.dll" CDECL ALIAS "xlSheetPaperW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetPaper      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPaperW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL paper AS LONG) AS LONG


DECLARE FUNCTION xlSheetHeader      LIB "libxl.dll" CDECL ALIAS "xlSheetHeaderW"         _
                            (BYVAL sheet AS SheetHandle) AS DWORD
DECLARE FUNCTION xlSheetSetHeader      LIB "libxl.dll" CDECL ALIAS "xlSheetSetHeaderW"         _
                            (BYVAL sheet AS SheetHandle, BYREF header AS STRINGZ, BYVAL margin AS DOUBLE) AS LONG
DECLARE FUNCTION xlSheetHeaderMargin      LIB "libxl.dll" CDECL ALIAS "xlSheetHeaderMarginW"         _
                            (BYVAL sheet AS SheetHandle) AS DOUBLE


DECLARE FUNCTION xlSheetFooter      LIB "libxl.dll" CDECL ALIAS "xlSheetFooterW"         _
                            (BYVAL sheet AS SheetHandle) AS DWORD
DECLARE FUNCTION xlSheetSetFooter      LIB "libxl.dll" CDECL ALIAS "xlSheetSetFooterW"         _
                            (BYVAL sheet AS SheetHandle, BYREF footer AS STRINGZ, BYVAL margin AS DOUBLE) AS LONG
DECLARE FUNCTION xlSheetFooterMargin      LIB "libxl.dll" CDECL ALIAS "xlSheetFooterMarginW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS DOUBLE


DECLARE FUNCTION xlSheetHCenter      LIB "libxl.dll" CDECL ALIAS "xlSheetHCenterW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetHCenter      LIB "libxl.dll" CDECL ALIAS "xlSheetSetHCenterW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL hCenter AS LONG) AS LONG


DECLARE FUNCTION xlSheetVCenter      LIB "libxl.dll" CDECL ALIAS "xlSheetVCenterW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetVCenter      LIB "libxl.dll" CDECL ALIAS "xlSheetSetVCenterW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL vCenter AS LONG) AS LONG


DECLARE FUNCTION xlSheetMarginLeft      LIB "libxl.dll" CDECL ALIAS "xlSheetMarginLeftW"         _
                            (BYVAL sheet AS SheetHandle) AS DOUBLE
DECLARE FUNCTION xlSheetSetMarginLeft      LIB "libxl.dll" CDECL ALIAS "xlSheetSetMarginLeftW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL margin AS DOUBLE) AS LONG


DECLARE FUNCTION xlSheetMarginRight      LIB "libxl.dll" CDECL ALIAS "xlSheetMarginRightW"         _
                            (BYVAL sheet AS SheetHandle) AS DOUBLE
DECLARE FUNCTION xlSheetSetMarginRight      LIB "libxl.dll" CDECL ALIAS "xlSheetSetMarginRightW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL margin AS DOUBLE) AS LONG


DECLARE FUNCTION xlSheetMarginTop      LIB "libxl.dll" CDECL ALIAS "xlSheetMarginTopW"         _
                            (BYVAL sheet AS SheetHandle) AS DOUBLE
DECLARE FUNCTION xlSheetSetMarginTop      LIB "libxl.dll" CDECL ALIAS "xlSheetSetMarginTopW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL margin AS DOUBLE) AS LONG


DECLARE FUNCTION xlSheetMarginBottom      LIB "libxl.dll" CDECL ALIAS "xlSheetMarginBottomW"         _
                            (BYVAL sheet AS SheetHandle) AS DOUBLE
DECLARE FUNCTION xlSheetSetMarginBottom      LIB "libxl.dll" CDECL ALIAS "xlSheetSetMarginBottomW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL margin AS DOUBLE) AS LONG


DECLARE FUNCTION xlSheetPrintRowCol      LIB "libxl.dll" CDECL ALIAS "xlSheetPrintRowColW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetPrintRowCol      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintRowColW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL print AS LONG) AS LONG


DECLARE FUNCTION xlSheetSetPrintRepeatRows      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintRepeatRowsW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetPrintRepeatCols      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintRepeatColsW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG
DECLARE FUNCTION xlSheetSetPrintArea      LIB "libxl.dll" CDECL ALIAS "xlSheetSetPrintAreaW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG


DECLARE FUNCTION xlSheetClearPrintRepeats      LIB "libxl.dll" CDECL ALIAS "xlSheetClearPrintRepeatsW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetClearPrintArea      LIB "libxl.dll" CDECL ALIAS "xlSheetClearPrintAreaW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG


DECLARE FUNCTION xlSheetGetNamedRange      LIB "libxl.dll" CDECL ALIAS "xlSheetGetNamedRangeW"         _
                            (BYVAL sheet AS SheetHandle, BYREF rangeName AS STRINGZ, BYVAL rowFirst AS LONG PTR, BYVAL rowLast AS LONG PTR, BYVAL colFirst AS LONG PTR, BYVAL colLast AS LONG PTR, _
                             BYVAL scopeId AS LONG, BYVAL hidden_ AS LONG PTR ) AS LONG
DECLARE FUNCTION xlSheetSetNamedRange      LIB "libxl.dll" CDECL ALIAS "xlSheetSetNamedRangeW"         _
                            (BYVAL sheet AS SheetHandle, BYREF rangeName AS STRINGZ, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG, BYVAL colFirst AS LONG, BYVAL colLast AS LONG, _
                             BYVAL scopeId AS LONG) AS LONG
DECLARE FUNCTION xlSheetDelNamedRange      LIB "libxl.dll" CDECL ALIAS "xlSheetDelNamedRangeW"         _
                            (BYVAL sheet AS SheetHandle, BYREF rangeName AS STRINGZ, BYVAL scopeId AS LONG) AS LONG

DECLARE FUNCTION xlSheetNamedRangeSize      LIB "libxl.dll" CDECL ALIAS "xlSheetNamedRangeSizeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetNamedRange      LIB "libxl.dll" CDECL ALIAS "xlSheetNamedRangeW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG, BYVAL rowFirst AS LONG PTR, BYVAL rowLast AS LONG PTR, BYVAL colFirst AS LONG PTR, BYVAL colLast AS LONG PTR, _
                             BYVAL scopeId AS LONG, BYVAL hidden_ AS LONG PTR ) AS DWORD


DECLARE FUNCTION xlSheetHyperlinkSize      LIB "libxl.dll" CDECL ALIAS "xlSheetHyperlinkSizeW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetHyperlink      LIB "libxl.dll" CDECL ALIAS "xlSheetHyperlinkW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG, BYVAL rowFirst AS LONG PTR, BYVAL rowLast AS LONG PTR, BYVAL colFirst AS LONG PTR, BYVAL colLast AS LONG PTR) AS DWORD
DECLARE FUNCTION xlSheetDelHyperlink      LIB "libxl.dll" CDECL ALIAS "xlSheetDelHyperlinkW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL index AS LONG) AS LONG
DECLARE FUNCTION xlSheetAddHyperlink      LIB "libxl.dll" CDECL ALIAS "xlSheetAddHyperlinkW"         _
                            (BYVAL sheet AS SheetHandle, BYREF hyperlink AS STRINGZ, BYVAL rowFirst AS LONG, BYVAL rowLast AS LONG, BYVAL colFirst AS LONG, BYVAL colLast AS LONG) AS LONG


DECLARE FUNCTION xlSheetName      LIB "libxl.dll" CDECL ALIAS "xlSheetNameW"         _
                            (BYVAL sheet AS SheetHandle) AS DWORD
DECLARE FUNCTION xlSheetSetName      LIB "libxl.dll" CDECL ALIAS "xlSheetSetNameW"         _
                            (BYVAL sheet AS SheetHandle, BYREF sheetName AS STRINGZ) AS LONG


DECLARE FUNCTION xlSheetProtect      LIB "libxl.dll" CDECL ALIAS "xlSheetProtectW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetProtect      LIB "libxl.dll" CDECL ALIAS "xlSheetSetProtectW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL protect AS LONG) AS LONG


DECLARE FUNCTION xlSheetHidden     LIB "libxl.dll" CDECL ALIAS "xlSheetHiddenW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetHidden     LIB "libxl.dll" CDECL ALIAS "xlSheetSetHiddenW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL hidden AS LONG) AS LONG


DECLARE FUNCTION xlSheetGetTopLeftView     LIB "libxl.dll" CDECL ALIAS "xlSheetGetTopLeftViewW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG PTR, BYVAL col AS LONG PTR) AS LONG
DECLARE FUNCTION xlSheetSetTopLeftView     LIB "libxl.dll" CDECL ALIAS "xlSheetSetTopLeftViewW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG) AS LONG


DECLARE FUNCTION xlSheetRightToLeft     LIB "libxl.dll" CDECL ALIAS "xlSheetRightToLeftW"         _
                            (BYVAL sheet AS SheetHandle) AS LONG
DECLARE FUNCTION xlSheetSetRightToLeft     LIB "libxl.dll" CDECL ALIAS "xlSheetSetRightToLeftW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL rightToLeft AS LONG) AS LONG


DECLARE FUNCTION xlSheetAddrToRowCol     LIB "libxl.dll" CDECL ALIAS "xlSheetAddrToRowColW"         _
                            (BYVAL sheet AS SheetHandle, BYREF addr_ AS STRINGZ, BYVAL row AS LONG PTR, BYVAL col AS LONG PTR, _
                             BYVAL rowRelative AS LONG PTR, BYVAL colRelative AS LONG PTR) AS LONG
DECLARE FUNCTION xlSheetRowColToAddr     LIB "libxl.dll" CDECL ALIAS "xlSheetRowColToAddrW"         _
                            (BYVAL sheet AS SheetHandle, BYVAL row AS LONG, BYVAL col AS LONG, BYVAL rowRelative AS LONG, BYVAL colRelative AS LONG) AS DWORD


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''Format function declarations'''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
DECLARE FUNCTION xlFormatFont    LIB "libxl.dll" CDECL ALIAS "xlFormatFontW"      _
                            (BYVAL format AS FormatHandle) AS FontHandle
DECLARE FUNCTION xlFormatSetFont LIB "libxl.dll" CDECL ALIAS "xlFormatSetFontW"      _
                            (BYVAL format AS FormatHandle, BYVAL font AS FontHandle) AS LONG

DECLARE FUNCTION xlFormatNumFormat    LIB "libxl.dll" CDECL ALIAS "xlFormatNumFormatW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetNumFormat LIB "libxl.dll" CDECL ALIAS "xlFormatSetNumFormatW"      _
                            (BYVAL format AS FormatHandle, BYVAL numFormat AS LONG) AS LONG

DECLARE FUNCTION xlFormatAlignH    LIB "libxl.dll" CDECL ALIAS "xlFormatAlignHW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetAlignH LIB "libxl.dll" CDECL ALIAS "xlFormatSetAlignHW"      _
                            (BYVAL format AS FormatHandle, BYVAL align AS LONG) AS LONG

DECLARE FUNCTION xlFormatAlignV    LIB "libxl.dll" CDECL ALIAS "xlFormatAlignVW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetAlignV LIB "libxl.dll" CDECL ALIAS "xlFormatSetAlignVW"      _
                            (BYVAL format AS FormatHandle, BYVAL align AS LONG) AS LONG

DECLARE FUNCTION xlFormatWrap    LIB "libxl.dll" CDECL ALIAS "xlFormatWrapW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetWrap LIB "libxl.dll" CDECL ALIAS "xlFormatSetWrapW"      _
                            (BYVAL format AS FormatHandle, BYVAL wrap AS LONG) AS LONG

DECLARE FUNCTION xlFormatRotation     LIB "libxl.dll" CDECL ALIAS "xlFormatRotationW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetRotation  LIB "libxl.dll" CDECL ALIAS "xlFormatSetRotationW"      _
                            (BYVAL format AS FormatHandle, BYVAL rotation AS LONG) AS LONG

DECLARE FUNCTION xlFormatIndent     LIB "libxl.dll" CDECL ALIAS "xlFormatIndentW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetIndent  LIB "libxl.dll" CDECL ALIAS "xlFormatSetIndentW"      _
                            (BYVAL format AS FormatHandle, BYVAL indent AS LONG) AS LONG

DECLARE FUNCTION xlFormatShrinkToFit     LIB "libxl.dll" CDECL ALIAS "xlFormatShrinkToFitW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetShrinkToFit  LIB "libxl.dll" CDECL ALIAS "xlFormatSetShrinkToFitW"      _
                            (BYVAL format AS FormatHandle, BYVAL shrinkToFit AS LONG) AS LONG

DECLARE FUNCTION xlFormatSetBorder     LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderW"      _
                            (BYVAL format AS FormatHandle, BYVAL style AS LONG) AS LONG
DECLARE FUNCTION xlFormatSetBorderColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderLeft     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderLeftW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderLeft  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderLeftW"      _
                            (BYVAL format AS FormatHandle, BYVAL style AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderRight     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderRightW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderRight  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderRightW"      _
                            (BYVAL format AS FormatHandle, BYVAL style AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderTop     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderTopW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderTop  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderTopW"      _
                            (BYVAL format AS FormatHandle, BYVAL style AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderBottom     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderBottomW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderBottom  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderBottomW"      _
                            (BYVAL format AS FormatHandle, BYVAL style AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderLeftColor     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderLeftColorW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderLeftColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderLeftColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderRightColor     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderRightColorW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderRightColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderRightColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderTopColor     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderTopColorW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderTopColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderTopColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderBottomColor     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderBottomColorW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderBottomColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderBottomColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderDiagonal     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderDiagonalW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderDiagonal  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderDiagonalW"      _
                            (BYVAL format AS FormatHandle, BYVAL border AS LONG) AS LONG

DECLARE FUNCTION xlFormatBorderDiagonalStyle     LIB "libxl.dll" CDECL ALIAS "xlFormatBorderDiagonalStyleW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetBorderDiagonalStyle  LIB "libxl.dll" CDECL ALIAS "xlFormatSetBorderDiagonalStyleW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatFillPattern     LIB "libxl.dll" CDECL ALIAS "xlFormatFillPatternW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetFillPattern  LIB "libxl.dll" CDECL ALIAS "xlFormatSetFillPatternW"      _
                            (BYVAL format AS FormatHandle, BYVAL pattern AS LONG) AS LONG

DECLARE FUNCTION xlFormatPatternForegroundColor     LIB "libxl.dll" CDECL ALIAS "xlFormatPatternForegroundColorW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetPatternForegroundColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetPatternForegroundColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatPatternBackgroundColor     LIB "libxl.dll" CDECL ALIAS "xlFormatPatternBackgroundColorW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetPatternBackgroundColor  LIB "libxl.dll" CDECL ALIAS "xlFormatSetPatternBackgroundColorW"      _
                            (BYVAL format AS FormatHandle, BYVAL color AS LONG) AS LONG

DECLARE FUNCTION xlFormatLocked     LIB "libxl.dll" CDECL ALIAS "xlFormatLockedW"      _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetLocked  LIB "libxl.dll" CDECL ALIAS "xlFormatSetLockedW"      _
                            (BYVAL format AS FormatHandle, BYVAL locked AS LONG) AS LONG

DECLARE FUNCTION xlFormatHidden     LIB "libxl.dll" CDECL ALIAS "xlFormatHiddenW"         _
                            (BYVAL format AS FormatHandle) AS LONG
DECLARE FUNCTION xlFormatSetHidden  LIB "libxl.dll" CDECL ALIAS "xlFormatSetHiddenW"      _
                            (BYVAL format AS FormatHandle, BYVAL hidden AS LONG) AS LONG

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''''Font function declarations'''''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
DECLARE FUNCTION xlFontSize    LIB "libxl.dll" CDECL ALIAS "xlFontSizeW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetSize LIB "libxl.dll" CDECL ALIAS "xlFontSetSizeW"      _
                            (BYVAL font AS FontHandle, BYVAL fontsize AS LONG) AS LONG

DECLARE FUNCTION xlFontItalic    LIB "libxl.dll" CDECL ALIAS "xlFontItalicW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetItalic LIB "libxl.dll" CDECL ALIAS "xlFontSetItalicW"      _
                            (BYVAL font AS FontHandle, BYVAL italic AS LONG) AS LONG

DECLARE FUNCTION xlFontStrikeOut    LIB "libxl.dll" CDECL ALIAS "xlFontStrikeOutW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetStrikeOut LIB "libxl.dll" CDECL ALIAS "xlFontSetStrikeOutW"      _
                            (BYVAL font AS FontHandle, BYVAL strikeOut AS LONG) AS LONG

DECLARE FUNCTION xlFontColor    LIB "libxl.dll" CDECL ALIAS "xlFontColorW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetColor LIB "libxl.dll" CDECL ALIAS "xlFontSetColorW"      _
                            (BYVAL font AS FontHandle, BYVAL fColor AS LONG) AS LONG

DECLARE FUNCTION xlFontBold    LIB "libxl.dll" CDECL ALIAS "xlFontBoldW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetBold LIB "libxl.dll" CDECL ALIAS "xlFontSetBoldW"      _
                            (BYVAL font AS FontHandle, BYVAL bold AS LONG) AS LONG

DECLARE FUNCTION xlFontScript    LIB "libxl.dll" CDECL ALIAS "xlFontScriptW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetScript LIB "libxl.dll" CDECL ALIAS "xlFontSetScriptW"      _
                            (BYVAL font AS FontHandle, BYVAL script AS LONG) AS LONG

DECLARE FUNCTION xlFontUnderline    LIB "libxl.dll" CDECL ALIAS "xlFontUnderlineW"      _
                            (BYVAL font AS FontHandle) AS LONG
DECLARE FUNCTION xlFontSetUnderline LIB "libxl.dll" CDECL ALIAS "xlFontSetUnderlineW"      _
                            (BYVAL font AS FontHandle, BYVAL underline AS LONG) AS LONG

DECLARE FUNCTION xlFontName    LIB "libxl.dll" CDECL ALIAS "xlFontNameW"      _
                            (ByVal Font As FontHandle) As Dword
DECLARE FUNCTION xlFontSetName LIB "libxl.dll" CDECL ALIAS "xlFontSetNameW"      _
                            (BYVAL font AS FontHandle, BYREF fontName AS STRINGZ) AS LONG
