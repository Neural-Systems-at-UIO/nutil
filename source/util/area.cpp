#include "area.h"

Area::Area()
{

}

void Area::CalculateStatistics()
{
    m_center = QPoint(0,0);
    for (QPointF p: m_points)
        m_center += p;

    m_center /= m_points.count();
    m_pixelArea = m_points.count();
}
