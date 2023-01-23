#include "coordinatetransform.h"
#include "source/IO/xmlanchor.h"
#include <array>

CoordinateTransform::CoordinateTransform(XMLData &data) {
    m_xmlData = &data;
    const auto width = data.m_width;
    const auto height = data.m_height;
    m_linear = QMatrix4x4(data.m_u.x()/width,  data.m_u.y()/width,  data.m_u.z()/width,  0,
                          data.m_v.x()/height, data.m_v.y()/height, data.m_v.z()/height, 0,
                          0, 0, 0, 0,
                          data.m_o.x(), data.m_o.y(), data.m_o.z(), 1);
    QVector<QVector4D> vertices;
    vertices.append(QVector4D(-0.1*width, -0.1*height, -0.1*width, -0.1*height));
    vertices.append(QVector4D( 1.1*width, -0.1*height,  1.1*width, -0.1*height));
    vertices.append(QVector4D(-0.1*width,  1.1*height, -0.1*width,  1.1*height));
    vertices.append(QVector4D( 1.1*width,  1.1*height,  1.1*width,  1.1*height));
    m_triangles.push_back(Triangle(0, 1, 2, vertices));
    m_triangles.push_back(Triangle(1, 2, 3, vertices));
    const auto &markers = data.m_markers;
    std::shared_ptr<int[]> edges(new int[(markers.length()+4)*(markers.length()+3)/2]());
    m_triangles[0].addedges(edges.get());
    m_triangles[0].addedges(edges.get());
    m_triangles[1].addedges(edges.get());
    m_triangles[1].addedges(edges.get());
    edges[3] = 2;
    for(auto &&marker : markers) {
        auto x{marker[2]}, y{marker[3]};
        auto found = false;
        for(auto &&triangle : m_triangles)
            if (triangle.intriangle(x, y)) {
                found = true;
                break;
            }
        if(found) {
            m_triangles.erase(
                std::remove_if(m_triangles.begin(), m_triangles.end(), [&](auto &&triangle) {
                    if (triangle.incirc(x, y)) {
                        triangle.dropedges(edges.get());
                        return true;
                    }
                    return false;
                }), m_triangles.end());
            int v = vertices.length();
            vertices.append(marker);
            std::vector<Triangle> newtriangles;
            for(auto i = 0; i < v-1; i++)
                for(auto j = i+1; j < v; j++)
                    if (edges[i + j*(j-1)/2] == 1)
                        newtriangles.push_back(Triangle(i, j, v, vertices));
            for (auto &&triangle : newtriangles) {
                triangle.addedges(edges.get());
                m_triangles.push_back(triangle);
            }
        }
    }
//    qDebug() <<m_triangles.size();
}

QVector3D CoordinateTransform::Linear(QVector2D img_coords){
    return (QVector4D(img_coords[0], img_coords[1], 0, 1)*m_linear).toVector3D();
}

QVector3D CoordinateTransform::NonLinear(QVector2D img_coords){
    for(auto &&triangle : m_triangles)
        if (triangle.transform(img_coords[0], img_coords[1]))
            return Linear(img_coords);

    return QVector3D();
}

QVector3D CoordinateTransform::getProjection(QVector3D& v)
{
    if (isNonLinear())
       return NonLinear(QVector2D(v.x(),v.y()));

    return Linear(QVector2D(v.x(),v.y()));


}

bool CoordinateTransform::isNonLinear()
{
    return m_xmlData->m_markers.count()!=0;
}

CoordinateTransform::Triangle::Triangle(int a, int b, int c, QVector<QVector4D> &vertices) {
    e1 = a < b ? b*(b-1)/2 + a : a*(a-1)/2 + b;
    e2 = a < c ? c*(c-1)/2 + a : a*(a-1)/2 + c;
    e3 = c < b ? b*(b-1)/2 + c : c*(c-1)/2 + b;
    const auto &A = vertices[a];
    const auto &B = vertices[b];
    const auto &C = vertices[c];

    auto Ax = A[2], Ay = A[3];
    auto Bx = B[2], By = B[3];
    auto Cx = C[2], Cy = C[3];

    ax  = A[0];    ay  = A[1];
    abx = B[0]-ax; aby = B[1]-ay;
    acx = C[0]-ax; acy = C[1]-ay;

    decomp = Matrix3x3(Bx-Ax, By-Ay, 0,
                       Cx-Ax, Cy-Ay, 0,
                       Ax,    Ay,    1).inverse();

    auto a2 = d2(Bx, By, Cx, Cy);
    auto b2 = d2(Ax, Ay, Cx, Cy);
    auto c2 = d2(Ax, Ay, Bx, By);
    auto fa = a2*(b2+c2-a2);
    auto fb = b2*(c2+a2-b2);
    auto fc = c2*(a2+b2-c2);
    den = fa+fb+fc;
    Mdenx = fa*Ax + fb*Bx + fc*Cx;
    Mdeny = fa*Ay + fb*By + fc*Cy;
    r2den = d2(Ax*den, Ay*den, Mdenx, Mdeny);
}

bool CoordinateTransform::Triangle::intriangle(float x, float y) {
    float row[]{x, y, 1};
    auto uv1 = decomp.rowmul(row);
    return !(uv1[0]<0 || uv1[0]>1 || uv1[1]<0 || uv1[1]>1 || uv1[0]+uv1[1]>1);
}

bool CoordinateTransform::Triangle::transform(float &x, float &y) {
    float row[]{x, y, 1};
    auto uv1 = decomp.rowmul(row);
    if(uv1[0]<0 || uv1[0]>1 || uv1[1]<0 || uv1[1]>1 || uv1[0]+uv1[1]>1)
        return false;
    x = ax + abx*uv1[0] + acx*uv1[1];
    y = ay + aby*uv1[0] + acy*uv1[1];
    return true;
}

CoordinateTransform::Matrix3x3 CoordinateTransform::Matrix3x3::inverse(){
    float det = m[0][0] * (m[1][1]*m[2][2] - m[2][1]*m[1][2])
              - m[0][1] * (m[1][0]*m[2][2] - m[1][2]*m[2][0])
              + m[0][2] * (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
//    if (det == 0) {
//        return null;
//    }
    return Matrix3x3(
                (m[1][1]*m[2][2] - m[2][1]*m[1][2]) / det, (m[0][2]*m[2][1] - m[0][1]*m[2][2]) / det, (m[0][1]*m[1][2] - m[0][2]*m[1][1]) / det,
                (m[1][2]*m[2][0] - m[1][0]*m[2][2]) / det, (m[0][0]*m[2][2] - m[0][2]*m[2][0]) / det, (m[1][0]*m[0][2] - m[0][0]*m[1][2]) / det,
                (m[1][0]*m[2][1] - m[2][0]*m[1][1]) / det, (m[2][0]*m[0][1] - m[0][0]*m[2][1]) / det, (m[0][0]*m[1][1] - m[1][0]*m[0][1]) / det);
}
std::array<float, 3> CoordinateTransform::Matrix3x3::rowmul(float row[3]){
    std::array<float,3> ret{};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            ret[i] += row[j]*m[j][i];
    return ret;
}
