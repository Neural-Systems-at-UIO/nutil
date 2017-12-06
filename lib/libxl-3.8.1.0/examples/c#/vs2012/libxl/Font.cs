using System;
using System.Runtime.InteropServices;

namespace libxl
{
    public class Font
    {
        public IntPtr handle;
        Book book;

        public Font(IntPtr handle, Book book)
        {
            this.handle = handle;
            this.book = book;
        }

        public int size
        {
            get { return xlFontSize(handle); }
            set { xlFontSetSize(handle, value); }
        }

        public bool bold
        {
            get { return xlFontBold(handle) > 0; }
            set { xlFontSetBold(handle, value ? 1 : 0); }
        }

        public bool italic
        {
            get { return xlFontItalic(handle) > 0; }
            set { xlFontSetItalic(handle, value ? 1 : 0); }
        }

        public Underline underline
        {
            get { return (Underline)xlFontUnderline(handle); }
            set { xlFontSetUnderline(handle, (int)value); }
        }

        public bool strikeOut
        {
            get { return xlFontStrikeOut(handle) > 0; }
            set { xlFontSetStrikeOut(handle, value ? 1 : 0); }
        }

        public Script script
        {
            get { return (Script)xlFontScript(handle); }
            set { xlFontSetScript(handle, (int)value); }
        }

        public Color color
        {
            get { return (Color)xlFontColor(handle); }
            set { xlFontSetColor(handle, (int)value); }
        }
                      
        public string name
        {
            get 
            {
                IntPtr pStr = xlFontName(handle);
                String s = Marshal.PtrToStringAuto(pStr);
                return s;
            }
            set
            {
                int result = xlFontSetName(handle, value);
                if (result == 0)
                {
                    throw new Exception(book.errorMessage());
                }
            }
        }

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontSize(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetSize(IntPtr handle, int size);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontItalic(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetItalic(IntPtr handle, int italic);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontStrikeOut(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetStrikeOut(IntPtr handle, int strikeOut);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontColor(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetColor(IntPtr handle, int color);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontBold(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetBold(IntPtr handle, int bold);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontScript(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetScript(IntPtr handle, int script);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontUnderline(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFontSetUnderline(IntPtr handle, int underline);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlFontName(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFontSetName(IntPtr handle, string name);

    }
}
