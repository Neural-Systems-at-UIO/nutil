#ifndef PROCESSITEM_H
#define PROCESSITEM_H


#include <QString>


class ProcessItem {
public:
    QString m_inFile;
    QString m_outFile;

    QString m_outFolder;
    QString m_outFileSingle;


    QString m_id;

    float m_angle;
    float m_scale;

    float m_pixelAreaScale;

    ProcessItem() {

    }

    ProcessItem(QString inFile, QString outFile, float angle, float scale, QString outFileSingle, QString outFolder) {
        m_inFile = inFile;
        m_outFile = outFile;
        m_angle = angle;
        m_scale = scale;
        m_outFolder = outFolder;
        m_outFileSingle = outFileSingle;
    }


};

#endif // PROCESSITEM_H
