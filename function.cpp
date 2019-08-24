#include "function.h"

Function::~Function()
{

}

void Function::calculate(QString expression,
                         QString minX,
                         QString maxX,
                         QString minY,
                         QString maxY,
                         QString numPoints)
{
    m_expression = expression;
    m_minXString = minX;
    m_maxXString = maxX;
    m_minYString = minY;
    m_maxYString = maxY;
    m_pointsString = numPoints;

    performCalculation();
}

void Function::performCalculation()
{
    replaceConstants();
    if (check())
        calculatePoints();    
}

void Function::replaceConstants()
{
    QString piString = QString::number(M_PI);
    QString eString = QString::number(M_E);

    m_minXString.replace("pi", piString);
    m_minXString.replace("e", eString);
    m_minYString.replace("pi", piString);
    m_minYString.replace("e", eString);

    m_maxXString.replace("pi", piString);
    m_maxXString.replace("e", eString);
    m_maxYString.replace("pi", piString);
    m_maxYString.replace("e", eString);
}

bool Function::check()
{
    bool okMin, okMax, okMinY, okMaxY, okPoints;
    double minDouble = m_minXString.toDouble(&okMin);
    if (okMin) {
        m_minX = minDouble;
    }
    else {
        emit error(tr("Minimum is not a real number."));
        return false;
    }

    double maxDouble = m_maxXString.toDouble(&okMax);
    if (okMax) {
        m_maxX = maxDouble;
    }
    else {
        emit error(tr("Maximum is not a real number."));
        return false;
    }

    double minYDouble = m_minYString.toDouble(&okMinY);
    if (okMinY) {
        m_minY = minYDouble;
    }
    else {
        emit error(tr("Minimum Y is not a real number."));
        return false;
    }

    double maxYDouble = m_maxYString.toDouble(&okMaxY);
    if (okMaxY) {
        m_maxY = maxYDouble;
    }
    else {
        emit error(tr("Maximum Y is not a real number."));
        return false;
    }

    int pointsInt = m_pointsString.toInt(&okPoints);
    if (okPoints) {
        m_numPoints = pointsInt;
    }
    else {
        emit error(tr("Points must be a positive integer number"));
        return false;
    }

    if (m_maxX <= m_minX) {
        emit error(tr("Maximum must be greater than minimum."));
        return false;
    }

    if (m_maxY <= m_minY) {
        emit error(tr("Maximum Y must be greater than minimum Y."));
        return false;
    }

    if (m_numPoints < MIN_POINTS) {
        emit error (tr("Points must be greater than zero."));
        return false;
    }

    if (m_numPoints > MAX_POINTS) {
        emit error (tr("Points must be fewer than 10000"));
        return false;
    }


    m_fparser.AddConstant("pi", M_PI);
    m_fparser.AddConstant("e", M_E);
    int res = m_fparser.Parse(m_expression.toStdString(), "x");
    if(res > 0) {
        emit error(tr("Cannot understand expression.\n") + m_fparser.ErrorMsg());
        return false;
    }

    return true;
}

void Function::calculatePoints()
{
    double x, result;
    Point tmpPoint;

    m_linePoints.clear();

    double vals[] = { 0 };
    double step;
    int res;

    step = (m_maxX - m_minX) / LINE_POINTS;
    for (int i = 0; i < LINE_POINTS; i++) {
        x = m_minX + i * step;
        vals[0] = x;
        result = m_fparser.Eval(vals);
        res = m_fparser.EvalError();
        tmpPoint.x = x;
        tmpPoint.y = result;
        if (res == 0)
            tmpPoint.isValid = true;
        else if (res > 0)
            tmpPoint.isValid = false;

        m_linePoints.append(tmpPoint);
    }

    m_minValue = m_linePoints[0].y;
    m_maxValue = m_linePoints[0].y;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (m_linePoints[i].y < m_minValue)
            m_minValue = m_linePoints[i].y;
        if (m_linePoints[i].y > m_maxValue)
            m_maxValue = m_linePoints[i].y;
    }

    emit update();
}

double Function::x(int i) const
{
    return m_linePoints[i].x;
}

double Function::y(int i) const
{
    return m_linePoints[i].y;
}

int Function::lineSize() const
{
    return m_linePoints.size();
}

double Function::minX() const
{
    return m_minX;
}

double Function::maxX() const
{
    return m_maxX;
}

double Function::minY() const
{
    return m_minY;
}

double Function::maxY() const
{
    return m_maxY;
}

double Function::minValue() const
{
    return m_minValue;
}

double Function::maxValue() const
{
    return m_maxValue;
}
