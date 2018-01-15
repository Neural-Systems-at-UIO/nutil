#include "nauto.h"
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include "source/util/util.h"

using namespace std;

Nauto::Nauto(QString filename, int sheetIndex)
{
    m_sheetIndex = sheetIndex;
    m_filename = filename;
}

Nauto::Nauto(QString filename)
{
    m_filename = filename;
}

Nauto::Nauto()
{

}

void Nauto::Load(QString filename)
{
    m_filename = filename;
    m_book = xlCreateBook();
    if(m_book)
    {
        wchar_t* arr = new wchar_t[m_filename.size()+1];
        m_filename.toWCharArray(arr);
        arr[m_filename.size()]=L'\0';
        if(m_book->load(arr)) {
            LMessage::lMessage.Message("File " + m_filename + " loaded.");
        }
        else
        {
            LMessage::lMessage.Error(m_book->errorMessage());
        }
    }
}

void Nauto::Execute()
{
    if (m_status!=Status::Idle) {
        LMessage::lMessage.Error("Cannot start new job before previous is finished");
        return;
    }


    if (!m_book) {
        LMessage::lMessage.Error("No excel document loaded.");
        return;
    }
    m_sheet = m_book->getSheet(m_sheetIndex);
    if(!m_sheet)
    {
        LMessage::lMessage.Error(m_book->errorMessage());
    }

    ReadeHeader();

    m_status = Status::Working;
    Util::CancelSignal = false;


    if (m_type.toLower()=="rotation")
        ExecuteTransformation();
    else
        LMessage::lMessage.Error("Unknown command: " + m_type);

    if (m_status != Status::Idle)
        m_status = Status::Finished;
}

void Nauto::ExecuteTransformation()
{
    bool ok = false;
    int y = 8;
    int x = 2;

    m_pm.m_processItems.clear();


    bool isJente = false;


    while (!ok) {
        QString inFile = QString::fromWCharArray(m_sheet->readStr(y,x));
        if (inFile == "") {
            ok = true;
            break;
        }
        inFile += ".tif";

        QFile test(m_inputDir+inFile);
        if(!test.exists()) {
            LMessage::lMessage.Error("Could not find file '" + inFile + "' for processing. Please fix input data and try again.");
            m_status = Status::Idle;
            return;
        }

        QString outFile = QString::fromWCharArray(m_sheet->readStr(y,x+1)) + ".tif";
        float angle = m_sheet->readNum(y,x+2);

        angle = angle/360*(2*M_PI);

        float scale = 1;//QString::fromWCharArray(m_sheet->readStr(y,x+3)).toFloat();
        m_pm.m_processItems.append(new ProcessItem(m_inputDir+  inFile, m_outputDir+ outFile, angle, scale));
        y++;
        qDebug() << "Added " << inFile << " to " << outFile;
    }

    m_pm.ExecuteTransform(m_compression, m_background);



}

void Nauto::ReadeHeader()
{
    m_type = QString::fromWCharArray(m_sheet->readStr(0,1));
    m_batchName = QString::fromWCharArray(m_sheet->readStr(1,1));
    m_compression = QString::fromWCharArray(m_sheet->readStr(2,1));
    m_inputDir = QString::fromWCharArray(m_sheet->readStr(4,1));
    m_outputDir = QString::fromWCharArray(m_sheet->readStr(5,1));
    float col_r = m_sheet->readNum(3,1);
    float col_g = m_sheet->readNum(3,2);
    float col_b = m_sheet->readNum(3,3);
    m_background = QColor(col_r, col_g, col_b);

}

void Nauto::BuildInfo()
{
    if (m_status == Status::Idle) {
        m_mainInfo = "No job loaded.";
        return;
    }



    QString t = "";
    t = t + "Batch <b>'" + m_batchName + "'</b> type <b>" + m_type + "</b><br>";
    t = t + "Converting from <b>" + m_inputDir + "</b> to <b>"  + m_outputDir + "</b> with saved compression <b>" + m_compression + "</b><br>";
    t = t + "Background color: (" + QString::number(m_background.red()) + ", " + QString::number(m_background.green()) + ", " + QString::number(m_background.blue()) + ")<br>";

//    t = t + "Total amou: " + QString::number(m_pm.m_processes.length()) + " \n";

    t = t +"<br>";
    float total = 0;

    for (int i=0;i<m_pm.m_processes.length();i++) {
        float progress = m_pm.m_processes[i]->getProgress();
        total+=min(progress,100.0f);
        if (progress<100 && progress >0) {
            float degrees = m_pm.m_processItems[i]->m_angle;
            t = t + "Worker " +QString::number(i) + ": " + m_pm.m_processItems[i]->m_inFile + " [ <b>" +  QString::number( progress, 'f', 1 ) + "% </b>] " + m_pm.m_processes[i]->m_infoText;
            /*for (int j=0;j<progress;j++) {
            t+="#";
        }*/
            t = t + "<br>";
        }
    }
    if (m_status == Status::Working)
        m_elapsedTime = Util::globalTimer.elapsed();

    total/=m_pm.m_processes.length();
    int totalTime = (m_elapsedTime )/(total/100.0);


    t+="Total: [ <b><font size=\"+1\">"+ QString::number(total,'f', 1)+ "% </font></b>] <br>";
    t+="Elapsed: "+ Util::MilisecondToString(m_elapsedTime) +" / <b>" + Util::MilisecondToString(totalTime) + "</b> <br>";

    if (m_status == Status::Finished) {
        t+="<br>Job is finished and Nutil can be safely closed!<br>";
    }


    m_mainInfo = t;



}

void Nauto::Abort()
{
    //m_pm.Abort();
}

void Nauto::Release()
{
    if (m_book)
        m_book->release();

    m_book = nullptr;
}

QStringList Nauto::getSheetList()
{
    QStringList l;
    for (int i=0;i<m_book->sheetCount();i++) {
        l<< QString::fromWCharArray(m_book->getSheet(i)->name());
    }
    return l;
}

Nauto::~Nauto()
{
    if (m_book)
        m_book->release();

}
