#include "report.h"
#include <QMatrix4x4>
#include "source/IO/nifti.h"
#include <QPointF>

void Report::GenerateSheet(LBook* book, QString units)
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
            sheet->writeStr(1+i,2, units);
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
    sheet->setName("All");

    if (sheet) {

        sheet->writeStr(0,0, "Region name");
        sheet->writeStr(0,1, "Region pixels");
        sheet->writeStr(0,2, "Region area");
        sheet->writeStr(0,3, "Area unit");
        sheet->writeStr(0,4, "Object count");
        sheet->writeStr(0,5, "Object pixel");
        sheet->writeStr(0,6, "Object area");
        sheet->writeStr(0,7, "Area unit");
        sheet->writeStr(0,8, "Load");


        int i = 1;
        for (Report& r : m_reports) {
            sheet->writeStr(i,0, r.m_filename);
            sheet->writeNum(i,1, r.m_regionPixelArea);
            sheet->writeNum(i,2, r.m_regionArea);
            sheet->writeStr(i,3, r.m_unit);
            sheet->writeNum(i,4, r.m_areasOfInterest.count());
            sheet->writeNum(i,5, r.m_totalPixelArea);
            sheet->writeNum(i,6, r.m_totalArea);
            sheet->writeStr(i,7, r.m_unit);
            if (r.m_regionPixelArea!=0)
                sheet->writeNum(i,8, r.m_totalPixelArea/(float)r.m_regionPixelArea);


            i++;
        }

    }

}

void Reports::CreateRefAtlasRegions(QString fileName, AtlasLabels *atlasLabels, QVector<NutilProcess*> processes, QVector<ProcessItem*> items, QString units, QString bookType)
{
    LBook* book = LBookFactory::Create(bookType);
//    LSheet* sheet = book->CreateSheet("All");
    LSheet* sheet = book->GetSheet(0);

//    if (dynamic_cast<LBookXlnt*>(book))
  //      book->RemoveSheet(1);




    sheet->writeStr(0,0,"Region ID");
    sheet->writeStr(0,1,"Region Name");
    sheet->writeStr(0,2,"Region pixels");
    sheet->writeStr(0,3,"Region area");
    sheet->writeStr(0,4,"Area unit");
    sheet->writeStr(0,5,"Object count");
    sheet->writeStr(0,6,"Object pixels");
    sheet->writeStr(0,7,"Object area");
    sheet->writeStr(0,8,"Area unit");
    sheet->writeStr(0,9,"Load");


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

//    qSort(sorted.begin(), sorted.end(),
  //        [](const AtlasLabel* a, const AtlasLabel* b) -> bool { return a->extra2.y() > b->extra2.y(); });

    int y = 1;
    for (AtlasLabel* al: sorted) {
        // Header
        //if (al->extra2.length()!=0)
        {
            sheet->writeNum(y,0,al->index);
            sheet->writeStr(y,1,al->name);
            sheet->writeNum(y,2,al->area);
            sheet->writeNum(y,3,al->areaScaled);
            sheet->writeStr(y,4,units);
            if (Data::data.m_hasAreaSplitting)
                sheet->writeStr(y,5,"N/A");
            else
                sheet->writeNum(y,5,al->count);

            sheet->writeNum(y,6,al->extra2.x());
            sheet->writeNum(y,7,al->extra2.y());
            sheet->writeStr(y,8,units);
            sheet->writeNum(y,9,0);
            //sheet->writeNum(y,,10);

            if (al->area!=0.0 && !isnan(al->extra2.x()/al->area))
                sheet->writeNum(y,9,al->extra2.x()/al->area);
 //           if (al->areaScaled!=0)
   //             sheet->writeNum(y,10,al->extra2.y()/al->areaScaled);

            y++;
        }

    }
    book->Save(fileName);
}

