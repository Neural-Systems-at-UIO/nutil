#include "xmlanchor.h"
#include <QXmlDefaultHandler>
#include <QXmlStreamReader>
#include "source/util/lmessage.h"
#include "source/data.h"
#include <QJsonDocument>
#include <QObject>
#include "source/util/util.h"
/*
XMLAnchor::XMLAnchor()
{

}
*/
XMLData AbstractAnchor::findData(QString name)
{
    for (XMLData& d : m_data) {
 //       qDebug() <
        if (d.m_filename.contains(name))
            return d;
    }

//    qDebug() << "Could not find xmldata for:" << name;
    LMessage::lMessage.Message("<font color=\"" + Data::data.warningColor.name()+ "\">Warning: Could not find xmldata in .xml file for slice '" + name +"', so 3D data will be incorrect. Please make sure that there exists a corresponding field in the xml file!</font>");

    return XMLData();

}

void XMLAnchor::Load(QString file)
{
    QFile f(file);
    f.open(QFile::ReadOnly);
    QByteArray qa = f.readAll();

    QByteArray n;
    for (int i=0;i<qa.size();i++) {
        if (qa[i]=='&') {
            n.append('&');
            n.append('a');
            n.append('m');
            n.append('p');
            n.append(';');
        }
        else
            n.append(qa[i]);
    }

//    qDebug() << "Loading xml file:" << file;
    QXmlStreamReader xml(n);
    QList< QMap<QString,QString> > files;
        /* We'll parse the XML until we reach end of it.*/
        while(!xml.atEnd() &&
                !xml.hasError()) {
            /* Read next element.*/
            QXmlStreamReader::TokenType token = xml.readNext();
            /* If token is just StartDocument, we'll go to next.*/
            if(token == QXmlStreamReader::StartDocument) {
                continue;
            }

            /* If token is StartElement, we'll see if we can read it.*/
            if(token == QXmlStreamReader::StartElement)
            {
                /* If it's named persons, we'll go to the next.*/
                if (xml.name()=="series") {
                    //continue;
                }
                if(xml.name() == "slice") {

                    XMLData d;
                    QXmlStreamAttributes attributes = xml.attributes();
                    d.m_filename = attributes.value("filename").toString();
                    d.m_nr = attributes.value("nr").toInt();
                    d.m_width = attributes.value("width").toInt();
                    d.m_height = attributes.value("height").toInt();
                    QStringList anLst = attributes.value("anchoring").toString().split("&");
                    //qDebug() << anLst.count();
                    d.m_o = QVector3D(anLst[0].split("=")[1].toFloat(), anLst[1].split("=")[1].toFloat(),anLst[2].split("=")[1].toFloat());
                    d.m_u = QVector3D(anLst[3].split("=")[1].toFloat(), anLst[4].split("=")[1].toFloat(),anLst[5].split("=")[1].toFloat());
                    d.m_v = QVector3D(anLst[6].split("=")[1].toFloat(), anLst[7].split("=")[1].toFloat(),anLst[8].split("=")[1].toFloat());

//                    qDebug() << d.m_o;
//                    qDebug() << d.m_v;

                   // qDebug() << "Adding slice:" << d.m_filename;

                    m_data.append(d);
                        /* Let's check that person has id attribute. */
                }
                /* If it's named person, we'll dig the information from there.*/
                //}
            }
        }
        if(xml.hasError()) {
            qDebug() << "XML ERROR: " << xml.errorString();
            LMessage::lMessage.Error("Error: Error parsing xml anchoring file: " + xml.errorString());

           }
}

void JSONAnchor::Load(QString file)
{

    QString val = Util::loadTextFile(file);

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());

    //get the jsonObject
    QJsonObject jObject = doc.object();

    //convert the json object to variantmap
    QVariantMap mainMap = jObject.toVariantMap();

    //convert the json object to variantmap
    QVariantList dataList = mainMap["slices"].toList();

    for (int i=0;i<dataList.count();i++) {
        QVariantMap map = dataList[i].toMap();
        XMLData d;
        d.m_filename = map.value("filename").toString();
        d.m_nr = map.value("nr").toInt();
        d.m_width = map.value("width").toInt();
        d.m_height = map.value("height").toInt();
        QVariantList anLst = map.value("anchoring").toList();
//        qDebug() << anLst.count() << anLst;

        d.m_o = QVector3D(anLst[0].toFloat(), anLst[1].toFloat(),anLst[2].toFloat());
        d.m_u = QVector3D(anLst[3].toFloat(), anLst[4].toFloat(),anLst[5].toFloat());
        d.m_v = QVector3D(anLst[6].toFloat(), anLst[7].toFloat(),anLst[8].toFloat());

//        qDebug() << d.m_filename << d.m_nr << d.m_width << d.m_height;
//                    qDebug() << d.m_o;
//                    qDebug() << d.m_v;

       // qDebug() << "Adding slice:" << d.m_filename;

        m_data.append(d);


//        qDebug() << fileMap.keys();
    }

  //  exit(1);

}
