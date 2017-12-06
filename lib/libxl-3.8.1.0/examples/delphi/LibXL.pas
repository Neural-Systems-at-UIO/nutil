unit LibXL;

{$Z4}

interface

uses SysUtils;

type
  AlignH = (ALIGNH_GENERAL, ALIGNH_LEFT, ALIGNH_CENTER, ALIGNH_RIGHT, ALIGNH_FILL, ALIGNH_JUSTIFY,
            ALIGNH_MERGE, ALIGNH_DISTRIBUTED);
type
  AlignV = (ALIGNV_TOP, ALIGNV_CENTER, ALIGNV_BOTTOM, ALIGNV_JUSTIFY, ALIGNV_DISTRIBUTED);

type
  BorderStyle = (BORDERSTYLE_NONE, BORDERSTYLE_THIN, BORDERSTYLE_MEDIUM, BORDERSTYLE_DASHED,
                 BORDERSTYLE_DOTTED, BORDERSTYLE_THICK, BORDERSTYLE_DOUBLE, BORDERSTYLE_HAIR,
                 BORDERSTYLE_MEDIUMDASHED, BORDERSTYLE_DASHDOT, BORDERSTYLE_MEDIUMDASHDOT,
                 BORDERSTYLE_DASHDOTDOT, BORDERSTYLE_MEDIUMDASHDOTDOT, BORDERSTYLE_SLANTDASHDOT);
type
  BorderDiagonal = (BORDERDIAGONAL_NONE, BORDERDIAGONAL_DOWN, BORDERDIAGONAL_UP,
                    BORDERDIAGONAL_BOTH);
type
  FillPattern = (FILLPATTERN_NONE, FILLPATTERN_SOLID, FILLPATTERN_GRAY50, FILLPATTERN_GRAY75,
                 FILLPATTERN_GRAY25, FILLPATTEN_HORSTRIPE, FILLPATTERN_VERSTRIPE,
                 FILLPATTERN_REVDIAGSTRIPE, FILLPATTERN_DIAGSTRIPE, FILLPATTERN_DIAGCROSSHATCH,
                 FILLPATTERN_THICKDIAGCROSSHATCH, FILLPATTERN_THINHORSTRIPE,
                 FILLPATTERN_THINVERSTRIPE, FILLPATTERN_THINREVDIAGSTRIPE,
                 FILLPATTERN_THINDIAGSTRIPE, FILLPATTERN_THINHORCROSSHATCH,
                 FILLPATTERN_THINDIAGCROSSHATCH, FILLPATTERN_GRAY12P5, FILLPATTERN_GRAY6P25);
type
  NumFormat = (NUMFORMAT_GENERAL, NUMFORMAT_NUMBER, NUMFORMAT_NUMBER_D2, NUMFORMAT_NUMBER_SEP,
               NUMFORMAT_NUMBER_SEP_D2, NUMFORMAT_CURRENCY_NEGBRA, NUMFORMAT_CURRENCY_NEGBRARED,
               NUMFORMAT_CURRENCY_D2_NEGBRA, NUMFORMAT_CURRENCY_D2_NEGBRARED, NUMFORMAT_PERCENT,
               NUMFORMAT_PERCENT_D2, NUMFORMAT_SCIENTIFIC_D2, NUMFORMAT_FRACTION_ONEDIG,
               NUMFORMAT_FRACTION_TWODIG, NUMFORMAT_DATE, NUMFORMAT_CUSTOM_D_MON_YY,
               NUMFORMAT_CUSTOM_D_MON, NUMFORMAT_CUSTOM_MON_YY, NUMFORMAT_CUSTOM_HMM_AM,
               NUMFORMAT_CUSTOM_HMMSS_AM, NUMFORMAT_CUSTOM_HMM, NUMFORMAT_CUSTOM_HMMSS,
               NUMFORMAT_CUSTOM_MDYYYY_HMM, NUMFORMAT_NUMBER_SEP_NEGBRA = 37,
               NUMFORMAT_NUMBER_SEP_NEGBRARED, NUMFORMAT_NUMBER_D2_SEP_NEGBRA,
               NUMFORMAT_NUMBER_D2_SEP_NEGBRARED, NUMFORMAT_ACCOUNT, NUMFORMAT_ACCOUNTCUR,
               NUMFORMAT_ACCOUNT_D2, NUMFORMAT_ACCOUNT_D2_CUR, NUMFORMAT_CUSTOM_MMSS,
               NUMFORMAT_CUSTOM_H0MMSS, NUMFORMAT_CUSTOM_MMSS0, NUMFORMAT_CUSTOM_000P0E_PLUS0,
               NUMFORMAT_TEXT);
type
  Color = (COLOR_BLACK = 8, COLOR_WHITE, COLOR_RED, COLOR_BRIGHTGREEN, COLOR_BLUE, COLOR_YELLOW,
           COLOR_PINK, COLOR_TURQUOISE, COLOR_DARKRED, COLOR_GREEN, COLOR_DARKBLUE,
           COLOR_DARKYELLOW, COLOR_VIOLET, COLOR_TEAL, COLOR_GRAY25, COLOR_GRAY50,
           COLOR_PERIWINKLE_CF, COLOR_PLUM_CF, COLOR_IVORY_CF, COLOR_LIGHTTURQUOISE_CF,
           COLOR_DARKPURPLE_CF, COLOR_CORAL_CF, COLOR_OCEANBLUE_CF, COLOR_ICEBLUE_CF,
           COLOR_DARKBLUE_CL, COLOR_PINK_CL, COLOR_YELLOW_CL, COLOR_TURQUOISE_CL, COLOR_VIOLET_CL,
           COLOR_DARKRED_CL, COLOR_TEAL_CL, COLOR_BLUE_CL, COLOR_SKYBLUE, COLOR_LIGHTTURQUOISE,
           COLOR_LIGHTGREEN, COLOR_LIGHTYELLOW, COLOR_PALEBLUE, COLOR_ROSE, COLOR_LAVENDER,
           COLOR_TAN, COLOR_LIGHTBLUE, COLOR_AQUA, COLOR_LIME, COLOR_GOLD, COLOR_LIGHTORANGE,
           COLOR_ORANGE, COLOR_BLUEGRAY, COLOR_GRAY40, COLOR_DARKTEAL, COLOR_SEAGREEN,
           COLOR_DARKGREEN, COLOR_OLIVEGREEN, COLOR_BROWN, COLOR_PLUM, COLOR_INDIGO, COLOR_GRAY80,
           COLOR_DEFAULT_FOREGROUND = $0040, COLOR_DEFAULT_BACKGROUND = $0041,
           COLOR_TOOLTIP = $0051, COLOR_AUTO = $7FFF);

type
  SheetType = (SHEETTYPE_SHEET, SHEETTYPE_CHART, SHEETTYPE_UNKNOWN);

type
  CellType = (CELLTYPE_EMPTY, CELLTYPE_NUMBER, CELLTYPE_STRING, CELLTYPE_BOOLEAN, CELLTYPE_BLANK,
              CELLTYPE_ERROR);
type
  ErrorType = (ERRORTYPE_NULL = $00, ERRORTYPE_DIV_0 = $07, ERRORTYPE_VALUE = $0F,
               ERRORTYPE_REF = $17, ERRORTYPE_NAME = $1D, ERRORTYPE_NUM = $24, ERRORTYPE_NA = $2A,
               ERRORTYPE_NOERROR = $FF);
type
  PictureType = (PICTURETYPE_PNG, PICTURETYPE_JPEG, PICTURETYPE_WMF, PICTURETYPE_DIB, PICTURETYPE_EMF,
                 PICTURETYPE_PICT, PICTURETYPE_TIFF, PICTURETYPE_ERROR = $FF);
type
  SheetState = (SHEETSTATE_VISIBLE, SHEETSTATE_HIDDEN, SHEETSTATE_VERYHIDDEN);
type
  Paper = (PAPER_DEFAULT, PAPER_LETTER, PAPER_LETTERSMALL, PAPER_TABLOID, PAPER_LEDGER, PAPER_LEGAL,
           PAPER_STATEMENT, PAPER_EXECUTIVE, PAPER_A3, PAPER_A4, PAPER_A4SMALL, PAPER_A5, PAPER_B4,
           PAPER_B5, PAPER_FOLIO, PAPER_QUATRO, PAPER_10x14, PAPER_10x17, PAPER_NOTE,
           PAPER_ENVELOPE_9, PAPER_ENVELOPE_10, PAPER_ENVELOPE_11, PAPER_ENVELOPE_12,
           PAPER_ENVELOPE_14, PAPER_C_SIZE, PAPER_D_SIZE, PAPER_E_SIZE, PAPER_ENVELOPE_DL,
           PAPER_ENVELOPE_C5, PAPER_ENVELOPE_C3, PAPER_ENVELOPE_C4, PAPER_ENVELOPE_C6,
           PAPER_ENVELOPE_C65, PAPER_ENVELOPE_B4, PAPER_ENVELOPE_B5, PAPER_ENVELOPE_B6,
           PAPER_ENVELOPE, PAPER_ENVELOPE_MONARCH, PAPER_US_ENVELOPE, PAPER_FANFOLD,
           PAPER_GERMAN_STD_FANFOLD, PAPER_GERMAN_LEGAL_FANFOLD, PAPER_B4_ISO,
           PAPER_JAPANESE_POSTCARD, PAPER_9x11, PAPER_10x11, PAPER_15x11, PAPER_ENVELOPE_INVITE,
           PAPER_US_LETTER_EXTRA = 50, PAPER_US_LEGAL_EXTRA, PAPER_US_TABLOID_EXTRA, PAPER_A4_EXTRA,
           PAPER_LETTER_TRANSVERSE, PAPER_A4_TRANSVERSE, PAPER_LETTER_EXTRA_TRANSVERSE,
           PAPER_SUPERA, PAPER_SUPERB, PAPER_US_LETTER_PLUS, PAPER_A4_PLUS, PAPER_A5_TRANSVERSE,
           PAPER_B5_TRANSVERSE, PAPER_A3_EXTRA, PAPER_A5_EXTRA, PAPER_B5_EXTRA, PAPER_A2,
           PAPER_A3_TRANSVERSE, PAPER_A3_EXTRA_TRANSVERSE, PAPER_JAPANESE_DOUBLE_POSTCARD, PAPER_A6,
           PAPER_JAPANESE_ENVELOPE_KAKU2, PAPER_JAPANESE_ENVELOPE_KAKU3,
           PAPER_JAPANESE_ENVELOPE_CHOU3, PAPER_JAPANESE_ENVELOPE_CHOU4, PAPER_LETTER_ROTATED,
           PAPER_A3_ROTATED, PAPER_A4_ROTATED, PAPER_A5_ROTATED, PAPER_B4_ROTATED, PAPER_B5_ROTATED,
           PAPER_JAPANESE_POSTCARD_ROTATED, PAPER_DOUBLE_JAPANESE_POSTCARD_ROTATED,
           PAPER_A6_ROTATED, PAPER_JAPANESE_ENVELOPE_KAKU2_ROTATED,
           PAPER_JAPANESE_ENVELOPE_KAKU3_ROTATED, PAPER_JAPANESE_ENVELOPE_CHOU3_ROTATED,
           PAPER_JAPANESE_ENVELOPE_CHOU4_ROTATED, PAPER_B6, PAPER_B6_ROTATED, PAPER_12x11,
           PAPER_JAPANESE_ENVELOPE_YOU4, PAPER_JAPANESE_ENVELOPE_YOU4_ROTATED, PAPER_PRC16K,
           PAPER_PRC32K, PAPER_PRC32K_BIG, PAPER_PRC_ENVELOPE1, PAPER_PRC_ENVELOPE2,
           PAPER_PRC_ENVELOPE3, PAPER_PRC_ENVELOPE4, PAPER_PRC_ENVELOPE5, PAPER_PRC_ENVELOPE6,
           PAPER_PRC_ENVELOPE7, PAPER_PRC_ENVELOPE8, PAPER_PRC_ENVELOPE9, PAPER_PRC_ENVELOPE10,
           PAPER_PRC16K_ROTATED, PAPER_PRC32K_ROTATED, PAPER_PRC32KBIG_ROTATED,
           PAPER_PRC_ENVELOPE1_ROTATED, PAPER_PRC_ENVELOPE2_ROTATED, PAPER_PRC_ENVELOPE3_ROTATED,
           PAPER_PRC_ENVELOPE4_ROTATED, PAPER_PRC_ENVELOPE5_ROTATED, PAPER_PRC_ENVELOPE6_ROTATED,
           PAPER_PRC_ENVELOPE7_ROTATED, PAPER_PRC_ENVELOPE8_ROTATED, PAPER_PRC_ENVELOPE9_ROTATED,
           PAPER_PRC_ENVELOPE10_ROTATED);
type
  Underline = (UNDERLINE_NONE, UNDERLINE_SINGLE, UNDERLINE_DOUBLE,
               UNDERLINE_SINGLEACC = $21, UNDERLINE_DOUBLEACC = $22);
type
  Script = (SCRIPT_NORMAL, SCRIPT_SUPER, SCRIPT_SUB);
type
  Scope = (SCOPE_UNDEFINED = -2, SCOPE_WORKBOOK = -1);
type
  Operator = (OPERATOR_EQUAL, OPERATOR_GREATER_THAN, OPERATOR_GREATER_THAN_OR_EQUAL, OPERATOR_LESS_THAN, OPERATOR_LESS_THAN_OR_EQUAL, OPERATOR_NOT_EQUAL );

type
  Filter = (FILTER_VALUE, FILTER_TOP10, FILTER_CUSTOM, FILTER_DYNAMIC, FILTER_COLOR, FILTER_ICON, FILTER_EXT, FILTER_NOT_SET);

type
  EnhancedProtection = (PROT_DEFAULT = -1, PROT_ALL = 0, PROT_OBJECTS = 1, PROT_SCENARIOS = 2, PROT_FORMAT_CELLS = 4, PROT_FORMAT_COLUMNS = 8, PROT_FORMAT_ROWS = 16,
                        PROT_INSERT_COLUMNS = 32, PROT_INSERT_ROWS = 64, PROT_INSERT_HYPERLINKS = 128, PROT_DELETE_COLUMNS = 256, PROT_DELETE_ROWS = 512,
                        PROT_SEL_LOCKED_CELLS = 1024, PROT_SORT = 2048, PROT_AUTOFILTER = 4096, PROT_PIVOTTABLES = 8192, PROT_SEL_UNLOCKED_CELLS = 16384);
type
  IgnoredError = (IERR_NO_ERROR = 0, IERR_EVAL_ERROR = 1, IERR_EMPTY_CELLREF = 2, IERR_NUMBER_STORED_AS_TEXT = 4, IERR_INCONSIST_RANGE = 8,
                  IERR_INCONSIST_FMLA = 16, IERR_TWODIG_TEXTYEAR = 32, IERR_UNLOCK_FMLA = 64, IERR_DATA_VALIDATION = 128);

type
  DataValidationType = (VALIDATION_TYPE_NONE, VALIDATION_TYPE_WHOLE, VALIDATION_TYPE_DECIMAL, VALIDATION_TYPE_LIST,
                        VALIDATION_TYPE_DATE, VALIDATION_TYPE_TIME, VALIDATION_TYPE_TEXTLENGTH, VALIDATION_TYPE_CUSTOM);

type
  DataValidationOperator = (VALIDATION_OP_BETWEEN, VALIDATION_OP_NOTBETWEEN, VALIDATION_OP_EQUAL, VALIDATION_OP_NOTEQUAL,
                            VALIDATION_OP_LESSTHAN, VALIDATION_OP_LESSTHANOREQUAL, VALIDATION_OP_GREATERTHAN, VALIDATION_OP_GREATERTHANOREQUAL);

type
  DataValidationErrorStyle = (VALIDATION_ERRSTYLE_STOP, VALIDATION_ERRSTYLE_WARNING, VALIDATION_ERRSTYLE_INFORMATION);

type
  BookHandle = Pointer;
type
  SheetHandle = Pointer;
type
  FormatHandle = Pointer;
type
  FontHandle = Pointer;
type
  PFormatHandle = ^FormatHandle;
type
  AutoFilterHandle = Pointer;
type
  FilterColumnHandle = Pointer;
type
  ByteArray = array of byte;
type
  PByteArray = ^ByteArray;
type
  PCardinal = ^Cardinal;
type
  PInteger = ^Integer;
type
  PBoolean = ^boolean;
type
  PDouble = ^double;

////////////////////////////////////////////////////////////////////////////////////////////////////

function xlCreateBookC(): BookHandle cdecl;
external 'libxl' name 'xlCreateBookCA';

function xlCreateXMLBookC(): BookHandle cdecl;
external 'libxl' name 'xlCreateXMLBookCA';

function xlBookLoad(handle: BookHandle; filename: PAnsiChar): Integer cdecl;
external 'libxl' name 'xlBookLoadA';

function xlBookSave(handle: BookHandle; filename: PAnsiChar): Integer cdecl;
external 'libxl' name 'xlBookSaveA';