void Reports::CreateRefAtlasRegionsSlices(QString filename, AtlasLabels *atlasLabels, QVector<NutilProcess *> processes, QVector<ProcessItem *> items, QString units, QString bookType)
{
    LBook* book = LBookFactory::Create(bookType);
    /*   QVector<AtlasLabel*> sorted;
    for (AtlasLabel* al: atlasLabels->atlases)
        sorted.append(al);
*/
    //    qSort(sorted.begin(), sorted.end(),
    //        [](const AtlasLabel* a, const AtlasLabel* b) -> bool { return a->extra2.y() > b->extra2.y(); });






    for (int i=0;i<processes.length();i++) {
        LSheet* sheet = book->CreateSheet(items[i]->m_reportName);
        int y = 1;

        for (AtlasLabel* al: atlasLabels->atlases) {
            al->extra2 = QVector3D(0,0,0);
            al->count = 0;
        }
        for (Area& a: processes[i]->m_areas) {
            {
                a.atlasLabel->extra2.setX(a.atlasLabel->extra2.x() + a.m_pixelArea);
                a.atlasLabel->extra2.setY(a.atlasLabel->extra2.y() + a.m_area);
                a.atlasLabel->count+=1;
            }
        }


        sheet->writeStr(0,0,"Region ID");
        sheet->writeStr(0,1,"Region Name");
        sheet->writeStr(0,2,"Region pixels");
        sheet->writeStr(0,3,"Region area");
        sheet->writeStr(0,4,"Area unit");
        sheet->writeStr(0,5,"Object count");
        sheet->writeStr(0,6,"Object pixels");
        sheet->writeStr(0,7,"Object area");
        sheet->writeStr(0,8,"Area unit");
        sheet->writeStr(0,9,"Load");

        //        slice->
        for (AtlasLabel* al : atlasLabels->atlases) {
            {
                sheet->writeNum(y,0,al->index);
                sheet->writeStr(y,1,al->name);
                sheet->writeNum(y,2,al->sliceArea[i]);
                //            sheet->writeNum(y,3,al->areaScaled);
                sheet->writeStr(y,4,units);
                if (Data::data.m_hasAreaSplitting)
                    sheet->writeStr(y,5,"N/A");
                else
                    sheet->writeNum(y,5,al->count);




                sheet->writeNum(y,6,al->extra2.x());
                sheet->writeNum(y,7,al->extra2.y());
                sheet->writeStr(y,8,units);
                sheet->writeNum(y,9,0);
                 if (al->area!=0)
                    sheet->writeNum(y,9,al->extra2.x()/al->area);
                y++;
            }

        }

    }
    book->Save(filename);

}

