#include "limage.h"
#include <QPainter>
#include <QPen>
#include "source/data.h"



NLIParent* NLImage::image()
{
    return m_image;
}

void NLImage::Load(QString filename)
{
//    QImage test(filename);
//    qDebug() << filename << test.format();
//    test.setPixel(0,0,QColor(1,0,0).rgb());
  //  test.setPixelColor(0,0,QColor(1,0,0));
    //exit(1);

    //filename = "c:\\data\\test.png";
    if (!QFile::exists(filename)) {
        LMessage::lMessage.Error("Could not find file: " +filename);
    }

    if (filename.endsWith(".tif")) {
        qDebug() << "NOT IMPLEMENTED NLIMAGETIFF";
        m_type = TIFF;
        exit(1);
    }
    else m_type = OTHER;

    m_image = createImage(1,1);
    m_index = createImage(1,1);



    if (!m_image->Load(filename) || m_image->width()==0)
    {
        qDebug() << "Error opening file: " + filename;
        LMessage::lMessage.Error("Error opening file: " + filename);
    }
    if (m_image->width()==0) {
        qDebug() << "Error opening file (size 0): " + filename;
        LMessage::lMessage.Error("Error opening file (size 0): " + filename);
    }


}

void NLImage::ApplyMask(QString maskFile, QVector3D useColor, QColor background)
{
    QImage mask;
    mask.load(maskFile);


    QColor testColor(1,1,1);
    if (background==testColor)
        testColor = QColor(0,0,0);
    for (int j=0;j<m_image->height();j++)
        for (int i=0;i<m_image->width();i++) {
            //QVector3D imgCol = Util::fromColor(QColor(m_image->getPixel(i,j)));
            float x = (i/(float)m_image->width())*(float)mask.width();
            float y = (j/(float)m_image->height())*(float)mask.height();
            if (x<mask.width() && y<mask.height()) {
                QVector3D maskCol = Util::fromColor(QColor(mask.pixel(x,y)));
                //qDebug() << maskCol << useColor;

                if (!Util::QVector3DIsClose(maskCol,useColor,QVector3D(1,1,1)*2))
                {
                    m_image->setPixel(i,j,testColor.rgba());
                    //                qDebug() << i<< j;
                }
            }
        }


}


void NLImage::Release()
{
    //m_image = QImage(1,1,QImage::Format_RGB32);
    /*if (m_testImage!=nullptr)
        delete m_testImage;

    m_testImage = nullptr;
*/
   // m_index = QImage(1,1,QImage::Format_RGB32);

    if (m_index)
    m_index->Release();
    if (m_image)
    m_image->Release();


}

void NLImage::FindAreas(QColor testColor, QVector3D colorWidth, Counter* counter, QVector<Area>* m_areas,int pixelCutoff, int pMax)
{

    if (m_index!=nullptr)
        delete m_index;

    m_index = createImage(m_image->width(), m_image->height());


    bool isBfs = true;
    if (Data::data.m_settings!=nullptr)
        isBfs = Data::data.m_settings->getString("fill_method")=="bfs";
    m_index->fill(unset);
    for (int i=0;i<m_index->width();i++)
        for (int j=0;j<m_index->height();j++)
            m_index->setPixel(i,j, unset.rgba());

    counter->Init(m_image->width()*m_image->height());
//    qDebug() << "A";
    for (int i=0;i<m_image->width();i++)
        for (int j=0;j<m_image->height();j++) {
            counter->Tick();
            if (Data::data.abort)
                return;

            // Check if unset



            if (QColor(m_index->getPixel(i,j)) == unset) {
                QColor pix = QColor(m_image->getPixel(i,j));
  //              if (pix.red()!=0)
//                    qDebug() << pix.red();

                bool found = Util::QVector3DIsClose( pix, testColor, colorWidth );

//                if (pix == testColor) {
                if (found) {
                    Area area;
                    if (isBfs)
                        FillAreaBFS(area, i,j, testColor, colorWidth, pMax);
                    else
                        FillAreaDFS(area, i,j, testColor, colorWidth, pMax);

                    area.CalculateStatistics();

                    if (area.m_pixelArea>=pixelCutoff) {
                        m_areas->append(area);
//                        qDebug() << "Area found" << m_areas->size() << " ," << area.m_pixelArea;
                    }

                }
            }
        }
  //  qDebug() << "B";

    qSort(m_areas->begin(), m_areas->end());
}


