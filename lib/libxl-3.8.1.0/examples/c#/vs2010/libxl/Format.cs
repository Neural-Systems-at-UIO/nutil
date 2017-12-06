using System;
using System.Runtime.InteropServices;

namespace libxl
{
    public class Format
    {
        public IntPtr handle;
        Book book;

        public Format(IntPtr handle, Book book)
        {
            this.handle = handle;
            this.book = book;
        }

        public Font font
        {
            get
            {
                IntPtr fontHandle = xlFormatFont(handle);
                if (fontHandle == (IntPtr)0)
                {
                    throw new Exception(book.errorMessage());
                }
                return new Font(fontHandle, book);
            }

            set
            {
                int result = xlFormatSetFont(handle, value.handle);
                if (result == 0)
                {
                    throw new Exception(book.errorMessage());
                }       
            }
        }

        public int numFormat()
        {
            return xlFormatNumFormat(handle);
        }

        public void setNumFormat(int numFormat)
        {
            xlFormatSetNumFormat(handle, numFormat);
        }

        public void setNumFormat(NumFormat numFormat)
        {
            xlFormatSetNumFormat(handle, (int)numFormat);
        }
        
        public AlignH alignH
        {
            get { return (AlignH)xlFormatAlignH(handle); }
            set { xlFormatSetAlignH(handle, (int)value); }
        }

        public AlignV alignV
        {
            get { return (AlignV)xlFormatAlignV(handle); }
            set { xlFormatSetAlignV(handle, (int)value); }
        }

        public bool wrap
        {
            get { return xlFormatWrap(handle) > 0; }
            set { xlFormatSetWrap(handle, value ? 1 : 0); }
        }

        public int rotation
        {
            get { return xlFormatRotation(handle); }
            set { 
                int result = xlFormatSetRotation(handle, value);
                if (result == 0)
                {
                    throw new Exception(book.errorMessage());
                }
            }
        }

        public int indent
        {
            get { return xlFormatIndent(handle); }
            set { xlFormatSetIndent(handle, value); }
        }

        public bool shrinkToFit
        {
            get { return xlFormatShrinkToFit(handle) > 0 ? true : false; }
            set { xlFormatSetShrinkToFit(handle, value ? 1 : 0); }
        }

        public void setBorder(BorderStyle style)
        {
            xlFormatSetBorder(handle, (int)style);
        }

        public void setBorderColor(Color color)
        {
            xlFormatSetBorderColor(handle, (int)color);
        }

        public BorderStyle borderLeft
        {
            get { return (BorderStyle)xlFormatBorderLeft(handle); }
            set { xlFormatSetBorderLeft(handle, (int)value); }
        }

        public BorderStyle borderRight
        {
            get { return (BorderStyle)xlFormatBorderRight(handle); }
            set { xlFormatSetBorderRight(handle, (int)value); }
        }

        public BorderStyle borderTop
        {
            get { return (BorderStyle)xlFormatBorderTop(handle); }
            set { xlFormatSetBorderTop(handle, (int)value); }
        }

        public BorderStyle borderBottom
        {
            get { return (BorderStyle)xlFormatBorderBottom(handle); }
            set { xlFormatSetBorderBottom(handle, (int)value); }
        }

        public Color borderLeftColor
        {
            get { return (Color)xlFormatBorderLeftColor(handle); }
            set { xlFormatSetBorderLeftColor(handle, (int)value); }
        }

        public Color borderRightColor
        {
            get { return (Color)xlFormatBorderRightColor(handle); }
            set { xlFormatSetBorderRightColor(handle, (int)value); }
        }

        public Color borderTopColor
        {
            get { return (Color)xlFormatBorderTopColor(handle); }
            set { xlFormatSetBorderTopColor(handle, (int)value); }
        }

        public Color borderBottomColor
        {
            get { return (Color)xlFormatBorderBottomColor(handle); }
            set { xlFormatSetBorderBottomColor(handle, (int)value); }
        }

        public BorderDiagonal borderDiagonal
        {
            get { return (BorderDiagonal)xlFormatBorderDiagonal(handle); }
            set { xlFormatSetBorderDiagonal(handle, (int)value); }
        }

        public BorderStyle borderDiagonalStyle
        {
            get { return (BorderStyle)xlFormatBorderDiagonalStyle(handle); }
            set { xlFormatSetBorderDiagonalStyle(handle, (int)value); }
        }

        public Color borderDiagonalColor
        {
            get { return (Color)xlFormatBorderDiagonalColor(handle); }
            set { xlFormatSetBorderDiagonalColor(handle, (int)value); }
        }

        public FillPattern fillPattern
        {
            get { return (FillPattern)xlFormatFillPattern(handle); }
            set { xlFormatSetFillPattern(handle, (int)value); }
        }

        public Color patternForegroundColor
        {
            get { return (Color)xlFormatPatternForegroundColor(handle); }
            set { xlFormatSetPatternForegroundColor(handle, (int)value); }
        }

        public Color patternBackgroundColor
        {
            get { return (Color)xlFormatPatternBackgroundColor(handle); }
            set { xlFormatSetPatternBackgroundColor(handle, (int)value); }
        }

        public bool locked
        {
            get { return xlFormatLocked(handle) > 0 ? true : false; }
            set { xlFormatSetLocked(handle, value ? 1 : 0); }
        }

        public bool hidden
        {
            get { return xlFormatHidden(handle) > 0 ? true : false; }
            set { xlFormatSetHidden(handle, value ? 1 : 0); }
        }

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlFormatFont(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatSetFont(IntPtr handle, IntPtr fontHandle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatNumFormat(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetNumFormat(IntPtr handle, int numFormat);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatAlignH(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetAlignH(IntPtr handle, int align);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatAlignV(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetAlignV(IntPtr handle, int align);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatWrap(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetWrap(IntPtr handle, int wrap);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void func(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatRotation(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatSetRotation(IntPtr handle, int rotation);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatIndent(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetIndent(IntPtr handle, int indent);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatShrinkToFit(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetShrinkToFit(IntPtr handle, int shrinkToFit);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorder(IntPtr handle, int style);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderLeft(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderLeft(IntPtr handle, int style);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderRight(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderRight(IntPtr handle, int style);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderTop(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderTop(IntPtr handle, int style);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderBottom(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderBottom(IntPtr handle, int style);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderLeftColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderLeftColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderRightColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderRightColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderTopColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderTopColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderBottomColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderBottomColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderDiagonal(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderDiagonal(IntPtr handle, int border);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderDiagonalStyle(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderDiagonalStyle(IntPtr handle, int style);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatBorderDiagonalColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetBorderDiagonalColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatFillPattern(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetFillPattern(IntPtr handle, int pattern);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatPatternForegroundColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetPatternForegroundColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatPatternBackgroundColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetPatternBackgroundColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatLocked(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetLocked(IntPtr handle, int locked);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFormatHidden(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFormatSetHidden(IntPtr handle, int hidden);
    }
}