function xlBookLoadRaw(handle: BookHandle; data: PByteArray; size: Cardinal): Integer cdecl;
external 'libxl' name 'xlBookLoadRawA';

function xlBookSaveRaw(handle: BookHandle; data: PByteArray; size: PCardinal): Integer cdecl;
external 'libxl' name 'xlBookSaveRawA';

function xlBookAddSheet(handle: BookHandle; name: PAnsiChar; initSheet: SheetHandle): SheetHandle cdecl;
external 'libxl' name 'xlBookAddSheetA';

function xlBookInsertSheet(handle: BookHandle; index: Integer; name: PAnsiChar; initSheet: SheetHandle): SheetHandle cdecl;
external 'libxl' name 'xlBookInsertSheetA';

function xlBookGetSheet(handle: BookHandle; index: Integer): SheetHandle cdecl;
external 'libxl' name 'xlBookGetSheetA';

function xlBookSheetType(handle: BookHandle; index: Integer): Integer cdecl;
external 'libxl' name 'xlBookSheetTypeA';

function xlBookMoveSheet(handle: BookHandle; srcIndex: Integer; dstIndex: Integer): Integer cdecl;
external 'libxl' name 'xlBookMoveSheetA';

function xlBookDelSheet(handle: BookHandle; index: Integer): Integer cdecl;
external 'libxl' name 'xlBookDelSheetA';