void NLImage::FillAreaDFS(Area &area, const int i, const int j, const QColor& testColor, const QVector3D& spread,int pMax)
{
    if (i>m_index->width()-2 || i<=0 || j>m_index->height()-2 || j<=0) return;
    if (area.m_points.size()>=pMax) { area.m_areaHasReachedCutoff=true;return;}
    // First test if this is unset
    if (QColor(m_index->getPixel(i,j)) == unset) {
        m_index->setPixel(i,j,set.rgba());
        //qDebug() << i << ", " << j << " :" << m_index->width() << ", " << m_index->height() ;
//        if (QColor(m_image->getPixel(i,j)) == testColor) {
           if (Util::QVector3DIsClose(QColor(m_image->getPixel(i,j)),testColor, spread)) {
            area.m_points.append(QPoint(i,j));
            /*if (area.m_points.count()>3000)
            qDebug() << area.m_points.count() << " :" << i << ", " << j << " :" << m_index->width() << ", " << m_index->height();
            if (area.m_points.count()>3000)
                return;
*/
            if (i+1<m_index->width()-1)
                FillAreaDFS(area, i+1, j, testColor, spread, pMax);
            if (i-1>=0)
               FillAreaDFS(area, i-1, j, testColor,spread, pMax);
            if (j+1<m_index->height()-1)
                FillAreaDFS(area, i, j+1, testColor, spread,pMax);
            if (j-1>=0)
                FillAreaDFS(area, i, j-1, testColor, spread,pMax);
        }
    }

}

void NLImage::FillAreaBFS(Area &area, const int i, const int j, const QColor &testColor, const QVector3D& spread,int pMax)
{
    if (i>m_index->width()-2 || i<=0 || j>m_index->height()-2 || j<=0) return;
    if (area.m_points.size()>=pMax) { area.m_areaHasReachedCutoff=true;return;}
    // First test if this is unset


    QVector<QPoint> queue;
    queue.append(QPoint(i,j));

    while (queue.count()!=0) {
        QPoint q = queue.last();
        queue.removeLast();
        if (QColor(m_index->getPixel(q.x(),q.y())) == unset) {
            m_index->setPixel(q.x(),q.y(),set.rgba());
            //qDebug() << i << ", " << j << " :" << m_index->width() << ", " << m_index->height() ;
//            if (QColor(m_image->getPixel(q.x(),q.y())) == testColor) {
            if (Util::QVector3DIsClose(QColor(m_image->getPixel(q.x(),q.y())),testColor, spread)) {

                area.m_points.append(q);
                /*if (area.m_points.count()>3000)
                qDebug() << area.m_points.count() << " :" << i << ", " << j << " :" << m_index->width() << ", " << m_index->height();
                if (area.m_points.count()>3000)
                    return;
    */
                if (q.x()+1<m_index->width()-1)
                    queue.append(QPoint(q.x()+1,q.y()));
                if (q.x()-1>=0)
                   queue.append(QPoint(q.x()-1,q.y()));
                if (q.y()+1<m_index->height()-1)
                   queue.append(QPoint(q.x(),q.y()+1));
                if (q.y()-1>=0)
                    queue.append(QPoint(q.x(),q.y()-1));
            }
        }
//        qDebug() << "cnt:"  << queue.count();

    }

//    qDebug() << area.m_points.count();
}

void NLImage::CountAtlasArea(Flat2D &refImage, AtlasLabels &labels, float scale, float areaScale, int slice, QString maskFile, QVector3D maskColor)
{
    m_totalPixelArea = 0;
    bool useMask = false;
    QImage maskImage;
    if (QFile::exists(maskFile)) {
        maskImage.load(maskFile);
        useMask=true;
    }
    for (int i=0;i<refImage.width();i++)
        for (int j=0;j<refImage.height();j++) {
            bool canTest=true;
            if (useMask) {
                int ix = (i/(float)refImage.width())*(float)maskImage.width();
                int iy = (j/(float)refImage.height())*(float)maskImage.height();
                QVector3D c = Util::fromColor(maskImage.pixelColor(ix,iy));
                if (!Util::QVector3DIsClose(c,maskColor,QVector3D(1,1,1))) {
                    canTest=false;
                }

            }

            if (canTest && refImage.pixel(i,j)!=0)

//            if (refImage.pixel(i,j)!=0)
                {
                m_totalPixelArea++;

                AtlasLabel* al =labels.get(refImage.pixel(i,j), refImage.m_newFormat);

              //  AtlasLabel* al =labels.get(refImage.pixel(i,j));
                if (al!=nullptr) {
                    al->area+=scale;
                    al->areaScaled +=scale*areaScale;

                    al->sliceArea[slice]+=scale;
                    al->sliceAreaScaled[slice]+=scale*areaScale;


                   // qDebug() << QString::number(scale*areaScale);
                }
            }
        }


}

