#include "nifti.h"
#include <QDebug>
#include <cmath>
#include <qmath.h>

NiftiHeader Nifti::HeaderFromStream(QFile &f)
{
    QByteArray m_rawHeader;

    m_rawHeader = f.read(348);
    NiftiHeader* h = ((NiftiHeader*)m_rawHeader.data());
    NiftiHeader head; // copy
    return *h;
}

Nifti::DataType Nifti::getDataType(int type)
{
    type = abs (type);
    if (type == 1)
        return DataType::DT_BINARY;
    if (type == 2)
        return DataType::DT_UNSIGNED_CHAR;
    if (type == 4)
        return DataType::DT_SIGNED_SHORT;
    if (type == 8)
        return DataType::DT_SIGNED_INT;
    if (type == 16)
        return DataType::DT_FLOAT;
    if (type == 32)
        return DataType::DT_DOUBLE;
    if (type == 128)
        return DataType::DT_RGB;
    if (type == 512)
        return DataType::DT_UINT16;
    if (type == 768)
        return DataType::DT_UINT32;
    if (type == 1024)
        return DataType::DT_INT64;
    if (type == 1280)
        return DataType::DT_UINT64;
    if (type == 1536)
        return DataType::DT_FLOAT128;


    return DataType::DT_NONE;
}

int Nifti::setDataType(DataType t)
{
    int type=0;
    if (t == DataType::DT_BINARY)
        type = 1;

    if (t == DataType::DT_UNSIGNED_CHAR)
        type = 2;

    if (t == DataType::DT_SIGNED_SHORT)
        type = 4;

    if (t == DataType::DT_SIGNED_INT)
        type = 8;

    if (t == DataType::DT_FLOAT)
        type = 16;

    if (t == DataType::DT_DOUBLE)
        type = 32;

    if (t == DataType::DT_RGB)
        type = 128;

    if (t == DataType::DT_UINT16)
        type = 512;

    if (t == DataType::DT_UINT32)
        type = 768;

    if (t == DataType::DT_INT64)
        type = 1024;

    if (t == DataType::DT_UINT64)
        type = 1280;

    if (t == DataType::DT_FLOAT128)
        type = 1536;


    return type;
}



void Nifti::Normalize(float array[], int len)
{
    float minn = 1E30f, maxx = -1E30f;
    for (int i = 0; i < len; i++) {
        minn = std::min (array [i], minn);
        maxx = std::max (array [i], maxx);
    }
    for (int i = 0; i < len; i++)
        array [i] /= maxx * 255.0;


}

void Nifti::SetRGBPixel(const QVector3D &p, QColor color)
{
    if (BytesPerPixel!=3 || header.datatype!=128 ) {
        qDebug() << "Nifti: cannot use SetRGBPixel on non-rgb nifti file";
    }

    if (p.x()>=size.x() || p.x()<0) {
//        qDebug() << "Nifti::SetRGBPixel out of bounds:"  << p;
        return;
    }

    if (p.y()>=size.y() || p.y()<0) {
  //      qDebug() << "Nifti::SetRGBPixel out of bounds:"  << p;
        return;
    }

    if (p.z()>=size.z() || p.z()<0) {
    //    qDebug() << "Nifti::SetRGBPixel out of bounds:"  << p;
        return;
    }

/*    if (rand()%100>97)
        qDebug() << p << " " << size;
*/
    int i = p.x();
    int j = p.y();
    int k = p.z();

    long idx = (i*size.z() * size.y() + j * size.z() + k);

    if (idx<0 || idx>=rawData.size()) {
        qDebug() << "Nifti::SetRGBPixel out of bounds:" << idx << p;
        return;
    }
    AddColor(idx, color);
/*    rawData [3 * idx + 0] = color.red();
    rawData [3 * idx + 1] = color.green();
    rawData [3 * idx + 2] = color.blue();
*/
}

void Nifti::Load(QString filename)
{
    if (!QFile::exists(filename)) {
        return;
    }
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    header = Nifti::HeaderFromStream (f);
    dataType = getDataType ((int)header.datatype);
    BytesPerPixel = header.bitpix / 8;

    /*        if (VerifyFeature ()) {
                Allocate ();
                //Debug.Log ("File size should be " + (BytesPerPixel * size.x * size.y * size.z) / 1024 + " mb");
                fs.Read (rawData, 0, (int)(size.x * size.y * size.z * BytesPerPixel));
        } else
                Debug.Log ("ERROR: File type " + dataType + " not yet supported aargh");

        fs.Close ();
*/
}

