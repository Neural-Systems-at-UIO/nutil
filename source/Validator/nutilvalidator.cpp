#include "nutilvalidator.h"

NutilValidator::NutilValidator()
{

}

void NutilValidator::CreateSegmentedImage(QString fname, int w, int h, int blobs, QColor col)
{
    QImage img(w,h,QImage::Format_RGB32);
    img.fill(QColor(255,255,255,255));
    QVector<int> data;

    int N = sqrt(blobs);
    int dx = w/N;
    int dy = h/N;
    SimplexNoise sn;
    int cur = 0;
    data.resize(N*N);
    for (int y=0;y<N;y++)
        for (int x=0;x<N;x++) {
            int sr = dx/4;
            int px = (x+0.33)*(float)dx;
            int py = (y+0.33)*(float)dy;
            float d = (rand()%100)/400.0 + 0.2;
            for (int i=0;i<sr;i++)
                for (int j=0;j<sr;j++) {
//                    float p1 = (i+px)/(float)w*13.123;
  //                  float p2 = (j+py)/(float)h*11.123;
    //                if (sn.noise(p1,p2)>0.5)
                    if (sqrt(pow((i-sr/2)/(float)sr,2) + pow((j-sr/2)/(float)sr,2))<d) {
                       img.setPixelColor(i+px,j+py,col);
                       data[cur]++;
                    }
                }
            cur++;

        }

    img.save(fname + ".png");

    QString fn =  fname + ".txt";
    if (QFile::exists(fn))
        QFile::remove(fn);

    QFile file( fn );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        for (int i=0;i<data.size();i++)
            stream << "blob " << QString::number(i) << " " <<  QString::number(data[i]) <<endl;
    }
    file.close();

}