/*void NLImage::GenerateAreaReport(QString outExcelFile,Counter *counter)
{
//    for (Area a : m_areas)
  //      qDebug() <<" Area size: " << a.m_pixelArea << " center pixel " << a.m_center;

    Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
    if (counter!=nullptr)
        counter->Init(m_areas.count());
    if(book)
    {
        Sheet* sheet = book->addSheet(L"Report");
        if(sheet)
        {
            sheet->writeStr(1,0, L"Pixel count");
            sheet->writeStr(1,1, L"Area (not yet defined)");

            sheet->writeStr(1, 2, L"object_area_units");
            sheet->writeStr(1, 3, L"Center X");
            sheet->writeStr(1, 4, L"Center Y");
            for (int i=0;i<m_areas.count();i++) {
                sheet->writeNum(2+i,0, m_areas[i].m_pixelArea);
                sheet->writeNum(2+i,3, m_areas[i].m_center.x());
                sheet->writeNum(2+i,4, m_areas[i].m_center.y());
                if (counter)
                    counter->Tick();
            }
        }
        wchar_t* arr = new wchar_t[outExcelFile.size()+1];
        outExcelFile.toWCharArray(arr);
        arr[outExcelFile.size()]=0;

        book->save(arr);
        delete[] arr;
        book->release();
    }

}
*/
void NLImage::SaveAreasImage(QString filename,Counter *counter, QVector<Area>* m_areas,QVector<QVector<long>> reportList, QVector<QColor> cols)
{
    QRgb off = QColor(255,255,255,255).rgba();

    if (m_index!=nullptr)
        delete m_index;
    m_index = createImage(scale*m_image->width(), scale*m_image->height());//QImage(QSize(scale*m_image->width(), scale*m_image->height()),QImage::Format_RGB32);


    for (int i=0;i<m_index->width();i++)
        for (int j=0;j<m_index->height();j++)
            m_index->setPixel(i,j, off);


    if (counter!=nullptr)
        counter->Init(m_areas->count());



    for (Area& a: *m_areas) {
        QRgb on = QColor(200,0,0,255).rgba();
        if (a.atlasLabel != nullptr) {
//            if (rand()%100>90)
  //              qDebug() << a.atlasLabel->color;
            //on = QColor(a.atlasLabel->color.x(), a.atlasLabel->color.y(), a.atlasLabel->color.z(),255).rgba();
        }

        if (counter)
            counter->Tick();
        for (QPointF qp: a.m_points) {
            for (int i=0;i<1;i++)
            for (int j=0;j<1;j++)
                m_index->setPixel(scale*qp.x()+i, scale*qp.y()+j, on);
        }

       // if (a.atlasLabel!=nullptr)
//            painter.drawText(a.m_center*scale,  QString::number(a.atlasLabel->index));
    }

    // Rescale background image
    if (m_testImage!=nullptr) {

        for (int i=0;i<m_index->width();i++)
            for (int j=0;j<m_index->height();j++) {
                QPoint p((float)i/(float)m_index->width()*(float)m_testImage->width(),(float)j/(float)m_index->height()*(float)m_testImage->height());
                if (p.x()<0) p.setX(0);
                if (p.y()<0) p.setY(0);
                if (p.x()>m_testImage->width()-1) p.setX(m_testImage->width()-1);
                if (p.y()>m_testImage->height()-1) p.setY(m_testImage->height()-1);
                QColor c = QColor(m_testImage->pixel(p.x(), p.y()));
                QColor c2 =QColor(m_index->getPixel(i,j));
                if (c2.red()>=250 && c2.green()>=250 && c2.blue()>250 ) {
                    c.setRed(min((int)(c.red()*0.7 + c2.red()*0),255));
                    c.setGreen(min((int)(c.green()*0.7 + c2.green()*0),255));
                    c.setBlue(min((int)(c.blue()*0.7 + c2.blue()*0),255));
                    m_index->setPixel(i,j,c.rgba());
                }

            }



        delete m_testImage;
    }

    // Then test reports

    //QColor cols[4] = { QColor(255,0,0), QColor(0,255,0), QColor(0,0,255), QColor(255,0,255) };
    int idx=0;
    for (QVector<long>& lst : reportList) {
        QColor c = cols[idx];
        for (long i : lst) {
            for (Area& a: *m_areas)
                if (a.atlasLabel !=nullptr )
                    if (a.atlasLabel->index == i) {
                        for (QPointF& q: a.m_points)
                            for (int i=0;i<scale;i++)
                            for (int j=0;j<scale;j++)
                              m_index->setPixel(scale*q.x()+i, scale*q.y()+j, c.rgba() );
                    }


        }
        idx++;

    }

    NLIQImage* qi = dynamic_cast<NLIQImage*>(m_index);
    if (qi!=nullptr && !Data::data.isConsole) {
        QPainter painter(&qi->m_image);
        QPen penHText(QColor("#001010"));//Here lines are also drawn using this color
        painter.setPen(penHText);
        QFont fnt = QFont("Times", 8, QFont::Normal);
        fnt.setStyleStrategy(QFont::NoAntialias);
        painter.setFont(fnt);
        for (Area& a: *m_areas) {
            if (a.atlasLabel!=nullptr)
                painter.drawText(a.m_center*scale,  QString::number(a.atlasLabel->index));
        }
    }
    m_index->Save(filename);

}

