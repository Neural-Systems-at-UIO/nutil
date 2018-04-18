#include "nifti.h"

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
   // QByteArray data;
   // data.pointer =
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

void Nifti::Allocate()
{
    size.setX(header.dim [0]);
    size.setY(header.dim [1]);
    size.setZ(header.dim [2]);
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
