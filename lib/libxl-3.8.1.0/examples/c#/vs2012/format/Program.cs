using System;
using libxl;

namespace format
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Book book = new BinBook();

                Font font = book.addFont();
                font.size = 36;

                Format format = book.addFormat();
                format.alignH = AlignH.ALIGNH_CENTER;
                format.setBorder(BorderStyle.BORDERSTYLE_MEDIUMDASHDOTDOT);
                format.setBorderColor(Color.COLOR_RED);
                format.font = font;

                Sheet sheet = book.addSheet("Sheet1");
                sheet.writeStr(2, 1, "Format", format);
                sheet.setCol(1, 1, 25);

                book.save("format.xls");

                System.Diagnostics.Process.Start("format.xls");                 
            } 
            catch(System.Exception e)
            {
                Console.WriteLine(e.Message);
            }            
        }
    }
}
