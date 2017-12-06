#include "Gra.ch"
#include "Xbp.ch"
#include "Common.ch"
#include "Inkey.ch"

*************************
#include "ot4xb.ch"
#include "HBLibXl.CH"
*************************

procedure main()
   local oBook, oSheet, cFile, bBuffer, x, nRow, nCol, nSize, oFormat, oFormat2, oFont, nActiveSheet, cCell, oFormatDate
   local cLName := GETENV("LIBXL_NAME") // nur für meine Entwicklung, normalerweise fest einbauen (Funktion, *.CH, etc.)
   local cLKey  := GETENV("LIBXL_KEY")  // only for my testing, normaly you will write it in the code (function, *.CH, etc.)

   set date german
   set charset to ansi       // ANSI

   set alternate to (cPathRemoveExt(appname())+".txt")
   set alternate on

   cFile := "MyDefault.XLS"

   ? "Test XbpCrt() / GUI / ANSI App ! äöü"
   ?
   ? "ot4xb() ? = ",ot4xb()
   ?
   ? "load from File ..."
   ?

   oBook := xlCreateBook() // cLName,cLKey )
   if oBook # NIL
      ? "oBook:BookLoad(cFile) ... ", cFile
      if ! oBook:BookLoad(cFile)
         ?? "Error !",oBook:BookErrorMessage()
      else
         ?? "loaded !"

         ? "AddFormat()"
         oFormat := oBook:BookAddFormat() // get Format-Objekt
         oFormat:FormatSetNumFormat(NUMFORMAT_TEXT)
         oFormat:FormatSetAlignH(ALIGNH_CENTER)
         oFormat:FormatSetAlignV(ALIGNV_CENTER)
         oFont   := oFormat:FormatFont()    // don't change
         ? "Old FontName(): ",oFont:FontName(), " Size:",oFont:FontSize()

         oFont   := oBook:BookAddFont() // reuse object is OK.
         oFont:FontSetName("Arial")
         oFont:FontSetSize(16)
         ? "New FontName(): ",oFont:FontName(), " Size:",oFont:FontSize()

         oFormat2 := oBook:BookAddFormat(oFormat)
         oFormat2:FormatSetFont(oFont)

         ? "Sheet count: ", oBook:BookSheetCount() // 3 but nIndex 0 to 2
         ? "Delete sheet > 1"
         do while oBook:BookSheetCount() > 1
            ? "Delete ",oBook:BookSheetCount(),oBook:BookDelSheet(oBook:BookSheetCount()-1),oBook:BookSheetCount()
         enddo
         ? "SheetType...",oBook:BookSheetType(0)
         oSheet := oBook:BookGetSheet(0)
         if ! empty(oSheet)
            ? "Name:       ",oSheet:SheetName()
            ? "SetName:    ",oSheet:SheetSetName("List 1-b")
            ? "Neuer Name: ",oSheet:SheetName()
            ?
            ? "Info zu SheetCellFormat(2,0):"
            oFormat := oSheet:SheetCellFormat(2,0)
            ? "FormatFillPattern():            ",oFormat:FormatFillPattern()
            ? "FormatPatternForegroundColor(): ",oFormat:FormatPatternForegroundColor()
            ? "FormatPatternBackgroundColor(): ",oFormat:FormatPatternBackgroundColor()
            ? "Info über Handles:"
            ? "hBook:  ",oBook:hHandle
            ? "hSheet: ",oSheet:hHandle
            ? "Set col width ..."
            ? "0,0,20.0",oSheet:SheetSetCol( 2,3, 20.0 )      // does not work with DEMO !
            ? "2,2,20.0",oSheet:SheetSetCol( 12, 20, 15.0 )      // Column 2 to 2 => Column C (3), 20 chars
            ? "set Row ",oSheet:SheetSetRow( 9, 20 )      // Column 2 to 2 => Column C (3), 20 chars
            ? "fill ..."
            oSheet:SheetWriteStr( 2,2, "2/2" )

            for x := 1 to 5
                nRow := x - 1 + 4 // first line 5 in Excel.
                nCol := 0         // first columne
                ? "oBook SheetWrite ... Row:",x,;
                  oSheet:SheetWriteStr( nRow, nCol++, "Name"+str(x,2), nil) ,;
                  oSheet:SheetWriteNum( nRow, nCol++, x+100 ),;
                  oSheet:SheetWriteStr( nRow, nCol++, "Some Info "+str(x,2) )
            next
            nRow += 2

            oSheet:SheetWriteStr( nRow,  0, "Sum:" )
            // Excel Formeln / Formulas
            // Funktionsnamen in englisch, siehe Macros !
            // look into Excel Macros for the function names (=> english)!
            oSheet:SheetWriteFormula( nRow,  1, "=SUM(B5:B9)", nil)

            cCell := "J5"
            oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
            oSheet:SheetWriteDate(nRow,nCol,date())

            cCell := "J7"
            oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
            oSheet:SheetWriteDate(nRow,nCol,date()+5)


            ? "Format to Font Arial 12pt  "
            oFont   := oBook:BookAddFont() // reuse object is OK.
            oFont:FontSetName("Arial") // "Times New Roman")
            oFont:FontSetSize(12)
            ? "New FontName(): ",oFont:FontName(), " Size:",oFont:FontSize()

            oFormatDate := oBook:BookAddFormat( oSheet:SheetCellFormat(nRow, nCol) )
            oFormatDate:FormatSetFont(oFont)

            cCell := "L5"
            oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
            oSheet:SheetWriteDate(nRow,nCol,date(),oFormatDate)

            cCell := "L7"
            oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
            oSheet:SheetWriteDate(nRow,nCol,date()+5,oFormatDate)

            // Format ...
            oSheet:SheetAddrToRowCol("I2",@nRow, @nCol)
            oSheet:SheetWriteStr( nRow, nCol, "Format oFormat", oFormat )
            oSheet:SheetAddrToRowCol("I4",@nRow, @nCol)
            oSheet:SheetWriteStr( nRow, nCol, "Format oFormat2", oFormat2 )

         endif
         ? "oBook save: ",;
           oBook:BookSave( "MyNewFile1" ) // automatische Endung ?

         bBuffer := ""
         nSize   := 0
         ? "BookSaveRaw()",;
           oBook:BookSaveRaw(@bBuffer, @nSize),;
           "LEN-DATA: ",len(bBuffer)," nSize: ",nSize
         lMemoWrite( "MyNewFile1-RAW"+oBook:cFileExt , bBuffer )

         // don't release oBook before end !

      endif

      ?
      ? "Erstelle XLS Datei aus Muster im RAM "
      ?
      ? "Dateiname: ",cFile," laden ... "
      bBuffer := memoread(cFile)
      ?? "Byte: ",len(bBuffer), "... for later use ..."

      ? "oBook:BookLoadRaw(...) ... "
      if ! oBook:BookLoadRaw(@bBuffer, len(bBuffer))
         ?? "Error !",oBook:BookErrorMessage()
      else
         ?? "loaded !"

         nActiveSheet := oBook:BookActiveSheet()

         oSheet := oBook:BookGetSheet(nActiveSheet)

         if ! empty(oSheet)
            ? "Name:       ",oSheet:SheetName()
            ? "SetName:    ",oSheet:SheetSetName("From RAM")
            ? "Neuer Name: ",oSheet:SheetName()
            ? "fill ..."
            for x := 1 to 10
                nRow := x - 1 + 4 // first line 5 in Excel.
                nCol := 0         // first columne
                ? "oBook SheetWrite ... Row:",x,;
                  oSheet:SheetWriteStr( nRow, nCol++, "Name"+str(x,2), nil) ,;
                  oSheet:SheetWriteNum( nRow, nCol++, x+100 ),;
                  oSheet:SheetWriteStr( nRow, nCol++, "Some Info "+str(x,2) )
            next
         endif
         ? "Info über Handles:"
         ? "hBook:  ",oBook:hHandle
         ? "hSheet: ",oSheet:hHandle
         ? "Set col width ..."
         ? "0,0,20.0",oSheet:SheetSetCol( 8, 9, 20.0 )      // does not work ... maybe DEMO ?
         ? "2,2,20.0",oSheet:SheetSetCol( 12, 20, 15.0 )      // Column 2 to 2 => Column C (3), 20 chars
         ? "set Row ",oSheet:SheetSetRow( 9, 20 )      // Column 2 to 2 => Column C (3), 20 chars

         ? "oBook save: ",;
         oBook:BookSave( "MyNewFile2" ) // automatische Endung ?
         // this is enougth, but ...
         oBook:destroy()
         // this is no problem too ...
         oBook:destroy()
         oBook:BookRelease()
         oBook:destroy()
         oBook:BookRelease()
         oBook:destroy()

      endif

   else
      msgbox("LibXL.DLL konnte nicht geladen werden !","Eigene (flexible) Fehlermeldung !") // eigene Fehlermeldung
   endif


   ? "Ende in 10 Sekunden, oder durch Tastendruck ..."

   inkey(10)

return


