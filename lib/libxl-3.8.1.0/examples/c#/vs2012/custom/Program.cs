using System;
using libxl;

namespace custom
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Book book = new BinBook();

                int f1 = book.addCustomNumFormat("0.0");
                int f2 = book.addCustomNumFormat("0.00");
                int f3 = book.addCustomNumFormat("0.000");
                int f4 = book.addCustomNumFormat("0.0000");
                int f5 = book.addCustomNumFormat("#,###.00 $");
                int f6 = book.addCustomNumFormat("#,###.00 $[Black][<1000];#,###.00 $[Red][>=1000]");

                Format format1 = book.addFormat();
                format1.setNumFormat(f1);

                Format format2 = book.addFormat();
                format2.setNumFormat(f2);

                Format format3 = book.addFormat();
                format3.setNumFormat(f3);

                Format format4 = book.addFormat();
                format4.setNumFormat(f4);

                Format format5 = book.addFormat();
                format5.setNumFormat(f5);

                Format format6 = book.addFormat();
                format6.setNumFormat(f6);

                Sheet sheet = book.addSheet("Custom formats");
                sheet.setCol(0, 20);

                sheet.writeNum(2, 0, 25.718, format1);
                sheet.writeNum(3, 0, 25.718, format2);
                sheet.writeNum(4, 0, 25.718, format3);
                sheet.writeNum(5, 0, 25.718, format4);

                sheet.writeNum(7, 0, 1800.5, format5);

                sheet.writeNum(9, 0, 500, format6);
                sheet.writeNum(10, 0, 1600, format6);

                book.save("custom.xls");

                System.Diagnostics.Process.Start("custom.xls");
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.Message);
            }            
        }
    }
}
