#include "function.h"

void Function::calculate(FunctionInput functionInput)
{
    m_expression = functionInput.expression;
    m_minString = functionInput.minimum;
    m_maxString = functionInput.maximum;
    m_pointsString = functionInput.numPoints;

    performCalculation();
}

void Function::calculate(QString expression,
                         QString min,
                         QString max,
                         QString minY,
                         QString maxY,
                         QString numPoints)
{
    m_expression = expression;
    m_minString = min;
    m_maxString = max;
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

    m_minString.replace("pi", piString);
    m_minString.replace("e", eString);
    m_minYString.replace("pi", piString);
    m_minYString.replace("e", eString);

    m_maxString.replace("pi", piString);
    m_maxString.replace("e", eString);
    m_maxYString.replace("pi", piString);
    m_maxYString.replace("e", eString);
}

bool Function::check()
{
    bool okMin, okMax, okMinY, okMaxY, okPoints;
    double minDouble = m_minString.toDouble(&okMin);
    if (okMin) {
        m_min = minDouble;
    }
    else {
        emit error(tr("Minimum is not a real number."));
        return false;
    }

    double maxDouble = m_maxString.toDouble(&okMax);
    if (okMax) {
        m_max = maxDouble;
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

    if (m_max <= m_min) {
        emit error(tr("Maximum must be greater than minimum."));
        return false;
    }

    if (m_maxY <= m_minY) {
        emit error(tr("Maximum Y must be greater than minimum Y."));
        return false;
    }

    if (m_numPoints < 1) {
        emit error (tr("Points must be greater than zero."));
        return false;
    }

    if (m_numPoints > 100000) {
        emit error (tr("Points must be fewer than 100000"));
        return false;
    }


    m_fparser.AddConstant("pi", M_PI);
    m_fparser.AddConstant("e", M_E);
    int res = m_fparser.Parse(m_expression.toStdString(), "x");
//    m_fparser.Optimize();
    if(res > 0) {
        emit error(tr("Cannot understand expression.\n") + m_fparser.ErrorMsg());
        return false;
    }

    return true;
}

void Function::calculatePoints()
{
    double x, result;

    m_points.clear();
    m_linePoints.clear();

    double vals[] = { 0 };
    double step;
    int res;

    step = (m_max - m_min) / m_numPoints;
    Point tmpPoint;
    int pointsToCalculate = m_numPoints + 1;
    for (int i = 0; i < pointsToCalculate; i++) {
        x = m_min + i * step;
        vals[0] = x;
        result = m_fparser.Eval(vals);
        res = m_fparser.EvalError();
        tmpPoint.x = x;
        tmpPoint.y = result;
        if (res == 0)
            tmpPoint.isValid = true;
        else if (res > 0)
            tmpPoint.isValid = false;
        m_points.append(tmpPoint);
    }

    step = (m_max - m_min) / LINE_POINTS;
    for (int i = 0; i < LINE_POINTS; i++) {
        x = m_min + i * step;
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

    emit update();
}

double Function::maxY() const
{
    return m_maxY;
}

double Function::minY() const
{
    return m_minY;
}

QVector<double> Function::yLineCoords() const
{
    return m_yLineCoords;
}

QVector<double> Function::xLineCoords() const
{
    return m_xLineCoords;
}

QVector<double> Function::xCoords() const
{
    return m_xCoords;
}

QVector<double> Function::yCoords() const
{
    return m_yCoords;
}

int Function::size()
{
    return m_points.size();
}

int Function::lineSize()
{
    return m_linePoints.size();
}

void Function::calcScrCoords(int width, int height)
{
    if (m_points.size() > 0) {
        m_xCoords.clear();
        m_yCoords.clear();
        m_xLineCoords.clear();
        m_yLineCoords.clear();
        double xStart = m_points.first().x;
        double xEnd = m_points.last().x;



//        m_minY = m_points.first().y;
//        m_maxY = m_minY;

//        for (int i = 0; i < m_points.size(); i++) {
//            if (m_points.at(i).y < m_minY)
//                m_minY = m_points.at(i).y;
//            if (m_points.at(i).y > m_maxY)
//                m_maxY = m_points.at(i).y;
//        }

        for (int i = 0; i < m_points.size(); i++) {
//            int x =  round( width / (xEnd - xStart) * (m_points.at(i).x - xStart) );
//            int y = round( height / (m_maxY - m_minY) * (m_points.at(i).y - m_minY) );

            double x =  ( width / (xEnd - xStart) * (m_points.at(i).x - xStart) );
            double y = ( height / (m_maxY - m_minY) * (m_points.at(i).y - m_minY) );

            y = height - y;
            m_xCoords.push_back(x);
            m_yCoords.push_back(y);
        }

        for (int i = 0; i < LINE_POINTS; i++) {
//            int x =  round( width / (xEnd - xStart) * (m_linePoints.at(i).x - xStart) );
//            int y = round( height / (m_maxY - m_minY) * (m_linePoints.at(i).y - m_minY) );

            double x =  ( width / (xEnd - xStart) * (m_linePoints.at(i).x - xStart) );
            double y = ( height / (m_maxY - m_minY) * (m_linePoints.at(i).y - m_minY) );

            y = height - y;
            m_xLineCoords.push_back(x);
            m_yLineCoords.push_back(y);
        }
    }
}

double Function::x(int point)
{
    return m_points.at(point).x;
}

double Function::y(int point)
{
    return m_points.at(point).y;
}

bool Function::isValid(int point)
{
    return m_points.at(point).isValid;
}

double Function::xLine(int point)
{
    return m_linePoints.at(point).x;
}

double Function::yLine(int point)
{
    return m_linePoints.at(point).y;
}

bool Function::isValidLine(int point)
{
    return m_linePoints.at(point).isValid;
}
