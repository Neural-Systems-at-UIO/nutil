#include "report.h"
#include <QMatrix4x4>
#include "source/IO/nifti.h"
#include <QPointF>

void Report::GenerateSheet(LBook* book)
{
    LSheet* sheet = book->CreateSheet(m_filename);
    if(sheet)
    {
        sheet->writeStr(0,0, "Pixel count");
        sheet->writeStr(0,1, "Area");

        sheet->writeStr(0, 2, "object_area_units");
        sheet->writeStr(0, 3, "Center X");
        sheet->writeStr(0, 4, "Center Y");
        sheet->writeStr(0, 5, "Area ID");
        sheet->writeStr(0, 6, "Area name");

        for (int i=0;i<m_areasOfInterest.count();i++) {
  //          qDebug() << i << " / " << m_areasOfInterest.count();
            sheet->writeNum(1+i,0, m_areasOfInterest[i]->m_pixelArea);
            sheet->writeNum(1+i,1, m_areasOfInterest[i]->m_area);
            sheet->writeNum(1+i,3, m_areasOfInterest[i]->m_center.x());
            sheet->writeNum(1+i,4, m_areasOfInterest[i]->m_center.y());
            if (!m_areasOfInterest[i]->atlasLabel) {
                LMessage::lMessage.Message("WARNING: Could not find atlasLabel coupling for area: " + QString::number(i) + " in sheet " + m_filename);
            }
            else {
                sheet->writeNum(1+i,5, m_areasOfInterest[i]->atlasLabel->index);
                sheet->writeStr(1+i,6, m_areasOfInterest[i]->atlasLabel->name);
            }
        }

    }
}

void Reports::CreateSummary(AtlasLabels* atlasLabels)
{
    LSheet* sheet = m_book->GetSheet(0);//CreateSheet("Summary");
    Calculate(atlasLabels);

    if (sheet) {

        sheet->writeStr(0,0, "Region name");
        sheet->writeStr(0,1, "reg_idx_full");
        sheet->writeStr(0,2, "reg_idx");
        sheet->writeStr(0,3, "Region pixel area");
        sheet->writeStr(0,4, "Region area");
        sheet->writeStr(0,5, "Area unit");
        sheet->writeStr(0,6, "Object count");
        sheet->writeStr(0,7, "Object region count ratio");
        sheet->writeStr(0,8, "Object pixel");
        sheet->writeStr(0,9, "Object area");
        sheet->writeStr(0,10, "Object area unit");
        sheet->writeStr(0,11, "Pixel area ratio");
        sheet->writeStr(0,12, "Object area ratio");

        int i = 1;
        for (Report& r : m_reports) {
            sheet->writeStr(i,0, r.m_filename);
            sheet->writeNum(i,3, r.m_regionPixelArea);
            sheet->writeNum(i,4, r.m_regionArea);
            sheet->writeNum(i,6, r.m_areasOfInterest.count());
            sheet->writeNum(i,8, r.m_totalPixelArea);
            sheet->writeNum(i,9, r.m_totalArea);
            sheet->writeNum(i,11, r.m_totalPixelArea/(float)r.m_regionPixelArea);
            sheet->writeNum(i,12, r.m_totalArea/(float)r.m_regionArea);



            i++;
        }

    }

}

void Reports::CreateCombinedList(QString fileName, AtlasLabels *atlasLabels, QVector<NutilProcess*> processes, QVector<ProcessItem*> items)
{
    LBook* book = new LBookXlnt();
    LSheet* sheet = book->CreateSheet("Entire region summary");
    sheet->writeStr(0,0,"Region ID");
    sheet->writeStr(0,1,"Region Name");
    sheet->writeStr(0,2,"Pixel area");
    sheet->writeStr(0,3,"Object area");
    sheet->writeStr(0,4,"units");
    sheet->writeStr(0,5,"No Objects");

    for (AtlasLabel* al: atlasLabels->atlases) {
        al->extra2 = QVector3D(0,0,0);
        al->count = 0;

    }
    for (NutilProcess* process: processes) {
        for (Area& a: process->m_areas) {
            //if (a->atlasLabel->index==al->index)
            {
                a.atlasLabel->extra2.setX(a.atlasLabel->extra2.x() + a.m_pixelArea);
                a.atlasLabel->extra2.setY(a.atlasLabel->extra2.y() + a.m_area);
                a.atlasLabel->count+=1;
            }
        }
    }


    QVector<AtlasLabel*> sorted;
    for (AtlasLabel* al: atlasLabels->atlases)
        sorted.append(al);

    qSort(sorted.begin(), sorted.end(),
          [](const AtlasLabel* a, const AtlasLabel* b) -> bool { return a->extra2.x() > b->extra2.x(); });

    int y = 1;
    for (AtlasLabel* al: sorted) {
        // Header
        if (al->extra2.length()!=0) {
            sheet->writeNum(y,0,al->index);
            sheet->writeStr(y,1,al->name);
            sheet->writeNum(y,2,al->extra2.x());
            sheet->writeNum(y,3,al->extra2.y());
            sheet->writeStr(y,4,"");
            sheet->writeNum(y,5,al->count);
            y++;
        }

    }
    book->Save(fileName);
}

