#include "util.h"
#include <QDebug>
#include <QProcess>


#ifdef _WIN32
//#include <sysinfoapi.h>
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#endif
#include <algorithm>
//#include <QtGlobal>
QString Util::path = "";
QElapsedTimer Util::globalTimer;
bool Util::CancelSignal = false;
#ifndef _WIN32
using namespace std;
#endif

QColor Util::colorScale(QColor &col, int mean, int std)
{
    float f = 1.0/(2*std)*255;
    QVector3D c;



    c.setX((col.red()-mean)*f + mean);
    c.setY((col.green()-mean)*f + mean);
    c.setZ((col.blue()-mean)*f + mean);
    c = clamp(c,0,255);
    return QColor(c.x(), c.y(), c.z());

}

QColor Util::colorScale2(QColor &col, int x0, int x1)
{
    float f = 1.0/((x1-x0))*255;
    QVector3D c;



    c.setX((col.red()-x0)*f);
    c.setY((col.green()-x0)*f);
    c.setZ((col.blue()-x0)*f);
    c = clamp(c,0,255);
    return QColor(c.x(), c.y(), c.z());

}

QString Util::RemoveFinalFiletype(QString input)
{
    QStringList ls = input.split(".");
    if (ls.count()==1)
        return input;
    QString res = "";
    for (int i=0;i<ls.count()-1;i++)
        res+=ls[i]+".";
    res.remove(res.length()-1,1);
    return res;
}

void Util::CreateDir(QString path)
{
    QDir dirr(path);
    if (!dirr.exists())
        dirr.mkpath(".");
}

QString Util::getBaseFilename(QString fn)
{
    if (!fn.contains("."))
        return fn;
    QStringList s = fn.split(".");
    s.removeLast();
    QString file ="";
    for (QString str : s)
        file += str +".";

    file = file.remove(file.count()-1,1);
    return file;

}

bool Util::CompareIdenticalFiles(QString fa, QString fb)
{

    if (fa.toLower().endsWith(".png")) {
        QImage i1(fa);
        QImage i2(fa);
        if (i1.width()!=i2.width()) return false;
        if (i1.height()!=i2.height()) return false;
        for (int j=0;j<i1.height();j++)
            for (int i=0;i<i1.width();i++) {
                if (i1.pixel(i,j)!=i2.pixel(i,j))
                    return false;
            }
        return true;
    }

    if (fa.toLower().endsWith(".csv")) {
        QString a = Util::loadTextFile(fa);
        QString b = Util::loadTextFile(fb);
        QStringList l1 = a.trimmed().simplified().remove("\n").split(";");
        QStringList l2 = b.trimmed().simplified().remove("\n").split(";");
        l1.removeAll(QString(""));
        l2.removeAll(QString(""));
//        qDebug() << l1 << l2;
        if (l1.count()!=l2.count()) {
            qDebug() << "CSV files do not have the same count of elements";
            return false;
        }

        for (int i=0;i<l1.count();i++) {
            if (l1[i].trimmed()!=l2[i].trimmed()) {
                qDebug() << "CSV file not equal for fields "<<l1[i]<<" and " <<l2[i];
                return false;
            }
        }
        return true;
    }

    QByteArray ba = loadBinaryFile(fa);
    QByteArray bb = loadBinaryFile(fb);
    if (ba.count()!=bb.count())
        return false;
    for (long l=0;l<ba.size();l++)
        if (ba.at(l)!=bb.at(l))
            return false;

    return true;
}

QByteArray Util::loadBinaryFile(QString filename) {
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    file.close();
    return ba;
}

float Util::getFreeRam()
{
#ifdef _WIN32
    MEMORYSTATUSEX memory_status;
    ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memory_status)) {
        return memory_status.ullTotalPhys / (1024 * 1024);
    } else {
        return 0;
    }
#endif

#ifdef __linux__

    QProcess p;
    p.start("awk", QStringList() << "/MemFree/ { print $2 }" << "/proc/meminfo");
    p.waitForFinished();
    QString memory = p.readAllStandardOutput();
    return memory.toLong() / 1024.0/1024.0;
    p.close();

#endif
}

float Util::getAmountOfInstalledMemory()
{
#ifdef _WIN32
    MEMORYSTATUSEX memory_status;
    ZeroMemory(&memory_status, sizeof(MEMORYSTATUSEX));
    memory_status.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memory_status)) {
        return memory_status.ullTotalPhys / (1024 * 1024);
    } else {
      return 0;
    }
#elif __linux__
//    Linux (/proc/meminfo)

    QProcess p;
    p.start("awk", QStringList() << "/MemTotal/ { print $2 }" << "/proc/meminfo");
    p.waitForFinished();
    QString memory = p.readAllStandardOutput();
    return memory.toLong() / 1024.0/1024.0;
#elif __APPLE__
/*    Mac (sysctl)

    QProcess p;
    p.start("sysctl", QStringList() << "kern.version" << "hw.physmem");
    p.waitForFinished();
    QString system_info = p.readAllStandardOutput();
    p.close();*/
#endif
}

std::string Util::c2x(int x, int y) {
    std::string s ="";
    int k=y/26;
    if (k!=0) s = s+char('A' + k-1);

    s = s+char('A' + (y%26));
    s += std::to_string(x+1);
 //   if (x<4)
   //     qDebug() <<QString::fromStdString(s) <<k << x << y;
    return s;
}


bool Util::VerifyImageFileSize(QString file, int avgDimension)
{
    QImageReader reader(file);
    if (reader.size().width()>avgDimension || reader.size().height()>avgDimension){
        return false;
    }
    return true;

}

