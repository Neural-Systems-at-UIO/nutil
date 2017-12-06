#include "libxl.h"

using namespace libxl;

int main()
{
    Book* book = xlCreateBook(); // use xlCreateXMLBook() for working with xlsx files

    Sheet* sheet = book->addSheet("Sheet1");

    sheet->writeStr(2, 1, "Hello, World !");
    sheet->writeNum(4, 1, 1000);
    sheet->writeNum(5, 1, 2000);

    Font* font = book->addFont();
    font->setColor(COLOR_RED);
    font->setBold(true);
    Format* boldFormat = book->addFormat();
    boldFormat->setFont(font);
    sheet->writeFormula(6, 1, "SUM(B5:B6)", boldFormat);

    Format* dateFormat = book->addFormat();
    dateFormat->setNumFormat(NUMFORMAT_DATE);
    sheet->writeNum(8, 1, book->datePack(2011, 7, 20), dateFormat);

    sheet->setCol(1, 1, 12);

    book->save("report.xls");

    book->release();
}
