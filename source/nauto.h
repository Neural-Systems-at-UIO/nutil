#ifndef NAUTO_H
#define NAUTO_H

#include <QString>
#include <QColor>
#include <QStringList>
#include "libxl.h"
#include "processmanager.h"
#include "source/util/lmessage.h"

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
    int m_elapsedTime;
    ProcessManager m_pm;

    Status m_status = Status::Idle;

    QString m_inputDir, m_outputDir;
    QString m_type, m_batchName;
    QString m_compression = "jpg";
    QString m_mainInfo;



    Nauto(QString filename, int shee);
    Nauto(QString filename);
    Nauto();
    void Load(QString filename);
    void Execute();
    void ExecuteTransformation();
    void ReadeHeader();
    void BuildInfo();
    void Abort();
    void Release();
    QStringList getSheetList();
    ~Nauto();
};

#endif // NAUTO_H
