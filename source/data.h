#ifndef DATA_H
#define DATA_H

#include <QString>
#include "source/util/cinifile.h"


class Data
{
public:
    Data();
    float version = 0.01;
    bool redrawOutput=false;
    bool redrawInput=false;
    bool forceRedraw = false;
    bool redrawFileList = false;
    bool m_isQuickNII = true;
    QColor m_maskedOutColor = Qt::black;
    QString m_globalMessage = "";
    bool abort = false;
    bool requestSaveAs = false;
    bool requestCloseWindow = false;
    bool blink = false;
    CIniFile* m_settings = nullptr;
    QString m_currentPath="";
    float percent = 0;
    unsigned char currentColor = 0;
    bool currentIsColor = false;
    static Data data;
    bool isConsole = false;
    bool m_hasAreaSplitting = true;
    bool quiet = false;
    void Redraw();
    QString comma = ",";

    QColor warningColor = Qt::blue;
    QColor errorColor = Qt::red;

};

#endif // DATA_H
