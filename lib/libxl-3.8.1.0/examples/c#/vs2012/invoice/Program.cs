using System;
using libxl;

namespace invoice
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Book book = new XmlBook();

                Font boldFont = book.addFont();
                boldFont.bold = true;

                Font titleFont = book.addFont();
                titleFont.name = "Arial Black";
                titleFont.size = 16;

                Format titleFormat = book.addFormat();
                titleFormat.font = titleFont;

                Format headerFormat = book.addFormat();
                headerFormat.alignH = AlignH.ALIGNH_CENTER;
                headerFormat.setBorder(BorderStyle.BORDERSTYLE_THIN);
                headerFormat.font = boldFont;
                headerFormat.fillPattern = FillPattern.FILLPATTERN_SOLID;
                headerFormat.patternForegroundColor = Color.COLOR_TAN;

                Format descriptionFormat = book.addFormat();
                descriptionFormat.borderLeft = BorderStyle.BORDERSTYLE_THIN;

                Format amountFormat = book.addFormat();
                amountFormat.setNumFormat(NumFormat.NUMFORMAT_CURRENCY_NEGBRA);
                amountFormat.borderLeft = BorderStyle.BORDERSTYLE_THIN;
                amountFormat.borderRight = BorderStyle.BORDERSTYLE_THIN;

                Format totalLabelFormat = book.addFormat();
                totalLabelFormat.borderTop = BorderStyle.BORDERSTYLE_THIN;
                totalLabelFormat.alignH = AlignH.ALIGNH_RIGHT;
                totalLabelFormat.font = boldFont;

                Format totalFormat = book.addFormat();
                totalFormat.setNumFormat(NumFormat.NUMFORMAT_CURRENCY_NEGBRA);
                totalFormat.setBorder(BorderStyle.BORDERSTYLE_THIN);
                totalFormat.font = boldFont;
                totalFormat.fillPattern = FillPattern.FILLPATTERN_SOLID;
                totalFormat.patternForegroundColor = Color.COLOR_YELLOW;

                Format signatureFormat = book.addFormat();
                signatureFormat.alignH = AlignH.ALIGNH_CENTER;
                signatureFormat.borderTop = BorderStyle.BORDERSTYLE_THIN;

                Sheet sheet = book.addSheet("Invoice");

                sheet.writeStr(2, 1, "Invoice No. 3568", titleFormat);

                sheet.writeStr(4, 1, "Name: John Smith");
                sheet.writeStr(5, 1, "Address: San Ramon, CA 94583 USA");

                sheet.writeStr(7, 1, "Description", headerFormat);
                sheet.writeStr(7, 2, "Amount", headerFormat);

                sheet.writeStr(8, 1, "Ball-Point Pens", descriptionFormat);
                sheet.writeNum(8, 2, 85, amountFormat);
                sheet.writeStr(9, 1, "T-Shirts", descriptionFormat);
                sheet.writeNum(9, 2, 150, amountFormat);
                sheet.writeStr(10, 1, "Tea cups", descriptionFormat);
                sheet.writeNum(10, 2, 45, amountFormat);

                sheet.writeStr(11, 1, "Total:", totalLabelFormat);
                sheet.writeFormula(11, 2, "=SUM(C9:C11)", totalFormat);

                sheet.writeStr(14, 2, "Signature", signatureFormat);

                sheet.setCol(1, 1, 40);
                sheet.setCol(2, 2, 15);
                
                book.save("invoice.xlsx");

                System.Diagnostics.Process.Start("invoice.xlsx");                
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.Message);
            }            
        }
    }
}
