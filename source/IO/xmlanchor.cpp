#include "xmlanchor.h"
//#include <QXmlDefaultHandler>
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
                if (xml.name()==QString("series")) {
                    //continue;
                    QXmlStreamAttributes attributes = xml.attributes();
                    m_atlas = attributes.value("target").toString().split(".").first();
//                    qDebug() << "ATlas is : "<<m_atlas<<attributes.value("target").toString();
                }
                if(xml.name() == QString("slice")) {

                    XMLData d;
                    QXmlStreamAttributes attributes = xml.attributes();
                    d.m_filename = attributes.value("filename").toString();
                    d.m_nr = attributes.value("nr").toInt();
                    d.m_width = attributes.value("width").toInt();
                    d.m_height = attributes.value("height").toInt();
                    QStringList anLst = attributes.value("anchoring").toString().split("&");
                    if (anLst.count()<9) {
                        LMessage::lMessage.Message("Error loading XML anchor file '"+file+"', anchor matrix for slice '"+ QString::number(d.m_nr)+"'. <br>Please make sure that the XML anchor file is valid, or else 3D coordinate data will be incorrect.");
//                        Data::data.abort = true;
  //                      return;
                    } else {

                        d.m_o = QVector3D(anLst[0].split("=")[1].toFloat(), anLst[1].split("=")[1].toFloat(),anLst[2].split("=")[1].toFloat());
                        d.m_u = QVector3D(anLst[3].split("=")[1].toFloat(), anLst[4].split("=")[1].toFloat(),anLst[5].split("=")[1].toFloat());
                        d.m_v = QVector3D(anLst[6].split("=")[1].toFloat(), anLst[7].split("=")[1].toFloat(),anLst[8].split("=")[1].toFloat());
                    }
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

    if (mainMap.contains("bucket")) {
        LoadWebNII(mainMap);
        return;
    }

    //convert the json object to variantmap
    QVariantList dataList = mainMap["slices"].toList();

    //convert the json object to variantmap
    m_atlas = mainMap["target"].toString().split(".").first();
//    qDebug() << "target:" <<m_atlas << mainMap.keys() << mainMap["target"].toString() << dataList.count()<<mainMap["name"].toString();
  //    exit(1);
    for (int i=0;i<dataList.count();i++) {
        QVariantMap map = dataList[i].toMap();
        XMLData d;
        d.m_filename = map.value("filename").toString();
        d.m_nr = map.value("nr").toInt();
        d.m_width = map.value("width").toInt();
        d.m_height = map.value("height").toInt();
        if (!map.contains("anchoring")) {
            LMessage::lMessage.Error("Error: the anchioring file is missing anchoring data for slice: '"+d.m_filename+"'. Please make sure that this slice is correctly anchored and validated before retrying.");
            Data::data.abort = true;
            return;
        }
        else {
            QVariantList anLst = map.value("anchoring").toList();
    //        qDebug() << anLst.count() << anLst;
            d.m_o = QVector3D(anLst[0].toFloat(), anLst[1].toFloat(),anLst[2].toFloat());
            d.m_u = QVector3D(anLst[3].toFloat(), anLst[4].toFloat(),anLst[5].toFloat());
            d.m_v = QVector3D(anLst[6].toFloat(), anLst[7].toFloat(),anLst[8].toFloat());
        }
//        qDebug() << d.m_filename << d.m_nr << d.m_width << d.m_height;
//                    qDebug() << d.m_o;
//                    qDebug() << d.m_v;

       // qDebug() << "Adding slice:" << d.m_filename;

        m_data.append(d);


//        qDebug() << fileMap.keys();
    }

  //  exit(1);

}

void JSONAnchor::LoadWebNII(QVariantMap &mainMap)
{
    //convert the json object to variantmap
    QVariantList dataList = mainMap["bucket"].toList();

    //convert the json object to variantmap
    m_atlas = mainMap["target"].toString().split(".").first();



    //convert the json object to variantmap
    QVariantList slices = mainMap["slices"].toList();

    for (int i=0;i<slices.count();i++) {
        QVariantMap map = slices[i].toMap();
        XMLData d;

        d.m_filename = map.value("filename").toString();
        d.m_filename = d.m_filename.remove(".tif").remove(".png");
        qDebug() << map.value("filename").toString();
        d.m_nr = i+1;//map.value("nr").toInt();
        d.m_width = map.value("width").toInt();
        d.m_height = map.value("height").toInt();
        if (map.contains("anchoring")) {
            QVariantList anLst = map.value("anchoring").toList();
    //        qDebug() << anLst.count() << anLst;

            d.m_o = QVector3D(anLst[0].toFloat(), anLst[1].toFloat(),anLst[2].toFloat());
            d.m_u = QVector3D(anLst[3].toFloat(), anLst[4].toFloat(),anLst[5].toFloat());
            d.m_v = QVector3D(anLst[6].toFloat(), anLst[7].toFloat(),anLst[8].toFloat());
        }
        else {
            LMessage::lMessage.Message("<font color=\"#FF0000\">Warning: Slice "+QString::number(d.m_nr)+" lacks anchoring ("+d.m_filename+")</font>");
        }
//        qDebug() << d.m_filename << d.m_nr << d.m_width << d.m_height;
//                    qDebug() << d.m_o;
//                    qDebug() << d.m_v;

       // qDebug() << "Adding slice:" << d.m_filename;

        m_data.append(d);


//        qDebug() << fileMap.keys();
    }

}