void Reports::CreateSliceReports(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items)
{
    LBook* book = new LBookXlnt();
    LSheet* summary = book->GetSheet(0);

    float sumPixel=0;
    float sumArea = 0;
    float totalSumPixel=0;
    float totalSumArea = 0;

    summary->writeStr(0,0,"Total pixel area");
    summary->writeStr(0,1,"Total object area");
    summary->writeStr(2,0,"Pixel area");
    summary->writeStr(2,1,"Object area");
    summary->writeStr(2,2,"units");
    summary->writeStr(2,3,"Center X");
    summary->writeStr(2,4,"Center Y");
    summary->writeStr(2,5,"Region ID");
    summary->writeStr(2,6,"Region Name");
    int yy=3;

    for (int i=0;i<items.count();i++) {
        LSheet* sheet = book->CreateSheet(items[i]->m_id);
        // Header
        sheet->writeStr(0,0,"Total pixel area");
        sheet->writeStr(0,1,"Total object area");
        sheet->writeStr(2,0,"Pixel area");
        sheet->writeStr(2,1,"Object area");
        sheet->writeStr(2,2,"units");
        sheet->writeStr(2,3,"Center X");
        sheet->writeStr(2,4,"Center Y");
        sheet->writeStr(2,5,"Region ID");
        sheet->writeStr(2,6,"Region Name");
        int y = 3;
        for (Area& a: processes[i]->m_areas) {
            sheet->writeNum(y,0,a.m_pixelArea);
            sheet->writeNum(y,1,a.m_area);

            sumPixel+=a.m_pixelArea;
            sumArea+=a.m_area;
            totalSumPixel+=a.m_pixelArea;
            totalSumArea+=a.m_area;

            sheet->writeNum(y,3,a.m_center.x());
            sheet->writeNum(y,4,a.m_center.y());
            if (a.atlasLabel!=nullptr) {
                sheet->writeNum(y,5,a.atlasLabel->index);
                sheet->writeStr(y,6,a.atlasLabel->name);
            }
            y++;

            summary->writeNum(yy,0,a.m_pixelArea);
            summary->writeNum(yy,1,a.m_area);
            summary->writeNum(yy,3,a.m_center.x());
            summary->writeNum(yy,4,a.m_center.y());
            if (a.atlasLabel!=nullptr) {
                summary->writeNum(yy,5,a.atlasLabel->index);
                summary->writeStr(yy,6,a.atlasLabel->name);
            }
            yy++;

        }

        sheet->writeNum(1,0,sumPixel);
        sheet->writeNum(1,1,sumArea);
        sumArea=0;
        sumPixel=0;


    }
    summary->writeNum(1,0,totalSumPixel);
    summary->writeNum(1,1,totalSumArea);
    book->Save(filename);
}

void Reports::Create3DSummary(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items, int xyzSize)
{

    QString o;
    o += "SCALE 3\n";



    for (int i=0;i<m_reports.count();i++) {
        //qDebug() << mat;
        //  items[i]->m_xmlData.matrix
        QColor c = m_reports[i].m_color;
        QString color = QString::number((float)c.red()/255.0) + " " + QString::number((float)c.green()/255.0) + " " + QString::number((float)c.blue()/255.0) +" 1";
        o +="RGBA " + color +" \n";
        qDebug() << m_reports[i].m_filename << " " << m_reports[i].m_areasOfInterest.count();
        int count=0;
        for (Area* a: m_reports[i].m_areasOfInterest) {
/*            if (rand()%100>90)
                qDebug() << color << " vs " << a->color;
*/


/*
 *
            QVector3D v(1,a->m_center.x()/a->m_width,a->m_center.y()/a->m_height);
            v=v*a->m_mat;
            o +=QString::number(v.x()) + ",";
            o +=QString::number(v.y()) + ",";
            o +=QString::number(v.z()) + "\n";
*/


            for (int k=0;k<a->m_points.count();k+=(a->m_points.count()/xyzSize)+1) {
                QPointF& p =a->m_points[k];
                QVector3D v(1,p.x()/a->m_width,p.y()/a->m_height);
                v=v*a->m_mat;
                o +=QString::number(v.x()) + ",";
                o +=QString::number(v.y()) + ",";
                o +=QString::number(v.z()) + "\n";
                if (count++>1000) {
                    o +="RGBA " + color +" \n";
                    count=0;

                }
            }


        }
    }

    QFile file (filename);
    file.open(QFile::Text | QFile::WriteOnly);
    QTextStream outstream(&file);
    outstream << o;
    file.close();
}

