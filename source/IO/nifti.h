/*
Nutil - Neuroimaging utilities - aims to both simplify and streamline the mechanism of
pre-and-post processing 2D brain image data. Nutil is developed as a stand-alone application
that runs on all operating systems with a minimalistic user interface requiring little-to-no
experience to execute.

Copyright (C) 2020 nicolaas.groeneboom@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef NIFTI_H
#define NIFTI_H
#include <QChar>
#include <QMap>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <algorithm>
#include <QVector3D>
#include <QColor>


struct NiftiHeader
{
public:


     int   sizeof_hdr;    /*!< MUST be 348           */  /* int sizeof_hdr;      */
     char  data_type[10]; /*!< ++UNUSED++            */  /* char data_type[10];  */
     char  db_name[18];   /*!< ++UNUSED++            */  /* char db_name[18];    */
     int   extents;       /*!< ++UNUSED++            */  /* int extents;         */
     short session_error; /*!< ++UNUSED++            */  /* short session_error; */
     char  regular;       /*!< ++UNUSED++            */  /* char regular;        */
     char  dim_info;      /*!< MRI slice ordering.   */  /* char hkey_un0;       */

                                          /*--- was image_dimension substruct ---*/
     short dim[8];        /*!< Data array dimensions.*/  /* short dim[8];        */
     float intent_p1 ;    /*!< 1st intent parameter. */  /* short unused8;       */
                                                         /* short unused9;       */
     float intent_p2 ;    /*!< 2nd intent parameter. */  /* short unused10;      */
                                                         /* short unused11;      */
     float intent_p3 ;    /*!< 3rd intent parameter. */  /* short unused12;      */
                                                         /* short unused13;      */
     short intent_code ;  /*!< NIFTI_INTENT_* code.  */  /* short unused14;      */
     short datatype;      /*!< Defines data type!    */  /* short datatype;      */
     short bitpix;        /*!< Number bits/voxel.    */  /* short bitpix;        */
     short slice_start;   /*!< First slice index.    */  /* short dim_un0;       */
     float pixdim[8];     /*!< Grid spacings.        */  /* float pixdim[8];     */
     float vox_offset;    /*!< Offset into .nii file */  /* float vox_offset;    */
     float scl_slope ;    /*!< Data scaling: slope.  */  /* float funused1;      */
     float scl_inter ;    /*!< Data scaling: offset. */  /* float funused2;      */
     short slice_end;     /*!< Last slice index.     */  /* float funused3;      */
     char  slice_code ;   /*!< Slice timing order.   */
     char  xyzt_units ;   /*!< Units of pixdim[1..4] */
     float cal_max;       /*!< Max display intensity */  /* float cal_max;       */
     float cal_min;       /*!< Min display intensity */  /* float cal_min;       */
     float slice_duration;/*!< Time for 1 slice.     */  /* float compressed;    */
     float toffset;       /*!< Time axis shift.      */  /* float verified;      */
     int   glmax;         /*!< ++UNUSED++            */  /* int glmax;           */
     int   glmin;         /*!< ++UNUSED++            */  /* int glmin;           */

                                             /*--- was data_history substruct ---*/
     char  descrip[80];   /*!< any text you like.    */  /* char descrip[80];    */
     char  aux_file[24];  /*!< auxiliary filename.   */  /* char aux_file[24];   */

     short qform_code ;   /*!< NIFTI_XFORM_* code.   */  /*-- all ANALYZE 7.5 ---*/
     short sform_code ;   /*!< NIFTI_XFORM_* code.   */  /*   fields below here  */
                                                         /*   are replaced       */
     float quatern_b ;    /*!< Quaternion b param.   */
     float quatern_c ;    /*!< Quaternion c param.   */
     float quatern_d ;    /*!< Quaternion d param.   */
     float qoffset_x ;    /*!< Quaternion x shift.   */
     float qoffset_y ;    /*!< Quaternion y shift.   */
     float qoffset_z ;    /*!< Quaternion z shift.   */

     float srow_x[4] ;    /*!< 1st row affine transform.   */
     float srow_y[4] ;    /*!< 2nd row affine transform.   */
     float srow_z[4] ;    /*!< 3rd row affine transform.   */

     char intent_name[16];/*!< 'name' or meaning of data.  */

     char magic[4] ;      /*!< MUST be "ni1\0" or "n+1\0". */

};

class Nifti {
public:
    Nifti() {}
    enum DataType
    {
        DT_NONE,
        DT_BINARY,
        DT_UNSIGNED_CHAR,
        DT_SIGNED_SHORT,
        DT_SIGNED_INT,
        DT_FLOAT,
        DT_COMPLEX,
        DT_DOUBLE,
        DT_RGB,
        DT_INT8,
        DT_UINT16,
        DT_UINT32,
        DT_INT64,
        DT_UINT64,
        DT_FLOAT128}

    ;


    DataType dataType = DataType::DT_NONE;
    int BytesPerPixel = 0;
    //    QMap<int, Label> indexedColors = new Dictionary<int, Label> ();
    NiftiHeader header;
    QByteArray rawData;
    bool hasIndexing = false;
    QVector3D size = QVector3D (1, 1, 1);
    uchar floatArray[4];
    //public BigArray<byte> rawData;

    Nifti (QString filename, QString path);
    Nifti(QVector3D s) {
        size = s;
    }


