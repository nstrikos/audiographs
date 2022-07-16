#include "currentPoint.h"
#include "constants.h"
#include "math.h"
#include "function/functionModel.h"
#include "ICurrentPoint.h"

CurrentPoint::CurrentPoint(ICurrentPoint &iface, FunctionModel &model) :
    iface(iface),
    model(model)
{
    iface.addCurrentPoint(this);

    timer.setTimerType(Qt::PreciseTimer);
    timer.setInterval(INTERVAL_MILLISECONDS);
    connect(&timer, &QTimer::timeout, this, &CurrentPoint::timerExpired);

    m_point = 0;
    m_step = 10;
}

void CurrentPoint::startMoving(int duration)
{
    m_duration = duration * 1000;
    m_point = 0;
    m_timeElapsed = 0;
    timer.start();
}

void CurrentPoint::timerExpired()
{
    m_timeElapsed += timer.interval();
    if (m_timeElapsed >= m_duration) {
        timer.stop();
        m_point = 0;
        return;
    }

    double cx = (double) m_timeElapsed / m_duration;
    m_point = round(cx * LINE_POINTS);
    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;
    if (m_point < 0)
        m_point = 0;

    setPoint(m_point);
}

int CurrentPoint::step() const
{
    return m_step;
}

void CurrentPoint::setPoint(int point)
{
    if (point < 0)
        return;

    if (point >= model.size())
        return;

    m_point = point;

    m_x = model.x(m_point);
    m_y = model.y(m_point);

    iface.newCurrentPoint(m_x, m_y);
}

void CurrentPoint::incPoint(int step)
{
    m_point += step;

    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;

    setPoint(m_point);
}

void CurrentPoint::next()
{
    m_point += m_step;
    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;

    setPoint(m_point);
}

void CurrentPoint::decPoint(int step)
{
    m_point -= step;

    if (m_point <= 0)
        m_point = 0;

    setPoint(m_point);
}

void CurrentPoint::endPoint()
{
    timer.stop();

    if (model.size() > 0) {
        m_point = model.size() - 1;
        setPoint(m_point);
    }
}

void CurrentPoint::stop()
{
    timer.stop();
}

void CurrentPoint::reset()
{
    timer.stop();
    setPoint(0);
}

void CurrentPoint::previous()
{
    m_point -= m_step;
    if (m_point < 0)
        m_point = 0;

    setPoint(m_point);
}

int CurrentPoint::point()
{
    return m_point;
}

void CurrentPoint::decStep()
{
    m_step -= 10;
    m_step = round(m_step);
    if (m_step < 1)
        m_step = 1;
}

void CurrentPoint::incStep()
{
    if (m_step == 1) {
        m_step = 10;
        return;
    }

    m_step += 10;
    m_step = round(m_step);
    if (m_step > 100)
        m_step = 100;
}
