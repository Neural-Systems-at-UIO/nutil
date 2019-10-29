#ifndef LMESSAGE_H
#define LMESSAGE_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QProcess>
#include <QThread>
class LMessage
{
public:

    int m_max = 15;

    QString m_logFileName = "nutil_log.txt";

    QVector<QString> m_messages;
    QVector<QString> m_logMessages;

    static LMessage lMessage;

    bool isChanged = false;

    bool changed() {
        if (isChanged) {
          isChanged = false;
          return true;
        }
        return false;

    }


    LMessage(int max);
    LMessage();
    void Maintain();
    void Message(QString s);
    void Error(QString s);
    void Log(QString s);


    void AppendMainLog(QString s);

    //void Save(QString fileName);
    void Clear();
    void EndOK();
    void SendFile();
    QString Build();
};

#endif // LMESSAGE_H
