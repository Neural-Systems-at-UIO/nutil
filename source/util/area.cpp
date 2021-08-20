#include "area.h"

int Area::s_area_id_counter = 0;


Area::Area()
{

    id = s_area_id_counter;
    s_area_id_counter++;


//   DrawLine(center, up);


}

void Area::CalculateStatistics()
{
    m_center = QPoint(0,0);
    for (QPointF p: m_points)
        m_center += p;
    if (m_points.count()!=0)
       m_center /= m_points.count();
    m_pixelArea = m_points.count();
}
