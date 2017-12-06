using System;
using System.Runtime.InteropServices;

namespace libxl
{
    public class AutoFilter
    {
        public IntPtr handle;
        Book book;

        public AutoFilter(IntPtr handle, Book book)
        {
            this.handle = handle;
            this.book = book;
        }

        public bool getRef(ref int rowFirst, ref int rowLast, ref int colFirst, ref int colLast)
        {
            return xlAutoFilterGetRef(handle, ref rowFirst, ref rowLast, ref colFirst, ref colLast) > 0;
        }

        public void setRef(int rowFirst, int rowLast, int colFirst, int colLast)
        {
            xlAutoFilterSetRef(handle, rowFirst, rowLast, colFirst, colLast);
        }

        public FilterColumn column(int colId)
        {
            IntPtr filterColumnHandle = xlAutoFilterColumn(handle, colId);
            return new FilterColumn(filterColumnHandle, book);
        }

        public int columnSize()
        {
            return xlAutoFilterColumnSize(handle);
        }

        public FilterColumn columnByIndex(int index)
        {
            IntPtr filterColumnHandle = xlAutoFilterColumnByIndex(handle, index);
            return new FilterColumn(filterColumnHandle, book);
        }

        public bool getSortRange(ref int rowFirst, ref int rowLast, ref int colFirst, ref int colLast)
        {
            return xlAutoFilterGetSortRange(handle, ref rowFirst, ref rowLast, ref colFirst, ref colLast) > 0;
        }

        public bool getSort(ref int columnIndex, ref bool descending)
        {
            int iDescending = 0;
            bool status = xlAutoFilterGetSort(handle, ref columnIndex, ref iDescending) > 0;
            descending = iDescending > 0;
            return status;
        }

        public bool setSort(int columnIndex)
        {            
            return xlAutoFilterSetSort(handle, columnIndex, 0) > 0;            
        }

        public bool setSort(int columnIndex, bool descending)
        {
            return xlAutoFilterSetSort(handle, columnIndex, descending ? 1 : 0) > 0;
        }
        
        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlAutoFilterGetRef(IntPtr handle, ref int rowFirst, ref int rowLast, ref int colFirst, ref int colLast);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void xlAutoFilterSetRef(IntPtr handle, int rowFirst, int rowLast, int colFirst, int colLast);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlAutoFilterColumn(IntPtr handle, int col);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlAutoFilterColumnSize(IntPtr handle);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr xlAutoFilterColumnByIndex(IntPtr handle, int index);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlAutoFilterGetSortRange(IntPtr handle, ref int rowFirst, ref int rowLast, ref int colFirst, ref int colLast);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlAutoFilterGetSort(IntPtr handle, ref int columnIndex, ref int descending);

        [DllImport("libxl.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern int xlAutoFilterSetSort(IntPtr handle, int columnIndex, int descending);
    }
}

