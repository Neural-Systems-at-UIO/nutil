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
    bool Validator();
    bool ValidateRun(QString file, QStringList checkFiles);
    void PrintFailure();
    void PrintSuccess();
    bool CompareFiles(QString directory, QString extension);
};

#endif // NUTILAPPLICATION_H
