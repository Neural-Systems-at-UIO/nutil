program invoice

use libxl

integer i
type(BookHandle) book
type(SheetHandle) sheet, nullSheet
type(FontHandle) nullFont, boldFont, titleFont
type(FormatHandle) nullFormat, titleFormat, headerFormat, descriptionFormat, amountFormat, totalLabelFormat, totalFormat, signatureFormat

book = xlCreateXMLBook()

boldFont = xlBookAddFont(book, nullFont)
call xlFontSetBold(boldFont, 1)

titleFont = xlBookAddFont(book, nullFont)
i = xlFontSetName(titleFont, "Arial Black")
call xlFontSetSize(titleFont, 16)

titleFormat = xlBookAddFormat(book, nullFormat)
i = xlFormatSetFont(titleFormat, titleFont)

headerFormat = xlBookAddFormat(book, nullFormat)
call xlFormatSetAlignH(headerFormat, ALIGNH_CENTER)
call xlFormatSetBorder(headerFormat, BORDERSTYLE_THIN)
i = xlFormatSetFont(headerFormat, boldFont)
call xlFormatSetFillPattern(headerFormat, FILLPATTERN_SOLID)
call xlFormatSetPatternForegroundColor(headerFormat, COLOR_TAN)

descriptionFormat = xlBookAddFormat(book, nullFormat)
call xlFormatSetBorderLeft(descriptionFormat, BORDERSTYLE_THIN)

amountFormat = xlBookAddFormat(book, nullFormat)
call xlFormatSetNumFormat(amountFormat, NUMFORMAT_CURRENCY_NEGBRA)
call xlFormatSetBorderLeft(amountFormat, BORDERSTYLE_THIN)
call xlFormatSetBorderRight(amountFormat, BORDERSTYLE_THIN)

totalLabelFormat = xlBookAddFormat(book, nullFormat)
call xlFormatSetBorderTop(totalLabelFormat, BORDERSTYLE_THIN)
call xlFormatSetAlignH(totalLabelFormat, ALIGNH_RIGHT)
i = xlFormatSetFont(totalLabelFormat, boldFont)

totalFormat = xlBookAddFormat(book, nullFormat)
call xlFormatSetNumFormat(totalFormat, NUMFORMAT_CURRENCY_NEGBRA)
call xlFormatSetBorder(totalFormat, BORDERSTYLE_THIN)
i = xlFormatSetFont(totalFormat, boldFont)
call xlFormatSetFillPattern(totalFormat, FILLPATTERN_SOLID)
call xlFormatSetPatternForegroundColor(totalFormat, COLOR_YELLOW)

signatureFormat = xlBookAddFormat(book, nullFormat)
call xlFormatSetAlignH(signatureFormat, ALIGNH_CENTER)
call xlFormatSetBorderTop(signatureFormat, BORDERSTYLE_THIN)

sheet = xlBookAddSheet(book, "Invoice", nullSheet)

i = xlSheetWriteStr(sheet, 2, 1, "Invoice No. 3568", titleFormat)
i = xlSheetWriteStr(sheet, 4, 1, "Name: John Smith", nullFormat)
i = xlSheetWriteStr(sheet, 5, 1, "Address: San Ramon, CA 94583 USA", nullFormat)
i = xlSheetWriteStr(sheet, 7, 1, "Description", headerFormat)
i = xlSheetWriteStr(sheet, 7, 2, "Amount", headerFormat)
i = xlSheetWriteStr(sheet, 8, 1, "Ball-Point Pens", descriptionFormat)
i = xlSheetWriteNum(sheet, 8, 2, 85, amountFormat)
i = xlSheetWriteStr(sheet, 9, 1, "T-Shirts", descriptionFormat)
i = xlSheetWriteNum(sheet, 9, 2, 150, amountFormat)
i = xlSheetWriteStr(sheet, 10, 1, "Tea cups", descriptionFormat)
i = xlSheetWriteNum(sheet, 10, 2, 45, amountFormat)
i = xlSheetWriteStr(sheet, 11, 1, "Total:", totalLabelFormat)
i = xlSheetWriteFormula(sheet, 11, 2, "=SUM(C9:C11)", totalFormat)
i = xlSheetWriteStr(sheet, 14, 2, "Signature", signatureFormat)

i = xlSheetSetCol(sheet, 1, 1, 40, nullFormat, 0);
i = xlSheetSetCol(sheet, 2, 2, 15, nullFormat, 0);

i = xlBookSave(book, "invoice.xlsx")

call xlBookRelease(book)

end program invoice