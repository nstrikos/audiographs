#include "curveabstract.h"

CurveAbstract::CurveAbstract()
{
    m_function = nullptr;
}

CurveAbstract::~CurveAbstract()
{

}

void CurveAbstract::calcCoords(int width, int height)
{
    if (m_function != nullptr) {
        m_points.clear();
        Point tmpPoint;

        int size = m_function->lineSize();

        double xStart = m_function->x(0);
        double xEnd = m_function->x(size - 1);

        for (int i = 0; i < size; i++) {
            double minY = m_function->minY();
            double maxY = m_function->maxY();
            double x =  ( width / (xEnd - xStart) * (m_function->x(i) - xStart) );
            double y = ( height / (maxY - minY) * (m_function->y(i) - minY) );

            y = height - y;
            tmpPoint.x = x;
            tmpPoint.y = y;
            m_points.append(tmpPoint);
        }
    }
}

QColor CurveAbstract::color() const
{
    return m_color;
}

void CurveAbstract::setColor(const QColor &color)
{
    m_color = color;
}
