using System;
using System.Runtime.InteropServices;

namespace libxl
{
    public class FilterColumn
    {
        public IntPtr handle;
        Book book;

        public FilterColumn(IntPtr handle, Book book)
        {
            this.handle = handle;
            this.book = book;
        }

        public int index()
        {
            return xlFilterColumnIndex(handle);
        }

        Filter filterType()
        {
            return (Filter)xlFilterColumnFilterType(handle);
        }

        public int filterSize()
        {
            return xlFilterColumnFilterSize(handle);
        }

        public string filter(int index)
        {
            IntPtr pStr = xlFilterColumnFilter(handle, index);
            if (pStr == (IntPtr)0)
            {
                throw new Exception(book.errorMessage());
            }
            String s = Marshal.PtrToStringAuto(pStr);
            return s;
        }

        public void addFilter(string value)
        {
            xlFilterColumnAddFilter(handle, value);
        }

        public bool getTop10(ref double value, ref bool top, ref bool percent)
        {
            int iTop = 0;
            int iPercent = 0;
            bool status = xlFilterColumnGetTop10(handle, ref value, ref iTop, ref iPercent) > 0;
            top = iTop > 0;
            percent = iPercent > 0;
            return status;
        }

        public void setTop10(double value)
        {
            xlFilterColumnSetTop10(handle, value, 1, 0);
        }

        public void setTop10(double value, bool top)
        {
            xlFilterColumnSetTop10(handle, value, top ? 1 : 0, 0);
        }

        public void setTop10(double value, bool top, bool percent)
        {
            xlFilterColumnSetTop10(handle, value, top ? 1 : 0, percent ? 1 : 0);
        }

        public bool getCustomFilter(ref Operator op1, ref string v1, ref Operator op2, ref string v2, ref bool andOp)
        {
            int iAndOp = 0;
            int iOp1 = 0;
            int iOp2 = 0;        
            bool status = xlFilterColumnGetCustomFilter(handle, ref iOp1, ref v1, ref iOp2, ref v2, ref iAndOp) > 0;
            op1 = (Operator)iOp1;
            op2 = (Operator)iOp2;
            andOp = iAndOp > 0;
            return status;
        }

        public void setCustomFilter(Operator op, string v)
        {
            xlFilterColumnSetCustomFilter(handle, (int)op, v);
        }

        public void setCustomFilter(Operator op1, string v1, Operator op2, string v2, bool andOp)
        {
            xlFilterColumnSetCustomFilterEx(handle, (int)op1, v1, (int)op2, v2, andOp ? 1 : 0);
        }

        public void clear()
        {
            xlFilterColumnClear(handle);
        }
        
        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnIndex(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnFilterType(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnFilterSize(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlFilterColumnFilter(IntPtr handle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFilterColumnAddFilter(IntPtr handle, string value);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlAutoFilterGetSortRange(IntPtr handle, ref int rowFirst, ref int rowLast, ref int colFirst, ref int colLast);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnGetTop10(IntPtr handle, ref double value, ref int top, ref int percent);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFilterColumnSetTop10(IntPtr handle, double value, int top, int percent);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnGetCustomFilter(IntPtr handle, ref int op1, ref string v1, ref int op2, ref string v2, ref int andOp);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnSetCustomFilter(IntPtr handle, int op, string v);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlFilterColumnSetCustomFilterEx(IntPtr handle, int op1, string v1, int op2, string v2, int andOp);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlFilterColumnClear(IntPtr handle);
    }
}

