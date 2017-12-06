#ifndef NAUTO_H
#define NAUTO_H

#include <QString>
#include <QColor>
#include "libxl.h"
#include "processmanager.h"

using namespace libxl;

class Nauto
{
private:

public:

    enum Status { Idle, Working, Finished };

    Book* m_book = nullptr;
    Sheet* m_sheet = nullptr;
    QColor m_background = QColor(255,255,255,255);
    QString m_filename;
    int m_sheetIndex;
    ProcessManager m_pm;

    Status status = Status::Idle;

    QString m_inputDir, m_outputDir;
    QString m_type, m_batchName;
    QString m_compression = "jpg";
    QString m_mainInfo;

    Nauto(QString filename, int shee);
    Nauto(QString filename);
    Nauto();
    QString m_error;
    void Load(QString filename);
    void Execute();
    void ExecuteTransformation();
    void ReadeHeader();
    void BuildInfo();
    ~Nauto();
};

#endif // NAUTO_H