void Reports::CreateSliceReports(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items, AtlasLabels* labels, QString units, QString bType)
{
    LBook* book = LBookFactory::Create(bType);
    LSheet* summary = book->GetSheet(0);

    float sumPixel=0;
    float sumArea = 0;
    float totalSumPixel=0;
    float totalSumArea = 0;


    summary->writeStr(0,1,"Object pixels");
    summary->writeStr(0,2,"Object area");
    summary->writeStr(0,3,"units");
    summary->writeStr(0,4,"Center X");
    summary->writeStr(0,5,"Center Y");
    summary->writeStr(0,6,"Region ID");
    summary->writeStr(0,7,"Region Name");
    //summary->writeStr(0,8,"Slice");
    int yy=1;
    float sumTotalAtlasArea=0;
    Counter cnt(items.count(),"");


    summary->setName("All");

    for (int i=0;i<items.count();i++) {


        //qDebug() << "  Generating sliced report : " << items[i]->m_reportName;
        LSheet* sheet = book->CreateSheet(items[i]->m_reportName);
        // Header
        cnt.Tick();
        Data::data.m_globalMessage = "Creating individual section reports: " + cnt.getPercentFormatted();
/*        sheet->writeStr(0,0,"Total pixel area");
        sheet->writeStr(0,1,"Total object area");
        sheet->writeStr(0,2,"Total atlas area");*/
        sheet->writeStr(0,0,"Object pixels");
        sheet->writeStr(0,1,"Object area");
        sheet->writeStr(0,2,"units");
        sheet->writeStr(0,3,"Center X");
        sheet->writeStr(0,4,"Center Y");
        sheet->writeStr(0,5,"Region ID");
  //      sheet->writeStr(2,6,"Region Area");
        sheet->writeStr(0,6,"Region Name");
        sheet->writeStr(0,7,"Cutoff reached");
  // max object size cut off: objects greater in size were divided into max size or smaller. This feature should be removed.
        int y = 1;
   //     qDebug() << "  Writing areas : " << processes[i]->m_areas.count();
        for (Area& a: processes[i]->m_areas) {
            sheet->writeNum(y,0,a.m_pixelArea);
            sheet->writeNum(y,1,a.m_area);
            sheet->writeStr(y,2,units);

            sumPixel+=a.m_pixelArea;
            sumArea+=a.m_area;
            totalSumPixel+=a.m_pixelArea;
            totalSumArea+=a.m_area;

            sheet->writeNum(y,3,a.m_center.x());
            sheet->writeNum(y,4,a.m_center.y());
            if (a.m_areaHasReachedCutoff)
                sheet->writeNum(y,8,1);

            if (a.atlasLabel!=nullptr) {
                sheet->writeNum(y,5,a.atlasLabel->index);
                //sheet->writeNum(y,6,a.atlasLabel->area);
                sheet->writeStr(y,6,a.atlasLabel->name);
            }
            y++;


            summary->writeStr(yy,0,items[i]->m_reportName);
            summary->writeNum(yy,1,a.m_pixelArea);
            summary->writeNum(yy,2,a.m_area);
            summary->writeStr(yy,3,units);
            summary->writeNum(yy,4,a.m_center.x());
            summary->writeNum(yy,5,a.m_center.y());
//            summary->writeStr(yy,8,items[i]->m_id);

            if (a.atlasLabel!=nullptr) {
                summary->writeNum(yy,6,a.atlasLabel->index);
              //  if (a.atlasLabel->area!=a.atlasLabel->area)
              //  qDebug() << a.atlasLabel->area;
//                summary->writeNum(yy,6,a.atlasLabel->area);
                summary->writeStr(yy,7,a.atlasLabel->name);
            }

            yy++;


        }

        sumArea=0;
        sumPixel=0;
        sumTotalAtlasArea+=items[i]->m_atlasAreaScaled;

    }
    Data::data.m_globalMessage = "Saving section reports... (this might take some time)";

    book->Save(filename);
    Data::data.m_globalMessage = "Done saving.";

    //qDebug() << "SAVED";
}

