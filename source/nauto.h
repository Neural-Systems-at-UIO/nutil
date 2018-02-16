#ifndef NAUTO_H
#define NAUTO_H

#include <QString>
#include <QColor>
#include <QStringList>
//#include "libxl.h"
#include "source/ProcessManager/processmanager.h"
#include "source/util/lmessage.h"
#include "source/LBook/lbook.h"
#include "source/LBook/lbookxlnt.h"

using namespace libxl;

class Nauto
{
private:

public:

    enum Status { Idle, Working, Finished };

/*      Book* m_book = nullptr;

    Sheet* m_sheet = nullptr;*/
    LBook *m_book = nullptr;
    LSheet* m_sheet = nullptr;


    QString m_filename;
    int m_sheetIndex;
    int m_elapsedTime;
    ProcessManager* m_pm = nullptr;

    Counter m_mainCounter;

    Status m_status = Status::Idle;
    QString m_type;
    QString m_batchName;


    QString m_mainInfo;


    Nauto(QString filename, int shee);
    Nauto(QString filename);
    Nauto();



    void Load(QString filename);
    void Execute();
    void ExecuteTransformation();
//    void ExecuteAutoContrast();
    void ExecutePCounter();
    void ReadHeader();
    void BuildInfo();
    void Abort();
    void Release();
    QStringList getSheetList();
    ~Nauto();
};

#endif // NAUTO_H
