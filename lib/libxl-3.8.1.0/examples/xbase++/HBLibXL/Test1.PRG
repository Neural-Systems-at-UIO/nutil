#include "Gra.ch"
#include "Xbp.ch"
#include "Common.ch"
#include "Inkey.ch"

*************************
#include "ot4xb.ch"
#include "HBLibXl.CH"
*************************

procedure main()
   local oBook, oSheet, cFile, oHBXL
   local oFormat, cCell, nRow, nCol, dDate
   local cLName := GETENV("LIBXL_NAME") // nur fÅr meine Entwicklung, normalerweise fest einbauen (Funktion, *.CH, etc.)
   local cLKey  := GETENV("LIBXL_KEY")  // only for my testing, normaly you will write it in the code (function, *.CH, etc.)


   set date german

   set alternate to (cPathRemoveExt(appname())+".txt")
   set alternate on

   cFile := "TestÑîÅ"  // OEM

   ? "Test mit XbpCrt() / Console / OEM Anwendung !"
   ?
   ? "ot4xb() ? = ",ot4xb()
   ?
   ? "Erstelle XLS Datei direkt mit den gegebenen Funktionen (oBook KANN NIL sein !):"
   ?
   ? "Dateiname: ",cFile," kann man die Endung weg lassen ? "
   ?

   oBook := xlCreateBook(cName,cKey)
   if oBook # NIL
      ? "oBook XLS erstellt !"
      oSheet := oBook:BookAddSheet("Test1 ÑîÅ" )
      if ! empty(oSheet)
        ? "oBook SheetWrite ..."                           ,;
        oSheet:SheetWriteStr( 5, 5, "5/5", nil) ,;
        oSheet:SheetWriteStr( 2, 1, "Hello, World ÑîÅ !", nil) ,;
        oSheet:SheetWriteNum( 4, 2, 1000)
        oSheet:SheetWriteNum( 5, 2, 99999.88)
        ? "Name:       ",oSheet:SheetName()
        ? "SetName:    ",oSheet:SheetSetName("Test Arbeitsblatt")
        ? "Neuer Name: ",oSheet:SheetName()
        ? "Protect:    ",oSheet:SheetProtect()
        ? "SetProtect: ",oSheet:SheetSetProtect() // Vorgabe .t.
        ? "Protect:    ",oSheet:SheetProtect()
        ? "Hidden:     ",oSheet:SheetHidden()
        ? "SetProtect: ",oSheet:SheetSetProtect(.f.)
        ? "Writing date ... create double ... format ... not very usefull !"
        ? oSheet:SheetSetCol(5,5,12.5)
        ? oSheet:SheetSetRow(5, 24.0)
        oSheet:SheetWriteStr(15,4, "Date:")
        oFormat := oBook:BookaddFormat()
        oFormat:FormatSetNumFormat(NUMFORMAT_DATE)
        * oFormat:FormatSetShrinkToFit(.t.) // verkleinert den Text bis er passt / smaller text size if needed
        ? "Datum schreiben     25.12.2013 ..."
        nRow := 15
        nCol := 5
        oSheet:SheetWriteNum(nRow,nCol,oBook:BookDatePack(2013, 12, 25), oFormat)
        ? "Datum wieder lesen  "
        dDate := oSheet:SheetReadDate(nRow,nCol)
        ?? dtoc(dDate)," das wurde ausgelesen, + 5 Tage ..."
        dDate += 5 // add 5 days
        nRow++
        ? " + 5 days  ...     ",dDate
        oSheet:SheetWriteDate(nRow,nCol,dDate)
        cCell := "AA5"
        oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
        ? "=>",cCell,;
        oSheet:SheetWriteStr( nRow, nCol, cCell+" = R:"+str(nRow,3)+" C:"+str(nCol,3))
        cCell := "IV5"
        oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
        ? "=>",cCell,;
        oSheet:SheetWriteStr( nRow, nCol, cCell+" = R:"+str(nRow,3)+" C:"+str(nCol,3))

      endif
      ? "oBook save: ",;
        oBook:BookSave( cFile ) // automatische Endung ?
        oBook:destroy()
   else
      msgbox("LibXL.DLL konnte nicht geladen werden !","Eigene (flexible) Fehlermeldung !") // eigene Fehlermeldung
   endif

   oBook := xlCreateXmlBook()
   if oBook # NIL
      ? "oBook XML erstellt !"
      oSheet := oBook:BookAddSheet("Test1 éôö ")
      if ! empty(oSheet)
        ? oSheet:SheetSetCol(7,7,30)
        ? oSheet:SheetSetRow(5, 24.0)
        ? "Writing date ... create double ... format ... not very usefull !"
        oSheet:SheetWriteStr(15,4, "Date:")
        oFormat := oBook:BookaddFormat()
        oFormat:FormatSetNumFormat(NUMFORMAT_DATE)
        * oFormat:FormatSetShrinkToFit(.t.) // verkleinert den Text bis er passt / smaller text size if needed
        ? "Datum schreiben     25.12.2013 ..."
        nRow := 15
        nCol := 5
        oSheet:SheetWriteNum(nRow,nCol,oBook:BookDatePack(2013, 12, 25), oFormat)
        ? "Datum wieder lesen  "
        dDate := oSheet:SheetReadDate(nRow,nCol)
        ?? dtoc(dDate)," das wurde ausgelesen, + 5 Tage ..."
        dDate += 5 // add 5 days
        nRow++
        ? " + 5 days  ...     ",dDate
        oSheet:SheetWriteDate(nRow,nCol,dDate)
        cCell := "AA5"
        oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
        ? "=>",cCell,;
        oSheet:SheetWriteStr( nRow, nCol, cCell+" = R:"+str(nRow,3)+" C:"+str(nCol,3))
        cCell := "IV5"
        oSheet:SheetAddrToRowCol(cCell,@nRow, @nCol)
        ? "=>",cCell,;
        oSheet:SheetWriteStr( nRow, nCol, cCell+" = R:"+str(nRow,3)+" C:"+str(nCol,3))
      endif
      ? "oBook save: ",;
        oBook:BookSave( cFile+"1" )  // oBook kennt die richtige Endung, oBook knows the right extension
        oBook:destroy()        // => xlBookRelease()
      // KEIN ELSE Zweig, keine Fehlermeldung ... no error message if you don't need it
   endif

   ? "oder erstelle ein HBLibXL() Objekt um die Probleme genauer zu behandeln."

   oHBXL := HBLibXL(cName,cKey)
   oBook := oHBXL:CreateXmlBook()
   if ! IsNil(oBook)
      ? "oBook XML erstellt !"
      ? "Wrong Key = DEMO "
      oBook:BookSetKey( "your Name","your Key" ) // wrong values => DEMO MODE
      ? "IsDemoMode ? ",oBook:IsDemoMode()

      oSheet := oBook:BookAddSheet("Test1 @˝¸")
      if ! empty(oSheet)
         ? "oBook SheetWrite ..."                           ,;
            oSheet:SheetWriteStr( 2, 1, "Hello, World ÑîÅ !", nil) ,;
            oSheet:SheetWriteNum( 4, 2, 1000)
      endif
      ? "oBook save: ",;
         oBook:BookSave( cFile+"2" ) // automatische Endung ?
         oBook:destroy()
   else
      msgbox("NO LibXL.DLL !","Fehler / Error") // eigene Fehlermeldung - your own message
   endif

   ? "Ende in 10 Sekunden, oder durch Tastendruck ..."

   inkey(10)

return


