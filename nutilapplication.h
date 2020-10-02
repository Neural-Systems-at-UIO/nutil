#ifndef NUTILAPPLICATION_H
#define NUTILAPPLICATION_H

#include <QVector>
#include <QString>
#include "source/ltiff/ltiff.h"

class NutilApplication
{
private:
    int m_argc;
    QVector<QString> m_argv;
public:
    NutilApplication(int argc, char *argv[]);
    void exec();

private:
    bool RotateTiff();
    bool Transform();
    void PrintUsage();
    bool Batch();
    void Validator(QString directory);
};

#endif // NUTILAPPLICATION_H
