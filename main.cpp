#include <QApplication>
#include <QtPlugin>
#include "nutilapplication.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    if (argc == 1)  {
        QApplication app(argc, argv);
        MainWindow window;
        window.show();
        return app.exec();
    }
    else {
        NutilApplication a(argc, argv);
        return a.exec();
    }
}