void Nifti::Save(QString filename)
{
    QFile file(filename);
    file.open(QFile::WriteOnly);

    header.sizeof_hdr=348;
    header.magic[0]='n';
    header.magic[1]='+';
    header.magic[2]='1';
    header.magic[3]='\0';

    header.qoffset_x=1;
    header.qoffset_y=1;
    header.qoffset_z=1;







    header.pixdim[0]=3;
    header.pixdim[1]=0.039;
    header.pixdim[2]=0.039;
    header.pixdim[3]=0.039;
//    header.vox_offset

    file.write(reinterpret_cast<char*>(&header),sizeof(NiftiHeader));
    //qDebug() << "Regular : " << header.regular;
    //qDebug() << "Header size: " << sizeof(NiftiHeader);
    file.write(rawData);
  //  qDebug() << " : " << header.regular;

//    qDebug() << "Dim info:" << QString::number(((uchar*)(&header))[39]);

    file.close();
}

float Nifti::getValueAtIndex(ulong idx)
{
    float val = 0;
    if (dataType == DataType::DT_RGB)
        val = (rawData.at(3 * idx + 0) + rawData.at(3 * idx + 0) + rawData.at(3 * idx + 0)) / 3.0;

    if (dataType == DataType::DT_UINT16)
        val = (ushort)(((rawData.at(2 * idx + 1)) << 8) | (rawData.at(2 * idx + 0)));

    if (dataType == DataType::DT_FLOAT)
    {
        for (ulong l = 0; l < 4; l++)
            floatArray[l] = rawData.at(4 * idx + l);

        val = *((float*)floatArray);
        //            val = BitConverter.ToSingle(floatArray, 0);

    }

    if (dataType == DataType::DT_SIGNED_SHORT)
    {
        val = (short)(((rawData.at(2 * idx + 1)) << 8) | (rawData.at(2 * idx + 0)));

    }
    return val;
}

QVector3D Nifti::getBounds()
{
    QVector3D minMax = QVector3D(1E30, -1E30, 0);
    uchar floatArray[4];
    for (ulong idx = 0; idx < size.x()*size.y()*size.z();idx+=100)
    {
        float val = getValueAtIndex(idx);
        minMax.setY(std::max(minMax.y(), val));
        minMax.setX(std::min(minMax.x(), val));
    }

    return minMax;
}

void Nifti::AddColor(long idx, QColor c)
{
    int r = std::min(rawData [(int)(3 * idx + 0)]+c.red(), 255);
    int g = std::min(rawData [(int)(3 * idx + 1)]+c.green(), 255);
    int b = std::min(rawData [(int)(3 * idx + 2)]+c.blue(), 255);
    rawData [int(3 * idx + 0)] = r;
    rawData [int(3 * idx + 1)] = g;
    rawData [int(3 * idx + 2)] = b;

}

void Nifti::Create(QVector3D dim, Nifti::DataType type, int bpp)
{
    size = dim;
    header.dim[0] = 3;
    header.dim[1] = dim.x();
    header.dim[2] = dim.y();
    header.dim[3] = dim.z();

    header.datatype = setDataType(type);
    header.bitpix = bpp;
    BytesPerPixel = header.bitpix / 8;



    Allocate();
}

void Nifti::Allocate()
{
    size.setX(header.dim [1]);
    size.setY(header.dim [2]);
    size.setZ(header.dim [3]);
    long totalSize = (long)(size.x() * size.y() * size.z() * BytesPerPixel);
    rawData.resize(totalSize);
}

Nifti::Nifti(QString filename, QString path)
{
    QStringList split = filename.split (".");

    int final = split.count() - 1;

    if (split [final] == "nii") {
        hasIndexing = false;
        Load (path + filename);
        return;
    }
    if (split [final] == "label") {
        /*LoadLabel (path + filename);
                hasIndexing = true;
                Load (path + split [0] + ".nii");

                return;
                */
    }
    //        Debug.Log ("Could not recognize file format");

}