function xlBookSheetCount(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookSheetCountA';

function xlBookAddFormat(handle: BookHandle; initFormat: FormatHandle): FormatHandle cdecl;
external 'libxl' name 'xlBookAddFormatA';

function xlBookAddFont(handle: BookHandle; initFont: FormatHandle): FontHandle cdecl;
external 'libxl' name 'xlBookAddFontA';

function xlBookAddCustomNumFormat(handle: BookHandle; const customNumFormat: PAnsiChar): Integer cdecl;
external 'libxl' name 'xlBookAddCustomNumFormatA';

function xlBookCustomNumFormat(handle: BookHandle; fmt: Integer): PAnsiChar cdecl;
external 'libxl' name 'xlBookCustomNumFormatA';

function xlBookFormat(handle: BookHandle; index: Integer): FormatHandle cdecl;
external 'libxl' name 'xlBookFormatA';

function xlBookFormatSize(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookFormatSizeA';

function xlBookFont(handle: BookHandle; index: Integer): FontHandle cdecl;
external 'libxl' name 'xlBookFontA';

function xlBookFontSize(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookFontSizeA';

function xlBookDatePack(handle: BookHandle; year: Integer; month: Integer; day: Integer; hour: Integer; min: Integer; sec: Integer; msec: Integer): double cdecl;
external 'libxl' name 'xlBookDatePackA';

function xlBookDateUnpack(handle: BookHandle; value: double; year: PInteger; month: PInteger; day: PInteger; hour: PInteger; min: PInteger; sec: PInteger; msec: PInteger): Integer cdecl;
external 'libxl' name 'xlBookDateUnpackA';

function xlBookColorPack(handle: BookHandle; red: Integer; green: Integer; blue: Integer): Integer cdecl;
external 'libxl' name 'xlBookColorPackA';

procedure xlBookColorUnpack(handle: BookHandle; color: Integer; red: PInteger; green: PInteger; blue: PInteger) cdecl;
external 'libxl' name 'xlBookColorUnpackA';

function xlBookActiveSheet(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookActiveSheetA';

procedure xlBookSetActiveSheet(handle: BookHandle; index: Integer) cdecl;
external 'libxl' name 'xlBookSetActiveSheetA';

function xlBookPictureSize(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookPictureSizeA';

function xlBookGetPicture(hanlde: BookHandle; index: Integer; data: PByteArray; size: PCardinal): Integer cdecl;
external 'libxl' name 'xlBookGetPictureA';

function xlBookAddPicture(handle: BookHandle; filename: PAnsiChar): Integer cdecl;
external 'libxl' name 'xlBookAddPictureA';

function xlBookAddPicture2(handle: BookHandle; data: PByteArray; size: Cardinal): Integer cdecl;
external 'libxl' name 'xlBookAddPicture2A';

function xlBookAddPictureAsLink(handle: BookHandle; filename: PAnsiChar; insert: Integer): Integer cdecl;
external 'libxl' name 'xlBookAddPictureAsLinkA';

function xlBookDefaultFont(handle: BookHandle; fontSize: PInteger): PAnsiChar cdecl;
external 'libxl' name 'xlBookDefaultFontA';

procedure xlBookSetDefaultFont(handle: BookHandle; const name: PAnsiChar; fontSize: Integer) cdecl;
external 'libxl' name 'xlBookSetDefaultFontA';

function xlBookRefR1C1(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookRefR1C1A';

procedure xlBookSetRefR1C1(handle: BookHandle; refR1C1: Integer) cdecl;
external 'libxl' name 'xlBookSetRefR1C1A';

procedure xlBookSetKey(handle: BookHandle; const name: PAnsiChar; const key: PAnsiChar) cdecl;
external 'libxl' name 'xlBookSetKeyA';

function xlBookRgbMode(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookRgbModeA';

procedure xlBookSetRgbMode(handle: BookHandle; rgbMode: Integer) cdecl;
external 'libxl' name 'xlBookSetRgbModeA';

function xlBookIsDate1904(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookIsDate1904A';

procedure xlBookSetDate1904(handle: BookHandle; date1904: Integer) cdecl;
external 'libxl' name 'xlBookSetDate1904A';

function xlBookIsTemplate(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookIsTemplateA';

procedure xlBookSetTemplate(handle: BookHandle; tmpl: Integer) cdecl;
external 'libxl' name 'xlBookSetTemplateA';

function xlBookBiffVersion(handle: BookHandle): Integer cdecl;
external 'libxl' name 'xlBookBiffVersionA';

procedure xlBookSetLocale(handle: BookHandle; const locale: PAnsiChar) cdecl;
external 'libxl' name 'xlBookSetLocaleA';

function xlBookErrorMessage(handle: BookHandle): PAnsiChar cdecl;
external 'libxl' name 'xlBookErrorMessageA';

procedure xlBookRelease(handle: BookHandle) cdecl;
external 'libxl' name 'xlBookReleaseA';

////////////////////////////////////////////////////////////////////////////////////////////////////

function xlSheetCopyCell(handle: SheetHandle; rowSrc, colSrc, rowDst, colDst: Integer): Integer cdecl;
external 'libxl' name 'xlSheetCopyCellA';

function xlSheetCellType(handle: SheetHandle; row: Integer; col: Integer): Integer cdecl;
external 'libxl' name 'xlSheetCellTypeA';

function xlSheetReadStr(handle: SheetHandle; row: Integer; col: Integer; format: PFormatHandle): PAnsiChar cdecl;
external 'libxl' name 'xlSheetReadStrA';

function xlSheetWriteStr(handle: SheetHandle; row: Integer; col: Integer; value: PAnsiChar; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteStrA';

function xlSheetReadNum(handle: SheetHandle; row: Integer; col: Integer; format: PFormatHandle): double cdecl;
external 'libxl' name 'xlSheetReadNumA';

function xlSheetWriteNum(handle: SheetHandle; row: Integer; col: Integer; value: double; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteNumA';

function xlSheetReadBool(handle: SheetHandle; row: Integer; col: Integer; format: PFormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetReadBoolA';

function xlSheetWriteBool(handle: SheetHandle; row: Integer; col: Integer; value: Integer; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteBoolA';

function xlSheetReadBlank(handle: SheetHandle; row: Integer; col: Integer; format: PFormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetReadBlankA';

function xlSheetWriteBlank(handle: SheetHandle; row: Integer; col: Integer; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteBlankA';

function xlSheetReadComment(handle: SheetHandle; row: Integer; col: Integer): PAnsiChar cdecl;
external 'libxl' name 'xlSheetReadCommentA';

procedure xlSheetWriteComment(handle: SheetHandle; row: Integer; col: Integer; const value: PAnsiChar; const author: PAnsiChar; width: Integer; height: Integer) cdecl;
external 'libxl' name 'xlSheetWriteCommentA';

procedure xlSheetRemoveComment(handle: SheetHandle; row: Integer; col: Integer) cdecl;
external 'libxl' name 'xlSheetRemoveCommentA';

function xlSheetIsDate(handle: SheetHandle; row: Integer; col: Integer): Integer cdecl;
external 'libxl' name 'xlSheetIsDateA';

function xlSheetReadError(handle: SheetHandle; row: Integer; col: Integer): Integer cdecl;
external 'libxl' name 'xlSheetReadErrorA';

procedure xlSheetWriteError(handle: SheetHandle; row: Integer; col: Integer; error: Integer; format: FormatHandle) cdecl;
external 'libxl' name 'xlSheetWriteErrorA';

function xlSheetColWidth(handle: SheetHandle; col: Integer): double cdecl;
external 'libxl' name 'xlSheetColWidthA';

function xlSheetRowHeight(handle: SheetHandle; row: Integer): double cdecl;
external 'libxl' name 'xlSheetRowHeightA';

function xlSheetSetCol(handle: SheetHandle; colFirst: Integer; colLast: Integer; width: double; format: FormatHandle; hidden: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetColA';

function xlSheetSetRow(handle: SheetHandle; row: Integer; height: double; format: FormatHandle; hidden: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetRowA';

function xlSheetRowHidden(handle: SheetHandle; row: Integer): Integer cdecl;
external 'libxl' name 'xlSheetRowHiddenA';

function xlSheetSetRowHidden(handle: SheetHandle; row: Integer; hidden: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetRowHiddenA';

function xlSheetColHidden(handle: SheetHandle; col: Integer): Integer cdecl;
external 'libxl' name 'xlSheetColHiddenA';

function xlSheetSetColHidden(handle: SheetHandle; col: Integer; hidden: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetColHiddenA';

function xlSheetGetMerge(handle: SheetHandle; row: Integer; col: Integer; rowFirst: PInteger; rowLast: PInteger; colFirst: PInteger; colLast: PInteger) : Integer cdecl;
external 'libxl' name 'xlSheetGetMergeA';

function xlSheetSetMerge(handle: SheetHandle; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetMergeA';

function xlSheetDelMerge(handle: SheetHandle; row: Integer; col: Integer): Integer cdecl;
external 'libxl' name 'xlSheetDelMergeA';

function xlSheetPictureSize(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetPictureSizeA';

function xlSheetGetPicture(handle: SheetHandle; index: Integer; rowTop: PInteger; colLeft: PInteger; rowBottom: PInteger; colRight: PInteger;
                                                 width: PInteger; height: PInteger; offset_x: PInteger; offset_y: PInteger): Integer cdecl;
external 'libxl' name 'xlSheetGetPictureA';

procedure xlSheetSetPicture(handle: SheetHandle; row: Integer; col: Integer; pictureId: Integer; scale: double; offset_x: Integer; offset_y: Integer; pos: Integer) cdecl;
external 'libxl' name 'xlSheetSetPictureA';

procedure xlSheetSetPicture2(handle: SheetHandle; row: Integer; col: Integer; pictureId: Integer; widht: Integer; height: Integer; offset_x: Integer; offset_y: Integer; pos: Integer) cdecl;
external 'libxl' name 'xlSheetSetPicture2A';

function xlSheetGetHorPageBreak(handle: SheetHandle; index: Integer): Integer cdecl;
external 'libxl' name 'xlSheetGetHorPageBreakA';

function xlSheetGetHorPageBreakSize(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetGetHorPageBreakSizeA';

function xlSheetGetVerPageBreak(handle: SheetHandle; index: Integer): Integer cdecl;
external 'libxl' name 'xlSheetGetVerPageBreakA';

function xlSheetGetVerPageBreakSize(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetGetVerPageBreakSizeA';

function xlSheetSetHorPageBreak(handle: SheetHandle; row: Integer; pageBreak: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetHorPageBreakA';

function xlSheetSetVerPageBreak(handle: SheetHandle; col: Integer; pageBreak: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetVerPageBreakA';

procedure xlSheetSplit(handle: SheetHandle; row: Integer; col: Integer) cdecl;
external 'libxl' name 'xlSheetSplitA';

function xlSheetGroupRows(handle: SheetHandle; rowFirst: Integer; rowLast: Integer; collapsed: Integer): Integer cdecl;
external 'libxl' name 'xlSheetGroupRowsA';

function xlSheetGroupCols(handle: SheetHandle; colFirst: Integer; colLast: Integer; collapsed: Integer): Integer cdecl;
external 'libxl' name 'xlSheetGroupColsA';

function xlSheetGroupSummaryBelow(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetGroupSummaryBelowA';

procedure xlSheetSetGroupSummaryBelow(handle: SheetHandle; below: Integer) cdecl;
external 'libxl' name 'xlSheetSetGroupSummaryBelowA';

function xlSheetGroupSummaryRight(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetGroupSummaryRightA';

procedure xlSheetSetGroupSummaryRight(handle: SheetHandle; right: Integer) cdecl;
external 'libxl' name 'xlSheetSetGroupSummaryRightA';

procedure xlSheetClear(handle: SheetHandle; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer) cdecl;
external 'libxl' name 'xlSheetClearA';

function xlSheetInsertCol(handle: SheetHandle; colFirst: Integer; colLast: Integer): Integer cdecl;
external 'libxl' name 'xlSheetInsertColA';

function xlSheetInsertRow(handle: SheetHandle; rowFirst: Integer; rowLast: Integer): Integer cdecl;
external 'libxl' name 'xlSheetInsertRowA';

function xlSheetRemoveCol(handle: SheetHandle; colFirst: Integer; colLast: Integer): Integer cdecl;
external 'libxl' name 'xlSheetRemoveColA';

function xlSheetRemoveRow(handle: SheetHandle; rowFirst: Integer; rowLast: Integer): Integer cdecl;
external 'libxl' name 'xlSheetRemoveRowA';

function xlSheetFirstRow(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetFirstRowA';

function xlSheetLastRow(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetLastRowA';

function xlSheetFirstCol(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetFirstColA';

function xlSheetLastCol(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetLastColA';

function xlSheetDisplayGridlines(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetDisplayGridlinesA';

procedure xlSheetSetDisplayGridlines(handle: SheetHandle; show: Integer) cdecl;
external 'libxl' name 'xlSheetSetDisplayGridlinesA';

function xlSheetPrintGridlines(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetPrintGridlinesA';

procedure xlSheetSetPrintGridlines(handle: SheetHandle; print: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintGridlinesA';

function xlSheetZoom(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetZoomA';

procedure xlSheetSetZoom(handle: SheetHandle; print: Integer) cdecl;
external 'libxl' name 'xlSheetSetZoomA';

function xlSheetPrintZoom(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetPrintZoomA';

procedure xlSheetSetPrintZoom(handle: SheetHandle; print: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintZoomA';

function xlSheetGetPrintFit(handle: SheetHandle; wPages: PInteger; hPages: PInteger): Integer cdecl;
external 'libxl' name 'xlSheetGetPrintFitA';

procedure xlSheetSetPrintFit(handle: SheetHandle; wPages: Integer; hPages: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintFitA';

function xlSheetLandscape(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetLandscapeA';

procedure xlSheetSetLandscape(handle: SheetHandle; landscape: Integer) cdecl;
external 'libxl' name 'xlSheetSetLandscapeA';

function xlSheetPaper(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetPaperA';

procedure xlSheetSetPaper(handle: SheetHandle; Paper: Integer) cdecl;
external 'libxl' name 'xlSheetSetPaperA';

function xlSheetHeader(handle: SheetHandle): PAnsiChar cdecl;
external 'libxl' name 'xlSheetHeaderA';

function xlSheetSetHeader(handle: SheetHandle; const header: PAnsiChar; margin: double): Integer cdecl;
external 'libxl' name 'xlSheetSetHeaderA';

function xlSheetHeaderMargin(handle: SheetHandle): double cdecl;
external 'libxl' name 'xlSheetHeaderMarginA';

function xlSheetFooter(handle: SheetHandle): PAnsiChar cdecl;
external 'libxl' name 'xlSheetFooterA';

function xlSheetSetFooter(handle: SheetHandle; const footer: PAnsiChar; margin: double): Integer cdecl;
external 'libxl' name 'xlSheetSetFooterA';

function xlSheetFooterMargin(handle: SheetHandle): double cdecl;
external 'libxl' name 'xlSheetFooterMarginA';

function xlSheetHCenter(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetHCenterA';

procedure xlSheetSetHCenter(handle: SheetHandle; hCenter: Integer) cdecl;
external 'libxl' name 'xlSheetSetHCenterA';

function xlSheetVCenter(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetVCenterA';

procedure xlSheetSetVCenter(handle: SheetHandle; vCenter: Integer) cdecl;
external 'libxl' name 'xlSheetSetVCenterA';

function xlSheetMarginLeft(handle: SheetHandle): double cdecl;
external 'libxl' name 'xlSheetMarginLeftA';

procedure xlSheetSetMarginLeft(handle: SheetHandle; margin: double) cdecl;
external 'libxl' name 'xlSheetSetMarginLeftA';

function xlSheetMarginRight(handle: SheetHandle): double cdecl;
external 'libxl' name 'xlSheetMarginRightA';

procedure xlSheetSetMarginRight(handle: SheetHandle; margin: double) cdecl;
external 'libxl' name 'xlSheetSetMarginRightA';

function xlSheetMarginTop(handle: SheetHandle): double cdecl;
external 'libxl' name 'xlSheetMarginTopA';

procedure xlSheetSetMarginTop(handle: SheetHandle; margin: double) cdecl;
external 'libxl' name 'xlSheetSetMarginTopA';

function xlSheetMarginBottom(handle: SheetHandle): double cdecl;
external 'libxl' name 'xlSheetMarginBottomA';

procedure xlSheetSetMarginBottom(handle: SheetHandle; margin: double) cdecl;
external 'libxl' name 'xlSheetSetMarginBottomA';

function xlSheetPrintRowCol(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetPrintRowColA';

procedure xlSheetSetPrintRowCol(handle: SheetHandle; print: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintRowColA';

function xlSheetProtect(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetProtectA';

procedure xlSheetSetProtect(handle: SheetHandle; protect: Integer) cdecl;
external 'libxl' name 'xlSheetSetProtectA';

procedure xlSheetSetProtectEx(handle: SheetHandle; protect: Integer; const name: PAnsiChar; enhancedProtection: Integer) cdecl;
external 'libxl' name 'xlSheetSetProtectExA';

function xlSheetRightToLeft(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetRightToLeftA';

procedure xlSheetSetRightToLeft(handle: SheetHandle; rightToLeft: Integer) cdecl;
external 'libxl' name 'xlSheetSetRightToLeftA';

procedure xlSheetSetPrintRepeatRows(handle: SheetHandle; rowFirst: Integer; rowLast: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintRepeatRowsA';

procedure xlSheetSetPrintRepeatCols(handle: SheetHandle; colFirst: Integer; colLast: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintRepeatColsA';

procedure xlSheetSetPrintArea(handle: SheetHandle; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer) cdecl;
external 'libxl' name 'xlSheetSetPrintAreaA';

procedure xlSheetClearPrintRepeats(handle: SheetHandle) cdecl;
external 'libxl' name 'xlSheetClearPrintRepeatsA';

procedure xlSheetClearPrintArea(handle: SheetHandle) cdecl;
external 'libxl' name 'xlSheetClearPrintAreaA';

function xlSheetGetNamedRange(handle: SheetHandle; const name: PAnsiChar; rowFirst: PInteger; rowLast: PInteger; colFirst: PInteger; colLast: PInteger; scopeId: Integer; hidden: PBoolean): Integer cdecl;
external 'libxl' name 'xlSheetGetNamedRangeA';

function xlSheetSetNamedRange(handle: SheetHandle; const name: PAnsiChar; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; scopeId: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetNamedRangeA';

function xlSheetDelNamedRange(handle: SheetHandle; const name: PAnsiChar; scopeId: Integer): Integer cdecl;
external 'libxl' name 'xlSheetDelNamedRangeA';

function xlSheetNamedRangeSize(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetNamedRangeSizeA';

function xlSheetNamedRange(handle: SheetHandle; index: Integer; rowFirst: PInteger; rowLast: PInteger; colFirst: PInteger; colLast: PInteger; scopeId: PInteger; hidden: PBoolean): PAnsiChar cdecl;
external 'libxl' name 'xlSheetNamedRangeA';

function xlSheetTableSize(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetTableSizeA';

function xlSheetTable(handle: SheetHandle; index: Integer; rowFirst: PInteger; rowLast: PInteger; colFirst: PInteger; colLast: PInteger; headerRowCount: PInteger; totalsRowCount: PInteger): PAnsiChar cdecl;
external 'libxl' name 'xlSheetTableA';

function xlSheetHyperlinkSize(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetHyperlinkSizeA';

function xlSheetHyperlink(handle: SheetHandle; index: Integer; rowFirst: PInteger; rowLast: PInteger; colFirst: PInteger; colLast: PInteger): PAnsiChar cdecl;
external 'libxl' name 'xlSheetHyperlinkA';

function xlSheetDelHyperlink(handle: SheetHandle; index: Integer): Integer cdecl;
external 'libxl' name 'xlSheetDelHyperlinkA';

procedure xlSheetAddHyperlink(handle: SheetHandle; const hyperlink: PAnsiChar; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer) cdecl;
external 'libxl' name 'xlSheetAddHyperlinkA';

function xlSheetAutoFilter(handle: SheetHandle): AutoFilterHandle cdecl;
external 'libxl' name 'xlSheetAutoFilterA';

procedure xlSheetApplyFilter(handle: SheetHandle) cdecl;
external 'libxl' name 'xlSheetApplyFilterA';

procedure xlSheetRemoveFilter(handle: SheetHandle) cdecl;
external 'libxl' name 'xlSheetRemoveFilterA';

function xlSheetName(handle: SheetHandle): PAnsiChar cdecl;
external 'libxl' name 'xlSheetNameA';

procedure xlSheetSetName(handle: SheetHandle; const name: PAnsiChar) cdecl;
external 'libxl' name 'xlSheetSetNameA';

function xlSheetCellFormat(handle: SheetHandle; row: Integer; col: Integer): FormatHandle cdecl;
external 'libxl' name 'xlSheetCellFormatA';

procedure xlSheetSetCellFormat(handle: SheetHandle; row: Integer; col: Integer; format: PFormatHandle) cdecl;
external 'libxl' name 'xlSheetSetCellFormatA';

function xlSheetIsFormula(handle: SheetHandle; row: Integer; col: Integer): Integer cdecl;
external 'libxl' name 'xlSheetIsFormulaA';

function xlSheetReadFormula(handle: SheetHandle; row: Integer; col: Integer; format: PFormatHandle): PAnsiChar cdecl;
external 'libxl' name 'xlSheetReadFormulaA';

function xlSheetWriteFormula(handle: SheetHandle; row: Integer; col: Integer; value: PAnsiChar; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteFormulaA';

function xlSheetWriteFormulaNum(handle: SheetHandle; row: Integer; col: Integer; expr: PAnsiChar; value: double; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteFormulaNumA';

function xlSheetWriteFormulaStr(handle: SheetHandle; row: Integer; col: Integer; expr: PAnsiChar; value: PAnsiChar; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteFormulaStrA';

function xlSheetWriteFormulaBool(handle: SheetHandle; row: Integer; col: Integer; expr: PAnsiChar; value: Integer; format: FormatHandle): Integer cdecl;
external 'libxl' name 'xlSheetWriteFormulaBoolA';

function xlSheetHidden(handle: SheetHandle): Integer cdecl;
external 'libxl' name 'xlSheetHiddenA';

function xlSheetSetHidden(handle: SheetHandle; hidden: Integer): Integer cdecl;
external 'libxl' name 'xlSheetSetHiddenA';

procedure xlSheetAddrToRowCol(handle: SheetHandle; const name: PAnsiChar; row: PInteger; col: PInteger; rowRelative: PInteger; colRelative: PInteger) cdecl;
external 'libxl' name 'xlSheetAddrToRowColA';

function xlSheetRowColToAddr(handle: SheetHandle; row: Integer; col: Integer; rowRelative: Integer; colRelative: Integer): PAnsiChar cdecl;
external 'libxl' name 'xlSheetRowColToAddrA';

procedure xlSheetSetTabColor(handle: SheetHandle; color: Integer) cdecl;
external 'libxl' name 'xlSheetSetTabColorA';

procedure xlSheetSetTabRgbColor(handle: SheetHandle; red: Integer; green: Integer; blue: Integer) cdecl;
external 'libxl' name 'xlSheetSetTabRgbColorA';

function xlSheetAddIgnoredError(handle: SheetHandle; rowFirst: Integer; colFirst: Integer; rowLast: Integer; colLast: Integer; iError: Integer): Integer cdecl;
external 'libxl' name 'xlSheetAddIgnoredErrorA';

procedure xlSheetAddDataValidation(handle: SheetHandle; vtype: Integer; op: Integer; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: PAnsiChar; value2: PAnsiChar) cdecl;
external 'libxl' name 'xlSheetAddDataValidationA';

procedure xlSheetAddDataValidationEx(handle: SheetHandle; vtype: Integer; op: Integer; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: PAnsiChar; value2: PAnsiChar;
                                     allowBlank: Integer; hideDropDown: Integer; showInputMessage: Integer; showErrorMessage: Integer; promptTitle: PAnsiChar; prompt: PAnsiChar;
                                     errorTitle: PAnsiChar; error: PAnsiChar; errorStyle: Integer) cdecl;
external 'libxl' name 'xlSheetAddDataValidationExA';

procedure xlSheetAddDataValidationDouble(handle: SheetHandle; vtype: Integer; op: Integer; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: double; value2: double) cdecl;
external 'libxl' name 'xlSheetAddDataValidationDoubleA';

procedure xlSheetAddDataValidationDoubleEx(handle: SheetHandle; vtype: Integer; op: Integer; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: double; value2: double;
                                     allowBlank: Integer; hideDropDown: Integer; showInputMessage: Integer; showErrorMessage: Integer; promptTitle: PAnsiChar; prompt: PAnsiChar;
                                     errorTitle: PAnsiChar; error: PAnsiChar; errorStyle: Integer) cdecl;
external 'libxl' name 'xlSheetAddDataValidationDoubleExA';

procedure xlSheetRemoveDataValidations(handle: SheetHandle) cdecl;
external 'libxl' name 'xlSheetRemoveDataValidationsA';

////////////////////////////////////////////////////////////////////////////////////////////////////

function xlFormatFont(handle: FormatHandle): FontHandle cdecl;
external 'libxl' name 'xlFormatFontA';

function xlFormatSetFont(handle: FormatHandle; FontHandle: FontHandle): FontHandle cdecl;
external 'libxl' name 'xlFormatSetFontA';

function xlFormatNumFormat(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatNumFormatA';

procedure xlFormatSetNumFormat(handle: FormatHandle; NumFormat: Integer) cdecl;
external 'libxl' name 'xlFormatSetNumFormatA';

function xlFormatAlignH(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatAlignHA';

procedure xlFormatSetAlignH(handle: FormatHandle; align: Integer) cdecl;
external 'libxl' name 'xlFormatSetAlignHA';

function xlFormatAlignV(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatAlignVA';

procedure xlFormatSetAlignV(handle: FormatHandle; align: Integer) cdecl;
external 'libxl' name 'xlFormatSetAlignVA';

function xlFormatWrap(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatWrapA';

procedure xlFormatSetWrap(handle: FormatHandle; wrap: Integer) cdecl;
external 'libxl' name 'xlFormatSetWrapA';

function xlFormatRotation(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatRotationA';

function xlFormatSetRotation(handle: FormatHandle; rotation: Integer): Integer cdecl;
external 'libxl' name 'xlFormatSetRotationA';

function xlFormatIndent(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatIndentA';

procedure xlFormatSetIndent(handle: FormatHandle; indent: Integer) cdecl;
external 'libxl' name 'xlFormatSetIndentA';

function xlFormatShrinkToFit(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatShrinkToFitA';

procedure xlFormatSetShrinkToFit(handle: FormatHandle; shrinkToFit: Integer) cdecl;
external 'libxl' name 'xlFormatSetShrinkToFitA';

procedure xlFormatSetBorder(handle: FormatHandle; style: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderA';

procedure xlFormatSetBorderColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderColorA';

function xlFormatBorderLeft(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderLeftA';

procedure xlFormatSetBorderLeft(handle: FormatHandle; style: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderLeftA';

function xlFormatBorderRight(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderRightA';

procedure xlFormatSetBorderRight(handle: FormatHandle; style: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderRightA';

function xlFormatBorderTop(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderTopA';

procedure xlFormatSetBorderTop(handle: FormatHandle; style: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderTopA';

function xlFormatBorderBottom(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderBottomA';

procedure xlFormatSetBorderBottom(handle: FormatHandle; style: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderBottomA';

function xlFormatBorderLeftColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderLeftColorA';

procedure xlFormatSetBorderLeftColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderLeftColorA';

function xlFormatBorderRightColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderRightColorA';

procedure xlFormatSetBorderRightColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderRightColorA';

function xlFormatBorderTopColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderTopColorA';

procedure xlFormatSetBorderTopColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderTopColorA';

function xlFormatBorderBottomColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderBottomColorA';

procedure xlFormatSetBorderBottomColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderBottomColorA';

function xlFormatBorderDiagonal(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderDiagonalA';

procedure xlFormatSetBorderDiagonal(handle: FormatHandle; border: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderDiagonalA';

function xlFormatBorderDiagonalStyle(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderDiagonalStyleA';

procedure xlFormatSetBorderDiagonalStyle(handle: FormatHandle; style: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderDiagonalStyleA';

function xlFormatBorderDiagonalColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatBorderDiagonalColorA';

procedure xlFormatSetBorderDiagonalColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetBorderDiagonalColorA';

function xlFormatFillPattern(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatFillPatternA';

procedure xlFormatSetFillPattern(handle: FormatHandle; pattern: Integer) cdecl;
external 'libxl' name 'xlFormatSetFillPatternA';

function xlFormatPatternForegroundColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatPatternForegroundColorA';

procedure xlFormatSetPatternForegroundColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetPatternForegroundColorA';

function xlFormatPatternBackgroundColor(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatPatternBackgroundColorA';

procedure xlFormatSetPatternBackgroundColor(handle: FormatHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFormatSetPatternBackgroundColorA';

function xlFormatLocked(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatLockedA';

procedure xlFormatSetLocked(handle: FormatHandle; locked: Integer) cdecl;
external 'libxl' name 'xlFormatSetLockedA';

function xlFormatHidden(handle: FormatHandle): Integer cdecl;
external 'libxl' name 'xlFormatHiddenA';

procedure xlFormatSetHidden(handle: FormatHandle; hidden: Integer) cdecl;
external 'libxl' name 'xlFormatSetHiddenA';

////////////////////////////////////////////////////////////////////////////////////////////////////

function xlFontSize(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontSizeA';

procedure xlFontSetSize(handle: FontHandle; size: Integer) cdecl;
external 'libxl' name 'xlFontSetSizeA';

function xlFontItalic(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontItalicA';

procedure xlFontSetItalic(handle: FontHandle; italic: Integer) cdecl;
external 'libxl' name 'xlFontSetItalicA';

function xlFontStrikeOut(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontStrikeOutA';

procedure xlFontSetStrikeOut(handle: FontHandle; strikeOut: Integer) cdecl;
external 'libxl' name 'xlFontSetStrikeOutA';

function xlFontColor(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontColorA';

procedure xlFontSetColor(handle: FontHandle; Color: Integer) cdecl;
external 'libxl' name 'xlFontSetColorA';

function xlFontBold(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontBoldA';

procedure xlFontSetBold(handle: FontHandle; bold: Integer) cdecl;
external 'libxl' name 'xlFontSetBoldA';

function xlFontScript(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontScriptA';

procedure xlFontSetScript(handle: FontHandle; Script: Integer) cdecl;
external 'libxl' name 'xlFontSetScriptA';

function xlFontUnderline(handle: FontHandle): Integer cdecl;
external 'libxl' name 'xlFontUnderlineA';

procedure xlFontSetUnderline(handle: FontHandle; Underline: Integer) cdecl;
external 'libxl' name 'xlFontSetUnderlineA';

function xlFontName(handle: FontHandle): PAnsiChar cdecl;
external 'libxl' name 'xlFontNameA';

function xlFontSetName(handle: FontHandle; const name: PAnsiChar): Integer cdecl;
external 'libxl' name 'xlFontSetNameA';

////////////////////////////////////////////////////////////////////////////////////////////////////

function xlAutoFilterGetRef(handle: AutoFilterHandle; rowFirst, rowLast, colFirst, colLast: PInteger): Integer cdecl;
external 'libxl' name 'xlAutoFilterGetRefA';

procedure xlAutoFilterSetRef(handle: AutoFilterHandle; rowFirst, rowLast, colFirst, colLast: Integer) cdecl;
external 'libxl' name 'xlAutoFilterSetRefA';

function xlAutoFilterColumn(handle: AutoFilterHandle; colId: Integer): FilterColumnHandle cdecl;
external 'libxl' name 'xlAutoFilterColumnA';

function xlAutoFilterColumnSize(handle: AutoFilterHandle): Integer cdecl;
external 'libxl' name 'xlAutoFilterColumnSizeA';

function xlAutoFilterColumnByIndex(handle: AutoFilterHandle; index: Integer): FilterColumnHandle cdecl;
external 'libxl' name 'xlAutoFilterColumnByIndexA';

function xlAutoFilterGetSortRange(handle: AutoFilterHandle; rowFirst, rowLast, colFirst, colLast: PInteger): Integer cdecl;
external 'libxl' name 'xlAutoFilterGetSortRangeA';

function xlAutoFilterGetSort(handle: AutoFilterHandle; columnIndex, descending: PInteger): Integer cdecl;
external 'libxl' name 'xlAutoFilterGetSortA';

function xlAutoFilterSetSort(handle: AutoFilterHandle; columnIndex, descending: Integer): Integer cdecl;
external 'libxl' name 'xlAutoFilterSetSortA';

////////////////////////////////////////////////////////////////////////////////////////////////////

function xlFilterColumnIndex(handle: FilterColumnHandle): Integer cdecl;
external 'libxl' name 'xlFilterColumnIndexA';

function xlFilterColumnFilterType(handle: FilterColumnHandle): Integer cdecl;
external 'libxl' name 'xlFilterColumnFilterTypeA';

function xlFilterColumnFilterSize(handle: FilterColumnHandle): Integer cdecl;
external 'libxl' name 'xlFilterColumnFilterSizeA';

function xlFilterColumnFilter(handle: FilterColumnHandle; index: Integer): PAnsiChar cdecl;
external 'libxl' name 'xlFilterColumnFilterA';

procedure xlFilterColumnAddFilter(handle: FilterColumnHandle; value: PAnsiChar) cdecl;
external 'libxl' name 'xlFilterColumnAddFilterA';

function xlFilterColumnGetTop10(handle: FilterColumnHandle; value: PDouble; top, percent: PInteger): Integer cdecl;
external 'libxl' name 'xlFilterColumnGetTop10A';

procedure xlFilterColumnSetTop10(handle: FilterColumnHandle; value: double; top, percent: Integer) cdecl;
external 'libxl' name 'xlFilterColumnSetTop10A';

function xlFilterColumnGetCustomFilter(handle: FilterColumnHandle; op1: PInteger; v1: PAnsiString; op2: PInteger; v2: PAnsiString; andOp: PInteger): Integer cdecl;
external 'libxl' name 'xlFilterColumnGetCustomFilterA';

procedure xlFilterColumnSetCustomFilter(handle: FilterColumnHandle; op: Integer; v: AnsiString) cdecl;
external 'libxl' name 'xlFilterColumnSetCustomFilterA';

procedure xlFilterColumnSetCustomFilterEx(handle: FilterColumnHandle; op1: Integer; v1: AnsiString; op2: Integer; v2: AnsiString; andOp: Integer) cdecl;
external 'libxl' name 'xlFilterColumnSetCustomFilterExA';

procedure xlFilterColumnClear(handle: FilterColumnHandle) cdecl;
external 'libxl' name 'xlFilterColumnClearA';

////////////////////////////////////////////////////////////////////////////////////////////////////


type
  ExceptionXL = class(Exception)
  private
  protected
  public
  published
    constructor Create(book: BookHandle); overload;
  end;

type
  TFilterColumn = class(TObject)
  private
    book: BookHandle;

  protected
  public
     handle: FilterColumnHandle;

     function index(): Integer;

     function filterType(): Filter;

     function filterSize(): Integer;
     function filter(index: Integer): PAnsiChar;
     procedure addFilter(const value: PAnsiChar);

     function getTop10(var value: double; var top, percent: boolean): boolean;
     procedure setTop10(value: double); overload;
     procedure setTop10(value: double; top: boolean); overload;
     procedure setTop10(value: double; top, percent: boolean); overload;

     function getCustomFilter(var op1: Operator; var v1: PAnsiChar; var op2: Operator; var v2: PAnsiChar; var andOp: boolean): boolean;
     procedure setCustomFilter(op: Operator; const v: PAnsiChar); overload;
     procedure setCustomFilter(op1: Operator; const v1: PAnsiChar; op2: Operator; const v2: PAnsiChar; andOp: boolean); overload;

     procedure clear();

  published
    constructor Create(handle: FilterColumnHandle; book: BookHandle);
    destructor Destroy; override;
  end;

type
  TAutoFilter = class(TObject)
  private
    book: BookHandle;

  protected
  public
     handle: AutoFilterHandle;

     function getRef(var rowFirst, rowLast, colFirst, colLast: Integer): boolean;
     procedure setRef(rowFirst, rowLast, colFirst, colLast: Integer);

     function column(colId: Integer): TFilterColumn;

     function columnSize(): Integer;
     function columnByIndex(index: Integer): TFilterColumn;

     function getSortRange(var rowFirst, rowLast, colFirst, colLast: Integer): boolean;

     function getSort(var columnIndex: Integer; var descending: boolean): boolean;
     function setSort(columnIndex: Integer; descending: boolean): boolean;

  published
    constructor Create(handle: AutoFilterHandle; book: BookHandle);
    destructor Destroy; override;
  end;

type
  TFont = class(TObject)
  private
    book: BookHandle;

    procedure Setsize(const value: Integer);
    function Getsize: Integer;

    procedure Setbold(const value: boolean);
    function Getbold: boolean;

    procedure Setitalic(const value: boolean);
    function Getitalic: boolean;

    procedure SetUnderline(const value: Underline);
    function GetUnderline: Underline;

    procedure SetstrikeOut(const value: boolean);
    function GetstrikeOut: boolean;

    procedure Setscript(const value: Script);
    function Getscript: Script;

    procedure Setcolor(const value: Color);
    function Getcolor: Color;

    procedure SetName(const value: AnsiString);
    function GetName: AnsiString;

    function Error: AnsiString;

  protected
  public
    handle: FontHandle;

    property size: Integer read Getsize write Setsize;
    property bold: boolean read Getbold write Setbold;
    property italic: boolean read Getitalic write Setitalic;
    property underline: Underline read GetUnderline write SetUnderline;
    property strikeOut: boolean read GetstrikeOut write SetstrikeOut;
    property script: Script read Getscript write Setscript;
    property color: Color read Getcolor write Setcolor;
    property name: AnsiString read GetName write SetName;

  published
    constructor Create(handle: FontHandle; book: BookHandle);
    destructor Destroy; override;
  end;

type
  TFormat = class(TObject)
  private
    book: BookHandle;
    procedure Error;

    procedure Setfont(const value: TFont);
    function Getfont: TFont;

    procedure SetalignH(const value: AlignH);
    function GetalignH: AlignH;

    procedure SetAlignV(const value: AlignV);
    function GetAlignV: AlignV;
    procedure Setwrap(const value: boolean);
    function Getwrap: boolean;
    procedure Setrotation(const value: Integer);
    function Getrotation: Integer;
    procedure Setindent(const value: Integer);
    function Getindent: Integer;
    procedure SetshrinkToFit(const value: boolean);
    function GetshrinkToFit: boolean;

    procedure SetborderLeft(const value: BorderStyle);
    function GetborderLeft: BorderStyle;
    procedure SetborderRight(const value: BorderStyle);
    function GetborderRight: BorderStyle;
    procedure SetborderTop(const value: BorderStyle);
    function GetborderTop: BorderStyle;
    procedure SetborderBottom(const value: BorderStyle);
    function GetborderBottom: BorderStyle;

    procedure SetborderLeftColor(const value: Color);
    function GetborderLeftColor: Color;
    procedure SetborderRightColor(const value: Color);
    function GetborderRightColor: Color;
    procedure SetborderTopColor(const value: Color);
    function GetborderTopColor: Color;
    procedure SetborderBottomColor(const value: Color);
    function GetborderBottomColor: Color;

    procedure SetborderDiagonal(const value: BorderDiagonal);
    function GetborderDiagonal: BorderDiagonal;
    procedure SetBorderDiagonalStyle(const value: BorderStyle);
    function GetBorderDiagonalStyle: BorderStyle;
    procedure SetborderDiagonalColor(const value: Color);
    function GetborderDiagonalColor: Color;

    procedure SetfillPattern(const value: FillPattern);
    function GetfillPattern: FillPattern;

    procedure SetpatternForegroundColor(const value: Color);
    function GetpatternForegroundColor: Color;
    procedure SetpatternBackgroundColor(const value: Color);
    function GetpatternBackgroundColor: Color;

    procedure Setlocked(const value: boolean);
    function Getlocked: boolean;

    procedure Sethidden(const value: boolean);
    function Gethidden: boolean;

  protected
  public
    handle: FormatHandle;

    function numFormat: Integer;
    procedure setNumFormat(NumFormat: Integer); overload;
    procedure setNumFormat(value: NumFormat); overload;
    procedure setBorder(style: BorderStyle);
    procedure setBorderColor(value: Color);

    property hidden: boolean read Gethidden write Sethidden;
    property locked: boolean read Getlocked write Setlocked;
    property fillPattern: FillPattern read GetfillPattern write SetfillPattern;
    property patternForegroundColor: Color read GetpatternForegroundColor write SetpatternForegroundColor;
    property patternBackgroundColor: Color read GetpatternBackgroundColor write SetpatternBackgroundColor;
    property borderDiagonal: BorderDiagonal read GetborderDiagonal write SetborderDiagonal;
    property borderDiagonalStyle: BorderStyle read GetBorderDiagonalStyle write SetBorderDiagonalStyle;
    property borderDiagonalColor: Color read GetborderDiagonalColor write SetborderDiagonalColor;

    property font: TFont read Getfont write Setfont;
    property alignH: AlignH read GetalignH write SetalignH;
    property alignV: AlignV read GetAlignV write SetAlignV;
    property wrap: boolean read Getwrap write Setwrap;
    property rotation: Integer read Getrotation write Setrotation;
    property indent: Integer read Getindent write Setindent;
    property shrinkToFit: boolean read GetshrinkToFit write SetshrinkToFit;

    property borderLeft: BorderStyle read GetborderLeft write SetborderLeft;
    property borderRight: BorderStyle read GetborderRight write SetborderRight;
    property borderTop: BorderStyle read GetborderTop write SetborderTop;
    property borderBottom: BorderStyle read GetborderBottom write SetborderBottom;

    property borderLeftColor: Color read GetborderLeftColor write SetborderLeftColor;
    property borderRightColor: Color read GetborderRightColor write SetborderRightColor;
    property borderTopColor: Color read GetborderTopColor write SetborderTopColor;
    property borderBottomColor: Color read GetborderBottomColor write SetborderBottomColor;

  published
    constructor Create(handle: FormatHandle; book: BookHandle);
    destructor Destroy; override;
  end;

type
  TSheet = class(TObject)
  private
    handle: SheetHandle;
    book: BookHandle;
    procedure Error;

    procedure SetDisplayGridlines(const value: boolean);
    function GetDisplayGridlines: boolean;

    procedure SetprintGridlines(const value: boolean);
    function GetprintGridlines: boolean;

    procedure SetZoom(const value: Integer);
    function GetZoom: Integer;

    procedure SetprintZoom(const value: Integer);
    function GetprintZoom: Integer;

    procedure Setlandscape(const value: boolean);
    function Getlandscape: boolean;

    procedure SetPaper(const value: Paper);
    function GetPaper: Paper;

    procedure Setheader(const value: AnsiString);
    function Getheader: AnsiString;

    procedure SetheaderMargin(const value: double);
    function GetheaderMargin: double;

    function Getfooter: AnsiString;
    procedure Setfooter(const value: AnsiString);
    function GetfooterMargin: double;
    procedure SetfooterMargin(const value: double);

    function GethCenter: boolean;
    procedure SethCenter(const value: boolean);

    function GetvCenter: boolean;
    procedure SetvCenter(const value: boolean);

    function GetmarginLeft: double;
    procedure SetmarginLeft(const value: double);
    function GetmarginRight: double;
    procedure SetmarginRight(const value: double);
    function GetmarginBottom: double;
    function GetmarginTop: double;
    procedure SetmarginBottom(const value: double);
    procedure SetmarginTop(const value: double);

    function GetprintRowCol: boolean;
    procedure SetprintRowCol(const value: boolean);

    function GetprotectImpl: boolean;
    procedure SetprotectImpl(const value: boolean);

    function Getrighttoleft: boolean;
    procedure Setrighttoleft(const value: boolean);

    function GetHidden: SheetState;
    procedure SetHidden(const value: SheetState);

    function GetName: AnsiString;
    procedure SetName(const value: AnsiString);

    function GetGroupSummaryBelow: boolean;
    procedure SetGroupSummaryBelow(const value: boolean);

    function GetGroupSummaryRight: boolean;
    procedure SetGroupSummaryRight(const value: boolean);

  protected
  public

    property displayGridlines: boolean read GetDisplayGridlines write SetDisplayGridlines;
    property printGridlines: boolean read GetprintGridlines write SetprintGridlines;
    property zoom: Integer read GetZoom write SetZoom;
    property printZoom: Integer read GetprintZoom write SetprintZoom;
    property landscape: boolean read Getlandscape write Setlandscape;
    property paper: Paper read GetPaper write SetPaper;
    property header: AnsiString read Getheader write Setheader;
    property headerMargin: double read GetheaderMargin write SetheaderMargin;
    property footer: AnsiString read Getfooter write Setfooter;
    property footerMargin: double read GetfooterMargin write SetfooterMargin;
    property hCenter: boolean read GethCenter write SethCenter;
    property vCenter: boolean read GetvCenter write SetvCenter;

    property marginLeft: double read GetmarginLeft write SetmarginLeft;
    property marginRight: double read GetmarginRight write SetmarginRight;
    property marginTop: double read GetmarginTop write SetmarginTop;
    property marginBottom: double read GetmarginBottom write SetmarginBottom;

    property printRowCol: boolean read GetprintRowCol write SetprintRowCol;
    property name: AnsiString read GetName write SetName;
    property groupSummaryBelow: boolean read GetGroupSummaryBelow write SetGroupSummaryBelow;
    property groupSummaryRight: boolean read GetGroupSummaryRight write SetGroupSummaryRight;

    property protect: boolean read GetprotectImpl write SetprotectImpl;
    property hidden: SheetState read GetHidden write SetHidden;
    property rightToLeft: boolean read Getrighttoleft write Setrighttoleft;

    function errorMessage(): AnsiString;

    function getCellType(row: Integer; col: Integer): CellType;
    function isFormula(row: Integer; col: Integer): boolean;

    function cellFormat(row: Integer; col: Integer): TFormat;
    procedure setCellFormat(row: Integer; col: Integer; format: TFormat);
    
    function readStr(row: Integer; col: Integer): AnsiString; overload;
    function readStr(row: Integer; col: Integer; var format: TFormat): AnsiString; overload;
    procedure writeStr(row: Integer; col: Integer; value: PAnsiChar); overload;
    procedure writeStr(row: Integer; col: Integer; value: PAnsiChar; format: TFormat); overload;

    function readNum(row: Integer; col: Integer): double; overload;
    function readNum(row: Integer; col: Integer; var format: TFormat): double; overload;
    procedure writeNum(row: Integer; col: Integer; value: double); overload;
    procedure writeNum(row: Integer; col: Integer; value: double; format: TFormat); overload;

    function readBool(row: Integer; col: Integer): boolean; overload;
    function readBool(row: Integer; col: Integer; var format: TFormat): boolean; overload;
    procedure writeBool(row: Integer; col: Integer; value: boolean); overload;
    procedure writeBool(row: Integer; col: Integer; value: boolean; format: TFormat); overload;

    procedure readBlank(row: Integer; col: Integer; var format: TFormat);
    procedure writeBlank(row: Integer; col: Integer; format: TFormat);

    function readFormula(row: Integer; col: Integer): AnsiString; overload;
    function readFormula(row: Integer; col: Integer; var format: TFormat): AnsiString; overload;
    procedure writeFormula(row: Integer; col: Integer; value: PAnsiChar); overload;
    procedure writeFormula(row: Integer; col: Integer; value: PAnsiChar; format: TFormat); overload;

    procedure writeFormulaNum(row: Integer; col: Integer; expr: PAnsiChar; value: double); overload;
    procedure writeFormulaNum(row: Integer; col: Integer; expr: PAnsiChar; value: double; format: TFormat); overload;

    procedure writeFormulaStr(row: Integer; col: Integer; expr: PAnsiChar; value: PAnsiChar); overload;
    procedure writeFormulaStr(row: Integer; col: Integer; expr: PAnsiChar; value: PAnsiChar; format: TFormat); overload;

    procedure writeFormulaBool(row: Integer; col: Integer; expr: PAnsiChar; value: Integer); overload;
    procedure writeFormulaBool(row: Integer; col: Integer; expr: PAnsiChar; value: Integer; format: TFormat); overload;

    function readComment(row: Integer; col: Integer): AnsiString;
    procedure writeComment(row: Integer; col: Integer; value: PAnsiChar; author: PAnsiChar; width, height: Integer);
    procedure removeComment(row: Integer; col: Integer);

    function isDate(row, col: Integer): boolean;

    function readError(row, col: Integer): ErrorType;
    procedure writeError(row, col: Integer; error: ErrorType); overload;
    procedure writeError(row, col: Integer; error: ErrorType; format: TFormat); overload;

    function colWidth(col: Integer): double;
    function rowHeight(col: Integer): double;

    procedure setCol(col: Integer; width: double); overload;
    procedure setCol(colFirst, colLast: Integer; width: double); overload;
    procedure setCol(col: Integer; width: double; format: TFormat); overload;
    procedure setCol(colFirst, colLast: Integer; width: double; format: TFormat); overload;
    procedure setCol(col: Integer; width: double; format: TFormat; hidden: boolean); overload;
    procedure setCol(colFirst, colLast: Integer; width: double; format: TFormat; hidden: boolean); overload;

    procedure setRow(row: Integer; height: double); overload;
    procedure setRow(row: Integer; height: double; format: TFormat); overload;
    procedure setRow(row: Integer; height: double; format: TFormat; hidden: boolean); overload;

    function rowHidden(row: Integer): boolean;
    procedure setRowHidden(row: Integer; hidden: boolean);

    function colHidden(col: Integer): boolean;
    procedure setColHidden(col: Integer; hidden: boolean);

    function getMerge(row, col: Integer; var rowFirst, rowLast, colFirst, colLast: Integer): boolean;
    function setMerge(rowFirst, rowLast, colFirst, colLast: Integer): boolean;
    function delMerge(row, col: Integer): boolean;

    function pictureSize: Integer;
    function getPicture(index: Integer): Integer; overload;
    function getPicture(index: Integer; var rowTop, colLeft, rowBottom, colRight: Integer): Integer; overload;
    function getPicture(index: Integer; var rowTop, colLeft, rowBottom, colRight, width, height: Integer): Integer; overload;
    function getPicture(index: Integer; var rowTop, colLeft, rowBottom, colRight, width, height, offset_x, offset_y: Integer): Integer; overload;

    procedure setPicture(row, col, pictureId: Integer); overload;
    procedure setPicture(row, col, pictureId: Integer; scale: double); overload;
    procedure setPicture(row, col, pictureId, width, height: Integer); overload;

    function getHorPageBreak(index: Integer): Integer;
    function getHorPageBreakSize: Integer;

    function getVerPageBreak(index: Integer): Integer;
    function getVerPageBreakSize: Integer;

    procedure setHorPageBreak(row: Integer);
    procedure delHorPageBreak(row: Integer);
    procedure setVerPageBreak(col: Integer);
    procedure delVerPageBreak(col: Integer);

    procedure split(row, col: Integer);

    procedure groupRows(rowFirst, rowLast: Integer; collapsed: boolean);
    procedure groupCols(colFirst, colLast: Integer; collapsed: boolean);

    procedure clear(rowFirst, rowLast: Integer; colFirst, colLast: Integer);

    procedure insertCol(colFirst, colLast: Integer);
    procedure insertRow(rowFirst, rowLast: Integer);
    procedure removeCol(colFirst, colLast: Integer);
    procedure removeRow(rowFirst, rowLast: Integer);

    procedure copyCell(rowSrc, colSrc, rowDst, colDst: Integer);

    function firstRow: Integer;
    function lastRow: Integer;
    function firstCol: Integer;
    function lastCol: Integer;

    function getPrintFit(var wPages, hPages: Integer): boolean;
    procedure setPrintFit(wPages, hPages: Integer);

    procedure setPrintRepeatRows(rowFirst, rowLast: Integer);
    procedure setPrintRepeatCols(colFirst, colLast: Integer);
    procedure setPrintArea(rowFirst, rowLast, colFirst, colLast: Integer);
    
    procedure clearPrintRepeats();
    procedure clearPrintArea();

    function getNamedRange(const name: PAnsiChar; var rowFirst, rowLast, colFirst, colLast: Integer): boolean; overload;
    function getNamedRange(const name: PAnsiChar; var rowFirst, rowLast, colFirst, colLast: Integer; scopeId: Integer): boolean; overload;
    function getNamedRange(const name: PAnsiChar; var rowFirst, rowLast, colFirst, colLast: Integer; scopeId: Integer; var hidden: boolean): boolean; overload;
    procedure setNamedRange(const name: PAnsiChar; rowFirst, rowLast, colFirst, colLast: Integer); overload;
    procedure setNamedRange(const name: PAnsiChar; rowFirst, rowLast, colFirst, colLast, scopeId: Integer); overload;
    procedure delNamedRange(const name: PAnsiChar); overload;
    procedure delNamedRange(const name: PAnsiChar; scopeId: Integer); overload;

    function namedRangeSize(): Integer;
    function namedRange(index: Integer; var rowFirst, rowLast, colFirst, colLast: Integer): AnsiString;

    function tableSize(): Integer;
    function table(index: Integer; var rowFirst, rowLast, colFirst, colLast, headerRowCount, totalsRowCount: Integer): AnsiString;

    function hyperlinkSize(): Integer;
    function hyperlink(index: Integer; var rowFirst, rowLast, colFirst, colLast: Integer): AnsiString;
    function delHyperlink(index: Integer): Integer;
    procedure addHyperlink(const hyperlink: PAnsiChar; rowFirst, rowLast, colFirst, colLast: Integer);

    function autoFilter(): TAutoFilter;
    procedure applyFilter();
    procedure removeFilter();

    procedure setProtect(protect: boolean; const password: PAnsiChar); overload;
    procedure setProtect(protect: boolean; const password: PAnsiChar; const prot: EnhancedProtection); overload;

    procedure addrToRowCol(const addr: PAnsiChar; var row, col: Integer); overload;
    procedure addrToRowCol(const addr: PAnsiChar; var row, col: Integer; var rowRelative, colRelative: boolean); overload;
    function rowColToAddr(row, col: Integer): AnsiString; overload;
    function rowColToAddr(row, col: Integer; rowRelative, colRelative: boolean): AnsiString; overload;

    procedure setTabColor(color: Color); overload;
    procedure setTabColor(red: Integer; green: Integer; blue: Integer); overload;

    function addIgnoredError(rowFirst: Integer; colFirst: Integer; rowLast: Integer; colLast: Integer; iError: IgnoredError): boolean;

    procedure addDataValidation(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; const value: PAnsiChar); overload;
    procedure addDataValidation(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; const value1: PAnsiChar; const value2: PAnsiChar); overload;
    procedure addDataValidation(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; const value1: PAnsiChar; const value2: PAnsiChar;
                                allowBlank: boolean; hideDropDown: boolean; showInputMessage: boolean; showErrorMessage: boolean; const promptTitle: PAnsiChar; const prompt: PAnsiChar;
                                const errorTitle: PAnsiChar; const error: PAnsiChar; errorStyle: DataValidationErrorStyle); overload;

    procedure addDataValidationDouble(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value: double); overload;
    procedure addDataValidationDouble(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: double; value2: double); overload;
    procedure addDataValidationDouble(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: double; value2: double;
                                allowBlank: boolean; hideDropDown: boolean; showInputMessage: boolean; showErrorMessage: boolean; const promptTitle: PAnsiChar; const prompt: PAnsiChar;
                                const errorTitle: PAnsiChar; const error: PAnsiChar; errorStyle: DataValidationErrorStyle); overload;

    procedure removeDataValidations();

  published
    constructor Create(handle: SheetHandle; book: BookHandle);
    destructor Destroy; override;
  end;

type
  // {$M+}
  TBook = class(TObject)
  private
    handle: BookHandle;
    procedure Release;

    function GetRefR1C1: boolean;
    procedure SetRefR1C1(const value: boolean);

    function GetDate1904: boolean;
    procedure SetDate1904(const value: boolean);

    function GetTemplate: boolean;
    procedure SetTemplate(const value: boolean);

  protected
  public
    procedure load(filename: PAnsiChar);
    procedure save(filename: PAnsiChar);

    procedure loadRaw(data: PByteArray; size: Cardinal);
    procedure saveRaw(var Buffer: ByteArray; var size: Cardinal);

    function addSheet(name: PAnsiChar): TSheet; overload;
    function addSheet(name: PAnsiChar; initSheet: TSheet): TSheet; overload;
    function insertSheet(index: Integer; name: PAnsiChar): TSheet; overload;
    function insertSheet(index: Integer; name: PAnsiChar; initSheet: TSheet): TSheet; overload;
    function getSheet(index: Integer): TSheet;
    function sheetType(index: Integer): SheetType;
    function moveSheet(srcIndex: Integer; dstIndex: Integer): boolean;
    procedure delSheet(index: Integer);
    function sheetCount(): Integer;

    function addFormat(): TFormat; overload;
    function addFormat(initFormat: TFormat): TFormat; overload;
    function addFont(): TFont; overload;
    function addFont(initFont: TFont): TFont; overload;
    function addCustomNumFormat(customNumFormat: PAnsiChar): Integer;
    function customNumFormat(fmt: Integer): AnsiString;

    function format(index: Integer): TFormat;
    function formatSize(): Integer;

    function font(index: Integer): TFont;
    function fontSize(): Integer;

    function datePack(year: Integer; month: Integer; day: Integer): double; overload;
    function datePack(year: Integer; month: Integer; day: Integer; hour: Integer; min: Integer; sec: Integer): double; overload;
    function datePack(year: Integer; month: Integer; day: Integer; hour: Integer; min: Integer; sec: Integer; msec: Integer): double; overload;

    procedure dateUnpack(value: double; var year: Integer; var month: Integer; var day: Integer); overload;
    procedure dateUnpack(value: double; var year: Integer; var month: Integer; var day: Integer; var hour: Integer; var min: Integer; var sec: Integer); overload;
    procedure dateUnpack(value: double; var year: Integer; var month: Integer; var day: Integer; var hour: Integer; var min: Integer; var sec: Integer; var msec: Integer); overload;

    function colorPack(red: Integer; green: Integer; blue: Integer): Color;
    procedure colorUnpack(color: Color; var red: Integer; var green: Integer; var blue: Integer);

    function activeSheet(): Integer;
    procedure setActiveSheet(index: Integer);

    function pictureSize(): Integer;
    function getPicture(index: Integer; var Buffer: ByteArray; var size: Cardinal): PictureType;

    function addPicture(filename: PAnsiChar): Integer;
    function addPicture2(data: PByteArray; size: Cardinal): Integer;
    function addPictureAsLink(filename: PAnsiChar; insert: boolean): Integer;

    function defaultFont(var fontSize: Integer): AnsiString;
    procedure setDefaultFont(fontName: PAnsiChar; fontSize: Integer);

    property refR1C1: boolean read GetRefR1C1 write SetRefR1C1;

    procedure setKey(name: PAnsiChar; key: PAnsiChar);

    function rgbMode(): boolean;
    procedure setRgbMode(rgbMode: boolean);

    function biffVersion(): Integer;

    property date1904: boolean read GetDate1904 write SetDate1904;
    property template: boolean read GetTemplate write SetTemplate;

    procedure setLocale(locale: PAnsiChar);

    function errorMessage(): AnsiString;

  published
    destructor Destroy; override;
  end;


  TBinBook = class(TBook)
  published
    constructor Create;    
  end;

  TXmlBook = class(TBook)
  published
    constructor Create;    
  end;
  

implementation


constructor ExceptionXL.Create(book: BookHandle);
begin
  inherited Create(AnsiString(xlBookErrorMessage(book)));
end;

constructor TFilterColumn.Create(handle: FilterColumnHandle; book: BookHandle);
begin
  inherited Create;
  self.book := book;
  self.handle := handle;
end;

destructor TFilterColumn.Destroy;
begin
  inherited Destroy;
end;

function TFilterColumn.index(): Integer;
begin
  result := xlFilterColumnIndex(handle);
end;

function TFilterColumn.filterType(): Filter;
begin
  result := LibXL.Filter(xlFilterColumnFilterType(handle));
end;

function TFilterColumn.filterSize(): Integer;
begin
  result := xlFilterColumnFilterSize(handle);
end;

function TFilterColumn.filter(index: Integer): PAnsiChar;
begin
  result := xlFilterColumnFilter(handle, index);
end;

procedure TFilterColumn.addFilter(const value: PAnsiChar);
begin
  xlFilterColumnAddFilter(handle, value);
end;

function TFilterColumn.getTop10(var value: double; var top, percent: boolean): boolean;
var
  iTop, iPercent: Integer;
begin
  result := xlFilterColumnGetTop10(handle, @value, @iTop, @iPercent) > 0;
  top := iTop > 0;
  percent := iPercent > 0;
end;

procedure TFilterColumn.setTop10(value: double);
begin
  xlFilterColumnSetTop10(handle, value, 1, 0);
end;

procedure TFilterColumn.setTop10(value: double; top: boolean);
begin
  xlFilterColumnSetTop10(handle, value, Integer(top), 0);
end;

procedure TFilterColumn.setTop10(value: double; top, percent: boolean);
begin
  xlFilterColumnSetTop10(handle, value, Integer(top), Integer(percent));
end;

function TFilterColumn.getCustomFilter(var op1: Operator; var v1: PAnsiChar; var op2: Operator; var v2: PAnsiChar; var andOp: boolean): boolean;
var
  iOp1, iOp2, iAndOp: Integer;
begin
  result := xlFilterColumnGetCustomFilter(handle, @iOp1, @v1, @iOp2, @v2, @iAndOp) > 0;
  op1 := Operator(iOp1);
  op2 := Operator(iOp2);
  andOp := iAndOp > 0;
end;

procedure TFilterColumn.setCustomFilter(op: Operator; const v: PAnsiChar);
begin
  xlFilterColumnSetCustomFilter(handle, Integer(op), v);
end;

procedure TFilterColumn.setCustomFilter(op1: Operator; const v1: PAnsiChar; op2: Operator; const v2: PAnsiChar; andOp: boolean);
begin
  xlFilterColumnSetCustomFilterEx(handle, Integer(op1), v1, Integer(op2), v2, Integer(andOp));
end;

procedure TFilterColumn.clear();
begin
  xlFilterColumnClear(handle);
end;

constructor TAutoFilter.Create(handle: AutoFilterHandle; book: BookHandle);
begin
  inherited Create;
  self.book := book;
  self.handle := handle;
end;

destructor TAutoFilter.Destroy;
begin
  inherited Destroy;
end;

function TAutoFilter.getRef(var rowFirst, rowLast, colFirst, colLast: Integer): boolean;
begin
  result := xlAutoFilterGetRef(handle, @rowFirst, @rowLast, @colFirst, @colLast) > 0;
end;

procedure TAutoFilter.setRef(rowFirst, rowLast, colFirst, colLast: Integer);
begin
  xlAutoFilterSetRef(handle, rowFirst, rowLast, colFirst, colLast);
end;

function TAutoFilter.column(colId: Integer): TFilterColumn;
var
  fcHandle: FilterColumnHandle;
begin
  fcHandle := xlAutoFilterColumn(handle, colId);
  result := TFilterColumn.Create(fcHandle, book);
end;

function TAutoFilter.columnSize(): Integer;
begin
  result := xlAutoFilterColumnSize(handle);
end;

function TAutoFilter.columnByIndex(index: Integer): TFilterColumn;
var
  fcHandle:  FilterColumnHandle;
begin
  fcHandle := xlAutoFilterColumnByIndex(handle, index);
  result := TFilterColumn.Create(fcHandle, book);
end;

function TAutoFilter.getSortRange(var rowFirst, rowLast, colFirst, colLast: Integer): boolean;
begin
  result := xlAutoFilterGetSortRange(handle, @rowFirst, @rowLast, @colFirst, @colLast) > 0;
end;

function TAutoFilter.getSort(var columnIndex: Integer; var descending: boolean): boolean;
var
  iDescending: Integer;
begin
  result := xlAutoFilterGetSort(handle, @columnIndex, @iDescending) > 0;
  descending := iDescending > 0;
end;

function TAutoFilter.setSort(columnIndex: Integer; descending: boolean): boolean;
begin
  result := xlAutoFilterSetSort(handle, columnIndex, Integer(descending)) > 0;
end;

function TFont.Error: AnsiString;
begin
  raise ExceptionXL.Create(book);
end;

constructor TFont.Create(handle: FontHandle; book: BookHandle);
begin
  inherited Create;
  self.book := book;
  self.handle := handle;
end;

destructor TFont.Destroy;
begin
  inherited Destroy;
end;

function TFont.Getbold: boolean;
begin
  result := (xlFontBold(handle) > 0);
end;

procedure TFont.Setbold(const value: boolean);
begin
  xlFontSetBold(handle, Integer(value));
end;

function TFont.GetName: AnsiString;
begin
  result := AnsiString(xlFontName(handle));
end;

procedure TFont.SetName(const value: AnsiString);
begin
  if xlFontSetName(handle, @(value[1])) = 0 then
    Error;
end;

function TFont.Getsize: Integer;
begin
  result := xlFontSize(handle);
end;

procedure TFont.Setsize(const value: Integer);
begin
  xlFontSetSize(handle, value);
end;

function TFont.GetUnderline: Underline;
begin
  result := LibXL.Underline(xlFontUnderline(handle));
end;

procedure TFont.SetUnderline(const value: LibXL.Underline);
begin
  xlFontSetUnderline(handle, Integer(value));
end;

function TFont.Getcolor: Color;
begin
  result := LibXL.Color(xlFontColor(handle));
end;

procedure TFont.Setcolor(const value: Color);
begin
  xlFontSetColor(handle, Integer(value));
end;

procedure TFont.Setitalic(const value: boolean);
begin
  xlFontSetItalic(handle, Integer(value));
end;

function TFont.Getitalic: boolean;
begin
  result := (xlFontItalic(handle) > 0);
end;

procedure TFont.Setscript(const value: Script);
begin
  xlFontSetScript(handle, Integer(value));
end;

function TFont.Getscript: Script;
begin
  result := LibXL.Script(xlFontScript(handle));
end;

procedure TFont.SetstrikeOut(const value: boolean);
begin
  xlFontSetStrikeOut(handle, Integer(value));
end;

function TFont.GetstrikeOut: boolean;
begin
  result := (xlFontStrikeOut(handle) > 0);
end;

constructor TFormat.Create(handle: FormatHandle; book: BookHandle);
begin
  inherited Create;
  self.book := book;
  self.handle := handle;
end;

destructor TFormat.Destroy;
begin
  inherited Destroy;
end;

procedure TFormat.Error;
begin
  raise ExceptionXL.Create(book);
end;

procedure TFormat.SetborderDiagonal(const value: BorderDiagonal);
begin
  xlFormatSetBorderDiagonal(handle, Integer(value));
end;

procedure TFormat.SetBorderDiagonalStyle(const value: BorderStyle);
begin
  xlFormatSetBorderDiagonalStyle(handle, Integer(value));
end;

procedure TFormat.SetborderDiagonalColor(const value: Color);
begin
  xlFormatSetBorderDiagonalColor(handle, Integer(value));
end;

procedure TFormat.SetborderLeft(const value: BorderStyle);
begin
  xlFormatSetBorderLeft(handle, Integer(value));
end;

procedure TFormat.SetborderLeftColor(const value: Color);
begin
  xlFormatSetBorderLeftColor(handle, Integer(value));
end;

procedure TFormat.SetborderRight(const value: BorderStyle);
begin
  xlFormatSetBorderRight(handle, Integer(value));
end;

procedure TFormat.SetborderRightColor(const value: Color);
begin
  xlFormatSetBorderRightColor(handle, Integer(value));
end;

procedure TFormat.SetborderTop(const value: BorderStyle);
begin
  xlFormatSetBorderTop(handle, Integer(value));
end;

procedure TFormat.SetborderTopColor(const value: Color);
begin
  xlFormatSetBorderTopColor(handle, Integer(value));
end;

procedure TFormat.SetfillPattern(const value: FillPattern);
begin
  xlFormatSetFillPattern(handle, Integer(value));
end;

procedure TFormat.Setfont(const value: TFont);
begin
  if xlFormatSetFont(handle, value.handle) = nil then
    Error;
end;

function TFormat.GetalignH: AlignH;
begin
  result := LibXL.AlignH(xlFormatAlignH(handle));
end;

function TFormat.GetAlignV: AlignV;
begin
  result := LibXL.AlignV(xlFormatAlignV(handle));
end;

function TFormat.GetborderBottom: BorderStyle;
begin
  result := BorderStyle(xlFormatBorderBottom(handle));
end;

function TFormat.GetborderBottomColor: Color;
begin
  result := Color(xlFormatBorderBottomColor(handle));
end;

function TFormat.GetborderDiagonal: BorderDiagonal;
begin
  result := LibXL.BorderDiagonal(xlFormatBorderDiagonal(handle));
end;

function TFormat.GetBorderDiagonalStyle: BorderStyle;
begin
  result := LibXL.BorderStyle(xlFormatBorderDiagonalStyle(handle));
end;

function TFormat.GetborderDiagonalColor: Color;
begin
  result := Color(xlFormatBorderDiagonalColor(handle));
end;

function TFormat.GetborderLeft: BorderStyle;
begin
  result := BorderStyle(xlFormatBorderLeft(handle));
end;

function TFormat.GetborderLeftColor: Color;
begin
  result := Color(xlFormatBorderLeftColor(handle));
end;

function TFormat.GetborderRight: BorderStyle;
begin
  result := BorderStyle(xlFormatBorderRight(handle));
end;

function TFormat.GetborderRightColor: Color;
begin
  result := Color(xlFormatBorderRightColor(handle));
end;

function TFormat.GetborderTop: BorderStyle;
begin
  result := BorderStyle(xlFormatBorderTop(handle));
end;

function TFormat.GetborderTopColor: Color;
begin
  result := Color(xlFormatBorderTopColor(handle));
end;

function TFormat.GetfillPattern: FillPattern;
begin
  result := LibXL.FillPattern(xlFormatFillPattern(handle));
end;

procedure TFormat.Sethidden(const value: boolean);
begin
  xlFormatSetHidden(handle, Integer(value));
end;

procedure TFormat.Setindent(const value: Integer);
begin
  xlFormatSetIndent(handle, Integer(value));
end;

procedure TFormat.Setlocked(const value: boolean);
begin
  xlFormatSetLocked(handle, Integer(value));
end;

function TFormat.Getfont: TFont;
var
  f: FontHandle;
begin
  f := xlFormatFont(handle);
  if f = nil then
    Error;
  result := TFont.Create(f, book);
end;

function TFormat.Gethidden: boolean;
begin
  result := (xlFormatHidden(handle) > 0);
end;

function TFormat.Getindent: Integer;
begin
  result := (xlFormatIndent(handle));
end;

function TFormat.Getlocked: boolean;
begin
  result := (xlFormatLocked(handle) > 0);
end;

function TFormat.GetpatternBackgroundColor: Color;
begin
  result := Color(xlFormatPatternBackgroundColor(handle));
end;

function TFormat.GetpatternForegroundColor: Color;
begin
  result := Color(xlFormatPatternForegroundColor(handle));
end;

function TFormat.Getrotation: Integer;
begin
  result := xlFormatRotation(handle);
end;

function TFormat.GetshrinkToFit: boolean;
begin
  result := (xlFormatShrinkToFit(handle) > 0);
end;

function TFormat.Getwrap: boolean;
begin
  result := (xlFormatWrap(handle) > 0);
end;

function TFormat.NumFormat: Integer;
begin
  result := xlFormatNumFormat(handle);
end;

procedure TFormat.SetalignH(const value: AlignH);
begin
  xlFormatSetAlignH(handle, Integer(value));
end;

procedure TFormat.SetAlignV(const value: AlignV);
begin
  xlFormatSetAlignV(handle, Integer(value));
end;

procedure TFormat.setNumFormat(NumFormat: Integer);
begin
  xlFormatSetNumFormat(handle, NumFormat);
end;

procedure TFormat.setNumFormat(value: NumFormat);
begin
  xlFormatSetNumFormat(handle, Integer(value));
end;

procedure TFormat.SetpatternBackgroundColor(const value: Color);
begin
  xlFormatSetPatternBackgroundColor(handle, Integer(value));
end;

procedure TFormat.SetpatternForegroundColor(const value: Color);
begin
  xlFormatSetPatternForegroundColor(handle, Integer(value));
end;

procedure TFormat.Setrotation(const value: Integer);
begin
  if xlFormatSetRotation(handle, value) = 0 then
    Error;
end;

procedure TFormat.SetshrinkToFit(const value: boolean);
begin
  xlFormatSetShrinkToFit(handle, Integer(value));
end;

procedure TFormat.Setwrap(const value: boolean);
begin
  xlFormatSetWrap(handle, Integer(value));
end;

procedure TFormat.setBorder(style: BorderStyle);
begin
  xlFormatSetBorder(handle, Integer(style));
end;

procedure TFormat.SetborderBottom(const value: BorderStyle);
begin
  xlFormatSetBorderBottom(handle, Integer(value));
end;

procedure TFormat.SetborderBottomColor(const value: Color);
begin
  xlFormatSetBorderBottomColor(handle, Integer(value));
end;

procedure TFormat.setBorderColor(value: Color);
begin
  xlFormatSetBorderColor(handle, Integer(value));
end;


constructor TSheet.Create(handle: SheetHandle; book: BookHandle);
begin
  inherited Create;
  self.book := book;
  self.handle := handle;
end;

destructor TSheet.Destroy;
begin
  inherited Destroy;
end;

function TSheet.ErrorMessage: AnsiString;
begin
  result := AnsiString(xlBookErrorMessage(book));
end;

function TSheet.getCellType(row, col: Integer): CellType;
begin
  result := CellType(xlSheetCellType(handle, row, col));
end;

function TSheet.cellFormat(row, col: Integer): TFormat;
begin
  result := TFormat.Create(xlSheetCellFormat(handle, row, col), book);
end;

procedure TSheet.setCellFormat(row: Integer; col: Integer; format: TFormat);
begin
  xlSheetSetCellFormat(handle, row, col, format.handle);
end;

function TSheet.isFormula(row, col: Integer): boolean;
var
  res: Integer;
begin
  res := xlSheetIsFormula(handle, row, col);
  if res > 0 then
    result := true
  else
    result := false;
end;

function TSheet.readStr(row, col: Integer): AnsiString;
var
  format: FormatHandle;
  ret: AnsiString;
begin
  ret := AnsiString(xlSheetReadStr(handle, row, col, @format));
  if @ret = nil then
    Error;
  result := ret;
end;

function TSheet.readStr(row, col: Integer; var format: TFormat): AnsiString;
var
  fmtHandle: FormatHandle;
  ret: AnsiString;
begin
  ret := AnsiString(xlSheetReadStr(handle, row, col, @fmtHandle));
  if @ret = nil then
    Error;
  format := TFormat.Create(fmtHandle, book);
  result := ret;
end;

procedure TSheet.writeStr(row, col: Integer; value: PAnsiChar);
begin
  if xlSheetWriteStr(handle, row, col, value, nil) = 0 then
    Error;
end;

procedure TSheet.writeStr(row, col: Integer; value: PAnsiChar; format: TFormat);
begin
  if xlSheetWriteStr(handle, row, col, value, format.handle) = 0 then
    Error;
end;

function TSheet.readNum(row, col: Integer): double;
var
  format: FormatHandle;
begin
  result := xlSheetReadNum(handle, row, col, @format);
  if format = nil then
    Error;
end;

function TSheet.readNum(row, col: Integer; var format: TFormat): double;
begin
  result := xlSheetReadNum(handle, row, col, @format.handle);
  if format = nil then
    Error;
end;

procedure TSheet.writeNum(row, col: Integer; value: double);
begin
  if xlSheetWriteNum(handle, row, col, value, nil) = 0 then
    Error;
end;

procedure TSheet.writeNum(row, col: Integer; value: double; format: TFormat);
begin
  if xlSheetWriteNum(handle, row, col, value, format.handle) = 0 then
    Error;
end;

function TSheet.readBool(row, col: Integer): boolean;
var
  format: FormatHandle;
  res: Integer;
begin
  res := xlSheetReadBool(handle, row, col, @format);
  if format = nil then
    Error;
  if res > 0 then
    result := true
  else
    result := false;
end;

function TSheet.readBool(row, col: Integer; var format: TFormat): boolean;
var
  res: Integer;
begin
  res := xlSheetReadBool(handle, row, col, @format.handle);
  if format = nil then
    Error;
  if res > 0 then
    result := true
  else
    result := false;
end;

procedure TSheet.writeBool(row, col: Integer; value: boolean);
begin
  if xlSheetWriteBool(handle, row, col, Integer(value), nil) = 0 then
    Error;
end;

procedure TSheet.writeBool(row, col: Integer; value: boolean; format: TFormat);
begin
  if xlSheetWriteBool(handle, row, col, Integer(value), format.handle) = 0 then
    Error;
end;

procedure TSheet.readBlank(row, col: Integer; var format: TFormat);
begin
  if xlSheetReadBlank(handle, row, col, @format.handle) = 0 then
    Error;
end;

procedure TSheet.writeBlank(row, col: Integer; format: TFormat);
begin
  if xlSheetWriteBlank(handle, row, col, format.handle) = 0 then
    Error;
end;

function TSheet.readFormula(row, col: Integer): AnsiString;
var
  format: FormatHandle;
  ret: AnsiString;
begin
  ret := AnsiString(xlSheetReadFormula(handle, row, col, @format));
  if @ret = nil then
    Error;
  result := ret;
end;

function TSheet.readFormula(row, col: Integer; var format: TFormat): AnsiString;
var
  fmtHandle: FormatHandle;
  ret: AnsiString;
begin
  ret := AnsiString(xlSheetReadFormula(handle, row, col, @fmtHandle));
  if @ret = nil then
    Error;
  format := TFormat.Create(fmtHandle, book);
  result := ret;
end;

procedure TSheet.writeFormula(row, col: Integer; value: PAnsiChar);
begin
  if xlSheetWriteFormula(handle, row, col, value, nil) = 0 then
    Error;
end;

procedure TSheet.writeFormula(row, col: Integer; value: PAnsiChar; format: TFormat);
begin
  if xlSheetWriteFormula(handle, row, col, value, format.handle) = 0 then
    Error;
end;

procedure TSheet.writeFormulaNum(row, col: Integer; expr: PAnsiChar; value: double);
begin
  if xlSheetWriteFormulaNum(handle, row, col, expr, value, nil) = 0 then
    Error;
end;

procedure TSheet.writeFormulaNum(row, col: Integer; expr: PAnsiChar; value: double; format: TFormat);
begin
  if xlSheetWriteFormulaNum(handle, row, col, expr, value, format.handle) = 0 then
    Error;
end;

procedure TSheet.writeFormulaStr(row, col: Integer; expr: PAnsiChar; value: PAnsiChar);
begin
  if xlSheetWriteFormulaStr(handle, row, col, expr, value, nil) = 0 then
    Error;
end;

procedure TSheet.writeFormulaStr(row, col: Integer; expr: PAnsiChar; value: PAnsiChar; format: TFormat);
begin
  if xlSheetWriteFormulaStr(handle, row, col, expr, value, format.handle) = 0 then
    Error;
end;

procedure TSheet.writeFormulaBool(row, col: Integer; expr: PAnsiChar; value: Integer);
begin
  if xlSheetWriteFormulaBool(handle, row, col, expr, value, nil) = 0 then
    Error;
end;

procedure TSheet.writeFormulaBool(row, col: Integer; expr: PAnsiChar; value: Integer; format: TFormat);
begin
  if xlSheetWriteFormulaBool(handle, row, col, expr, value, format.handle) = 0 then
    Error;
end;

function TSheet.readComment(row, col: Integer): AnsiString;
begin
  result := AnsiString(xlSheetReadComment(handle, row, col));
end;

procedure TSheet.writeComment(row, col: Integer; value, author: PAnsiChar; width, height: Integer);
begin
  xlSheetWriteComment(handle, row, col, value, author, width, height);
end;

procedure TSheet.removeComment(row, col: Integer);
begin
  xlSheetRemoveComment(handle, row, col);
end;

function TSheet.isDate(row, col: Integer): boolean;
begin
  if xlSheetIsDate(handle, row, col) > 0 then
    result := true
  else
    result := false;
end;

function TSheet.readError(row, col: Integer): ErrorType;
begin
  result := ErrorType(xlSheetReadError(handle, row, col));
end;

procedure TSheet.writeError(row, col: Integer; error: ErrorType);
begin
  xlSheetWriteError(handle, row, col, Integer(error), nil);
end;

procedure TSheet.writeError(row, col: Integer; error: ErrorType; format: TFormat);
begin
  xlSheetWriteError(handle, row, col, Integer(error), format.handle);
end;

function TSheet.colWidth(col: Integer): double;
begin
  result := xlSheetColWidth(handle, col);
end;

function TSheet.rowHeight(col: Integer): double;
begin
  result := xlSheetRowHeight(handle, col);
end;

procedure TSheet.setCol(col: Integer; width: double; format: TFormat);
begin
  setCol(col, col, width, format);
end;

procedure TSheet.setCol(colFirst, colLast: Integer; width: double);
begin
  if xlSheetSetCol(handle, colFirst, colLast, width, nil, 0) = 0 then
    Error;
end;

procedure TSheet.setCol(col: Integer; width: double);
begin
  setCol(col, col, width);
end;

procedure TSheet.setCol(colFirst, colLast: Integer; width: double; format: TFormat; hidden: boolean);
var
  fmtHandle: FormatHandle;
begin
  if format <> nil then
    fmtHandle := format.handle
  else
    fmtHandle := nil;
  if xlSheetSetCol(handle, colFirst, colLast, width, fmtHandle, Integer(hidden)) = 0 then
    Error;
end;

procedure TSheet.setCol(col: Integer; width: double; format: TFormat; hidden: boolean);
begin
  setCol(col, col, width, format, hidden);
end;

procedure TSheet.setCol(colFirst, colLast: Integer; width: double; format: TFormat);
begin
  if xlSheetSetCol(handle, colFirst, colLast, width, format.handle, 0) = 0 then
    Error;
end;

procedure TSheet.setRow(row: Integer; height: double);
begin
  if xlSheetSetRow(handle, row, height, nil, 0) = 0 then
    Error;
end;

procedure TSheet.setRow(row: Integer; height: double; format: TFormat);
begin
  if xlSheetSetRow(handle, row, height, format.handle, 0) = 0 then
    Error;
end;

procedure TSheet.setRow(row: Integer; height: double; format: TFormat; hidden: boolean);
var
  fmtHandle: FormatHandle;
begin
  if format <> nil then
    fmtHandle := format.handle
  else
    fmtHandle := nil;
  if xlSheetSetRow(handle, row, height, fmtHandle, Integer(hidden)) = 0 then
    Error;
end;

function TSheet.rowHidden(row: Integer): boolean;
begin
  result := xlSheetRowHidden(handle, row) > 0;
end;

procedure TSheet.setRowHidden(row: Integer; hidden: boolean);
begin
  if xlSheetSetRowHidden(handle, row, Integer(hidden)) = 0 then
    raise ExceptionXL.Create(handle);
end;

function TSheet.colHidden(col: Integer): boolean;
begin
  result := xlSheetColHidden(handle, col) > 0;
end;

procedure TSheet.setColHidden(col: Integer; hidden: boolean);
begin
  if xlSheetSetColHidden(handle, col, Integer(hidden)) = 0 then
    raise ExceptionXL.Create(handle);
end;

function TSheet.delMerge(row, col: Integer): boolean;
var
  res: Integer;
begin
  res := xlSheetDelMerge(handle, row, col);
  if res > 0 then
    result := true
  else
    result := false;
end;

function TSheet.getMerge(row, col: Integer; var rowFirst, rowLast, colFirst, colLast: Integer): boolean;
var
  res: Integer;
begin
  res := xlSheetGetMerge(handle, row, col, @rowFirst, @rowLast, @colFirst, @colLast);
  if res > 0 then
    result := true
  else
    result := false;
end;

function TSheet.setMerge(rowFirst, rowLast, colFirst, colLast: Integer): boolean;
var
  res: Integer;
begin
  res := xlSheetSetMerge(handle, rowFirst, rowLast, colFirst, colLast);
  if res > 0 then
    result := true
  else
    result := false;
end;

function TSheet.pictureSize: Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetPictureSize(handle);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getPicture(index: Integer): Integer;
var
  retcode: Integer;
  rowTop, colLeft, rowBottom, colRight, width, height, offset_x, offset_y: Integer;
begin
  retcode := xlSheetGetPicture(handle, index, @rowTop, @colLeft, @rowBottom, @colRight, @width, @height, @offset_x, @offset_y);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getPicture(index: Integer; var rowTop, colLeft, rowBottom, colRight: Integer): Integer;
var
  retcode: Integer;
  width, height, offset_x, offset_y: Integer;
begin
  retcode := xlSheetGetPicture(handle, index, @rowTop, @colLeft, @rowBottom, @colRight, @width, @height, @offset_x, @offset_y);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getPicture(index: Integer; var rowTop, colLeft, rowBottom, colRight, width, height: Integer): Integer;
var
  retcode: Integer;
  offset_x, offset_y: Integer;
begin
  retcode := xlSheetGetPicture(handle, index, @rowTop, @colLeft, @rowBottom, @colRight, @width, @height, @offset_x, @offset_y);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getPicture(index: Integer; var rowTop, colLeft, rowBottom, colRight, width, height, offset_x, offset_y: Integer): Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetGetPicture(handle, index, @rowTop, @colLeft, @rowBottom, @colRight, @width, @height, @offset_x, @offset_y);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

procedure TSheet.Error;
begin
  raise ExceptionXL.Create(book);
end;

procedure TSheet.delHorPageBreak(row: Integer);
begin
  if xlSheetSetHorPageBreak(handle, row, 0) = 0 then
    Error;
end;

procedure TSheet.delVerPageBreak(col: Integer);
begin
  if xlSheetSetVerPageBreak(handle, col, 0) = 0 then
    Error;
end;

procedure TSheet.setHorPageBreak(row: Integer);
begin
  if xlSheetSetHorPageBreak(handle, row, 1) = 0 then
    Error;
end;

procedure TSheet.setVerPageBreak(col: Integer);
begin
  if xlSheetSetVerPageBreak(handle, col, 1) = 0 then
    Error;
end;

procedure TSheet.setPicture(row, col, pictureId, width, height: Integer);
begin
  xlSheetSetPicture2(handle, row, col, pictureId, width, height, 0, 0, 0);
  if ErrorMessage() <> 'ok' then
    Error;
end;

procedure TSheet.setPicture(row, col, pictureId: Integer; scale: double);
begin
  xlSheetSetPicture(handle, row, col, pictureId, scale, 0, 0, 0);
  if ErrorMessage() <> 'ok' then
    Error;
end;

procedure TSheet.setPicture(row, col, pictureId: Integer);
begin
  setPicture(row, col, pictureId, 1);
end;

function TSheet.getHorPageBreak(index: Integer): Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetGetHorPageBreak(handle, index);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getHorPageBreakSize: Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetGetHorPageBreakSize(handle);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getVerPageBreak(index: Integer): Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetGetVerPageBreak(handle, index);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.getVerPageBreakSize: Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetGetVerPageBreakSize(handle);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

procedure TSheet.split(row, col: Integer);
begin
  xlSheetSplit(handle, row, col);
end;

procedure TSheet.groupCols(colFirst, colLast: Integer; collapsed: boolean);
begin
  if xlSheetGroupCols(handle, colFirst, colLast, Integer(collapsed)) = 0 then
    Error;
end;

procedure TSheet.groupRows(rowFirst, rowLast: Integer; collapsed: boolean);
begin
  if xlSheetGroupRows(handle, rowFirst, rowLast, Integer(collapsed)) = 0 then
    Error;
end;

procedure TSheet.clear(rowFirst, rowLast, colFirst, colLast: Integer);
begin
  xlSheetClear(handle, rowFirst, rowLast, colFirst, colLast);
end;

procedure TSheet.insertCol(colFirst, colLast: Integer);
begin
  xlSheetInsertCol(handle, colFirst, colLast);
end;

procedure TSheet.insertRow(rowFirst, rowLast: Integer);
begin
  xlSheetInsertRow(handle, rowFirst, rowLast);
end;

procedure TSheet.removeCol(colFirst, colLast: Integer);
begin
  xlSheetRemoveCol(handle, colFirst, colLast);
end;

procedure TSheet.removeRow(rowFirst, rowLast: Integer);
begin
  xlSheetRemoveRow(handle, rowFirst, rowLast);
end;

procedure TSheet.copyCell(rowSrc, colSrc, rowDst, colDst: Integer);
begin
  if xlSheetCopyCell(handle, rowSrc, colSrc, rowDst, colDst) = 0 then
    Error;
end;

procedure TSheet.setPrintRepeatRows(rowFirst, rowLast: Integer);
begin
  xlSheetSetPrintRepeatRows(handle, rowFirst, rowLast);
end;

procedure TSheet.setPrintRepeatCols(colFirst, colLast: Integer);
begin
  xlSheetSetPrintRepeatCols(handle, colFirst, colLast);
end;

procedure TSheet.setPrintArea(rowFirst, rowLast, colFirst, colLast: Integer);
begin
  xlSheetSetPrintArea(handle, rowFirst, rowLast, colFirst, colLast);
end;
    
procedure TSheet.clearPrintRepeats();
begin
  xlSheetClearPrintRepeats(handle);
end;

procedure TSheet.clearPrintArea();
begin
  xlSheetClearPrintArea(handle);
end;

function TSheet.getNamedRange(const name: PAnsiChar; var rowFirst, rowLast, colFirst, colLast: Integer): boolean;
var
  hidden: boolean;
begin
  result := xlSheetGetNamedRange(handle, name, @rowFirst, @rowLast, @colFirst, @colLast, -2, @hidden) > 0;
end;

function TSheet.getNamedRange(const name: PAnsiChar; var rowFirst, rowLast, colFirst, colLast: Integer; scopeId: Integer): boolean;
var
  hidden: boolean;
begin
  result := xlSheetGetNamedRange(handle, name, @rowFirst, @rowLast, @colFirst, @colLast, scopeId, @hidden) > 0;
end;

function TSheet.getNamedRange(const name: PAnsiChar; var rowFirst, rowLast, colFirst, colLast: Integer; scopeId: Integer; var hidden: boolean): boolean;
begin
  result := xlSheetGetNamedRange(handle, name, @rowFirst, @rowLast, @colFirst, @colLast, scopeId, @hidden) > 0;
end;

procedure TSheet.setNamedRange(const name: PAnsiChar; rowFirst, rowLast, colFirst, colLast: Integer);
begin
  if xlSheetSetNamedRange(handle, name, rowFirst, rowLast, colFirst, colLast, -2) = 0 then
    Error;
end;

procedure TSheet.setNamedRange(const name: PAnsiChar; rowFirst, rowLast, colFirst, colLast, scopeId: Integer);
begin
  if xlSheetSetNamedRange(handle, name, rowFirst, rowLast, colFirst, colLast, scopeId) = 0 then
    Error;
end;

procedure TSheet.delNamedRange(const name: PAnsiChar);
begin
  if xlSheetDelNamedRange(handle, name, -2) = 0 then
    Error;
end;

procedure TSheet.delNamedRange(const name: PAnsiChar; scopeId: Integer);
begin
  if xlSheetDelNamedRange(handle, name, scopeId) = 0 then
    Error;
end;

function TSheet.namedRangeSize(): Integer;
var
  retcode: Integer;
begin
  retcode := xlSheetNamedRangeSize(handle);
  if retcode = -1 then
    raise ExceptionXL.Create(handle);
  result := retcode;
end;

function TSheet.namedRange(index: Integer; var rowFirst, rowLast, colFirst, colLast: Integer): AnsiString;
var
  scopeId: Integer;
  hidden: boolean;
begin
  result := xlSheetNamedRange(handle, index, @rowFirst, @rowLast, @colFirst, @colLast, @scopeId, @hidden);
end;

function TSheet.tableSize(): Integer;
begin
  result := xlSheetTableSize(handle);
end;

function TSheet.table(index: Integer; var rowFirst, rowLast, colFirst, colLast, headerRowCount, totalsRowCount: Integer): AnsiString;
begin
  result := xlSheetTable(handle, index, @rowFirst, @rowLast, @colFirst, @colLast, @headerRowCount, @totalsRowCount);
end;

function TSheet.hyperlinkSize(): Integer;
begin
  result := xlSheetHyperlinkSize(handle);
end;

function TSheet.hyperlink(index: Integer; var rowFirst, rowLast, colFirst, colLast: Integer): AnsiString;
begin
  result := xlSheetHyperlink(handle, index, @rowFirst, @rowLast, @colFirst, @colLast);
end;

function TSheet.delHyperlink(index: Integer): Integer;
begin
  result := xlSheetDelHyperlink(handle, index);
end;

procedure TSheet.addHyperlink(const hyperlink: PAnsiChar; rowFirst, rowLast, colFirst, colLast: Integer);
begin
  xlSheetAddHyperlink(handle, hyperlink, rowFirst, rowLast, colFirst, colLast);
end;

function TSheet.autoFilter(): TAutoFilter;
begin
  result := TAutoFilter.Create(xlSheetAutoFilter(handle), book);
end;

procedure TSheet.applyFilter();
begin
  xlSheetApplyFilter(handle);
end;

procedure TSheet.removeFilter();
begin
  xlSheetRemoveFilter(handle);
end;

procedure TSheet.setProtect(protect: boolean; const password: PAnsiChar);
begin
  xlSheetSetProtectEx(handle, Integer(protect), password, -1);
end;

procedure TSheet.setProtect(protect: boolean; const password: PAnsiChar; const prot: EnhancedProtection);
begin
  xlSheetSetProtectEx(handle, Integer(protect), password, Integer(prot));
end;

function TSheet.firstRow: Integer;
begin
  result := xlSheetFirstRow(handle);
end;

function TSheet.lastRow: Integer;
begin
  result := xlSheetLastRow(handle);
end;

function TSheet.firstCol: Integer;
begin
  result := xlSheetFirstCol(handle);
end;

function TSheet.lastCol: Integer;
begin
  result := xlSheetLastCol(handle);
end;

function TSheet.getPrintFit(var wPages, hPages: Integer): boolean;
begin
  result := xlSheetGetPrintFit(handle, @wPages, @hPages) > 0;
end;

procedure TSheet.setPrintFit(wPages, hPages: Integer);
begin
  xlSheetSetPrintFit(handle, wPages, hPages);
end;

function TSheet.GetDisplayGridlines: boolean;
begin
  result := (xlSheetDisplayGridlines(handle) > 0);
end;

procedure TSheet.SetDisplayGridlines(const value: boolean);
begin
  xlSheetSetDisplayGridlines(handle, Integer(value));
end;

function TSheet.GetprintGridlines: boolean;
begin
  result := (xlSheetPrintGridlines(handle) > 0);
end;

procedure TSheet.SetprintGridlines(const value: boolean);
begin
  xlSheetSetPrintGridlines(handle, Integer(value));
end;

procedure TSheet.SetZoom(const value: Integer);
begin
  xlSheetSetZoom(handle, value);
end;

function TSheet.GetZoom: Integer;
begin
  result := xlSheetZoom(handle);
end;

function TSheet.GetprintZoom: Integer;
begin
  result := xlSheetPrintZoom(handle);
end;

procedure TSheet.SetprintZoom(const value: Integer);
begin
  xlSheetSetPrintZoom(handle, value);
end;

procedure TSheet.Setlandscape(const value: boolean);
begin
  xlSheetSetLandscape(handle, Integer(value));
end;

function TSheet.Getlandscape: boolean;
begin
  result := (xlSheetLandscape(handle) > 0);
end;

function TSheet.GetPaper: Paper;
begin
  result := LibXL.Paper(xlSheetPaper(handle));
end;

procedure TSheet.SetPaper(const value: Paper);
begin
  xlSheetSetPaper(handle, Integer(value));
end;

function TSheet.Getheader: AnsiString;
var
  s: PAnsiChar;
begin
  s := xlSheetHeader(handle);
  if s = nil then
    Error;
  result := AnsiString(s);
end;

procedure TSheet.Setheader(const value: AnsiString);
var
  PValue: PAnsiChar;
begin
  PValue := @(value[1]);
  if xlSheetSetHeader(handle, PValue, 0.5) = 0 then
    Error;
end;

function TSheet.GetheaderMargin: double;
begin
  result := xlSheetHeaderMargin(handle);
end;

procedure TSheet.SetheaderMargin(const value: double);
begin
  if xlSheetSetHeader(handle, @(self.header[1]), value) = 0 then
    Error;
end;

function TSheet.Getfooter: AnsiString;
var
  s: PAnsiChar;
begin
  s := xlSheetFooter(handle);
  if s = nil then
    Error;
  result := AnsiString(s);
end;

procedure TSheet.Setfooter(const value: AnsiString);
var
  PValue: PAnsiChar;
begin
  PValue := @(value[1]);
  if xlSheetSetFooter(handle, PValue, 0.5) = 0 then
    Error;
end;

function TSheet.GetfooterMargin: double;
begin
  result := xlSheetHeaderMargin(handle);
end;

procedure TSheet.SetfooterMargin(const value: double);
begin
  if xlSheetSetHeader(handle, @(self.footer[1]), value) = 0 then
    Error;
end;

procedure TSheet.SethCenter(const value: boolean);
begin
  xlSheetSetHCenter(handle, Integer(value));
end;

function TSheet.GethCenter: boolean;
begin
  result := (xlSheetHCenter(handle) > 0);
end;

procedure TSheet.SetvCenter(const value: boolean);
begin
  xlSheetSetVCenter(handle, Integer(value));
end;

function TSheet.GetvCenter: boolean;
begin
  result := (xlSheetVCenter(handle) > 0);
end;

procedure TSheet.SetmarginLeft(const value: double);
begin
  xlSheetSetMarginLeft(handle, value);
end;

function TSheet.GetmarginLeft: double;
begin
  result := xlSheetMarginLeft(handle);
end;

procedure TSheet.SetmarginRight(const value: double);
begin
  xlSheetSetMarginRight(handle, value);
end;

function TSheet.GetmarginRight: double;
begin
  result := xlSheetMarginRight(handle);
end;

procedure TSheet.SetmarginTop(const value: double);
begin
  xlSheetSetMarginTop(handle, value);
end;

function TSheet.GetmarginTop: double;
begin
  result := xlSheetMarginTop(handle);
end;

procedure TSheet.SetmarginBottom(const value: double);
begin
  xlSheetSetMarginBottom(handle, value);
end;

function TSheet.GetmarginBottom: double;
begin
  result := xlSheetMarginBottom(handle);
end;

function TSheet.Getname: AnsiString;
begin
  result := AnsiString(xlSheetName(handle));
end;

procedure TSheet.Setname(const value: AnsiString);
begin
  xlSheetSetName(handle, @(value[1]));
end;

function TSheet.GetprintRowCol: boolean;
begin
  result := (xlSheetPrintRowCol(handle) > 0);
end;

procedure TSheet.SetprintRowCol(const value: boolean);
begin
  xlSheetSetPrintRowCol(handle, Integer(value));
end;

function TSheet.GetprotectImpl: boolean;
begin
  result := (xlSheetProtect(handle) > 0);
end;

procedure TSheet.SetprotectImpl(const value: boolean);
begin
  xlSheetSetProtect(handle, Integer(value));
end;

function TSheet.Getrighttoleft: boolean;
begin
  result := (xlSheetRightToLeft(handle) > 0);
end;

procedure TSheet.Setrighttoleft(const value: boolean);
begin
  xlSheetSetRightToLeft(handle, Integer(value));
end;

function TSheet.GetHidden: SheetState;
begin
  result := SheetState(xlSheetHidden(handle));
end;

procedure TSheet.SetHidden(const value: SheetState);
begin
  xlSheetSetHidden(handle, Integer(value));
end;

function TSheet.GetGroupSummaryBelow: boolean;
begin
  result := (xlSheetGroupSummaryBelow(handle) > 0);
end;

procedure TSheet.SetGroupSummaryBelow(const value: boolean);
begin
  xlSheetSetGroupSummaryBelow(handle, Integer(value));
end;

function TSheet.GetGroupSummaryRight: boolean;
begin
  result := (xlSheetGroupSummaryRight(handle) > 0);
end;

procedure TSheet.SetGroupSummaryRight(const value: boolean);
begin
  xlSheetSetGroupSummaryRight(handle, Integer(value));
end;

procedure TSheet.addrToRowCol(const addr: PAnsiChar; var row, col: Integer);
begin
  xlSheetAddrToRowCol(handle, addr, @row, @col, nil, nil);
end;

procedure TSheet.addrToRowCol(const addr: PAnsiChar; var row, col: Integer; var rowRelative, colRelative: boolean);
var
  localRowRelative, localColRelative: Integer;
begin
  xlSheetAddrToRowCol(handle, addr, @row, @col, @localRowRelative, @localColRelative);
  rowRelative := localRowRelative > 0;
  colRelative := localColRelative > 0;
end;

function TSheet.rowColToAddr(row, col: Integer): AnsiString;
begin
  result := AnsiString(xlSheetRowColToAddr(handle, row, col, 0, 0));
end;

function TSheet.rowColToAddr(row, col: Integer; rowRelative, colRelative: boolean): AnsiString;
begin
  result := AnsiString(xlSheetRowColToAddr(handle, row, col, Integer(rowRelative), Integer(colRelative)));
end;

procedure TSheet.setTabColor(color: Color);
begin
  xlSheetSetTabColor(handle, Integer(color));
end;

procedure TSheet.setTabColor(red: Integer; green: Integer; blue: Integer);
begin
  xlSheetSetTabRgbColor(handle, red, green, blue);
end;

function TSheet.addIgnoredError(rowFirst: Integer; colFirst: Integer; rowLast: Integer; colLast: Integer; iError: IgnoredError): boolean;
begin
  result := xlSheetAddIgnoredError(handle,  rowFirst,  colFirst, rowLast, colLast, Integer(iError)) > 0;
end;

procedure TSheet.addDataValidation(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; const value: PAnsiChar);
begin
  xlSheetAddDataValidation(handle, Integer(vtype), Integer(op), rowFirst, rowLast, colFirst, colLast, value, nil);
end;

procedure TSheet.addDataValidation(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; const value1: PAnsiChar; const value2: PAnsiChar);
begin
  xlSheetAddDataValidation(handle, Integer(vtype), Integer(op), rowFirst, rowLast, colFirst, colLast, value1, value2);
end;

procedure TSheet.addDataValidation(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; const value1: PAnsiChar; const value2: PAnsiChar;
                                allowBlank: boolean; hideDropDown: boolean; showInputMessage: boolean; showErrorMessage: boolean; const promptTitle: PAnsiChar; const prompt: PAnsiChar;
                                const errorTitle: PAnsiChar; const error: PAnsiChar; errorStyle: DataValidationErrorStyle);
begin
  xlSheetAddDataValidationEx(handle, Integer(vtype), Integer(op), rowFirst, rowLast, colFirst, colLast, value1, value2, Integer(allowBlank), Integer(hideDropDown), Integer(showInputMessage), Integer(showErrorMessage), promptTitle, prompt, errorTitle, error, Integer(errorStyle));
end;

procedure TSheet.addDataValidationDouble(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value: double);
begin
  xlSheetAddDataValidationDouble(handle, Integer(vtype), Integer(op), rowFirst, rowLast, colFirst, colLast, value, 0);
end;

procedure TSheet.addDataValidationDouble(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: double; value2: double);
begin
  xlSheetAddDataValidationDouble(handle, Integer(vtype), Integer(op), rowFirst, rowLast, colFirst, colLast, value1, value2);
end;

procedure TSheet.addDataValidationDouble(vtype: DataValidationType; op: DataValidationOperator; rowFirst: Integer; rowLast: Integer; colFirst: Integer; colLast: Integer; value1: double; value2: double;
                                allowBlank: boolean; hideDropDown: boolean; showInputMessage: boolean; showErrorMessage: boolean; const promptTitle: PAnsiChar; const prompt: PAnsiChar;
                                const errorTitle: PAnsiChar; const error: PAnsiChar; errorStyle: DataValidationErrorStyle);
begin
  xlSheetAddDataValidationDoubleEx(handle, Integer(vtype), Integer(op), rowFirst, rowLast, colFirst, colLast, value1, value2, Integer(allowBlank), Integer(hideDropDown), Integer(showInputMessage), Integer(showErrorMessage), promptTitle, prompt, errorTitle, error, Integer(errorStyle));
end;

procedure TSheet.removeDataValidations();
begin
  xlSheetRemoveDataValidations(handle);
end;

procedure TBook.load(filename: PAnsiChar);
begin
  if xlBookLoad(handle, filename) = 0 then
    raise ExceptionXL.Create(handle);
end;

procedure TBook.save(filename: PAnsiChar);
begin
  if xlBookSave(handle, filename) = 0 then
    raise ExceptionXL.Create(handle);
end;

procedure TBook.loadRaw(data: PByteArray; size: Cardinal);
begin
  if xlBookLoadRaw(handle, addr(data^[0]), size) = 0 then
    raise ExceptionXL.Create(handle);
end;

procedure TBook.saveRaw(var Buffer: ByteArray; var size: Cardinal);
var
  ptr: PByteArray;
  i: Integer;
  p: PByte;
begin
  if xlBookSaveRaw(handle, @ptr, @size) = 0 then
    raise ExceptionXL.Create(handle)
  else
  begin
    SetLength(Buffer, size);
    p := @(ptr^);
    for i := 0 to size - 1 do
    begin
      Buffer[i] := Byte(p^);
      Inc(p);
    end;
  end;
end;

function TBook.addSheet(name: PAnsiChar): TSheet;
var
  new_sheetHandle: SheetHandle;
begin
  new_sheetHandle := xlBookAddSheet(handle, name, nil);
  if new_sheetHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TSheet.Create(new_sheetHandle, self.handle);
end;

function TBook.addSheet(name: PAnsiChar; initSheet: TSheet): TSheet;
var
  new_sheetHandle: SheetHandle;
begin
  new_sheetHandle := xlBookAddSheet(handle, name, initSheet.handle);
  if new_sheetHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TSheet.Create(new_sheetHandle, self.handle);
end;

function TBook.insertSheet(index: Integer; name: PAnsiChar): TSheet;
var
  new_sheetHandle: SheetHandle;
begin
  new_sheetHandle := xlBookInsertSheet(handle, index, name, nil);
  if new_sheetHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TSheet.Create(new_sheetHandle, self.handle);
end;

function TBook.insertSheet(index: Integer; name: PAnsiChar; initSheet: TSheet): TSheet;
var
  new_sheetHandle: SheetHandle;
begin
  new_sheetHandle := xlBookInsertSheet(handle, index, name, initSheet);
  if new_sheetHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TSheet.Create(new_sheetHandle, self.handle);
end;

function TBook.getSheet(index: Integer): TSheet;
var
  new_sheetHandle: SheetHandle;
begin
  new_sheetHandle := xlBookGetSheet(handle, index);
  if new_sheetHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TSheet.Create(new_sheetHandle, self.handle);
end;

function TBook.sheetType(index: Integer): SheetType;
var
  retval: Integer;
begin
  retval := xlBookSheetType(handle, index);
  result := SheetType(retval);
end;

function TBook.moveSheet(srcIndex: Integer; dstIndex: Integer): boolean;
begin
  result := xlBookMoveSheet(handle, srcIndex, dstIndex) > 0;
end;

procedure TBook.delSheet(index: Integer);
begin
  if xlBookDelSheet(handle, index) = 0 then
    raise ExceptionXL.Create(handle);
end;

function TBook.sheetCount: Integer;
begin
  result := xlBookSheetCount(handle);
end;

function TBook.addFormat: TFormat;
var
  fmtHandle: FormatHandle;
begin
  fmtHandle := xlBookAddFormat(handle, nil);
  if fmtHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TFormat.Create(fmtHandle, handle);
end;

function TBook.addFormat(initFormat: TFormat): TFormat;
var
  fmtHandle: FormatHandle;
begin
  fmtHandle := xlBookAddFormat(handle, initFormat.handle);
  if fmtHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TFormat.Create(fmtHandle, handle);
end;

function TBook.addFont: TFont;
var
  font: FontHandle;
begin
  font := xlBookAddFont(handle, nil); ;
  if font = nil then
    raise ExceptionXL.Create(handle);
  result := TFont.Create(font, handle);
end;

function TBook.addFont(initFont: TFont): TFont;
var
  font: FontHandle;
begin
  font := xlBookAddFont(handle, initFont.handle); ;
  if font = nil then
    raise ExceptionXL.Create(handle);
  result := TFont.Create(font, handle);
end;

function TBook.addCustomNumFormat(customNumFormat: PAnsiChar): Integer;
var
  fmt: Integer;
begin
  fmt := xlBookAddCustomNumFormat(handle, customNumFormat);
  if fmt = 0 then
    raise ExceptionXL.Create(handle);
  result := fmt;
end;

function TBook.customNumFormat(fmt: Integer): AnsiString;
var
  s: AnsiString;
begin
  s := AnsiString(xlBookCustomNumFormat(handle, fmt));
  if @s = nil then
    raise ExceptionXL.Create(handle);
  result := s;
end;

function TBook.format(index: Integer): TFormat;
var
  fmtHandle : FormatHandle;
begin
  fmtHandle := xlBookFormat(handle, index);
  if fmtHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TFormat.Create(fmtHandle, handle);
end;

function TBook.formatSize(): Integer;
begin
  result := xlBookFormatSize(handle);
end;

function TBook.font(index: Integer): TFont;
var
  fntHandle : FontHandle;
begin
  fntHandle := xlBookFont(handle, index);
  if fntHandle = nil then
    raise ExceptionXL.Create(handle);
  result := TFont.Create(fntHandle, handle);
end;

function TBook.fontSize(): Integer;
begin
  result := xlBookFontSize(handle);
end;

function TBook.datePack(year, month, day: Integer): double;
begin
  result := xlBookDatePack(handle, year, month, day, 0, 0, 0, 0);
end;

function TBook.datePack(year, month, day, hour, min, sec: Integer): double;
begin
  result := xlBookDatePack(handle, year, month, day, hour, min, sec, 0);
end;

function TBook.datePack(year, month, day, hour, min, sec, msec: Integer): double;
begin
  result := xlBookDatePack(handle, year, month, day, hour, min, sec, msec);
end;

procedure TBook.dateUnpack(value: double; var year: Integer; var month: Integer; var day: Integer);
begin
  if xlBookDateUnpack(handle, value, addr(year), addr(month), addr(day), nil, nil, nil, nil) = 0 then
    raise ExceptionXL.Create(handle);
end;

procedure TBook.dateUnpack(value: double; var year: Integer; var month: Integer; var day: Integer; var hour: Integer; var min: Integer; var sec: Integer);
var
  result: Integer;
begin
  result := xlBookDateUnpack(handle, value, addr(year), addr(month), addr(day), addr(hour), addr(min), addr(sec), nil);
  if result = 0 then
    raise ExceptionXL.Create(handle);
end;

procedure TBook.dateUnpack(value: double; var year: Integer; var month: Integer; var day: Integer; var hour: Integer; var min: Integer; var sec: Integer; var msec: Integer);
var
  result: Integer;
begin
  result := xlBookDateUnpack(handle, value, addr(year), addr(month), addr(day), addr(hour), addr(min), addr(sec), addr(msec));
  if result = 0 then
    raise ExceptionXL.Create(handle);
end;

function TBook.colorPack(red: Integer; green: Integer; blue: Integer): Color;
begin
  result := Color(xlBookColorPack(handle, red, green, blue));
end;

procedure TBook.colorUnpack(color: Color; var red: Integer; var green: Integer; var blue: Integer);
begin
  xlBookColorUnpack(handle, Integer(color), addr(red), addr(green), addr(blue));
end;

function TBook.activeSheet: Integer;
begin
  result := xlBookActiveSheet(handle);
end;

procedure TBook.setActiveSheet(index: Integer);
begin
  xlBookSetActiveSheet(handle, index);
end;

function TBook.pictureSize(): Integer;
var
  retval: Integer;
begin
  retval := xlBookPictureSize(handle);
  if retval = -1 then
    raise ExceptionXL.Create(handle);
  result := retval;
end;

function TBook.getPicture(index: Integer; var Buffer: ByteArray; var size: Cardinal): PictureType;
var
  ptr: PByteArray;
  i: Integer;
  p: PByte;
  retval: Integer;
begin
  retval := xlBookGetPicture(handle, index, @ptr, @size);
  if retval = $FF then
    raise ExceptionXL.Create(handle);
  SetLength(Buffer, size);
  p := @(ptr^);
  for i := 0 to size - 1 do
  begin
    Buffer[i] := Byte(p^);
    Inc(p);
  end;
  result := PictureType(retval);
end;

function TBook.addPicture(filename: PAnsiChar): Integer;
begin
  result := xlBookAddPicture(handle, filename);
  if result = -1 then
    raise ExceptionXL.Create(handle);
end;

function TBook.addPicture2(data: PByteArray; size: Cardinal): Integer;
begin
  result := xlBookAddPicture2(handle, data, size);
  if result = -1 then
     raise ExceptionXL.Create(handle);
end;

function TBook.addPictureAsLink(filename: PAnsiChar; insert: boolean): Integer;
begin
  result := xlBookAddPictureAsLink(handle, filename, Integer(insert));
  if result = -1 then
     raise ExceptionXL.Create(handle);
end;

function TBook.defaultFont(var fontSize: Integer): AnsiString;
var
  s: PAnsiChar;
begin
  s := xlBookDefaultFont(handle, addr(fontSize));
  if s = nil then
    raise ExceptionXL.Create(handle);
  result := AnsiString(s);
end;

procedure TBook.setDefaultFont(fontName: PAnsiChar; fontSize: Integer);
begin
  xlBookSetDefaultFont(handle, fontName, fontSize);
end;

function TBook.GetRefR1C1: boolean;
begin
  result := (xlBookRefR1C1(handle) > 0);
end;

procedure TBook.SetRefR1C1(const value: boolean);
begin
  xlBookSetRefR1C1(handle, Integer(value));
end;

function TBook.GetDate1904: boolean;
begin
  result := (xlBookIsDate1904(handle) > 0);
end;

procedure TBook.SetDate1904(const value: boolean);
begin
  xlBookSetDate1904(handle, Integer(value));
end;

function TBook.GetTemplate: boolean;
begin
  result := (xlBookIsTemplate(handle) > 0);
end;

procedure TBook.SetTemplate(const value: boolean);
begin
  xlBookSetTemplate(handle, Integer(value));
end;

procedure TBook.setKey(name, key: PAnsiChar);
begin
  xlBookSetKey(handle, name, key);
end;

function TBook.rgbMode(): boolean;
begin
  result := boolean(xlBookRgbMode(handle));
end;

procedure TBook.setRgbMode(rgbMode: boolean);
begin
  xlBookSetRgbMode(handle, Integer(rgbMode));
end;

function TBook.biffVersion(): Integer;
begin
  result := xlBookBiffVersion(handle);
end;

procedure TBook.setLocale(locale: PAnsiChar);
begin
  xlBookSetLocale(handle, locale);
end;


function TBook.errorMessage: AnsiString;
begin
  result := AnsiString(xlBookErrorMessage(handle));
end;


procedure TBook.Release;
begin
  try
    xlBookRelease(handle);
  finally
  end;
end;

destructor TBook.Destroy;
begin
  Release;
  inherited Destroy;
end;

constructor TBinBook.Create();
begin
  inherited Create;
  handle := xlCreateBookC;
end;

constructor TXmlBook.Create();
begin
  inherited Create;
  handle := xlCreateXMLBookC;
end;


end.
