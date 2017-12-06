using System;
using libxl;

namespace extract
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

                string s = sheet.readStr(2, 1);
                Console.WriteLine(s);

                double d = sheet.readNum(3, 1);
                Console.WriteLine(d);                
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.Message);
            }

            Console.Write("\nPress any key to exit...");
            Console.ReadKey();
        }
    }
}
