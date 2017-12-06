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
            m_error = "File loaded OK.";
        }
        else
        {
            m_error =  m_book->errorMessage();
        }
    }


}

void Nauto::Execute()
{
    if (!m_book) {
        m_error = "No excel document loaded.";
        return;
    }
    m_sheet = m_book->getSheet(m_sheetIndex);
    if(!m_sheet)
    {
        m_error = m_book->errorMessage();
    }

    ReadeHeader();

    if (m_type.toLower()=="rotation")
        ExecuteTransformation();
    else
        m_error = "Unknown command: " + m_type;


}

void Nauto::ExecuteTransformation()
{
    bool ok = false;
    int y = 8;
    int x = 2;

    m_pm.m_processItems.clear();


    while (!ok) {
        QString inFile = QString::fromWCharArray(m_sheet->readStr(y,x));
        if (inFile=="") {
            ok = true;
            break;
        }
        QString outFile = QString::fromWCharArray(m_sheet->readStr(y,x+1));
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
}

void Nauto::BuildInfo()
{
    QString t = "";
    t = t + "Batch '" + m_batchName + "' type " + m_type + "\n";
    t = t + "Converting from " + m_inputDir + " to "  + m_outputDir + " with saved compression " + m_compression + "\n";

//    t = t + "Total amou: " + QString::number(m_pm.m_processes.length()) + " \n";

    t = t +"\n";
    float total = 0;

    for (int i=0;i<m_pm.m_processes.length();i++) {
        float progress = m_pm.m_processes[i]->getProgress();
        total+=min(progress,100.0f);
        if (progress<100 && progress >0) {
            float degrees = m_pm.m_processItems[i]->m_angle;
            t = t + "Worker " +QString::number(i) + ": " + m_pm.m_processItems[i]->m_inFile + " [ " +  QString::number( progress, 'f', 1 ) + "% ] rotating " + QString::number(degrees/(2*M_PI)*360,'f',2) + " degrees" ;
            /*for (int j=0;j<progress;j++) {
            t+="#";
        }*/
            t = t + "\n";
        }
    }
    total/=m_pm.m_processes.length();
    int totalTime = (Util::globalTimer.elapsed() )/(total/100.0);

    t+="Total: [ "+ QString::number(total,'f', 1)+ "% ]  \n";
    t+="Elapsed: "+ Util::MilisecondToString(Util::globalTimer.elapsed()) +" / " + Util::MilisecondToString(totalTime);
    m_mainInfo = t;


    return;



}

Nauto::~Nauto()
{
    if (m_book)
        m_book->release();

}
