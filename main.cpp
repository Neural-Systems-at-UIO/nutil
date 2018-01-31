#include <QApplication>
#include <QtPlugin>
#include "nutilapplication.h"
#include "mainwindow.h"
#include <xlnt/xlnt.hpp>

int main(int argc, char *argv[])
{


/*    xlnt::workbook wb;
        xlnt::worksheet ws = wb.active_sheet();
        ws.cell("A1").value(5);
        ws.cell("B2").value("string data");
        ws.cell("C3").formula("=RAND()");
        ws.merge_cells("C3:C4");
        ws.freeze_panes("B2");
        wb.save("example.xlsx");
        return 0;
*/
    if (argc == 1)  {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    else {
        NutilApplication a(argc, argv);
        a.exec();
    }
}










