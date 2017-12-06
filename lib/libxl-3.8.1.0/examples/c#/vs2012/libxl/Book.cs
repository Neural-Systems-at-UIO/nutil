using System;
using System.Runtime.InteropServices;

namespace libxl
{
    abstract public class Book 
    {
        public IntPtr handle;

        ~Book()
        {
            release();                     
        }

        public void load(string filename)
        {
            int result = xlBookLoad(handle, filename);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void load(string filename, string tempFile)
        {
            int result = xlBookLoadUsingTempFile(handle, filename, tempFile);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void load(string filename, int sheetIndex)
        {
            int result = xlBookLoadPartially(handle, filename, sheetIndex, -1, -1);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void load(string filename, int sheetIndex, string tempFile)
        {
            int result = xlBookLoadPartiallyUsingTempFile(handle, filename, sheetIndex, -1, -1, tempFile);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void load(string filename, int sheetIndex, int firstRow, int lastRow)
        {
            int result = xlBookLoadPartially(handle, filename, sheetIndex, firstRow, lastRow);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void load(string filename, int sheetIndex, int firstRow, int lastRow, string tempFile)
        {
            int result = xlBookLoadPartiallyUsingTempFile(handle, filename, sheetIndex, firstRow, lastRow, tempFile);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void save(string filename)
        {
            int result = xlBookSave(handle, filename);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void save(string filename, bool useTempFile)
        {
            int result = xlBookSaveUsingTempFile(handle, filename, useTempFile ? 1 : 0);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void loadRaw(byte[] data, int size)
        {
            int result = xlBookLoadRaw(handle, data, size);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void loadRaw(byte[] data, int size, int sheetIndex)
        {
            int result = xlBookLoadRawPartially(handle, data, size, sheetIndex, -1, -1);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void loadRaw(byte[] data, int size, int sheetIndex, int firstRow, int lastRow)
        {
            int result = xlBookLoadRawPartially(handle, data, size, sheetIndex, firstRow, lastRow);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void saveRaw(ref byte[] data, ref int size)
        {
            IntPtr ptr = (IntPtr)0;
            int result = xlBookSaveRaw(handle, ref ptr, ref size);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
            else
            {
                data = new byte[size];
                Marshal.Copy(ptr, data, 0, size);
            }
        }

        public Sheet addSheet(string name)
        {
            IntPtr sheetHandle = xlBookAddSheet(handle, name, (IntPtr)0);
            if(sheetHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Sheet(sheetHandle, this);
        }

        public Sheet addSheet(string name, Sheet initSheet)
        {
            IntPtr sheetHandle = xlBookAddSheet(handle, name, initSheet.handle);
            if (sheetHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Sheet(sheetHandle, this);
        }

        public Sheet insertSheet(int index, string name)
        {
            IntPtr sheetHandle = xlBookInsertSheet(handle, index, name, (IntPtr)0);
            if (sheetHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Sheet(sheetHandle, this);
        }

        public Sheet insertSheet(int index, string name, Sheet initSheet)
        {
            IntPtr sheetHandle = xlBookInsertSheet(handle, index, name, initSheet.handle);
            if (sheetHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Sheet(sheetHandle, this);
        }
       
        public Sheet getSheet(int index)
        {
            IntPtr sheetHandle = xlBookGetSheet(handle, index);
            if (sheetHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Sheet(sheetHandle, this);
        }

        public SheetType sheetType(int index)
        {
            return (SheetType)xlBookSheetType(handle, index);
        }

        public bool moveSheet(int srcIndex, int dstIndex)
        {
	        return xlBookMoveSheet(handle, srcIndex, dstIndex) > 0;	            
        }

        public void delSheet(int index)
        {
            int result = xlBookDelSheet(handle, index);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public int sheetCount()
        {
            return xlBookSheetCount(handle);
        }

        public Format addFormat()
        {
            IntPtr formatHandle = xlBookAddFormat(handle, (IntPtr)0);
            if (formatHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Format(formatHandle, this);
        }

        public Format addFormat(Format initFormat)
        {
            IntPtr formatHandle = xlBookAddFormat(handle, initFormat.handle);
            if (formatHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Format(formatHandle, this);
        }

        public Font addFont()
        {
            IntPtr fontHandle = xlBookAddFont(handle, (IntPtr)0);
            if (fontHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Font(fontHandle, this);
        }

        public Font addFont(Font initFont)
        {
            IntPtr fontHandle = xlBookAddFont(handle, initFont.handle);
            if (fontHandle == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            return new Font(fontHandle, this);
        }

        public int addCustomNumFormat(string customNumFormat)
        {
            int fmt = xlBookAddCustomNumFormat(handle, customNumFormat);
            if (fmt == 0)
            {
                throw new Exception(errorMessage());
            }
            return fmt;
        }

        public string customNumFormat(int fmt)
        {
            IntPtr pStr = xlBookCustomNumFormat(handle, fmt);
            if (pStr == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            String s = Marshal.PtrToStringAuto(pStr);
            return s;
        }
       
        public Format format(int index)
        {
            IntPtr formatHandle = xlBookFormat(handle, index);
            if (formatHandle != (IntPtr)0)
            {
                return new Format(formatHandle, this);    
            }
            return null;            
        }

        public int formatSize()
        {
            return xlBookFormatSize(handle);
        }

        public Font font(int index)
        {
            IntPtr fontHandle = xlBookFont(handle, index);
            if (fontHandle != (IntPtr)0)
            {
                return new Font(fontHandle, this);
            }
            return null;
        }

        public int fontSize()
        {
            return xlBookFontSize(handle);
        }

        public double datePack(int year, int month, int day)
        {
            return xlBookDatePack(handle, year, month, day, 0, 0, 0, 0);
        }

        public double datePack(int year, int month, int day, int hour, int min, int sec)
        {
            return xlBookDatePack(handle, year, month, day, hour, min, sec, 0);
        }

        public double datePack(int year, int month, int day, int hour, int min, int sec, int msec)
        {
            return xlBookDatePack(handle, year, month, day, hour, min, sec, msec);
        }

        public void dateUnpack(double value, ref int year, ref int month, ref int day)
        {
            int hour = 0, min = 0, sec = 0, msec = 0;
            int result = xlBookDateUnpack(handle, value, ref year, ref month, ref day, ref hour, ref min, ref sec, ref msec);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void dateUnpack(double value, ref int year, ref int month, ref int day, ref int hour, ref int min, ref int sec)
        {
            int msec = 0;
            int result = xlBookDateUnpack(handle, value, ref year, ref month, ref day, ref hour, ref min, ref sec, ref msec);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public void dateUnpack(double value, ref int year, ref int month, ref int day, ref int hour, ref int min, ref int sec, ref int msec)
        {            
            int result = xlBookDateUnpack(handle, value, ref year, ref month, ref day, ref hour, ref min, ref sec, ref msec);
            if (result == 0)
            {
                throw new Exception(errorMessage());
            }
        }

        public Color colorPack(int red, int green, int blue)
        {
            return (Color)xlBookColorPack(handle, red, green, blue);
        }

        public void colorUnpack(Color color, ref int red, ref int green, ref int blue)
        {
            xlBookColorUnpack(handle, (int)color, ref red, ref green, ref blue);
        }

        public int activeSheet()
        {
            return xlBookActiveSheet(handle);
        }

        public void setActiveSheet(int index)
        {
            xlBookSetActiveSheet(handle, index);
        }

        public int pictureSize()
        {
            int result = xlBookPictureSize(handle);
            if(result == -1)
            {
                throw new Exception(errorMessage());
            }
            return result;
        }

        public PictureType getPicture(int index, ref byte[] data, ref int size)
        {
            IntPtr ptr = (IntPtr)0;
            int result = xlBookGetPicture(handle, index, ref ptr, ref size);
            if (result == 0xFF)
            {
                throw new Exception(errorMessage());
            }
            else
            {
                data = new byte[size];
                Marshal.Copy(ptr, data, 0, size);
            }
            return (PictureType)result;
        }

        public int addPicture(string filename)
        {
            int result = xlBookAddPicture(handle, filename);
            if (result == -1)
            {
                throw new Exception(errorMessage());
            }
            return result;
        }

        public int addPicture2(byte[] data, int size)
        {
            int result = xlBookAddPicture2(handle, data, size);
            if (result == -1)
            {                       
                throw new Exception(errorMessage());
            }
            return result;
        }

        public int addPictureAsLink(string filename, bool insert)
        {
            return xlBookAddPictureAsLink(handle, filename, insert ? 1 : 0);
        }

        public string defaultFont(ref int fontSize)
        {
            IntPtr pStr = xlBookDefaultFont(handle, ref fontSize);
            if (pStr == (IntPtr)0)
            {
                throw new Exception(errorMessage());
            }
            String s = Marshal.PtrToStringAuto(pStr);
            return s;
        }

        public void setDefaultFont(string fontName, int fontSize)
        {
            xlBookSetDefaultFont(handle, fontName, fontSize);
        }

        public void setKey(string name, string key)
        {
            xlBookSetKey(handle, name, key);
        }

        public bool refR1C1
        {
            get { return xlBookRefR1C1(handle) > 0; }
            set { xlBookSetRefR1C1(handle, value ? 1 : 0); }
        }

        public bool rgbMode
        {
            get { return xlBookRgbMode(handle) > 0; }
            set { xlBookSetRgbMode(handle, value ? 1 : 0); }
        }

        public int version
        {
            get { return xlBookVersion(handle); }
        }

        public int biffVersion
        {
            get { return xlBookBiffVersion(handle); }
        }

        public bool date1904
        {
            get { return xlBookIsDate1904(handle) > 0; }
            set { xlBookSetDate1904(handle, value ? 1 : 0); }
        }

        public bool template
        {
            get { return xlBookIsTemplate(handle) > 0; }
            set { xlBookSetTemplate(handle, value ? 1 : 0); }
        }

        public string errorMessage()
        {
            string msg = "";

            IntPtr ptr = xlBookErrorMessage(handle);
            if (ptr != (IntPtr)0)
            {
                msg = Marshal.PtrToStringAnsi(ptr);
            }

            return msg;            
        }

        private void release()
        {
            try
            {              
                xlBookRelease(handle);                                                
            }
            catch {}            
        }
               
        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookLoad(IntPtr bookHandle, string filename);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookLoadPartially(IntPtr bookHandle, string filename, int sheetIndex, int firstRow, int lastRow);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookLoadPartiallyUsingTempFile(IntPtr bookHandle, string filename, int sheetIndex, int firstRow, int lastRow, string tempFile);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookLoadUsingTempFile(IntPtr bookHandle, string filename, string tempFile);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookSave(IntPtr bookHandle, string filename);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookSaveUsingTempFile(IntPtr bookHandle, string filename, int useTempFile);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookLoadRaw(IntPtr bookHandle, byte[] data, int size);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookLoadRawPartially(IntPtr bookHandle, byte[] data, int size, int sheetIndex, int firstRow, int lastRow);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookSaveRaw(IntPtr bookHandle, ref IntPtr data, ref int size);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookAddSheet(IntPtr handle, string name, IntPtr initSheet);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookInsertSheet(IntPtr handle, int index, string name, IntPtr initSheet);
        
        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookGetSheet(IntPtr bookHandle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookSheetType(IntPtr bookHandle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookMoveSheet(IntPtr bookHandle, int srcIndex, int dstIndex);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookDelSheet(IntPtr bookHandle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern ushort xlBookSheetCount(IntPtr bookHandle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookAddFormat(IntPtr handle, IntPtr formatHandle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookAddFont(IntPtr handle, IntPtr fontHandle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookAddCustomNumFormat(IntPtr handle, string customNumFormat);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookCustomNumFormat(IntPtr handle, int fmt);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookFormat(IntPtr handle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookFormatSize(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookFont(IntPtr handle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookFontSize(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern double xlBookDatePack(IntPtr handle, int year, int month, int day, int hour, int min, int sec, int msec);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookDateUnpack(IntPtr handle, double value, ref int year, ref int month, ref int day, ref int hour, ref int min, ref int sec, ref int msec);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookColorPack(IntPtr handle, int red, int green, int blue);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookColorUnpack(IntPtr handle, int color, ref int red, ref int green, ref int blue);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookActiveSheet(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetActiveSheet(IntPtr handle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookPictureSize(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookGetPicture(IntPtr handle, int index, ref IntPtr data, ref int size);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookAddPicture(IntPtr handle, string filename);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookAddPicture2(IntPtr handle, byte[] data, int size);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookAddPictureAsLink(IntPtr handle, string filename, int insert);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlBookDefaultFont(IntPtr handle, ref int fontSize);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetDefaultFont(IntPtr handle, string fontName, int fontSize);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetKey(IntPtr handle, string name, string key);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookRefR1C1(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetRefR1C1(IntPtr handle, int refR1C1);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookRgbMode(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetRgbMode(IntPtr handle, int rgbMode);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookBiffVersion(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookVersion(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookIsDate1904(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetDate1904(IntPtr handle, int date1904);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlBookIsTemplate(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookSetTemplate(IntPtr handle, int template);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]        
        private static extern IntPtr xlBookErrorMessage(IntPtr bookHandle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlBookRelease(IntPtr handle);
    }

    public class BinBook : Book
    {
        public BinBook()
        {
            handle = xlCreateBookC();            
        }

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlCreateBookC();
    }

    public class XmlBook : Book
    {
        public XmlBook()
        {
            handle = xlCreateXMLBookC(); 
        }

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlCreateXMLBookC();
    }
}