float Util::getImageFileSizeInGB(QString file)
{

    QImageReader reader(file);
//    qDebug()<< "WIDTH " << reader.size().width();
    return reader.size().width()*reader.size().height()*4/1024/1024.0/1024.0;


}

QString Util::findFileInDirectory(QString search, QString dir, QString extension,QString exclusion)
{
    QDirIterator it(dir, QStringList() << "*." + extension, QDir::Files);
    while (it.hasNext()) {
        QString f = it.next();
        if (search=="")
            return f;
        QString stripped  = f.split("/").last().toLower();
        if (exclusion!="")
            if (stripped.toLower().contains(exclusion.toLower()))
                continue;

        if (stripped.toLower().contains(search.toLower()))
            return f;
    }
    return "";

}

QString Util::findFileInDirectory(QStringList search, QString dir, QString extension,QString exclusion)
{
    QDirIterator it(dir, QStringList() << "*." + extension, QDir::Files);
    while (it.hasNext()) {
        QString f = it.next();
        if (search.count()==0)
            return f;


        QString stripped  = f.split("/").last().toLower();
        if (exclusion!="")
        if (stripped.toLower().contains(exclusion.toLower()))
            continue;

        bool found = true;
        for (auto s: search)
            if (!stripped.contains(s.toLower()))
                found = false;
        if (found)
            return f;
    }
    return "";

}

QString Util::listFiles(QDir directory, QString searchFile)
{
        QDir dir(directory);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        foreach(QFileInfo finfo, list) {
              //  qDebug() << finfo.fileName();
                if (finfo.isDir()) {
                        QString s = listFiles(QDir(finfo.absoluteFilePath()), searchFile);
                        if (s!="")
                            return s;
                }
//                if (finfo.fileName().toLower()==searchFile.toLower())
                    if (finfo.fileName().toLower().contains(searchFile.toLower()))
                    return finfo.absoluteFilePath();

        }
        return "";
}

void Util::CopyFileHard(QString a, QString b)
{
    auto data = Util::loadTextFile(a);
    Util::SaveTextFile(b,data);
}



void Util::findFilesInSubDirectories(QStringList* lst, QString directory, QString extension, bool fullName)
{
    QDir dir(directory);
    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo finfo, list) {
            if (finfo.isDir())
                findFilesInSubDirectories(lst, finfo.absoluteFilePath(), extension,fullName);
            else
                if (finfo.fileName().toLower().endsWith(extension)) {
                    if (!fullName)
                        lst->append(finfo.fileName());
                    else
                        lst->append(finfo.filePath());
                }


    }

}



QString Util::findFileInSubDirectories(QString search, QString dir, QString extension)
{
    QDir directory(dir);
    return listFiles(directory, search);

}

float Util::clamp(float val, const float mi, const float ma) {
    val = std::min(ma, val);
    val = std::max(mi, val);
    return val;
}

QColor Util::Gamma(QColor c, float xexp, float shift)
{
    float x = c.red();
    float y = c.green();
    float z = c.blue();
    x = std::pow(x - shift, xexp);
    y = std::pow(y - shift, xexp);
    z = std::pow(z - shift, xexp);
    x = clamp(x,0,255);
    y = clamp(y,0,255);
    z = clamp(z,0,255);
    return QColor(x,y,z);
}

QVector3D Util::clamp(const QVector3D val, const float min, const float max)
{
    QVector3D v = val;
    v.setX(clamp(val.x(),min,max));
    v.setY(clamp(val.y(),min,max));
    v.setZ(clamp(val.z(),min,max));
    return v;
}

QString Util::getFileName(QString dir, QString baseName, QString type)
{
    QDirIterator it(dir,
                    QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
    int maxNumber = 1;
    while (it.hasNext()) {
        QString filename = it.next();
        QStringList split = filename.split("/");
        filename = split[split.length()-1];
        if (filename.contains(baseName)) {
            filename = filename.replace(baseName, "");
            filename = filename.replace("."+type, "");
            int num = filename.toInt();
            maxNumber = std::max(maxNumber, num);
        }
    }
    maxNumber++;
    return baseName + QString::number(maxNumber).rightJustified(4, '0');// + "." + type;

}

QString Util::loadTextFile(QString filename) {
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString data = in.readAll();
    file.close();
    return data;
}

void Util::SaveTextFile(QString fname, QString text)
{
    if (QFile::exists(fname)) {
        QFile::remove(fname);
    }
    if (fname=="")
        return;
    QFile file(fname);
    file.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream f(&file);
    f<<text;
    file.close();

}



float Util::smoothstep(float edge0, float edge1, float x)
{
    // Scale, bias and saturate x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
    // Evaluate polynomial
    return x*x*(3 - 2 * x);
}


bool Util::QVector3DIsClose(QVector3D a, QVector3D b, QVector3D spread)
{

    QVector3D c = b-a;
    if (abs(c.x())>spread.x())
        return false;
    if (abs(c.y())>spread.y())
        return false;
    if (abs(c.z())>spread.z())
        return false;
    return true;
}

bool Util::QVector3DIsClose(QColor a, QColor b, QVector3D spread)
{
    return Util::QVector3DIsClose( QVector3D(a.red(), a.green(), a.blue()),
                                        QVector3D(b.red(), b.green(), b.blue()), spread );

}

QVector3D Util::vecFromString(QString s)
{
    QStringList sl = s.split(";");

    return QVector3D(sl[0].toFloat(), sl[1].toFloat(),sl[2].toFloat());
}
