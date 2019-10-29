#include "lmessage.h"
#include <QDateTime>
#include <QDebug>

LMessage LMessage::lMessage;

LMessage::LMessage(int max)
{
    m_max = max;
}

LMessage::LMessage() {

    m_max = 15;
}

void LMessage::Maintain()
{
    if (m_messages.length()>m_max)
        m_messages.removeFirst();
    isChanged = true;
}

void LMessage::Message(QString s)
{
    m_messages.append(QDateTime::currentDateTime().toString() + " : " +  s);
    AppendMainLog("MESSAGE: " + s );
    Maintain();
}

void LMessage::Log(QString s)
{
    //m_messages.append("LOG:" << QDateTime::currentDateTime().toString() + " : " +  s);
    AppendMainLog("LOG: " + s );
    Maintain();
}

void LMessage::AppendMainLog(QString s)
{
    m_logMessages.append( s );
    QFile f(m_logFileName);
    if (f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream str(&f);
        str <<s << "\n";
    }
    f.close();
    f.flush();
    qDebug() << s;
}

void LMessage::Clear()
{
    m_logMessages.clear();
    m_messages.clear();
    Maintain();
    if (QFile::exists(m_logFileName))
        SendFile();

    AppendMainLog("");
//    SendFile();
}

void LMessage::EndOK()
{
    if (QFile::exists(m_logFileName))
        QFile::remove(m_logFileName);
}

void LMessage::SendFile()
{
    qDebug() << "Mailing logfile... ";
//    QDesktopServices::openUrl(QUrl("mailto:?to=nicolaas.groeneboom@gmail.com&subject=The subject of an email&body=Here is some email body text\nHALLABALLA", QUrl::TolerantMode));
    QProcess p;
 /*   QFile f(m_logFileName);
    qDebug() << "SIZE: "<<f.size();
    f.close();*/
    p.execute("curl", QStringList() <<"smtps://smtp.gmail.com:465" << "--mail-from" <<"nutiluio@gmail.com" <<"--mail-rcpt" <<"nutiluio@gmail.com" << "-ssl" <<"-u"
              <<"nutiluio@gmail.com:LompeSvette90" << "-T" << m_logFileName );
//            curl smtp://smtp.gmail.com:587 -v --mail-from \"SENDER.EMAIL@gmail.com\" --mail-rcpt \"RECEIVER.EMAIL@gmail.com\" --ssl -u SENDER.EMAIL@gmail.com:PASSWORD -T \"ATTACHMENT.FILE\" -k --anyauth
//    qDebug() << QFile::si
//    p.waitForFinished(10000);
 //   QThread::sleep(1);
    EndOK();
}

void LMessage::Error(QString s)
{
    AppendMainLog("ERROR: " + s );
    m_messages.append(QDateTime::currentDateTime().toString() + " : <font color=\"red\">" +  s + "</font>");
    Maintain();

}



QString LMessage::Build()
{
    QString m = "";
    for (QString s : m_messages) {
        m = m + s + "<br>";
    }
    return m;
}