void NLImage::AnchorSingle(QString filenameStripped, QString atlasFile, QString labelFile, AtlasLabels& labels,Counter *counter, QVector<Area>* m_areas, float pixelAreaScale, int slice, QString maskFile, QVector3D maskColor)
{

    Flat2D refImage;
    refImage.Load(atlasFile);

    m_testImage = refImage.toImage(labels);

    float scale = m_image->width()*m_image->height()/ (float)(refImage.m_width*refImage.m_height);




//    pixelAreaScale = 1;

//    CountAtlasArea(refImage, labels, scale, pixelAreaScale);
    CountAtlasArea(refImage, labels, scale, pixelAreaScale,slice, maskFile, maskColor);
    m_totalPixelArea*=scale*pixelAreaScale;
//    qDebug() << pixelAreaScale;
//    qDebug() << scale;

    if (counter!=nullptr)
        counter->Init(m_areas->count());

    for (Area& a: *m_areas) {
        if (counter)
            counter->Tick();
        if (Data::data.abort)
            return;
        QPointF p = a.m_points[0];
        p.setX(p.x()/(float)m_image->width());
        p.setY(p.y()/(float)m_image->height());

        a.m_width = m_image->width();
        a.m_height = m_image->height();

        long index = refImage.pixel(p.x()*refImage.width(),p.y()*refImage.height() );
        //if (index!=0)
        {
            AtlasLabel* al = labels.get(index, refImage.m_newFormat);

            if (al!=nullptr) {
                a.atlasLabel = al;
            }
        }

        a.m_area = a.m_pixelArea*pixelAreaScale;
        a.m_areaScale = pixelAreaScale*scale;

//        else qDebug() << "Error in label file: could not find atlas color " << QColor(idxVal);

    }

}


void NLImage::AnchorSplitting(QString filenameStripped, QString atlasFile, QString labelFile, AtlasLabels& labels,Counter *counter, QVector<Area>* m_areas, float pixelAreaScale, int slice, QString maskFile, QVector3D maskColor)
{

    Flat2D refImage;
    refImage.Load(atlasFile);

    m_testImage = refImage.toImage(labels);
//    testImage->save(labelFile);
 //   delete testImage;


    // First, count all areas

    float scale = m_image->width()*m_image->height()/ (float)(refImage.m_width*refImage.m_height);


//    pixelAreaScale = 1;

//    CountAtlasArea(refImage, labels, scale, pixelAreaScale);
    CountAtlasArea(refImage, labels, scale, pixelAreaScale,slice, maskFile, maskColor);
    m_totalPixelArea*=scale*pixelAreaScale;
//    qDebug() << pixelAreaScale;
//    qDebug() << scale;

    if (counter!=nullptr)
        counter->Init(m_areas->count());


    QVector<Area> newAreas;
    for (Area& a: *m_areas) {
        if (counter)
            counter->Tick();
        if (Data::data.abort)
            return;

        QVector<Area> splitAreas;
//        QMap<AtlasLabel*, Area> splitAreas;


        for (QPointF& p: a.m_points) {


//        QPointF p = a.m_points[0];
            QPointF orgP = p;
            p.setX(p.x()/(float)m_image->width());
            p.setY(p.y()/(float)m_image->height());

            a.m_width = m_image->width();
            a.m_height = m_image->height();

            long index = refImage.pixel(p.x()*refImage.width(),p.y()*refImage.height() );
            //if (index!=0)
                AtlasLabel* al = labels.get(index, refImage.m_newFormat);

                if (al!=nullptr) {
                    //a.atlasLabel = al;
                    Area* currentArea = nullptr;
                    for (Area& ar : splitAreas) {
                        if (ar.atlasLabel == al)
                            currentArea = &ar;
                    }
                    if (currentArea == nullptr) {
                        splitAreas.append(Area());
                        currentArea = &splitAreas.last();
                        currentArea->atlasLabel = al;
                        currentArea->m_width = m_image->width();
                        currentArea->m_height = m_image->height();
                        currentArea->m_mat = a.m_mat;

                    }
                    currentArea->m_points.append(orgP);

                }



        }
//        qDebug() << "*********** SPLIT AREAS: " << splitAreas.count();
        for (Area& a: splitAreas) {
            a.CalculateStatistics();
            a.m_area += a.m_pixelArea*pixelAreaScale;
            a.m_areaScale = pixelAreaScale*scale;
        }

        newAreas.append(splitAreas);

//        else qDebug() << "Error in label file: could not find atlas color " << QColor(idxVal);

    }
    m_areas->clear();
    m_areas->append(newAreas);

}

