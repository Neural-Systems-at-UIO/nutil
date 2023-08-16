#ifndef COORDINATETRANSFORM_H
#define COORDINATETRANSFORM_H

#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <memory>

class XMLData;

class CoordinateTransform {
private:
    class Matrix3x3 {
    private:
        double m[3][3]{};

    public:
        Matrix3x3() = default;
        Matrix3x3(double a11, double a21, double a31,
                  double a12, double a22, double a32,
                  double a13, double a23, double a33) : m{{a11, a21, a31}, {a12, a22, a32}, {a13, a23, a33}} {}
        Matrix3x3 inverse();
        std::array<double, 3> rowmul(double row[3]);
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
        bool intriangle(double x, double y);
        bool incirc(double x, double y) {return d2(x*den, y*den, Mdenx, Mdeny) < r2den;}
        bool transform(float &x, float &y);
        static double d2(double ax, double ay, double bx, double by) {return (ax-bx)*(ax-bx) + (ay-by)*(ay-by);}
    };

    QMatrix4x4 m_linear;
    std::vector<Triangle> m_triangles;

public:
    XMLData* m_xmlData = nullptr;
    CoordinateTransform(XMLData &data);
    QVector3D Linear(QVector2D img_coords);
    QVector3D NonLinear(QVector2D img_coords);
    QVector3D getProjection(QVector3D& p);
    bool isNonLinear();
};

#endif // COORDINATETRANSFORM_H
