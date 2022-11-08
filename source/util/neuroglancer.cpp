#include "neuroglancer.h"
#include "util.h"
#include "source/util/lmessage.h"


void NeuroGlancer::Open(QString directory)
{
    QString val = Util::loadTextFile(directory+"/info");

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    //get the jsonObject
    QJsonObject jObject = doc.object();

    //convert the json object to variantmap
    QVariantMap mainMap = jObject.toVariantMap();

    //convert the json object to variantmap
    QVariantList dataList = mainMap["num_channels"].toList();

    //convert the json object to variantmap
    int num_channels = mainMap["num_channels"].toString().toInt();

    QVariantMap scales = mainMap["scales"].toList()[0].toMap();

    QVariantList chunkList = scales["chunk_sizes"].toList()[0].toList();
    QVariantList size = scales["size"].toList();

    m_chunkSize = QPoint(chunkList[0].toInt(),chunkList[1].toInt());
    m_size = QPoint(size[0].toInt(),size[1].toInt());
    LMessage::lMessage.Message("Chunk sizes (" + QString::number(m_chunkSize.x()) + ", "+QString::number(m_chunkSize.y())+")");
    LMessage::lMessage.Message("Image size (" + QString::number(m_size.x()) + "," +QString::number(m_chunkSize.y())+")");
    m_chunkDir = directory + scales["key"].toString()+"/";


}

void NeuroGlancer::LoadAllChunks()
{
    m_img = QImage(m_size.x(), m_size.y(), QImage::Format_ARGB32);
    m_img.fill(0);
//    qDebug() << "chunk dir: "<<m_chunkDir;
    QDir directory(m_chunkDir);

    QStringList files = directory.entryList(QDir::Files);
    for (QString filename: files) {
        QStringList dims = filename.split("_");
        auto data = Util::loadBinaryFile(m_chunkDir+filename);
  //      qDebug() << filename;
        int startx = dims[0].split("-")[0].toInt();
        int endx = dims[0].split("-")[1].toInt();
        int starty = dims[1].split("-")[0].toInt();
        int endy = dims[1].split("-")[1].toInt();
        int sx = endx-startx;
        int sy = endy-starty;
        int diff = sx*sy;
    //    qDebug() << sx << sy << sx*sy*3 <<data.size();
        int pos = 0;
        for (int j=0;j<sy;j++) {
            for (int i=0;i<sx;i++) {
                int pos = j*sx + i;
                QColor color = QColor((uchar)data[pos+0],(uchar)data[pos+diff*1], (uchar)data[pos+diff*2]);
                m_img.setPixel(i+startx,j+starty,color.rgba());
            }
        }

    }

}