    QVector3D scaleValues = QVector3D(1,1,1);
    static NiftiHeader HeaderFromStream (QFile& f);
    static DataType getDataType (int type);
    static int setDataType(DataType t);

    static void Normalize (float array[], int len);

    void SetRGBPixel(const QVector3D& p, QColor color);

    void Load (QString filename);
    void Save (QString filename);
    float getValueAtIndex(ulong idx);

    QVector3D getBounds();

    void AddColor(long index, QColor c);

    void Create(QVector3D dim, DataType type, int bitsperpixel);
    void Allocate ();





    /*private void TestBall ()
{
        header.dim [0] = 128;
        header.dim [1] = 128;
        header.dim [2] = 128;
        //Debug.Log(header.bitpix);
        Allocate ();

        for (int i = 0; i < size.x; i++)
                for (int j = 0; j < size.y; j++)
                        for (int k = 0; k < size.z; k++) {
                                Vector3 p = (new Vector3 (i, j, k) - new Vector3 (size.x, size.y, size.z) / 2);
                                p.x /= size.x;
                                p.y /= size.y;
                                p.z /= size.z;
                                float d = p.magnitude;

                                float val = Mathf.Clamp (Mathf.Exp (-d * d / 0.02f) * 256, 0, 255);
                                int idx = (int)(i * size.y * size.z + j * size.z + k);
                                rawData [3 * idx + 0] = (byte)val;
                                rawData [3 * idx + 1] = (byte)val;
                                rawData [3 * idx + 2] = (byte)(val * 0.3f);
                        }
}
*/


    /*public Nifti downsampleToRGB (Vector3 newScale)
{
        int p = 0;
        Vector3 newSize = new Vector3 (size.x / newScale.x, size.y / newScale.y, size.z / newScale.z);
        byte[] data = new byte[(int)(3 * newSize.x * newSize.y * newSize.z)];
        byte c1 = 0, c2 = 0, c3 = 0;
Vector2 bounds = getBounds();
bounds.x /= 256;
bounds.y /= 256;


for (float i = 0; i < size.x; i += newScale.x)
                for (float j = 0; j < size.y; j += newScale.y)
                        for (float k = 0; k < size.z; k += newScale.z) {
                                int idx = (int)(i * size.z * size.y + j * size.z + k);
                                if (dataType == DataType.DT_RGB) {
                                        data [3 * p + 0] = rawData [3 * idx + 0];
                                        data [3 * p + 1] = rawData [3 * idx + 1];
                                        data [3 * p + 2] = rawData [3 * idx + 2];
                                }
                                if (dataType == DataType.DT_UINT16) {
                                        ushort val = (ushort)(((rawData [2 * idx + 1]) << 8) | (rawData [2 * idx + 0]));
                                        if (!hasIndexing || !indexedColors.ContainsKey (val)) {
                                                        c1 = (byte)(val / bounds.y);
                                                        c2 = (byte)(val / bounds.y);
                                                        c3 = (byte)(val / bounds.y);

                                        } else {
                                                Label l = indexedColors [val];
                                                if (l.toggle) {
                                                        c1 = (byte)l.color.x;
                                                        c2 = (byte)l.color.y;
                                                        c3 = (byte)l.color.z;
                                                } else {
                                                        c1 = c2 = c3 = 0;
                                                }
                                        }
                                        data [3 * p + 0] = c1;
                                        data [3 * p + 1] = c2;
                                        data [3 * p + 2] = c3;
                                }
                                if (dataType == DataType.DT_FLOAT) {
                                        for (int l = 0; l < 4; l++)
                                                floatArray [l] = rawData [4 * idx + l];

                                        float val = BitConverter.ToSingle (floatArray, 0);
                                        data [3 * p + 0] = (byte)(val / bounds.y);
                                        data [3 * p + 1] = (byte)(val / bounds.y);
                                        data [3 * p + 2] = (byte)(val / bounds.y);
                                }

           if (dataType == DataType.DT_SIGNED_SHORT)
            {
                short val = (short)(((rawData[2 * idx + 1]) << 8) | (rawData[2 * idx + 0]));
                c1 = (byte)(val / bounds.y);
                c2 = (byte)(val / bounds.y);
                c3 = (byte)(val / bounds.y);

                data[3 * p + 0] = c1;
                data[3 * p + 1] = c2;
                data[3 * p + 2] = c3;

            }


            p++;
                        }
        Nifti vt = new Nifti (newSize);
        vt.rawData = data;
        return vt;
}

public bool VerifyFeature ()
{
        if (dataType == DataType.DT_RGB || dataType == DataType.DT_UINT16 || dataType == DataType.DT_FLOAT || dataType == DataType.DT_SIGNED_SHORT)
                return true;

        return false;

}


public VolumetricTexture toTexture (Vector3 resizeScale, bool useNewData)
{
        if (!VerifyFeature ()) {
                Debug.Log ("Error: feature not implemented (" + dataType + ")");
                return null;
        }

        Nifti n = downsampleToRGB (resizeScale);
        VolumetricTexture vt = new VolumetricTexture (n.size);
vt.physicalCentermm = new Vector3(header.qoffset_x, header.qoffset_y, header.qoffset_z);
vt.physicalSizemm = new Vector3(size.x * header.pixdim[1], size.y * header.pixdim[2], size.z * header.pixdim[3]);

        vt.fromByteArray (n.rawData);
        return vt;

}
*/



};


#endif // NIFTI_H