void Reports::CreateCustomRegions(QString filename, QVector<NutilProcess *> processes, QVector<ProcessItem *> items, AtlasLabels *labels, QString bType)
{
    LMessage::lMessage.Log("Generating summary report");
    LBook* book = LBookFactory::Create(bType);
    LSheet* summary = book->GetSheet(0);

    float sumPixel=0;
    float sumArea = 0;
    float totalSumPixel=0;
    float totalSumArea = 0;

    Counter cnt(items.count()*m_reports.count(),"");


    for (int i=0;i<items.count();i++) {
//        qDebug() << "  Generating section report : " << items[i]->m_reportName;



        LSheet* sheet = book->CreateSheet("sheet"+QString::number(i)+"_"+items[i]->m_reportName);
//        LSheet* sheet = book->CreateSheet("sheet"+QString::number(i));
        sheet->writeStr(0,0, "Region name");
        sheet->writeStr(0,1, "Region pixel area");
        sheet->writeStr(0,2, "Region area");
        sheet->writeStr(0,3, "Area unit");
        sheet->writeStr(0,4, "Object count");
        sheet->writeStr(0,5, "Object pixel");
        sheet->writeStr(0,6, "Object area");
        sheet->writeStr(0,7, "Object area unit");
        sheet->writeStr(0,8, "Load");
//        sheet->writeStr(0,9, "Load");
        int j=1;
        for (Report& r : m_reports) {

            cnt.Tick();
            Data::data.m_globalMessage = "Creating summary reports: " + cnt.getPercentFormatted();
            float regionPixelArea=0;
            float regionArea=0;
            float totalPixelArea=0;//items[i]->m_pixelAreaScale;
//            float totalArea=0;
            float totalArea=0;//items[i]->m_atlasAreaScaled;
            int cnt=0;

//            QVector<AtlasLabel*> lbls;
            for (Area& a: processes[i]->m_areas) {

     //           totalPixelArea+=a.m_pixelArea;
       //         totalArea+=a.m_mrea;
//                regionPixelArea+=a.m_pixelArea;
  //              regionArea+=a.m_area;




                if (a.atlasLabel!=nullptr) {


                    if (r.m_IDs.contains(a.atlasLabel->index)) {
                        cnt++;
                        totalPixelArea+=a.m_pixelArea;
                        totalArea+=a.m_area;
                    }
                }

            }
  //          qDebug() << "xxx";
            // Now total area
            for (AtlasLabel* al : labels->atlases) {
                for (long ID: r.m_IDs)
                    if (ID==al->index) {

                    regionPixelArea +=al->sliceArea[i];
                    regionArea +=al->sliceAreaScaled[i];
                    }
            }
//            qDebug() << "TOTAL AREA: " <<" WITH : " << totalArea;



 /*           sheet->writeStr(0,0, "Region name");
            sheet->writeStr(0,1, "Region pixel area");
            sheet->writeStr(0,2, "Region area");
            sheet->writeStr(0,3, "Area unit");
            sheet->writeStr(0,4, "Object count");
            sheet->writeStr(0,5, "Object pixel");
            sheet->writeStr(0,6, "Object area");
            sheet->writeStr(0,7, "Object area unit");
            sheet->writeStr(0,8, "Load");
*/
    //        sheet->writeStr(0,9, "Load");


            sheet->writeStr(j,0, r.m_filename);
            sheet->writeNum(j,1, regionPixelArea);
            sheet->writeNum(j,2, regionArea);
            sheet->writeStr(j,3, r.m_unit);
            if (Data::data.m_hasAreaSplitting)
                sheet->writeStr(j,4, "N/A");
            else
                sheet->writeNum(j,4, cnt);
            sheet->writeNum(j,5, totalPixelArea);
            sheet->writeNum(j,6, totalArea);
            sheet->writeStr(j,7, r.m_unit);


            if (regionPixelArea>=1)
                sheet->writeNum(j,8, totalPixelArea/(float)regionPixelArea);
            else
                sheet->writeNum(j,8, 0);


//            if (regionArea>=1)
  //              sheet->writeNum(j,9, totalArea/(float)regionArea);

            /*if (regionPixelArea>=1)
                sheet->writeNum(j,8, totalPixelArea);
            if (r.m_regionArea>=1)
                sheet->writeNum(j,9, totalArea);
*/


            j++;
        }

    }


        // Header
/*        sheet->writeStr(0,0,"Total pixel area");
        sheet->writeStr(0,1,"Total object area");
        sheet->writeStr(0,2,"Total atlas area");
        sheet->writeStr(2,0,"Object pixels");
        sheet->writeStr(2,1,"Object area");
        sheet->writeStr(2,2,"units");
        sheet->writeStr(2,3,"Center X");
        sheet->writeStr(2,4,"Center Y");
        sheet->writeStr(2,5,"Region ID");
  //      sheet->writeStr(2,6,"Region Area");
        sheet->writeStr(2,6,"Region Name");
        sheet->writeStr(2,7,"Cutoff reached");
        int y = 3;
   //     qDebug() << "  Writing areas : " << processes[i]->m_areas.count();
        for (Area& a: processes[i]->m_areas) {
            sheet->writeNum(y,0,a.m_pixelArea);
            sheet->writeNum(y,1,a.m_area);

            sumPixel+=a.m_pixelArea;
            sumArea+=a.m_area;
            totalSumPixel+=a.m_pixelArea;
            totalSumArea+=a.m_area;

            sheet->writeNum(y,3,a.m_center.x());
            sheet->writeNum(y,4,a.m_center.y());
            if (a.m_areaHasReachedCutoff)
                sheet->writeNum(y,8,1);

            if (a.atlasLabel!=nullptr) {
                sheet->writeNum(y,5,a.atlasLabel->index);
                //sheet->writeNum(y,6,a.atlasLabel->area);
                sheet->writeStr(y,6,a.atlasLabel->name);
            }
            y++;


            summary->writeNum(yy,0,a.m_pixelArea);
            summary->writeNum(yy,1,a.m_area);
            summary->writeNum(yy,3,a.m_center.x());
            summary->writeNum(yy,4,a.m_center.y());

            if (a.atlasLabel!=nullptr) {
                summary->writeNum(yy,5,a.atlasLabel->index);
              //  if (a.atlasLabel->area!=a.atlasLabel->area)
              //  qDebug() << a.atlasLabel->area;
//                summary->writeNum(yy,6,a.atlasLabel->area);
                summary->writeStr(yy,6,a.atlasLabel->name);
            }

            yy++;


        }

        sheet->writeNum(1,0,sumPixel);
        sheet->writeNum(1,1,sumArea);
        sheet->writeNum(1,2,items[i]->m_atlasAreaScaled);
        sumArea=0;
        sumPixel=0;
        sumTotalAtlasArea+=items[i]->m_atlasAreaScaled;

        */

    book->Save(filename);
    if (QFile::exists(filename+".csv"))
        QFile::remove(filename+".csv");
//    filename.csv

}

