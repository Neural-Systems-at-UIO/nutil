#include <QApplication>
#include <QtPlugin>
#include "nutilapplication.h"
#include "mainwindow.h"
#include <xlnt/xlnt.hpp>
#include "source/unittest.h"

int main(int argc, char *argv[])
{




//    UnitTest::TestMemory();
//    exit(1);


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










