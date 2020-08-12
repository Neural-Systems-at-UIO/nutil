#include "nlimagetiff.h"

/*void NLImageTiff::Load(QString filename)
{
    if (!m_image.Open(inFile)) {
        LMessage::lMessage.Error("Could not open tiff file + '"+filename + "' ! Please check the filename and try again.");
        return;
    }
}

NLImageTiff::NLImageTiff()
{
    m_image.Close();
}
*/

void NLIQImage::FractalAnalyze()
{
    LGraph g;
    g.Initialize(100,20,m_image.width()/8);
    float prev = 1;
    for (int i=m_image.width()/4;i>2;i--) {
        QPointF p1 = BoxCount(i,QColor(0,0,0));
        qDebug() << "Count : " << p1.x();
        g.set(i,p1.x());
        //g.set(i,prev/p1.x());
        prev = p1.x();


        }
    g.SaveText("plot1.txt");
}

QPointF NLIQImage::BoxCount(int boxSize, QColor searchColor)
{
    int sx = m_image.width()/boxSize;
    int sy = m_image.height()/boxSize;
    int count = 0;


//    qDebug() << sx << sy << m_image.width();

    for (int j=0;j<sy;j++)
        for (int i=0;i<sx;i++) {

            bool found = false;
            for (int y=0;y<boxSize;y++)
                for (int x=0;x<boxSize;x++) {
                    int px = i*boxSize + x;
                    int py = j*boxSize + y;
                    QRgb col = m_image.pixel(px,py);
  //                  if (rand()%100>98)
    //                    qDebug() << col << searchColor.rgb();
                    if (col==searchColor.rgb())
                        found = true;
                }

            if (found)
                count++;


        }

    return QPointF(count,0);
}
