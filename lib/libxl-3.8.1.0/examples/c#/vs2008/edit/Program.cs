using System;
using libxl;

namespace edit
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Book book = new BinBook();
                book.load("example.xls");
                Sheet sheet = book.getSheet(0);
                double d = sheet.readNum(3, 1);
                sheet.writeNum(3, 1, d * 2);
                sheet.writeStr(4, 1, "new string");
                book.save("example.xls");

                System.Diagnostics.Process.Start("example.xls");
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.Message);
            }            
        }
    }
}
