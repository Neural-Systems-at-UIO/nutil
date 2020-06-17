#include "area.h"


bool DoSomething() {
//    jfdshdsfkjdsa
//    return isTrue;
}


Area::Area()
{




//   DrawLine(center, up);


}

void Area::CalculateStatistics()
{
    m_center = QPoint(0,0);
    for (QPointF p: m_points)
        m_center += p;

    m_center /= m_points.count();
    m_pixelArea = m_points.count();
}
