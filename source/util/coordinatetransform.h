#ifndef COORDINATETRANSFORM_H
#define COORDINATETRANSFORM_H

#include <QMatrix4x4>

class XMLData;

class CoordinateTransform {
private:
    class Matrix3x3 {
    private:
        float m[3][3]{};

    public:
        Matrix3x3() = default;
        Matrix3x3(float a11, float a21, float a31,
                  float a12, float a22, float a32,
                  float a13, float a23, float a33) : m{{a11, a21, a31}, {a12, a22, a32}, {a13, a23, a33}} {}
        Matrix3x3 inverse();
        std::array<float, 3> rowmul(float row[3]);
    };

    class Triangle {
    private:
        int e1, e2, e3;
        Matrix3x3 decomp;
        double ax, ay, abx, aby, acx, acy;
        double den, Mdenx, Mdeny, r2den;

    public:
        Triangle(int a, int b, int c, QVector<QVector4D> &vertices);
        void addedges(int edges[]) {edges[e1]++; edges[e2]++; edges[e3]++;}
        void dropedges(int edges[]) {edges[e1]--; edges[e2]--; edges[e3]--;}
        bool intriangle(float x, float y);
        bool incirc(float x, float y) {return d2(x*den, y*den, Mdenx, Mdeny) < r2den;}
        bool transform(float &x, float &y);
        static double d2(double ax, double ay, double bx, double by) {return (ax-bx)*(ax-bx) + (ay-by)*(ay-by);}
    };

    QMatrix4x4 m_linear;
    std::vector<Triangle> m_triangles;

public:
    CoordinateTransform(const XMLData &data);
    QVector3D Linear(QVector2D img_coords);
    QVector3D NonLinear(QVector2D img_coords);
};

#endif // COORDINATETRANSFORM_H
