VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub Form_Load()

Dim book As Long
Dim sheet As Long

book = xlCreateBook() ''// xlCreateXMLBook() for xlsx

''book = xlCreateBookW() ''// xlCreateXMLBook() for xlsx

''book = xlCreateBookCA() ''// xlCreateXMLBook() for xlsx

    If book <> 0 Then
        sheet = xlBookAddSheet(book, "Sheet1", 0)
        If sheet <> 0 Then
            Call xlSheetWriteStr(sheet, 2, 1, "Hello, World !", 0)
            Call xlSheetWriteNum(sheet, 3, 1, 123.456, 0)
        End If
        sheet = xlBookInsertSheet(book, 0, "MySheet2", 0)
        sheet = xlBookInsertSheet(book, 1, "MySheet3", sheet)
        
        Dim sheetCnt As Integer: sheetCnt = xlBookSheetCount(book)
        Me.Caption = "SheetCount = " & sheetCnt
        
        Call xlBookDelSheet(book, 1)
        
        Call xlBookSave(book, "example.xls")
        Call xlBookRelease(book)

End If

End Sub