void Reports::Create3DSummary(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items, float xyzSize)
{

    QString o;
    o += "SCALE 3\n";



    for (int i=0;i<m_reports.count();i++) {
        QColor c = m_reports[i].m_color;
        QString color = QString::number((float)c.red()/255.0) + " " + QString::number((float)c.green()/255.0) + " " + QString::number((float)c.blue()/255.0) +" 1";
        o +="RGBA " + color +" \n";
        //qDebug() << m_reports[i].m_filename << " " << m_reports[i].m_areasOfInterest.count();
        int count=0;
        for (Area* a: m_reports[i].m_areasOfInterest)
            {


            for (int k=0;k<a->m_points.count();k+=(a->m_points.count()/xyzSize)+1) {
                QPointF& p =a->m_points[k];
                //QVector3D v(1,p.x()/a->m_width,p.y()/a->m_height);
                QVector3D v(p.x()/a->m_width,p.y()/a->m_height,1);
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


void Reports::Create3DSummaryJson(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items, float xyzSize)
{

    QString o;

    o+="[\n";
    int cnt=0;

//    for (int i=0;i<m_reports.count();i++)
  //      k+=m_reports[i].m_areasOfInterest.count();

    for (Report& r: m_reports)
            r.FindAreasOfInterest(processes);

    Counter cntr(m_reports.count(),"");
    int tcount = 0;
    for (int i=0;i<m_reports.count();i++) {

        cntr.Tick();
        Data::data.m_globalMessage = "Creating 3D point clouds : " + cntr.getPercentFormatted();
        QColor c = m_reports[i].m_color;
        QString color = QString::number((float)c.red()/255.0) + " " + QString::number((float)c.green()/255.0) + " " + QString::number((float)c.blue()/255.0) +" 1";
        //o +="RGBA " + color +" \n";
        //qDebug() << m_reports[i].m_filename << " " << m_reports[i].m_areasOfInterest.count();

        int count = 0;//m_reports[i].m_areasOfInterest.count();
        for (int j=0;j<m_reports[i].m_areasOfInterest.count();j++)
            count+=m_reports[i].m_areasOfInterest[j]->m_points.count();
        if (cnt!=0) o+=",\n";
        o+="{\"idx\":"+QString::number(cnt)+",\"count\":"+QString::number((int)(count/xyzSize))+",";
        o+="\"r\":" + QString::number(c.red()) + ",\"g\":" + QString::number(c.green()) + ",\"b\":" + QString::number(c.blue()) + ",\"name\":\""+ m_reports[i].m_filename+ "\",";
        o+="\"triplets\":[";
        int cnt2=0;
        cnt++;

        for (Area* a: m_reports[i].m_areasOfInterest) {


//            if (cnt!=0) o+=",";

            for (float k=0;k<a->m_points.count();k+=xyzSize) { //(a->m_points.count()/xyzSize)+1) {
//                for (int k=0;k<a->m_points.count();k+=1) { //(a->m_points.count()/xyzSize)+1) {
                tcount++;
                QPointF& p =a->m_points[(int)k];
                //QVector3D v(1,p.x()/a->m_width,p.y()/a->m_height);
                QVector3D v(p.x()/a->m_width,p.y()/a->m_height,1);
                v=v*a->m_mat;



                if (cnt2!=0) o+=",\n";
//                o+="\"triplets\":[" +QString::number(v.x())+ ","+QString::number(v.y())+","+QString::number(v.z())+"]}";
                o+=QString::number(v.x())+ ","+QString::number(v.y())+","+QString::number(v.z());


                cnt2++;
             }


        }
        o+="]}";

    }

    o+="\n]\n";
    QFile file (filename);
    file.open(QFile::Text | QFile::WriteOnly);
    QTextStream outstream(&file);
    outstream << o;
    file.close();
    LMessage::lMessage.Message("****** Count of pixels " + QString::number(tcount));
}

void Reports::CreateNifti(QString filename, QVector<NutilProcess *> processes, QVector<ProcessItem *> items, int size)
{
    Nifti n;
    n.Create(QVector3D(size,size,size),Nifti::DataType::DT_RGB, 24);
    n.rawData.fill(0);
    LMessage::lMessage.Log("Creating nifti ..");

    int k=0;




    Counter cnt(m_reports.count(),"");
    for (int i=0;i<m_reports.count();i++) {
        QColor c = m_reports[i].m_color;
        //qDebug() << c.red() << ", " << c.green() << ", " << c.blue() << "  : " << m_reports[i].m_areasOfInterest.count();
  //      c= QColor(Qt::white);
        cnt.Tick();
        Data::data.m_globalMessage="Generating nifti file : " + cnt.getPercentFormatted();
        for (Area* a: m_reports[i].m_areasOfInterest) {

            //c.setRed(rand()%255);
            //c.setBlue(rand()%255);
            //qDebug() << a->m_points.count();
            for (QPointF& p: a->m_points) {
//                QPointF pp=a->m_center;

                QVector3D v(p.x()/a->m_width,p.y()/a->m_height,1);
                v=v*a->m_mat;
//                v=v/1;

                v.setX(v.x()/512*n.size.x() );
                v.setY(v.y()/512*n.size.y());
                v.setZ(v.z()/512*n.size.z());

//                               if (rand()%100==0)
  //                                 qDebug() << v;

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
    qDebug() << "done.";
}


void Reports::Create3DSliceJson(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items, float xyzSize)
{


//    for (int i=0;i<m_reports.count();i++)
  //      k+=m_reports[i].m_areasOfInterest.count();
    for (Report& r: m_reports)
            r.FindAreasOfInterest(processes);


    int tcount = 0;

    Counter cntr(m_reports.count()*items.count(),"");
    for (int itm=0;itm<items.count();itm++) {


        QString o;

        o+="[\n";
        int cnt=0;
        int k=0;


    for (int i=0;i<m_reports.count();i++) {

        cntr.Tick();
        Data::data.m_globalMessage = "Creating 3D point clouds (slices) : " + cntr.getPercentFormatted();
        QColor c = m_reports[i].m_color;
        QString color = QString::number((float)c.red()/255.0) + " " + QString::number((float)c.green()/255.0) + " " + QString::number((float)c.blue()/255.0) +" 1";
        //o +="RGBA " + color +" \n";
        //qDebug() << m_reports[i].m_filename << " " << m_reports[i].m_areasOfInterest.count();

        int count = 0;//m_reports[i].m_areasOfInterest.count();
        for (int j=0;j<m_reports[i].m_areasOfInterest.count();j++)
            count+=m_reports[i].m_areasOfInterest[j]->m_points.count();
        if (cnt!=0) o+=",\n";
        int cnt2=0;
        cnt++;


        QString data = "";
        for (Area* a: m_reports[i].m_areasOfInterest)
        {

            bool ok = false;
            for (int ka = 0;ka<processes[itm]->m_areas.count();ka++) {
                if (a==&processes[itm]->m_areas[ka])
                    ok = true;
            }
            if (!ok)
                continue;


//            qDebug() << "FOUND";
/*            if (processes[itm]->m_areas.contains(*a)) {
                qDebug() << "FOUND " << i;
            }
*/

//            if (cnt!=0) o+=",";

            for (float k=0;k<a->m_points.count();k+=xyzSize) { //(a->m_points.count()/xyzSize)+1) {
//                for (int k=0;k<a->m_points.count();k+=1) { //(a->m_points.count()/xyzSize)+1) {
                tcount++;
                QPointF& p =a->m_points[k];
                //QVector3D v(1,p.x()/a->m_width,p.y()/a->m_height);
                QVector3D v(p.x()/a->m_width,p.y()/a->m_height,1);
                v=v*a->m_mat;

                if (cnt2!=0) data+=",\n";
//                o+="\"triplets\":[" +QString::number(v.x())+ ","+QString::number(v.y())+","+QString::number(v.z())+"]}";
                data+=QString::number(v.x())+ ","+QString::number(v.y())+","+QString::number(v.z());


                cnt2++;
             }


        }
        o+="{\"idx\":"+QString::number(cnt)+",\"count\":"+QString::number(cnt2)+",";
        o+="\"r\":" + QString::number(c.red()) + ",\"g\":" + QString::number(c.green()) + ",\"b\":" + QString::number(c.blue()) + ",\"name\":\""+ m_reports[i].m_filename+"\",";
        o+="\"triplets\":[";

        o+=data;

        o+="]}";

    }
    o+="\n]\n";
    QFile file (filename+items[itm]->m_id+".json");
    file.open(QFile::Text | QFile::WriteOnly);
    QTextStream outstream(&file);
    outstream << o;
    file.close();

    }
    LMessage::lMessage.Message("****** Count of pixels " + QString::number(tcount));
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
            AtlasLabel* al = atlasLabels->get(i,false);
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

void Reports::CreateBook(QString filename, QString type)
{
     m_book = LBookFactory::Create(type);

    //m_book = xlCreateXMLBook();// for xlsx
    m_filename = filename;


}

void Reports::CreateSheets(QVector<NutilProcess*>& processes,AtlasLabels* atlasLabels, QString units, bool hasAreaSplitting)
{
    if (!m_book)
        return;

    LMessage::lMessage.Log("Finding areas of interest");
    Data::data.m_globalMessage = "Creating sheets 1/3";

    for (Report& r: m_reports)
            r.FindAreasOfInterest(processes);
    Data::data.m_globalMessage = "Creating sheets 2/3";

    LMessage::lMessage.Log("Creating summary ");
    CreateSummary(atlasLabels);

    LMessage::lMessage.Log("Generating sheets ");
    Data::data.m_globalMessage = "Creating sheets 3/3";

    if (!hasAreaSplitting)
    for (Report& r: m_reports) {
        //qDebug() << r.m_filename;
        r.GenerateSheet(m_book, units);
        //qDebug() << "Done";
    }
    LMessage::lMessage.Log("Saving report to " + m_filename);
    m_book->Save(m_filename);

    LMessage::lMessage.Log("Releasing " + m_filename);
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


