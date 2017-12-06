using System;
using libxl;

namespace generate
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Book book = new BinBook();                
                Sheet sheet = book.addSheet("Sheet1");

                sheet.writeStr(2, 1, "Hello, World !");
                sheet.writeNum(3, 1, 1000);

                Format dateFormat = book.addFormat();
                dateFormat.setNumFormat(NumFormat.NUMFORMAT_DATE);
                sheet.writeNum(4, 1, book.datePack(2008, 4, 29), dateFormat);
                sheet.setCol(1, 1, 12);

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
