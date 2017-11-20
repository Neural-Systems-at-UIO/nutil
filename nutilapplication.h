#ifndef NUTILAPPLICATION_H
#define NUTILAPPLICATION_H

#include <QVector>
#include <QString>

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
    void PrintUsage();

};

#endif // NUTILAPPLICATION_H