void Reports::CreateNifti(QString filename, QVector<NutilProcess *> processes, QVector<ProcessItem *> items, int size)
{
    Nifti n;
    n.Create(QVector3D(size,size,size),Nifti::DataType::DT_RGB, 24);
    n.rawData.fill(0);
    qDebug() << "Creating nifti..";
    qDebug() << n.size;
    for (int i=0;i<m_reports.count();i++) {
        QColor c = m_reports[i].m_color;
        qDebug() << c.red() << ", " << c.green() << ", " << c.blue() << "  : " << m_reports[i].m_areasOfInterest.count();

        for (Area* a: m_reports[i].m_areasOfInterest) {

            //c.setRed(rand()%255);
            //c.setBlue(rand()%255);
            //qDebug() << a->m_points.count();
            for (QPointF& p: a->m_points) {
//                QPointF pp=a->m_center;
                QVector3D v(1,p.x()/a->m_width,p.y()/a->m_height);

                v=v*a->m_mat;
                v=v/1.2;




/*                v = QVector3D(rand()%128, rand()%128, rand()%128);
                v=v/4.0;
*/
                //if (rand()%100>98) qDebug() << v;

                n.SetRGBPixel(v,c);
                n.SetRGBPixel(v + QVector3D(1,0,0),c);
                n.SetRGBPixel(v - QVector3D(1,0,0),c);
                n.SetRGBPixel(v + QVector3D(0,1,0),c);
                n.SetRGBPixel(v - QVector3D(0,1,0),c);
                n.SetRGBPixel(v + QVector3D(0,0,1),c);
                n.SetRGBPixel(v - QVector3D(0,0,1),c);
            }
        }
    }




    n.Save(filename);

}

void Report::FindAreasOfInterest(QVector<NutilProcess *>& processes)
{
    m_areasOfInterest.clear();
    for (long i : m_IDs) {
        for (NutilProcess* np : processes)
            for (Area& a: np->m_areas)
                if (a.atlasLabel!=nullptr) {
/*                    if (i==182305705)
                        if (i>18230570)
                        //if (a.atlasLabel->index>1000)
                        qDebug() << "Check: " << i << " vs " << a.atlasLabel->index;*/
                     if (a.atlasLabel->index == i) {
                        m_areasOfInterest.append(&a);
                     }

                }


    }
//    qDebug() << "Found amount: " << m_areasOfInterest.count();

}

void Reports::Calculate(AtlasLabels* atlasLabels)
{
    for (Report& r: m_reports) {
        r.m_totalPixelArea = 0;
        r.m_regionPixelArea = 0;
        r.m_totalArea = 0;
        r.m_regionArea = 0;
        for (Area* a: r.m_areasOfInterest) {
            r.m_totalPixelArea+=a->m_pixelArea;
            r.m_totalArea +=a->m_area;
            a->color = r.m_color;
//            if (rand()%100>98) qDebug() << r.m_color;
        }
        for (long i: r.m_IDs)
        {
            AtlasLabel* al = atlasLabels->get(i);
            if (al!=nullptr) {
                r.m_regionPixelArea += al->area;
                r.m_regionArea += al->areaScaled;
            }
        }

/*        QVector<long> used;


        for (long i: r.m_IDs)
        {
            bool ok = true;
            for (int j=0;j<used.count();j++)
                if (used[j]==i) ok=false;

            if (!ok)
                continue;
            AtlasLabel* al = atlasLabels->get(i);
            if (al!=nullptr) {
                r.m_regionPixelArea += al->area;
                r.m_regionArea += al->areaScaled;
                used.append(i);
            }
        }

*/
    }
}

void Reports::CreateBook(QString filename)
{
    m_book = new LBookXlnt();
    //m_book = xlCreateXMLBook();// for xlsx
    m_filename = filename;

}

void Reports::CreateSheets(QVector<NutilProcess*>& processes,AtlasLabels* atlasLabels)
{
    if (!m_book)
        return;

    qDebug() << "Finding areas of interest";
    for (Report& r: m_reports)
            r.FindAreasOfInterest(processes);

    qDebug() << "Creating summary ";
    CreateSummary(atlasLabels);

    qDebug() << "Generating sheets ";

    for (Report& r: m_reports) {
        qDebug() << r.m_filename;
        r.GenerateSheet(m_book);
        qDebug() << "Done";
    }
    qDebug() << "Saving to " << m_filename;
    m_book->Save(m_filename);

    qDebug() << "Releasing " << m_filename;
    m_book->Release();

}


QVector<QVector<long> > Reports::getList()
{
    QVector<QVector<long>> list;
    for (Report& r: m_reports) {
        list.append(r.m_IDs);
    }
    return list;
}


