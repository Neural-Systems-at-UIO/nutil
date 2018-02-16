#include "updater.h"
#include <QCoreApplication>

Updater::Updater()
{

}

void Updater::Initialize()
{
    int a = 1;
    QCoreApplication app(a, nullptr);

    QUrl versionUrl("https://www.irio.co.uk/med/nutil/version.txt");
    DownloadManager dm;
    dm.append(versionUrl);
    dm.saveFileName(versionUrl);
    //dm.st

    QObject::connect(&dm, SIGNAL(finished()), &app, SLOT(quit()));
    app.exec();

    qDebug() << "SAVED";

}
void Updater::loadVersion()
{
 //buttonImage.loadFromData(m_pImgCtrl->downloadedData());

}
