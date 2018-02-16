#include "report.h"

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
        sheet->writeStr(0,11, "Object area ratio");

        int i = 1;
        for (Report& r : m_reports) {
            sheet->writeStr(i,0, r.m_filename);
            sheet->writeNum(i,3, r.m_regionPixelArea);
            sheet->writeNum(i,4, r.m_regionArea);
            sheet->writeNum(i,6, r.m_areasOfInterest.count());
            sheet->writeNum(i,8, r.m_totalPixelArea);
            sheet->writeNum(i,9, r.m_totalArea);
            sheet->writeNum(i,11, r.m_totalPixelArea/(float)r.m_regionPixelArea);



            i++;
        }

    }

}

void Reports::CreateSliceReports(QString filename , QVector<NutilProcess*> processes, QVector<ProcessItem*> items)
{
    LBook* book = new LBookXlnt();
    for (int i=0;i<items.count();i++) {
        LSheet* sheet = book->CreateSheet(items[i]->m_id);
        // Header
        sheet->writeStr(0,0,"Pixel area");
        sheet->writeStr(0,1,"Object area");
        sheet->writeStr(0,2,"units");
        sheet->writeStr(0,3,"Center X");
        sheet->writeStr(0,4,"Center Y");
        sheet->writeStr(0,5,"Region ID");
        sheet->writeStr(0,6,"Region Name");
        int y = 1;
        for (Area& a: processes[i]->m_areas) {
            sheet->writeNum(y,0,a.m_pixelArea);
            sheet->writeNum(y,1,a.m_area);
            sheet->writeNum(y,3,a.m_center.x());
            sheet->writeNum(y,4,a.m_center.y());
            if (a.atlasLabel!=nullptr) {
                sheet->writeNum(y,5,a.atlasLabel->index);
                sheet->writeStr(y,6,a.atlasLabel->name);
            }
            y++;
        }

    }
    book->Save(filename);
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
                     if (a.atlasLabel->index == i)

                        m_areasOfInterest.append(&a);
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
        }
        for (long i: r.m_IDs) {
            AtlasLabel* al = atlasLabels->get(i);
            if (al!=nullptr) {
                r.m_regionPixelArea += al->area;
                r.m_regionArea += al->areaScaled;
            }
        }

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


