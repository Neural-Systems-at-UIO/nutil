#include <QApplication>
#include <QtPlugin>

#include "nutilapplication.h"

//Q_IMPORT_PLUGIN(qjpeg)

int main(int argc, char *argv[])
{
    NutilApplication a(argc, argv);

    return a.exec();
}
