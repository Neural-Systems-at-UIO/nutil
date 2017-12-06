module libxl

use ifnls

    integer, parameter :: ALIGNH_GENERAL=0, ALIGNH_LEFT=1, ALIGNH_CENTER=2, ALIGNH_RIGHT=3, ALIGNH_FILL=4, ALIGNH_JUSTIFY=5, ALIGNH_MERGE=6, ALIGNH_DISTRIBUTED=7
    integer, parameter :: ALIGNV_TOP=0,ALIGNV_CENTER=1,ALIGNV_BOTTOM=2,ALIGNV_JUSTIFY=3,ALIGNV_DISTRIBUTED=4
    integer, parameter :: BORDERSTYLE_NONE=0,BORDERSTYLE_THIN=1,BORDERSTYLE_MEDIUM=2,BORDERSTYLE_DASHED=3,BORDERSTYLE_DOTTED=4,BORDERSTYLE_THICK=5,BORDERSTYLE_DOUBLE=6,BORDERSTYLE_HAIR=7,BORDERSTYLE_MEDIUMDASHED=8,BORDERSTYLE_DASHDOT=9,BORDERSTYLE_MEDIUMDASHDOT=10,BORDERSTYLE_DASHDOTDOT=11,BORDERSTYLE_MEDIUMDASHDOTDOT=12,BORDERSTYLE_SLANTDASHDOT=13
    integer, parameter :: BORDERDIAGONAL_NONE=0,BORDERDIAGONAL_DOWN=1,BORDERDIAGONAL_UP=2,BORDERDIAGONAL_BOTH=3
    integer, parameter :: FILLPATTERN_NONE=0,FILLPATTERN_SOLID=1,FILLPATTERN_GRAY50=2,FILLPATTERN_GRAY75=3,FILLPATTERN_GRAY25=4,FILLPATTEN_HORSTRIPE=5,FILLPATTERN_VERSTRIPE=6,FILLPATTERN_REVDIAGSTRIPE=7,FILLPATTERN_DIAGSTRIPE=8,FILLPATTERN_DIAGCROSSHATCH=9,FILLPATTERN_THICKDIAGCROSSHATCH=10,FILLPATTERN_THINHORSTRIPE=11,FILLPATTERN_THINVERSTRIPE=12,FILLPATTERN_THINREVDIAGSTRIPE=13,FILLPATTERN_THINDIAGSTRIPE=14,FILLPATTERN_THINHORCROSSHATCH=15,FILLPATTERN_THINDIAGCROSSHATCH=16,FILLPATTERN_GRAY12P5=17,FILLPATTERN_GRAY6P25=18
    integer, parameter :: NUMFORMAT_GENERAL=0,NUMFORMAT_NUMBER=1,NUMFORMAT_NUMBER_D2=2,NUMFORMAT_NUMBER_SEP=3,NUMFORMAT_NUMBER_SEP_D2=4,NUMFORMAT_CURRENCY_NEGBRA=5,NUMFORMAT_CURRENCY_NEGBRARED=6,NUMFORMAT_CURRENCY_D2_NEGBRA=7,NUMFORMAT_CURRENCY_D2_NEGBRARED=8,NUMFORMAT_PERCENT=9,NUMFORMAT_PERCENT_D2=10,NUMFORMAT_SCIENTIFIC_D2=11,NUMFORMAT_FRACTION_ONEDIG=12,NUMFORMAT_FRACTION_TWODIG=13,NUMFORMAT_DATE=14,NUMFORMAT_CUSTOM_D_MON_YY=15,NUMFORMAT_CUSTOM_D_MON=16,NUMFORMAT_CUSTOM_MON_YY=17,NUMFORMAT_CUSTOM_HMM_AM=18,NUMFORMAT_CUSTOM_HMMSS_AM=19,NUMFORMAT_CUSTOM_HMM=20,NUMFORMAT_CUSTOM_HMMSS=21,NUMFORMAT_CUSTOM_MDYYYY_HMM=22,NUMFORMAT_NUMBER_SEP_NEGBRA=37,NUMFORMAT_NUMBER_SEP_NEGBRARED=38,NUMFORMAT_NUMBER_D2_SEP_NEGBRA=39,NUMFORMAT_NUMBER_D2_SEP_NEGBRARED=40,NUMFORMAT_ACCOUNT=41,NUMFORMAT_ACCOUNTCUR=42,NUMFORMAT_ACCOUNT_D2=43,NUMFORMAT_ACCOUNT_D2_CUR=44,NUMFORMAT_CUSTOM_MMSS=45,NUMFORMAT_CUSTOM_H0MMSS=46,NUMFORMAT_CUSTOM_MMSS0=47,NUMFORMAT_CUSTOM_000P0E_PLUS0=48,NUMFORMAT_TEXT=49
    integer, parameter :: COLOR_BLACK=8,COLOR_WHITE=9,COLOR_RED=10,COLOR_BRIGHTGREEN=11,COLOR_BLUE=12,COLOR_YELLOW=13,COLOR_PINK=14,COLOR_TURQUOISE=15,COLOR_DARKRED=16,COLOR_GREEN=17,COLOR_DARKBLUE=18,COLOR_DARKYELLOW=19,COLOR_VIOLET=20,COLOR_TEAL=21,COLOR_GRAY25=22,COLOR_GRAY50=23,COLOR_PERIWINKLE_CF=24,COLOR_PLUM_CF=25,COLOR_IVORY_CF=26,COLOR_LIGHTTURQUOISE_CF=27,COLOR_DARKPURPLE_CF=28,COLOR_CORAL_CF=29,COLOR_OCEANBLUE_CF=30,COLOR_ICEBLUE_CF=31,COLOR_DARKBLUE_CL=32,COLOR_PINK_CL=33,COLOR_YELLOW_CL=34,COLOR_TURQUOISE_CL=35,COLOR_VIOLET_CL=36,COLOR_DARKRED_CL=37,COLOR_TEAL_CL=38,COLOR_BLUE_CL=39,COLOR_SKYBLUE=40,COLOR_LIGHTTURQUOISE=41,COLOR_LIGHTGREEN=42,COLOR_LIGHTYELLOW=43,COLOR_PALEBLUE=44,COLOR_ROSE=45,COLOR_LAVENDER=46,COLOR_TAN=47,COLOR_LIGHTBLUE=48,COLOR_AQUA=49,COLOR_LIME=50,COLOR_GOLD=51,COLOR_LIGHTORANGE=52,COLOR_ORANGE=53,COLOR_BLUEGRAY=54,COLOR_GRAY40=55,COLOR_DARKTEAL=56,COLOR_SEAGREEN=57,COLOR_DARKGREEN=58,COLOR_OLIVEGREEN=59,COLOR_BROWN=60,COLOR_PLUM=61,COLOR_INDIGO=62,COLOR_GRAY80=63,COLOR_DEFAULT_FOREGROUND=64,COLOR_DEFAULT_BACKGROUND=65,COLOR_TOOLTIP=81,COLOR_AUTO=32767
    integer, parameter :: CELLTYPE_EMPTY=0,CELLTYPE_NUMBER=1,CELLTYPE_STRING=2,CELLTYPE_BOOLEAN=3,CELLTYPE_BLANK=4,CELLTYPE_ERROR=5
    integer, parameter :: ERRORTYPE_NULL=0,ERRORTYPE_DIV_0=7,ERRORTYPE_VALUE=15,ERRORTYPE_REF=23,ERRORTYPE_NAME=29,ERRORTYPE_NUM=36,ERRORTYPE_NA=42,ERRORTYPE_NOERROR=255
    integer, parameter :: PANETYPE_BOTRIGHT=0,PANETYPE_TOPRIGHT=1,PANETYPE_BOTTOMLEFT=2,PANETYPE_TOPLEFT=3
    integer, parameter :: PAPER_DEFAULT=0,PAPER_LETTER=1,PAPER_LETTERSMALL=2,PAPER_TABLOID=3,PAPER_LEDGER=4,PAPER_LEGAL=5,PAPER_STATEMENT=6,PAPER_EXECUTIVE=7,PAPER_A3=8,PAPER_A4=9,PAPER_A4SMALL=10,PAPER_A5=11,PAPER_B4=12,PAPER_B5=13,PAPER_FOLIO=14,PAPER_QUATRO=15,PAPER_10x14=16,PAPER_10x17=17,PAPER_NOTE=18,PAPER_ENVELOPE_9=19,PAPER_ENVELOPE_10=20,PAPER_ENVELOPE_11=21,PAPER_ENVELOPE_12=22,PAPER_ENVELOPE_14=23,PAPER_C_SIZE=24,PAPER_D_SIZE=25,PAPER_E_SIZE=26,PAPER_ENVELOPE_DL=27,PAPER_ENVELOPE_C5=28,PAPER_ENVELOPE_C3=29,PAPER_ENVELOPE_C4=30,PAPER_ENVELOPE_C6=31,PAPER_ENVELOPE_C65=32,PAPER_ENVELOPE_B4=33,PAPER_ENVELOPE_B5=34,PAPER_ENVELOPE_B6=35,PAPER_ENVELOPE=36,PAPER_ENVELOPE_MONARCH=37,PAPER_US_ENVELOPE=38,PAPER_FANFOLD=39,PAPER_GERMAN_STD_FANFOLD=40,PAPER_GERMAN_LEGAL_FANFOLD=41,PAPER_B4_ISO=42,PAPER_JAPANESE_POSTCARD=43,PAPER_9x11=44,PAPER_10x11=45,PAPER_15x11=46,PAPER_ENVELOPE_INVITE=47,PAPER_US_LETTER_EXTRA=50,PAPER_US_LEGAL_EXTRA=51,PAPER_US_TABLOID_EXTRA=52,PAPER_A4_EXTRA=53,PAPER_LETTER_TRANSVERSE=54,PAPER_A4_TRANSVERSE=55,PAPER_LETTER_EXTRA_TRANSVERSE=56,PAPER_SUPERA=57,PAPER_SUPERB=58,PAPER_US_LETTER_PLUS=59,PAPER_A4_PLUS=60,PAPER_A5_TRANSVERSE=61,PAPER_B5_TRANSVERSE=62,PAPER_A3_EXTRA=63,PAPER_A5_EXTRA=64,PAPER_B5_EXTRA=65,PAPER_A2=66,PAPER_A3_TRANSVERSE=67,PAPER_A3_EXTRA_TRANSVERSE=68,PAPER_JAPANESE_DOUBLE_POSTCARD=69,PAPER_A6=70,PAPER_JAPANESE_ENVELOPE_KAKU2=71,PAPER_JAPANESE_ENVELOPE_KAKU3=72,PAPER_JAPANESE_ENVELOPE_CHOU3=73,PAPER_JAPANESE_ENVELOPE_CHOU4=74,PAPER_LETTER_ROTATED=75,PAPER_A3_ROTATED=76,PAPER_A4_ROTATED=77,PAPER_A5_ROTATED=78,PAPER_B4_ROTATED=79,PAPER_B5_ROTATED=80,PAPER_JAPANESE_POSTCARD_ROTATED=81,PAPER_DOUBLE_JAPANESE_POSTCARD_ROTATED=82,PAPER_A6_ROTATED=83,PAPER_JAPANESE_ENVELOPE_KAKU2_ROTATED=84,PAPER_JAPANESE_ENVELOPE_KAKU3_ROTATED=85,PAPER_JAPANESE_ENVELOPE_CHOU3_ROTATED=86,PAPER_JAPANESE_ENVELOPE_CHOU4_ROTATED=87,PAPER_B6=88,PAPER_B6_ROTATED=89,PAPER_12x11=90,PAPER_JAPANESE_ENVELOPE_YOU4=91,PAPER_JAPANESE_ENVELOPE_YOU4_ROTATED=92,PAPER_PRC16K=93,PAPER_PRC32K=94,PAPER_PRC32K_BIG=95,PAPER_PRC_ENVELOPE1=96,PAPER_PRC_ENVELOPE2=97,PAPER_PRC_ENVELOPE3=98,PAPER_PRC_ENVELOPE4=99,PAPER_PRC_ENVELOPE5=100,PAPER_PRC_ENVELOPE6=101,PAPER_PRC_ENVELOPE7=102,PAPER_PRC_ENVELOPE8=103,PAPER_PRC_ENVELOPE9=104,PAPER_PRC_ENVELOPE10=105,PAPER_PRC16K_ROTATED=106,PAPER_PRC32K_ROTATED=107,PAPER_PRC32KBIG_ROTATED=108,PAPER_PRC_ENVELOPE1_ROTATED=109,PAPER_PRC_ENVELOPE2_ROTATED=110,PAPER_PRC_ENVELOPE3_ROTATED=111,PAPER_PRC_ENVELOPE4_ROTATED=112,PAPER_PRC_ENVELOPE5_ROTATED=113,PAPER_PRC_ENVELOPE6_ROTATED=114,PAPER_PRC_ENVELOPE7_ROTATED=115,PAPER_PRC_ENVELOPE8_ROTATED=116,PAPER_PRC_ENVELOPE9_ROTATED=117,PAPER_PRC_ENVELOPE10_ROTATED=118
    integer, parameter :: UNDERLINE_NONE=0,UNDERLINE_SINGLE=1,UNDERLINE_DOUBLE=2,UNDERLINE_SINGLEACC=33,UNDERLINE_DOUBLEACC=34
    integer, parameter :: SCRIPT_NORMAL=0,SCRIPT_SUPER=1,SCRIPT_SUB=2

    type BookHandle
        integer point
    end type 
    
    type SheetHandle
        integer point
    end type
    
    type FormatHandle
        integer point
    end type
    
    type FontHandle
        integer point
    end type

    interface
    
        type(BookHandle) function xlCreateBook()
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlCreateBookA':: xlCreateBook
        import
        end function
        
        type(BookHandle) function xlCreateXMLBook()
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlCreateXMLBookA':: xlCreateXMLBook
        import
        end function

        integer(4) function xlBookLoad(handle,filename)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookLoadA':: xlBookLoad
        !DEC$ATTRIBUTES REFERENCE :: filename
        import
        type(BookHandle) handle
        character(*) filename
        end function

        integer(4) function xlBookSave(handle,filename)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSaveA' :: xlBookSave
        !DEC$ATTRIBUTES REFERENCE :: filename
        import
        type(BookHandle) handle
        character(*) filename
        end function

        integer(4) function xlBookLoadRaw(handle,data_,size)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookLoadRawA' :: xlBookLoadRaw
        !DEC$ATTRIBUTES REFERENCE :: data_
        import
        type(BookHandle) handle
        character(*) data_
        integer(4) size
        end function

        integer(4) function xlBookSaveRaw(handle,data_,size)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSaveRawA' :: xlBookSaveRaw
        !DEC$ATTRIBUTES REFERENCE ::  data_
        !DEC$ATTRIBUTES REFERENCE :: size
        import
        type(BookHandle) handle
        character(*) data_
        integer(4) size
        end function

        type(SheetHandle) function xlBookAddSheet(handle,name,initSheet)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookAddSheetA' :: xlBookAddSheet
        !DEC$ATTRIBUTES REFERENCE :: name
        import
        type(BookHandle) handle
        character(*) name
        type(SheetHandle) initSheet
        end function
        
        type(SheetHandle) function xlBookGetSheet(handle,index)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookGetSheetA' :: xlBookGetSheet
        import
        type(BookHandle) handle
        integer(4) index
        end function

        integer(4) function xlBookDelSheet(handle,index)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookDelSheetA' :: xlBookDelSheet
        import
        type(BookHandle) handle
        integer(4) index
        end function

        integer(4) function xlBookSheetCount(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSheetCountA' :: xlBookSheetCount
        import
        type(BookHandle) handle
        end function

        type(FormatHandle) function xlBookAddFormat(handle,initFormat)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookAddFormatA' :: xlBookAddFormat
        import
        type(BookHandle) handle
        type(FormatHandle) initFormat        
        end function

        type(FontHandle) function xlBookAddFont(handle,initFont)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookAddFontA' :: xlBookAddFont
        import
        type(BookHandle) handle
        type(FontHandle) initFont
        end function

        integer(4) function xlBookAddCustomNumFormat(handle,customNumFormat)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookAddCustomNumFormatA' :: xlBookAddCustomNumFormat
        !DEC$ATTRIBUTES REFERENCE :: customNumFormat
        import
        type(BookHandle) handle
        character(*) customNumFormat
        end function

        integer(4) function xlBookCustomNumFormat(handle,fmt)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookCustomNumFormatA' :: xlBookCustomNumFormat
        !DEC$ATTRIBUTES REFERENCE :: xlBookCustomNumFormat
        import
        type(BookHandle) handle
        integer(4) fmt
        end function
        
        type(FormatHandle) function xlBookFormat(handle,index)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookFormatA' :: xlBookFormat
        import
        type(BookHandle) handle
        integer(4) index
        end function
        
        integer(4) function xlBookFormatSize(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookFormatSizeA' :: xlBookFormatSize
        import
        type(BookHandle) handle
        end function
        
        type(FontHandle) function xlBookFont(handle,index)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookFontA' :: xlBookFont
        import
        type(BookHandle) handle
        integer(4) index
        end function
        
        integer(4) function xlBookFontSize(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookFontSizeA' :: xlBookFontSize
        import
        type(BookHandle) handle
        end function
                              
        double precision function xlBookDatePack(handle,year,month,day,hour,min,sec,msec)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookDatePackA' :: xlBookDatePack
        import
        type(BookHandle) handle
        integer(4) year
        integer(4) month
        integer(4) day
        integer(4) hour
        integer(4) min
        integer(4) sec
        integer(4) msec
        end function

        integer(4) function xlBookDateUnpack(handle,value_,year,month,day,hour,min,sec,msec)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookDateUnpackA' :: xlBookDateUnpack
        !DEC$ATTRIBUTES REFERENCE :: year,month,day,hour,min,sec,msec
        import
        type(BookHandle) handle
        double precision value_
        integer(4) year
        integer(4) month
        integer(4) day
        integer(4) hour
        integer(4) min
        integer(4) sec
        integer(4) msec
        end function
        
        integer(4) function xlBookColorPack(handle,red,green,blue)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookColorPackA' :: xlBookColorPack
        import
        type(BookHandle) handle
        integer(4) red
        integer(4) green
        integer(4) blue
        end function
        
        subroutine xlBookColorUnpack(handle,color,red,green,blue)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookColorUnpackA' :: xlBookColorUnpack
        !DEC$ATTRIBUTES REFERENCE :: red,green,blue
        import
        type(BookHandle) handle
        integer(4) color
        integer(4) red
        integer(4) green
        integer(4) blue
        end subroutine
                            
        integer(4) function xlBookActiveSheet(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookActiveSheetA' :: xlBookActiveSheet
        import
        type(BookHandle) handle
        end function

        subroutine xlBookSetActiveSheet(handle,index)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSetActiveSheetA' :: xlBookSetActiveSheet
        import
        type(BookHandle) handle
        integer(4) index
        end subroutine

        integer(4) function xlBookAddPicture(handle,filename)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookAddPictureA' :: xlBookAddPicture
        !DEC$ATTRIBUTES REFERENCE :: filename
        import
        type(BookHandle) handle
        character(*) filename
        end function

        integer(4) function xlBookAddPicture2(handle,data_,size)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookAddPicture2A' :: xlBookAddPicture2
        !DEC$ATTRIBUTES REFERENCE :: data_
        import
        type(BookHandle) handle
        character(*) data_
        integer(4) size
        end function

        integer(4) function xlBookDefaultFont(handle,fontSize)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookDefaultFontA' :: xlBookDefaultFont
        !DEC$ATTRIBUTES REFERENCE :: xlBookDefaultFont
        !DEC$ATTRIBUTES REFERENCE :: fontSize
        import
        type(BookHandle) handle
        integer(4) fontSize
        end function

        subroutine xlBookSetDefaultFont(handle,fontName,fontSize)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSetDefaultFontA' :: xlBookSetDefaultFont
        !DEC$ATTRIBUTES REFERENCE :: fontName
        import
        type(BookHandle) handle
        character(*) fontName
        integer(4) fontSize
        end subroutine

        subroutine xlBookSetKeyPrivate(handle,name,key)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSetKeyA' :: xlBookSetKeyPrivate
        !DEC$ATTRIBUTES REFERENCE :: name
        !DEC$ATTRIBUTES REFERENCE :: key
        import
        type(BookHandle) handle
        integer(2), dimension(*) :: name
        integer(2), dimension(*) :: key
        end subroutine
        
        integer(4) function xlBookRgbMode(hanlde)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookRgbModeA' :: xlBookRgbMode
        import
        type(BookHandle) handle
        end function
        
        subroutine xlBookSetRgbMode(handle,rgbMode)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSetRgbModeA' :: xlBookSetRgbMode
        import
        type(BookHandle) handle
        integer(4) rgbMode
        end subroutine
                             
        subroutine xlBookSetLocale(handle,locale)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookSetLocaleA' :: xlBookSetLocale
        !DEC$ATTRIBUTES REFERENCE :: locale
        import
        type(BookHandle) handle
        character(*) locale
        end subroutine

        integer(4) function xlBookErrorMessage(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookErrorMessageA' :: xlBookErrorMessage
        !DEC$ATTRIBUTES REFERENCE :: xlBookErrorMessage
        import
        type(BookHandle) handle
        end function

        subroutine xlBookRelease(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlBookReleaseA' :: xlBookRelease
        import
        type(BookHandle) handle
        end subroutine

        integer(4) function xlSheetCellType(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetCellTypeA' :: xlSheetCellType
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function
        
        integer(4) function xlSheetIsFormula(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetIsFormulaA' :: xlSheetIsFormula
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function

        type(FormatHandle) function xlSheetCellFormat(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetCellFormatA' :: xlSheetCellFormat
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function
        
        subroutine xlSheetSetCellFormat(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetCellFormatA' :: xlSheetSetCellFormat
        !!DEC$ATTRIBUTES REFERENCE :: format_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end subroutine
              
        integer(4) function xlSheetReadStr(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadStrA' :: xlSheetReadStr
        !!DEC$ATTRIBUTES REFERENCE :: xlSheetReadStr
        !!DEC$ATTRIBUTES REFERENCE :: format_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetWriteStr(handle,row,col,value_,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetWriteStrA' :: xlSheetWriteStr
        !DEC$ATTRIBUTES REFERENCE :: value_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        character(*) value_
        type(FormatHandle) format_
        end function

        double precision function xlSheetReadNum(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadNumA' :: xlSheetReadNum
        !DEC$ATTRIBUTES REFERENCE :: format_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetWriteNum(handle,row,col,value_,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetWriteNumA' :: xlSheetWriteNum
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        double precision value_
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetReadBool(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadBoolA' :: xlSheetReadBool
        !DEC$ATTRIBUTES REFERENCE :: format_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetWriteBool(handle,row,col,value_,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetWriteBoolA' :: xlSheetWriteBool
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col,value_
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetReadBlank(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadBlankA' :: xlSheetReadBlank
        !DEC$ATTRIBUTES REFERENCE :: format_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetWriteBlank(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetWriteBlankA' :: xlSheetWriteBlank
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetReadFormula(handle,row,col,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadFormulaA' :: xlSheetReadFormula
        !DEC$ATTRIBUTES REFERENCE :: xlSheetReadFormula
        !DEC$ATTRIBUTES REFERENCE :: format_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetWriteFormula(handle,row,col,value_,format_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetWriteFormulaA' :: xlSheetWriteFormula
        !DEC$ATTRIBUTES REFERENCE :: value_
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        character(*) value_
        type(FormatHandle) format_
        end function

        integer(4) function xlSheetReadComment(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadCommentA' :: xlSheetReadComment
        !DEC$ATTRIBUTES REFERENCE :: xlSheetReadComment
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function

        subroutine xlSheetWriteComment(handle,row,col,value_,author,width,height)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetWriteCommentA' :: xlSheetWriteComment
        !DEC$ATTRIBUTES REFERENCE :: value_
        !DEC$ATTRIBUTES REFERENCE :: author
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        character(*) value_
        character(*) author
        integer(4) width
        integer(4) height
        end subroutine

        integer(4) function xlSheetIsDate(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetIsDateA' :: xlSheetIsDate
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function

        integer(4) function xlSheetReadError(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetReadErrorA' :: xlSheetReadError
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function

        double precision function xlSheetColWidth(handle,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetColWidthA' :: xlSheetColWidth
        import
        type(SheetHandle) handle
        integer(4) col
        end function

        double precision function xlSheetRowHeight(handle,row)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetRowHeightA' :: xlSheetRowHeight
        import
        type(SheetHandle) handle
        integer(4) row
        end function

        integer(4) function xlSheetSetCol(handle,colFirst,colLast,width,format_,hidden)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetColA' :: xlSheetSetCol
        import
        type(SheetHandle) handle
        integer(4) colFirst
        integer(4) colLast
        double precision width
        type(FormatHandle) format_
        integer(4) hidden
        end function

        integer(4) function xlSheetSetRow(handle,row,height,format_,hidden)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetRowA' :: xlSheetSetRow
        import
        type(SheetHandle) handle
        integer(4) row
        double precision height
        type(FormatHandle) format_
        integer(4) hidden
        end function

        integer(4) function xlSheetGetMerge(handle,row,col,rowFirst,rowLast,colFirst,colLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetGetMergeA' :: xlSheetGetMerge
        !DEC$ATTRIBUTES REFERENCE :: rowFirst,rowLast,colFirst,colLast
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        integer(4) rowFirst
        integer(4) rowLast
        integer(4) colFirst
        integer(4) colLast
        end function

        integer(4) function xlSheetSetMerge(handle,rowFirst,rowLast,colFirst,colLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetMergeA' :: xlSheetSetMerge
        import
        type(SheetHandle) handle
        integer(4) rowFirst
        integer(4) rowLast
        integer(4) colFirst
        integer(4) colLast
        end function

        integer(4) function xlSheetDelMerge(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetDelMergeA' :: xlSheetDelMerge
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end function

        subroutine xlSheetSetPicture(handle,row,col,pictureId,scale)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetPictureA' :: xlSheetSetPicture
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        integer(4) pictureId
        double precision scale
        end subroutine

        subroutine xlSheetSetPicture2(handle,row,col,pictureId,width,height)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetPicture2A' :: xlSheetSetPicture2
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        integer(4) pictureId
        integer(4) width
        integer(4) height
        end subroutine

        integer(4) function xlSheetSetHorPageBreak(handle,row,pageBreak)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetHorPageBreakA' :: xlSheetSetHorPageBreak
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) pageBreak
        end function

        integer(4) function xlSheetSetVerPageBreak(handle,col,pageBreak)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetVerPageBreakA' :: xlSheetSetVerPageBreak
        import
        type(SheetHandle) handle
        integer(4) col
        integer(4) pageBreak
        end function

        subroutine xlSheetSplit(handle,row,col)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSplitA' :: xlSheetSplit
        import
        type(SheetHandle) handle
        integer(4) row
        integer(4) col
        end subroutine

        integer(4) function xlSheetGroupRows(handle,rowFirst,rowLast,collapsed)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetGroupRowsA' :: xlSheetGroupRows
        import
        type(SheetHandle) handle
        integer(4) rowFirst
        integer(4) rowLast
        integer(4) collapsed
        end function

        integer(4) function xlSheetGroupCols(handle,colFirst,colLast,collapsed)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetGroupColsA' :: xlSheetGroupCols
        import
        type(SheetHandle) handle
        integer(4) colFirst
        integer(4) colLast
        integer(4) collapsed
        end function

        subroutine xlSheetClear(handle,rowFirst,rowLast,colFirst,colLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetClearA' :: xlSheetClear
        import
        type(SheetHandle) handle
        integer(4) rowFirst
        integer(4) rowLast
        integer(4) colFirst
        integer(4) colLast
        end subroutine

        integer(4) function xlSheetInsertRow(handle,rowFirst,rowLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetInsertRowA' :: xlSheetInsertRow
        import
        type(SheetHandle) handle
        integer(4) rowFirst
        integer(4) rowLast
        end function

        integer(4) function xlSheetInsertCol(handle,colFirst,colLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetInsertColA' :: xlSheetInsertCol
        import
        type(SheetHandle) handle
        integer(4) colFirst
        integer(4) colLast
        end function

        integer(4) function xlSheetRemoveRow(handle,rowFirst,rowLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetRemoveRowA' :: xlSheetRemoveRow
        import
        type(SheetHandle) handle
        integer(4) rowFirst
        integer(4) rowLast
        end function

        integer(4) function xlSheetRemoveCol(handle,colFirst,colLast)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetRemoveColA' :: xlSheetRemoveCol
        import
        type(SheetHandle) handle
        integer(4) colFirst
        integer(4) colLast
        end function

        integer(4) function xlSheetCopyCell(handle,rowSrc,colSrc,rowDst,colDst)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetCopyCellA' :: xlSheetCopyCell
        import
        type(SheetHandle) handle
        integer(4) rowSrc
        integer(4) colSrc
        integer(4) rowDst
        integer(4) colDst
        end function

        integer(4) function xlSheetFirstRow(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetFirstRowA' :: xlSheetFirstRow
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetLastRow(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetLastRowA' :: xlSheetLastRow
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetFirstCol(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetFirstColA' :: xlSheetFirstCol
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetLastCol(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetLastColA' :: xlSheetLastCol
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetDisplayGridlines(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetDisplayGridlineA' :: xlSheetSetDisplayGridline
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetDisplayGridlines(handle,show)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetDisplayGridlinesA' :: xlSheetSetDisplayGridlines
        import
        type(SheetHandle) handle
        integer(4) show
        end subroutine

        integer(4) function xlSheetPrintGridlines(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetPrintGridlinesA' :: xlSheetPrintGridlines
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetPrintGridlines(handle,print_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetPrintGridlinesA' :: xlSheetSetPrintGridlines
        import
        type(SheetHandle) handle
        integer(4) print_
        end subroutine

        integer(4) function xlSheetZoom(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetZoomA' :: xlSheetZoom
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetZoom(handle,zoom)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetZoomA' :: xlSheetSetZoom
        import
        type(SheetHandle) handle
        integer(4) zoom
        end subroutine

        integer(4) function xlSheetPrintZoom(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetPrintZoomA' :: xlSheetPrintZoom
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetPrintZoom(handle,zoom)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetPrintZoomA' :: xlSheetSetPrintZoom 
        import
        type(SheetHandle) handle
        integer(4) zoom
        end subroutine

        integer(4) function xlSheetLandscape(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetLandscapeA' :: xlSheetLandscape
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetLandscape(handle,landscape)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetLandscapeA' :: xlSheetSetLandscape
        import
        type(SheetHandle) handle
        integer(4) landscape
        end subroutine

        integer(4) function xlSheetPaper(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetPaperA' :: xlSheetPaper
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetPaper(handle,paper)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetPaperA' :: xlSheetSetPaper
        import
        type(SheetHandle) handle
        integer(4) paper
        end subroutine

        integer(4) function xlSheetHeader(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetHeaderA' :: xlSheetHeader
        !DEC$ATTRIBUTES REFERENCE :: xlSheetHeader
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetSetHeader(handle,header,margin)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetHeaderA' :: xlSheetSetHeader
        !DEC$ATTRIBUTES REFERENCE :: header
        import
        type(SheetHandle) handle
        character(*) header
        double precision margin
        end function

        double precision function xlSheetHeaderMargin(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetHeaderMarginA' :: xlSheetHeaderMargin 
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetFooter(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetFooterA' :: xlSheetFooter
        !DEC$ATTRIBUTES REFERENCE :: xlSheetFooter
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetSetFooter(handle,footer,margin)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetFooterA' :: xlSheetSetFooter
        !DEC$ATTRIBUTES REFERENCE :: footer
        import
        type(SheetHandle) handle
        character(*) footer
        double precision margin
        end function

        double precision function xlSheetFooterMargin(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetFooterMarginA' :: xlSheetFooterMargin 
        import
        type(SheetHandle) handle
        end function

        integer(4) function xlSheetHCenter(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetHCenterA' :: xlSheetHCenter
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetHCenter(handle,hCenter)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetHCenterA' :: xlSheetSetHCenter
        import
        type(SheetHandle) handle
        integer(4) hCenter
        end subroutine

        integer(4) function xlSheetVCenter(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetVCenterA' :: xlSheetVCenter
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetVCenter(handle,vCenter)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetVCenterA' :: xlSheetSetVCenter
        import
        type(SheetHandle) handle
        integer(4) vCenter
        end subroutine

        double precision function xlSheetMarginLeft(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetMarginLeftA' :: xlSheetMarginLeft
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetMarginLeft(handle,margin)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetMarginLeftA' :: xlSheetSetMarginLeft
        import
        type(SheetHandle) handle
        double precision margin
        end subroutine

        double precision function xlSheetMarginRight(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetMarginRightA' :: xlSheetMarginRight
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetMarginRight(handle,margin)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetMarginRightA' :: xlSheetSetMarginRight
        import
        type(SheetHandle) handle
        double precision margin
        end subroutine

        double precision function xlSheetMarginTop(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetMarginTopA' :: xlSheetMarginTop
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetMarginTop(handle,margin)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetMarginTopA' :: xlSheetSetMarginTop 
        import
        type(SheetHandle) handle
        double precision margin
        end subroutine

        double precision function xlSheetMarginBottom(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetMarginBottomA' :: xlSheetMarginBottom
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetMarginBottom(handle,margin)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetMarginBottomA' :: xlSheetSetMarginBottom
        import
        type(SheetHandle) handle
        double precision margin
        end subroutine

        integer(4) function xlSheetPrintRowCol(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetPrintRowColA' :: xlSheetPrintRowCol
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetPrintRowCol(handle,print_)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetPrintRowColA' :: xlSheetSetPrintRowCol
        import
        type(SheetHandle) handle
        integer(4) print_
        end subroutine

        integer(4) function xlSheetName(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetNameA' :: xlSheetName
        !DEC$ATTRIBUTES REFERENCE :: xlSheetName
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetName(handle,name)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetNameA' :: xlSheetSetName
        !DEC$ATTRIBUTES REFERENCE :: name
        import
        type(SheetHandle) handle
        character(*) name
        end subroutine

        integer(4) function xlSheetProtect(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetProtectA' :: xlSheetProtect
        import
        type(SheetHandle) handle
        end function

        subroutine xlSheetSetProtect(handle,protect)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlSheetSetProtectA' :: xlSheetSetProtect
        import
        type(SheetHandle) handle
        integer(4) protect
        end subroutine

        type(FontHandle) function xlFormatFont(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatFontA' :: xlFormatFont
        import
        type(FormatHandle) handle
        end function

        integer(4) function xlFormatSetFont(handle,FHandle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetFontA' :: xlFormatSetFont
        import
        type(FormatHandle) handle
        type(FontHandle) FHandle
        end function

        integer(4) function xlFormatNumFormat(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatNumFormatA' :: xlFormatNumFormat 
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetNumFormat(handle,numFormat)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetNumFormatA' :: xlFormatSetNumFormat
        import
        type(FormatHandle) handle
        integer(4) numFormat
        end subroutine

        integer(4) function xlFormatAlignH(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatAlignHA' :: xlFormatAlignH
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetAlignH(handle,align)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetAlignHA' :: xlFormatSetAlignH
        import
        type(FormatHandle) handle
        integer(4) align
        end subroutine

        integer(4) function xlFormatAlignV(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatAlignVA' :: xlFormatAlignV
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetAlignV(handle,align)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetAlignVA' :: xlFormatSetAlignV
        import
        type(FormatHandle) handle
        integer(4) align
        end subroutine

        integer(4) function xlFormatWrap(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatWrapA' :: xlFormatWrap
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetWrap(handle,wrap)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetWrapA' :: xlFormatSetWrap
        import
        type(FormatHandle) handle
        integer(4) wrap
        end subroutine

        integer(4) function xlFormatRotation(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatRotationA' :: xlFormatRotation
        import
        type(FormatHandle) handle
        end function

        integer(4) function xlFormatSetRotation(handle,rotation)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetRotationA' :: xlFormatSetRotation
        import
        type(FormatHandle) handle
        integer(4) rotation
        end function

        integer(4) function xlFormatIndent(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatIndentA' :: xlFormatIndent
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetIndent(handle,indent)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetIndentA' :: xlFormatSetIndent
        import
        type(FormatHandle) handle
        integer(4) indent
        end subroutine

        integer(4) function xlFormatShrinkToFit(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatShrinkToFitA' :: xlFormatShrinkToFit
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetShrinkToFit(handle,shrinkToFit)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetShrinkToFitA' :: xlFormatSetShrinkToFit
        import
        type(FormatHandle) handle
        integer(4) shrinkToFit
        end subroutine

        subroutine xlFormatSetBorder(handle,style)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderA' :: xlFormatSetBorder
        import
        type(FormatHandle) handle
        integer(4) style
        end subroutine

        subroutine xlFormatSetBorderColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderColorA' :: xlFormatSetBorderColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatBorderLeft(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderLeftA' :: xlFormatBorderLeft
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderLeft(handle,style)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderLeftA' :: xlFormatSetBorderLeft
        import
        type(FormatHandle) handle
        integer(4) style
        end subroutine

        integer(4) function xlFormatBorderRight(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderRightA' :: xlFormatBorderRight
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderRight(handle,style)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderRightA' :: xlFormatSetBorderRight
        import
        type(FormatHandle) handle
        integer(4) style
        end subroutine

        integer(4) function xlFormatBorderTop(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderTopA' :: xlFormatBorderTop
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderTop(handle,style)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderTopA' :: xlFormatSetBorderTop
        import
        type(FormatHandle) handle
        integer(4) style
        end subroutine

        integer(4) function xlFormatBorderBottom(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderBottomA' :: xlFormatBorderBottom
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderBottom(handle,style)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderBottomA' :: xlFormatSetBorderBottom
        import
        type(FormatHandle) handle
        integer(4) style
        end subroutine

        integer(4) function xlFormatBorderLeftColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderLeftColorA' :: xlFormatBorderLeftColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderLeftColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderLeftColorA' :: xlFormatSetBorderLeftColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatBorderRightColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderRightColorA' :: xlFormatBorderRightColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderRightColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderRightColorA' :: xlFormatSetBorderRightColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatBorderTopColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderTopColorA' :: xlFormatBorderTopColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderTopColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderTopColorA' :: xlFormatSetBorderTopColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatBorderBottomColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderBottomColorA' :: xlFormatBorderBottomColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderBottomColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderBottomColorA' :: xlFormatSetBorderBottomColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatBorderDiagonal(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderDiagonalA' :: xlFormatBorderDiagonal
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderDiagonal(handle,border)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderDiagonalA' :: xlFormatSetBorderDiagonal
        import
        type(FormatHandle) handle
        integer(4) border
        end subroutine

        integer(4) function xlFormatBorderDiagonalColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatBorderDiagonalColorA' :: xlFormatBorderDiagonalColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetBorderDiagonalColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetBorderDiagonalColorA' :: xlFormatSetBorderDiagonalColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatFillPattern(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatFillPatternA' :: xlFormatFillPattern
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetFillPattern(handle,pattern)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetFillPatternA' :: xlFormatSetFillPattern
        import
        type(FormatHandle) handle
        integer(4) pattern
        end subroutine

        integer(4) function xlFormatPatternForegroundColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatPatternForegroundColorA' :: xlFormatPatternForegroundColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetPatternForegroundColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetPatternForegroundColorA' :: xlFormatSetPatternForegroundColor 
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatPatternBackgroundColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatPatternBackgroundColorA' :: xlFormatPatternBackgroundColor
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetPatternBackgroundColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetPatternBackgroundColorA' :: xlFormatSetPatternBackgroundColor
        import
        type(FormatHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFormatLocked(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatLockedA' :: xlFormatLocked
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetLocked(handle,locked)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetLockedA' :: xlFormatSetLocked
        import
        type(FormatHandle) handle
        integer(4) locked
        end subroutine

        integer(4) function xlFormatHidden(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatHiddenA' :: xlFormatHidden
        import
        type(FormatHandle) handle
        end function

        subroutine xlFormatSetHidden(handle,hidden)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFormatSetHiddenA' :: xlFormatSetHidden
        import
        integer(4) hidden
        type(FormatHandle) handle
        end subroutine

        integer(4) function xlFontSize(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSizeA' :: xlFontSize
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetSize(handle,size)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetSizeA' :: xlFontSetSize
        import
        type(FontHandle) handle
        integer(4) size
        end subroutine

        integer(4) function xlFontItalic(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontItalicA' :: xlFontItalic
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetItalic(handle,italic)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetItalicA' :: xlFontSetItalic
        import
        type(FontHandle) handle
        integer(4) italic
        end subroutine

        integer(4) function xlFontStrikeOut(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontStrikeOutA' :: xlFontStrikeOut
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetStrikeOut(handle,strikeOut)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetStrikeOutA' :: xlFontSetStrikeOut
        import
        type(FontHandle) handle
        integer(4) strikeOut
        end subroutine

        integer(4) function xlFontColor(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontColorA' :: xlFontColor
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetColor(handle,color)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetColorA' :: xlFontSetColor
        import
        type(FontHandle) handle
        integer(4) color
        end subroutine

        integer(4) function xlFontBold(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontBoldA' :: xlFontBold
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetBold(handle,bold)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetBoldA' :: xlFontSetBold
        import
        type(FontHandle) handle
        integer(4) bold
        end subroutine

        integer(4) function xlFontScript(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontScriptA' :: xlFontScript
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetScript(handle,script)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetScriptA' :: xlFontSetScript
        import
        type(FontHandle) handle
        integer(4) script
        end subroutine

        integer(4) function xlFontUnderline(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontUnderlineA' :: xlFontUnderline
        import
        type(FontHandle) handle
        end function

        subroutine xlFontSetUnderline(handle,underline)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetUnderlineA' :: xlFontSetUnderline
        import
        type(FontHandle) handle
        integer(4) underline
        end subroutine

        integer(4) function xlFontName(handle)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontNameA' :: xlFontName
        !DEC$ATTRIBUTES REFERENCE :: xlFontName
        import
        type(FontHandle) handle
        end function

        integer(4) function xlFontSetName(handle,name)
        !DEC$ATTRIBUTES C, DLLIMPORT, ALIAS:'xlFontSetNameA' :: xlFontSetName
        !DEC$ATTRIBUTES REFERENCE :: name
        import
        type(FontHandle) handle
        character(*) name
        end function

    end interface
    
    contains

        subroutine xlBookSetKey(handle,name,key)
            type(BookHandle) handle
            character(*) name,key
            integer i,ii,iii
            integer(2),allocatable,dimension(:) :: buff1,buff2
            i=len(name)
            ii=len(key)
            allocate(buff1(i+1),buff2(ii+1))
            iii = MBConvertMBToUnicode(name,buff1)
            iii = MBConvertMBToUnicode(key,buff2)
            buff1(i+1)=0
            buff2(ii+1)=0
            call xlBookSetKeyPrivate(handle,buff1,buff2)
            deallocate(buff1,buff2)
        end subroutine

end module
