Attribute VB_Name = "xlDeclaration"
Option Explicit
'''''''''''''''''''''''
'' Factory functions
Declare Function xlCreateBook Lib "libxl.dll" Alias "xlCreateBookA" () As Long
'' Create a binary book instance for xls format. This function should be called first for receiving a book handler.
Declare Function xlCreateXMLBook Lib "libxl.dll" Alias "xlCreateXMLBookA" () As Long
'' Create a xml book instance for xlsx format. This function should be called first for receiving a book handler.
'' Book functions
Declare Function xlBookLoad Lib "libxl.dll" Alias "xlBookLoadA" (ByVal bookHandle As Long, ByVal filename As String) As Integer
Declare Function xlBookSave Lib "libxl.dll" Alias "xlBookSaveA" (ByVal bookHandle As Long, ByVal filename As String) As Integer
Declare Function xlBookLoadRaw Lib "libxl.dll" Alias "xlBookLoadRawA" (ByVal bookHandle As Long, ByVal data As String, ByVal size As Integer) As Integer
Declare Function xlBookSaveRaw Lib "libxl.dll" Alias "xlBookSaveRawA" (ByVal bookHandle As Long, ByRef data As String, ByRef size As Integer) As Integer
Declare Function xlBookAddSheet Lib "libxl.dll" Alias "xlBookAddSheetA" (ByVal bookHandle As Long, ByVal name As String, ByVal sheetHandle As Long) As Long
Declare Function xlBookInsertSheet Lib "libxl.dll" Alias "xlBookInsertSheetA" (ByVal bookHandle As Long, ByVal index As Integer, ByVal name As String, ByVal sheetHandle As Long) As Long
Declare Function xlBookGetSheet Lib "libxl.dll" Alias "xlBookGetSheetA" (ByVal bookHandle As Long, ByVal index As Integer) As Long
Declare Function xlBookSheetType Lib "libxl.dll" Alias "xlBookSheetTypeA" (ByVal bookHandle As Long, ByVal index As Integer) As Integer
Declare Function xlBookDelSheet Lib "libxl.dll" Alias "xlBookDelSheetA" (ByVal bookHandle As Long, ByVal index As Integer) As Integer
Declare Function xlBookSheetCount Lib "libxl.dll" Alias "xlBookSheetCountA" (ByVal bookHandle As Long) As Integer
Declare Function xlBookAddFormat Lib "libxl.dll" Alias "xlBookAddFormatA" (ByVal bookHandle As Long, ByVal formatHandle As Long) As Long
Declare Function xlBookAddFont Lib "libxl.dll" Alias "xlBookAddFontA" (ByVal bookHandle As Long, ByVal fontHandle As Long) As Long
Declare Function xlBookAddCustomNumFormat Lib "libxl.dll" Alias "xlBookAddCustomNumFormatA" (ByVal bookHandle As Long, ByVal customNumFormat As String) As Integer
Declare Function xlBookCustomNumFormat Lib "libxl.dll" Alias "xlBookCustomNumFormatA" (ByVal bookHandle As Long, ByVal fmt As Integer) As String
Declare Function xlBookFormat Lib "libxl.dll" Alias "xlBookFormatA" (ByVal bookHandle As Long, ByVal index As Integer) As Long
Declare Function xlBookFormatSize Lib "libxl.dll" Alias "xlBookFormatSizeA" (ByVal bookHandle As Long) As Integer
Declare Function xlBookFont Lib "libxl.dll" Alias "xlBookFontA" (ByVal bookHandle As Long, ByVal index As Integer) As Long
Declare Function xlBookFontSize Lib "libxl.dll" Alias "xlBookFontSizeA" (ByVal bookHandle As Long) As Integer
Declare Function xlBookDatePack Lib "libxl.dll" Alias "xlBookDatePackA" (ByVal bookHandle As Long, ByVal year As Integer, ByVal month As Integer, ByVal day As Integer, ByVal hour As Integer, ByVal min As Integer, ByVal sec As Integer, ByVal msec As Integer) As Double
Declare Function xlBookDateUnpack Lib "libxl.dll" Alias "xlBookDateUnpackA" (ByVal bookHandle As Long, ByVal value As Double, ByRef year As Integer, ByRef month As Integer, ByRef day As Integer, ByRef hour As Integer, ByRef min As Integer, ByRef sec As Integer, ByRef msec As Integer) As Integer
Declare Function xlBookColorPack Lib "libxl.dll" Alias "xlBookColorPackA" (ByVal bookHandle As Long, ByVal red As Integer, ByVal green As Integer, ByVal blue As Integer) As Integer
Declare Sub xlBookColorUnpack Lib "libxl.dll" Alias "xlBookColorUnpackA" (ByVal bookHandle As Long, ByVal color As Integer, ByRef red As Integer, ByRef green As Integer, ByRef blue As Integer)
Declare Function xlBookActiveSheet Lib "libxl.dll" Alias "xlBookActiveSheetA" (ByVal bookHandle As Long) As Integer
Declare Sub xlBookSetActiveSheet Lib "libxl.dll" Alias "xlBookSetActiveSheetA" (ByVal bookHandle As Long, ByVal index As Integer)
Declare Function xlBookPictureSize Lib "libxl.dll" Alias "xlBookPictureSizeA" (ByVal bookHandle As Long) As Integer
Declare Function xlBookGetPicture Lib "libxl.dll" Alias "xlBookGetPictureA" (ByVal bookHandle As Long, ByVal index As Integer, ByRef data As String, ByRef size As Integer) As Integer
Declare Function xlBookAddPicture Lib "libxl.dll" Alias "xlBookAddPictureA" (ByVal bookHandle As Long, ByVal filename As String) As Integer
Declare Function xlBookAddPicture2 Lib "libxl.dll" Alias "xlBookAddPicture2A" (ByVal bookHandle As Long, ByVal data As String, ByVal size As Integer) As Integer
Declare Function xlBookDefaultFont Lib "libxl.dll" Alias "xlBookDefaultFontA" (ByVal bookHandle As Long, ByRef fontSize As Integer) As String
Declare Sub xlBookSetDefaultFont Lib "libxl.dll" Alias "xlBookSetDefaultFontA" (ByVal bookHandle As Long, ByVal fontName As String, ByVal fontSize As Integer)
Declare Function xlBookRgbMode Lib "libxl.dll" Alias "xlBookRgbModeA" (ByVal bookHandle As Long) As Integer
Declare Sub xlBookSetRgbMode Lib "libxl.dll" Alias "xlBookSetRgbModeA" (ByVal bookHandle As Long, ByVal rgbMode As Integer)
Declare Function xlBookRefR1C1 Lib "libxl.dll" Alias "xlBookRefR1C1A" (ByVal bookHandle As Long) As Integer
Declare Sub xlBookSetRefR1C1 Lib "libxl.dll" Alias "xlBookSetRefR1C1A" (ByVal bookHandle As Long, ByVal refR1C1 As Integer)
Declare Function xlBookBiffVersion Lib "libxl.dll" Alias "xlBookBiffVersionA" (ByVal bookHandle As Long) As Integer
Declare Function xlBookIsDate1904 Lib "libxl.dll" Alias "xlBookIsDate1904A" (ByVal bookHandle As Long) As Integer
Declare Sub xlBookSetDate1904 Lib "libxl.dll" Alias "xlBookSetDate1904A" (ByVal bookHandle As Long, ByVal date1904 As Integer)
Declare Function xlBookIsTemplate Lib "libxl.dll" Alias "xlBookIsTemplateA" (ByVal bookHandle As Long) As Integer
Declare Sub xlBookSetTemplate Lib "libxl.dll" Alias "xlBookSetTemplateA" (ByVal bookHandle As Long, ByVal tmpl As Integer)
Declare Sub xlBookSetKey Lib "libxl.dll" Alias "xlBookSetKeyA" (ByVal bookHandle As Long, ByVal name As String, ByVal key As String)
Declare Function xlBookSetLocale Lib "libxl.dll" Alias "xlBookSetLocaleA" (ByVal bookHandle As Long, ByVal locale As String) As Integer
Declare Function xlBookErrorMessage Lib "libxl.dll" Alias "xlBookErrorMessageA" (ByVal bookHandle As Long) As String
Declare Sub xlBookRelease Lib "libxl.dll" Alias "xlBookReleaseA" (ByVal bookHandle As Long)
'' Sheet functions
Declare Function xlSheetCellType Lib "libxl.dll" Alias "xlSheetCellTypeA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As Integer
Declare Function xlSheetIsFormula Lib "libxl.dll" Alias "xlSheetIsFormulaA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As Integer
Declare Function xlSheetCellFormat Lib "libxl.dll" Alias "xlSheetCellFormatA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As Long
Declare Sub xlSheetSetCellFormat Lib "libxl.dll" Alias "xlSheetSetCellFormatA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal formatHandle As Long)
Declare Function xlSheetReadStr Lib "libxl.dll" Alias "xlSheetReadStrA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByRef format As Long) As String
Declare Function xlSheetWriteStr Lib "libxl.dll" Alias "xlSheetWriteStrA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal value As String, ByVal formatHandle As Long) As Integer
Declare Function xlSheetReadNum Lib "libxl.dll" Alias "xlSheetReadNumA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByRef format As Long) As Double
Declare Function xlSheetWriteNum Lib "libxl.dll" Alias "xlSheetWriteNumA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal value As Double, ByVal formatHandle As Long) As Integer
Declare Function xlSheetReadBool Lib "libxl.dll" Alias "xlSheetReadBoolA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByRef format As Long) As Integer
Declare Function xlSheetWriteBool Lib "libxl.dll" Alias "xlSheetWriteBoolA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal value As Integer, ByVal formatHandle As Long) As Integer
Declare Function xlSheetReadBlank Lib "libxl.dll" Alias "xlSheetReadBlankA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByRef format As Long) As Integer
Declare Function xlSheetWriteBlank Lib "libxl.dll" Alias "xlSheetWriteBlankA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal formatHandle As Long) As Integer
Declare Function xlSheetReadFormula Lib "libxl.dll" Alias "xlSheetReadFormulaA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByRef format As Long) As String
Declare Function xlSheetWriteFormula Lib "libxl.dll" Alias "xlSheetWriteFormulaA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal value As String, ByVal formatHandle As Long) As Integer
Declare Function xlSheetReadComment Lib "libxl.dll" Alias "xlSheetReadCommentA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As String
Declare Sub xlSheetWriteComment Lib "libxl.dll" Alias "xlSheetWriteCommentA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal value As String, ByVal author As String, ByVal width As Integer, ByVal height As Integer)
Declare Function xlSheetIsDate Lib "libxl.dll" Alias "xlSheetIsDateA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As Integer
Declare Function xlSheetReadError Lib "libxl.dll" Alias "xlSheetReadErrorA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As Integer
Declare Function xlSheetColWidth Lib "libxl.dll" Alias "xlSheetColWidthA" (ByVal sheetHandle As Long, ByVal col As Integer) As Double
Declare Function xlSheetRowHeight Lib "libxl.dll" Alias "xlSheetRowHeightA" (ByVal sheetHandle As Long, ByVal row As Integer) As Double
Declare Function xlSheetSetCol Lib "libxl.dll" Alias "xlSheetSetColA" (ByVal sheetHandle As Long, ByVal colFirst As Integer, ByVal colLast As Integer, ByVal width As Double, ByVal formatHandle As Long, ByVal hidden As Integer) As Integer
Declare Function xlSheetSetRow Lib "libxl.dll" Alias "xlSheetSetRowA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal height As Double, ByVal formatHandle As Long, ByVal hidden As Integer) As Integer
Declare Function xlSheetRowHidden Lib "libxl.dll" Alias "xlSheetRowHiddenA" (ByVal sheetHandle As Long, ByVal row As Integer) As Integer
Declare Function xlSheetSetRowHidden Lib "libxl.dll" Alias "xlSheetSetRowHiddenA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal hidden As Integer) As Integer
Declare Function xlSheetColHidden Lib "libxl.dll" Alias "xlSheetColHiddenA" (ByVal sheetHandle As Long, ByVal col As Integer) As Integer
Declare Function xlSheetSetColHidden Lib "libxl.dll" Alias "xlSheetSetColHiddenA" (ByVal sheetHandle As Long, ByVal col As Integer, ByVal hidden As Integer) As Integer
Declare Function xlSheetGetMerge Lib "libxl.dll" Alias "xlSheetGetMergeA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByRef rowFirst As Integer, ByRef rowLast As Integer, ByRef colFirst As Integer, ByRef colLast As Integer) As Integer
Declare Function xlSheetSetMerge Lib "libxl.dll" Alias "xlSheetSetMergeA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer, ByVal colFirst As Integer, ByVal colLast As Integer) As Integer
Declare Function xlSheetDelMerge Lib "libxl.dll" Alias "xlSheetDelMergeA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer) As Integer
Declare Function xlSheetMergeSize Lib "libxl.dll" Alias "xlSheetMergeSizeA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetMerge Lib "libxl.dll" Alias "xlSheetMergeA" (ByVal sheetHandle As Long, ByVal index As Integer, ByRef rowFirst As Integer, ByRef rowLast As Integer, ByRef colFirst As Integer, ByRef colLast As Integer) As Integer
Declare Function xlSheetDelMergeByIndex Lib "libxl.dll" Alias "xlSheetDelMergeByIndexA" (ByVal sheetHandle As Long, ByVal index As Integer) As Integer
Declare Function xlSheetPictureSize Lib "libxl.dll" Alias "xlSheetPictureSizeA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetGetPicture Lib "libxl.dll" Alias "xlSheetGetPictureA" (ByVal sheetHandle As Long, ByVal index As Integer, ByRef rowTop As Integer, ByRef colLeft As Integer, ByRef rowBottom As Integer, ByRef colRight As Integer, ByRef width As Integer, ByRef height As Integer, ByRef offset_x As Integer, ByRef offset_y As Integer) As Integer
Declare Sub xlSheetSetPicture Lib "libxl.dll" Alias "xlSheetSetPictureA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal pictureId As Integer, ByVal scaleX As Double, ByVal offset_x As Integer, ByVal offset_y As Integer)
Declare Sub xlSheetSetPicture2 Lib "libxl.dll" Alias "xlSheetSetPicture2A" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal pictureId As Integer, ByVal width As Integer, ByVal height As Integer, ByVal offset_x As Integer, ByVal offset_y As Integer)
Declare Function xlSheetGetHorPageBreak Lib "libxl.dll" Alias "xlSheetGetHorPageBreakA" (ByVal sheetHandle As Long, ByVal index As Integer) As Integer
Declare Function xlSheetGetHorPageBreakSize Lib "libxl.dll" Alias "xlSheetGetHorPageBreakSizeA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetGetVerPageBreak Lib "libxl.dll" Alias "xlSheetGetVerPageBreakA" (ByVal sheetHandle As Long, ByVal index As Integer) As Integer
Declare Function xlSheetGetVerPageBreakSize Lib "libxl.dll" Alias "xlSheetGetVerPageBreakSizeA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetSetHorPageBreak Lib "libxl.dll" Alias "xlSheetSetHorPageBreakA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal pageBreak As Integer) As Integer
Declare Function xlSheetSetVerPageBreak Lib "libxl.dll" Alias "xlSheetSetVerPageBreakA" (ByVal sheetHandle As Long, ByVal col As Integer, ByVal pageBreak As Integer) As Integer
Declare Sub xlSheetSplit Lib "libxl.dll" Alias "xlSheetSplitA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer)
Declare Function xlSheetSplitInfo Lib "libxl.dll" Alias "xlSheetSplitInfoA" (ByVal sheetHandle As Long, ByRef row As Integer, ByRef col As Integer) As Boolean
Declare Function xlSheetGroupRows Lib "libxl.dll" Alias "xlSheetGroupRowsA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer, ByVal collapsed As Integer) As Integer
Declare Function xlSheetGroupCols Lib "libxl.dll" Alias "xlSheetGroupColsA" (ByVal sheetHandle As Long, ByVal colFirst As Integer, ByVal colLast As Integer, ByVal collapsed As Integer) As Integer
Declare Function xlSheetGroupSummaryBelow Lib "libxl.dll" Alias "xlSheetGroupSummaryBelowA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetGroupSummaryBelow Lib "libxl.dll" Alias "xlSheetSetGroupSummaryBelowA" (ByVal sheetHandle As Long, ByVal below As Integer)
Declare Function xlSheetGroupSummaryRight Lib "libxl.dll" Alias "xlSheetGroupSummaryRightA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetGroupSummaryRight Lib "libxl.dll" Alias "xlSheetSetGroupSummaryRightA" (ByVal sheetHandle As Long, ByVal right As Integer)
Declare Sub xlSheetClear Lib "libxl.dll" Alias "xlSheetClearA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer, ByVal colFirst As Integer, ByVal colLast As Integer)
Declare Function xlSheetInsertRow Lib "libxl.dll" Alias "xlSheetInsertRowA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer) As Integer
Declare Function xlSheetInsertCol Lib "libxl.dll" Alias "xlSheetInsertColA" (ByVal sheetHandle As Long, ByVal colFirst As Integer, ByVal colLast As Integer) As Integer
Declare Function xlSheetRemoveRow Lib "libxl.dll" Alias "xlSheetRemoveRowA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer) As Integer
Declare Function xlSheetRemoveCol Lib "libxl.dll" Alias "xlSheetRemoveColA" (ByVal sheetHandle As Long, ByVal colFirst As Integer, ByVal colLast As Integer) As Integer
Declare Function xlSheetCopyCell Lib "libxl.dll" Alias "xlSheetCopyCellA" (ByVal sheetHandle As Long, ByVal rowSrc As Integer, ByVal colSrc As Integer, ByVal rowDst As Integer, ByVal colDst As Integer) As Integer
Declare Function xlSheetFirstRow Lib "libxl.dll" Alias "xlSheetFirstRowA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetLastRow Lib "libxl.dll" Alias "xlSheetLastRowA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetFirstCol Lib "libxl.dll" Alias "xlSheetFirstColA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetLastCol Lib "libxl.dll" Alias "xlSheetLastColA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetDisplayGridlines Lib "libxl.dll" Alias "xlSheetDisplayGridlinesA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetDisplayGridlines Lib "libxl.dll" Alias "xlSheetSetDisplayGridlinesA" (ByVal sheetHandle As Long, ByVal show As Integer)
Declare Function xlSheetPrintGridlines Lib "libxl.dll" Alias "xlSheetPrintGridlinesA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetPrintGridlines Lib "libxl.dll" Alias "xlSheetSetPrintGridlinesA" (ByVal sheetHandle As Long, ByVal printX As Integer)
Declare Function xlSheetZoom Lib "libxl.dll" Alias "xlSheetZoomA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetZoom Lib "libxl.dll" Alias "xlSheetSetZoomA" (ByVal sheetHandle As Long, ByVal zoom As Integer)
Declare Function xlSheetPrintZoom Lib "libxl.dll" Alias "xlSheetPrintZoomA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetPrintZoom Lib "libxl.dll" Alias "xlSheetSetPrintZoomA" (ByVal sheetHandle As Long, ByVal zoom As Integer)
Declare Function xlSheetLandscape Lib "libxl.dll" Alias "xlSheetLandscapeA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetLandscape Lib "libxl.dll" Alias "xlSheetSetLandscapeA" (ByVal sheetHandle As Long, ByVal landscape As Integer)
Declare Function xlSheetGetPrintFit Lib "libxl.dll" Alias "xlSheetGetPrintFitA" (ByVal sheetHandle As Long, ByRef wPages As Integer, ByRef hPages As Integer) As Integer
Declare Sub xlSheetSetPrintFit Lib "libxl.dll" Alias "xlSheetSetPrintFitA" (ByVal sheetHandle As Long, ByVal wPages As Integer, ByVal hPages As Integer)
Declare Function xlSheetPaper Lib "libxl.dll" Alias "xlSheetPaperA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetPaper Lib "libxl.dll" Alias "xlSheetSetPaperA" (ByVal sheetHandle As Long, ByVal paper As Integer)
Declare Function xlSheetHeader Lib "libxl.dll" Alias "xlSheetHeaderA" (ByVal sheetHandle As Long) As String
Declare Function xlSheetSetHeader Lib "libxl.dll" Alias "xlSheetSetHeaderA" (ByVal sheetHandle As Long, ByVal header As String, ByVal margin As Double) As Integer
Declare Function xlSheetHeaderMargin Lib "libxl.dll" Alias "xlSheetHeaderMarginA" (ByVal sheetHandle As Long) As Double
Declare Function xlSheetFooter Lib "libxl.dll" Alias "xlSheetFooterA" (ByVal sheetHandle As Long) As String
Declare Function xlSheetSetFooter Lib "libxl.dll" Alias "xlSheetSetFooterA" (ByVal sheetHandle As Long, ByVal footer As String, ByVal margin As Double) As Integer
Declare Function xlSheetFooterMargin Lib "libxl.dll" Alias "xlSheetFooterMarginA" (ByVal sheetHandle As Long) As Double
Declare Function xlSheetHCenter Lib "libxl.dll" Alias "xlSheetHCenterA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetHCenter Lib "libxl.dll" Alias "xlSheetSetHCenterA" (ByVal sheetHandle As Long, ByVal hCenter As Integer)
Declare Function xlSheetVCenter Lib "libxl.dll" Alias "xlSheetVCenterA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetVCenter Lib "libxl.dll" Alias "xlSheetSetVCenterA" (ByVal sheetHandle As Long, ByVal vCenter As Integer)
Declare Function xlSheetMarginLeft Lib "libxl.dll" Alias "xlSheetMarginLeftA" (ByVal sheetHandle As Long) As Double
Declare Sub xlSheetSetMarginLeft Lib "libxl.dll" Alias "xlSheetSetMarginLeftA" (ByVal sheetHandle As Long, ByVal margin As Double)
Declare Function xlSheetMarginRight Lib "libxl.dll" Alias "xlSheetMarginRightA" (ByVal sheetHandle As Long) As Double
Declare Sub xlSheetSetMarginRight Lib "libxl.dll" Alias "xlSheetSetMarginRightA" (ByVal sheetHandle As Long, ByVal margin As Double)
Declare Function xlSheetMarginTop Lib "libxl.dll" Alias "xlSheetMarginTopA" (ByVal sheetHandle As Long) As Double
Declare Sub xlSheetSetMarginTop Lib "libxl.dll" Alias "xlSheetSetMarginTopA" (ByVal sheetHandle As Long, ByVal margin As Double)
Declare Function xlSheetMarginBottom Lib "libxl.dll" Alias "xlSheetMarginBottomA" (ByVal sheetHandle As Long) As Double
Declare Sub xlSheetSetMarginBottom Lib "libxl.dll" Alias "xlSheetSetMarginBottomA" (ByVal sheetHandle As Long, ByVal margin As Double)
Declare Function xlSheetPrintRowCol Lib "libxl.dll" Alias "xlSheetPrintRowColA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetPrintRowCol Lib "libxl.dll" Alias "xlSheetSetPrintRowColA" (ByVal sheetHandle As Long, ByVal printX As Integer)
Declare Function xlSheetPrintRepeatRows Lib "libxl.dll" Alias "xlSheetPrintRepeatRowsA" (ByVal sheetHandle As Long, ByRef rowFirst As Integer, ByRef rowLast As Integer) As Integer
Declare Sub xlSheetSetPrintRepeatRows Lib "libxl.dll" Alias "xlSheetSetPrintRepeatRowsA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer)
Declare Function xlSheetPrintRepeatCols Lib "libxl.dll" Alias "xlSheetPrintRepeatColsA" (ByVal sheetHandle As Long, ByRef colFirst As Integer, ByRef colLast As Integer) As Integer
Declare Sub xlSheetSetPrintRepeatCols Lib "libxl.dll" Alias "xlSheetSetPrintRepeatColsA" (ByVal sheetHandle As Long, ByVal colFirst As Integer, ByVal colLast As Integer)
Declare Function xlSheetPrintArea Lib "libxl.dll" Alias "xlSheetPrintAreaA" (ByVal sheetHandle As Long, ByRef rowFirst As Integer, ByRef rowLast As Integer, ByRef colFirst As Integer, ByRef colLast As Integer) As Integer
Declare Sub xlSheetSetPrintArea Lib "libxl.dll" Alias "xlSheetSetPrintAreaA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal rowLast As Integer, ByVal colFirst As Integer, ByVal colLast As Integer)
Declare Sub xlSheetClearPrintRepeats Lib "libxl.dll" Alias "xlSheetClearPrintRepeatsA" (ByVal sheetHandle As Long)
Declare Sub xlSheetClearPrintArea Lib "libxl.dll" Alias "xlSheetClearPrintAreaA" (ByVal sheetHandle As Long)
Declare Function xlSheetGetNamedRange Lib "libxl.dll" Alias "xlSheetGetNamedRangeA" (ByVal sheetHandle As Long, ByVal name As String, ByRef rowFirst As Integer, ByRef rowLast As Integer, ByRef colFirst As Integer, ByRef colLast As Integer, ByVal scopeId As Integer, ByRef hidden As Integer) As Integer
Declare Function xlSheetSetNamedRange Lib "libxl.dll" Alias "xlSheetSetNamedRangeA" (ByVal sheetHandle As Long, ByVal name As String, ByVal rowFirst As Integer, ByVal rowLast As Integer, ByVal colFirst As Integer, ByVal colLast As Integer, ByVal scopeId As Integer) As Integer
Declare Function xlSheetDelNamedRange Lib "libxl.dll" Alias "xlSheetDelNamedRangeA" (ByVal sheetHandle As Long, ByVal name As String, ByVal scopeId As Integer) As Integer
Declare Function xlSheetNamedRangeSize Lib "libxl.dll" Alias "xlSheetNamedRangeSizeA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetNamedRange Lib "libxl.dll" Alias "xlSheetNamedRangeA" (ByVal sheetHandle As Long, ByVal index As Integer, ByRef rowFirst As Integer, ByRef rowLast As Integer, ByRef colFirst As Integer, ByRef colLast As Integer, ByRef scopeId As Integer, ByRef hidden As Integer) As String
Declare Function xlSheetHyperlinkSize Lib "libxl.dll" Alias "xlSheetHyperlinkSizeA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetHyperlink Lib "libxl.dll" Alias "xlSheetHyperlinkA" (ByVal sheetHandle As Long, ByVal index As Integer, ByRef rowFirst As Integer, ByRef rowLast As Integer, ByRef colFirst As Integer, ByRef colLast As Integer) As String
Declare Function xlSheetDelHyperlink Lib "libxl.dll" Alias "xlSheetDelHyperlinkA" (ByVal sheetHandle As Long, ByVal index As Integer) As Integer
Declare Sub xlSheetAddHyperlink Lib "libxl.dll" Alias "xlSheetAddHyperlinkA" (ByVal sheetHandle As Long, ByVal hyperlink As String, ByVal rowFirst As Integer, ByVal rowLast As Integer, ByVal colFirst As Integer, ByVal colLast As Integer)
Declare Function xlSheetName Lib "libxl.dll" Alias "xlSheetNameA" (ByVal sheetHandle As Long) As String
Declare Sub xlSheetSetName Lib "libxl.dll" Alias "xlSheetSetNameA" (ByVal sheetHandle As Long, ByVal name As String)
Declare Function xlSheetProtect Lib "libxl.dll" Alias "xlSheetProtectA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetProtect Lib "libxl.dll" Alias "xlSheetSetProtectA" (ByVal sheetHandle As Long, ByVal protect As Integer)
Declare Function xlSheetRightToLeft Lib "libxl.dll" Alias "xlSheetRightToLeftA" (ByVal sheetHandle As Long) As Integer
Declare Sub xlSheetSetRightToLeft Lib "libxl.dll" Alias "xlSheetSetRightToLeftA" (ByVal sheetHandle As Long, ByVal rightToLeft As Integer)
Declare Function xlSheetHidden Lib "libxl.dll" Alias "xlSheetHiddenA" (ByVal sheetHandle As Long) As Integer
Declare Function xlSheetSetHidden Lib "libxl.dll" Alias "xlSheetSetHiddenA" (ByVal sheetHandle As Long, ByVal hidden As Integer) As Integer
Declare Sub xlSheetGetTopLeftView Lib "libxl.dll" Alias "xlSheetGetTopLeftViewA" (ByVal sheetHandle As Long, ByRef row As Integer, ByRef col As Integer)
Declare Sub xlSheetSetTopLeftView Lib "libxl.dll" Alias "xlSheetSetTopLeftViewA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer)
Declare Sub xlSheetSetAutoFitArea Lib "libxl.dll" Alias "xlSheetSetAutoFitAreaA" (ByVal sheetHandle As Long, ByVal rowFirst As Integer, ByVal colFirst As Integer, ByVal rowLast As Integer, ByVal colLast As Integer)
Declare Sub xlSheetAddrToRowCol Lib "libxl.dll" Alias "xlSheetAddrToRowColA" (ByVal sheetHandle As Long, ByVal addr As String, ByRef row As Integer, ByRef col As Integer, ByRef rowRelative As Integer, ByRef colRelative As Integer)
Declare Function xlSheetRowColToAddr Lib "libxl.dll" Alias "xlSheetRowColToAddrA" (ByVal sheetHandle As Long, ByVal row As Integer, ByVal col As Integer, ByVal rowRelative As Integer, ByVal colRelative As Integer) As String
'' Format functions
Declare Function xlFormatFont Lib "libxl.dll" Alias "xlFormatFontA" (ByVal formatHandle As Long) As Long
Declare Function xlFormatSetFont Lib "libxl.dll" Alias "xlFormatSetFontA" (ByVal formatHandle As Long, ByVal fontHandle As Long) As Integer
Declare Function xlFormatNumFormat Lib "libxl.dll" Alias "xlFormatNumFormatA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetNumFormat Lib "libxl.dll" Alias "xlFormatSetNumFormatA" (ByVal formatHandle As Long, ByVal numFormat As Integer)
Declare Function xlFormatAlignH Lib "libxl.dll" Alias "xlFormatAlignHA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetAlignH Lib "libxl.dll" Alias "xlFormatSetAlignHA" (ByVal formatHandle As Long, ByVal align As Integer)
Declare Function xlFormatAlignV Lib "libxl.dll" Alias "xlFormatAlignVA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetAlignV Lib "libxl.dll" Alias "xlFormatSetAlignVA" (ByVal formatHandle As Long, ByVal align As Integer)
Declare Function xlFormatWrap Lib "libxl.dll" Alias "xlFormatWrapA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetWrap Lib "libxl.dll" Alias "xlFormatSetWrapA" (ByVal formatHandle As Long, ByVal wrap As Integer)
Declare Function xlFormatRotation Lib "libxl.dll" Alias "xlFormatRotationA" (ByVal formatHandle As Long) As Integer
Declare Function xlFormatSetRotation Lib "libxl.dll" Alias "xlFormatSetRotationA" (ByVal handle As Long, ByVal rotation As Integer) As Integer
Declare Function xlFormatIndent Lib "libxl.dll" Alias "xlFormatIndentA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetIndent Lib "libxl.dll" Alias "xlFormatSetIndentA" (ByVal formatHandle As Long, ByVal indent As Integer)
Declare Function xlFormatShrinkToFit Lib "libxl.dll" Alias "xlFormatShrinkToFitA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetShrinkToFit Lib "libxl.dll" Alias "xlFormatSetShrinkToFitA" (ByVal formatHandle As Long, ByVal shrinkToFit As Integer)
Declare Sub xlFormatSetBorder Lib "libxl.dll" Alias "xlFormatSetBorderA" (ByVal formatHandle As Long, ByVal style As Integer)
Declare Sub xlFormatSetBorderColor Lib "libxl.dll" Alias "xlFormatSetBorderColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatBorderLeft Lib "libxl.dll" Alias "xlFormatBorderLeftA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderLeft Lib "libxl.dll" Alias "xlFormatSetBorderLeftA" (ByVal formatHandle As Long, ByVal style As Integer)
Declare Function xlFormatBorderRight Lib "libxl.dll" Alias "xlFormatBorderRightA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderRight Lib "libxl.dll" Alias "xlFormatSetBorderRightA" (ByVal formatHandle As Long, ByVal style As Integer)
Declare Function xlFormatBorderTop Lib "libxl.dll" Alias "xlFormatBorderTopA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderTop Lib "libxl.dll" Alias "xlFormatSetBorderTopA" (ByVal formatHandle As Long, ByVal style As Integer)
Declare Function xlFormatBorderBottom Lib "libxl.dll" Alias "xlFormatBorderBottomA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderBottom Lib "libxl.dll" Alias "xlFormatSetBorderBottomA" (ByVal formatHandle As Long, ByVal style As Integer)
Declare Function xlFormatBorderLeftColor Lib "libxl.dll" Alias "xlFormatBorderLeftColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderLeftColor Lib "libxl.dll" Alias "xlFormatSetBorderLeftColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatBorderRightColor Lib "libxl.dll" Alias "xlFormatBorderRightColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderRightColor Lib "libxl.dll" Alias "xlFormatSetBorderRightColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatBorderTopColor Lib "libxl.dll" Alias "xlFormatBorderTopColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderTopColor Lib "libxl.dll" Alias "xlFormatSetBorderTopColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatBorderBottomColor Lib "libxl.dll" Alias "xlFormatBorderBottomColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderBottomColor Lib "libxl.dll" Alias "xlFormatSetBorderBottomColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatBorderDiagonal Lib "libxl.dll" Alias "xlFormatBorderDiagonalA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderDiagonal Lib "libxl.dll" Alias "xlFormatSetBorderDiagonalA" (ByVal formatHandle As Long, ByVal border As Integer)
Declare Function xlFormatBorderDiagonalStyle Lib "libxl.dll" Alias "xlFormatBorderDiagonalStyleA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderDiagonalStyle Lib "libxl.dll" Alias "xlFormatSetBorderDiagonalStyleA" (ByVal formatHandle As Long, ByVal style As Integer)
Declare Function xlFormatBorderDiagonalColor Lib "libxl.dll" Alias "xlFormatBorderDiagonalColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetBorderDiagonalColor Lib "libxl.dll" Alias "xlFormatSetBorderDiagonalColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatFillPattern Lib "libxl.dll" Alias "xlFormatFillPatternA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetFillPattern Lib "libxl.dll" Alias "xlFormatSetFillPatternA" (ByVal formatHandle As Long, ByVal pattern As Integer)
Declare Function xlFormatPatternForegroundColor Lib "libxl.dll" Alias "xlFormatPatternForegroundColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetPatternForegroundColor Lib "libxl.dll" Alias "xlFormatSetPatternForegroundColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatPatternBackgroundColor Lib "libxl.dll" Alias "xlFormatPatternBackgroundColorA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetPatternBackgroundColor Lib "libxl.dll" Alias "xlFormatSetPatternBackgroundColorA" (ByVal formatHandle As Long, ByVal color As Integer)
Declare Function xlFormatLocked Lib "libxl.dll" Alias "xlFormatLockedA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetLocked Lib "libxl.dll" Alias "xlFormatSetLockedA" (ByVal formatHandle As Long, ByVal locked As Integer)
Declare Function xlFormatHidden Lib "libxl.dll" Alias "xlFormatHiddenA" (ByVal formatHandle As Long) As Integer
Declare Sub xlFormatSetHidden Lib "libxl.dll" Alias "xlFormatSetHiddenA" (ByVal formatHandle As Long, ByVal hidden As Integer)
'' Font functions
Declare Function xlFontSize Lib "libxl.dll" Alias "xlFontSizeA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetSize Lib "libxl.dll" Alias "xlFontSetSizeA" (ByVal fontHandle As Long, ByVal size As Integer)
Declare Function xlFontItalic Lib "libxl.dll" Alias "xlFontItalicA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetItalic Lib "libxl.dll" Alias "xlFontSetItalicA" (ByVal fontHandle As Long, ByVal italic As Integer)
Declare Function xlFontStrikeOut Lib "libxl.dll" Alias "xlFontStrikeOutA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetStrikeOut Lib "libxl.dll" Alias "xlFontSetStrikeOutA" (ByVal fontHandle As Long, ByVal strikeOut As Integer)
Declare Function xlFontColor Lib "libxl.dll" Alias "xlFontColorA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetColor Lib "libxl.dll" Alias "xlFontSetColorA" (ByVal fontHandle As Long, ByVal color As Integer)
Declare Function xlFontBold Lib "libxl.dll" Alias "xlFontBoldA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetBold Lib "libxl.dll" Alias "xlFontSetBoldA" (ByVal fontHandle As Long, ByVal bold As Integer)
Declare Function xlFontScript Lib "libxl.dll" Alias "xlFontScriptA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetScript Lib "libxl.dll" Alias "xlFontSetScriptA" (ByVal fontHandle As Long, ByVal script As Integer)
Declare Function xlFontUnderline Lib "libxl.dll" Alias "xlFontUnderlineA" (ByVal fontHandle As Long) As Integer
Declare Sub xlFontSetUnderline Lib "libxl.dll" Alias "xlFontSetUnderlineA" (ByVal fontHandle As Long, ByVal underline As Integer)
Declare Function xlFontName Lib "libxl.dll" Alias "xlFontNameA" (ByVal fontHandle As Long) As String
Declare Function xlFontSetName Lib "libxl.dll" Alias "xlFontSetNameA" (ByVal fontHandle As Long, ByVal name As String) As Integer

