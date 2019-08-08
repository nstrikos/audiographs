#include "function.h"

void Function::calculate(QString expression,
                         QString min,
                         QString max,
                         QString minY,
                         QString maxY,
                         QString numPoints,
                         int width,
                         int height)
{
    m_expression = expression;
    m_minString = min;
    m_maxString = max;
    m_minYString = minY;
    m_maxYString = maxY;
    m_pointsString = numPoints;
    m_width = width;
    m_height = height;

    performCalculation();
}

void Function::performCalculation()
{
    replaceConstants();
    if (check()) {
        calculatePoints();
        calcScrCoords();
    }
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

    m_xValues.clear();
    m_yValues.clear();
    m_isValid.clear();

    m_xLineValues.clear();
    m_yLineValues.clear();
    m_isLineValid.clear();

    double vals[] = { 0 };
    double step;
    int res;

    step = (m_max - m_min) / m_numPoints;
    int pointsToCalculate = m_numPoints + 1;
    for (int i = 0; i < pointsToCalculate; i++) {
        x = m_min + i * step;
        vals[0] = x;
        result = m_fparser.Eval(vals);
        res = m_fparser.EvalError();
        m_xValues.append(x);
        m_yValues.append(result);
        if (res == 0)
            m_isValid.append(true);
        else if (res > 0)
            m_isValid.append(false);
    }

    step = (m_max - m_min) / LINE_POINTS;
    for (int i = 0; i < LINE_POINTS; i++) {
        x = m_min + i * step;
        vals[0] = x;
        result = m_fparser.Eval(vals);
        res = m_fparser.EvalError();
        m_xLineValues.append(x);
        m_yLineValues.append(result);
        if (res == 0)
            m_isLineValid.append(true);
        else if (res > 0)
            m_isLineValid.append(false);
    }

    m_minValue = m_yLineValues.at(0);
    m_maxValue = m_yLineValues.at(0);

    for (int i = 1; i < LINE_POINTS; i++) {
        if (m_yLineValues.at(i) < m_minValue)
            m_minValue = m_yLineValues.at(i);
        if (m_yLineValues.at(i) > m_maxValue)
            m_maxValue = m_yLineValues.at(i);
    }

    emit update();
}

void Function::calcScrCoords()
{
    m_xCoords.clear();
    m_yCoords.clear();
    m_xLineCoords.clear();
    m_yLineCoords.clear();
    double xStart = m_xValues.first();
    double xEnd = m_xValues.last();

    for (int i = 0; i < m_xValues.size(); i++) {
        double x =  ( m_width / (xEnd - xStart) * (m_xValues.at(i) - xStart) );
        double y = ( m_height / (m_maxY - m_minY) * (m_yValues.at(i) - m_minY) );

        y = m_height - y;
        m_xCoords.append(x);
        m_yCoords.append(y);
    }

    for (int i = 0; i < LINE_POINTS; i++) {
        double x =  ( m_width / (xEnd - xStart) * (m_xLineValues.at(i) - xStart) );
        double y = ( m_height / (m_maxY - m_minY) * (m_yLineValues.at(i) - m_minY) );
        y = m_height - y;
        m_xLineCoords.append(x);
        m_yLineCoords.append(y);
    }
}

double Function::minValue() const
{
    return m_minValue;
}

double Function::Y(int i) const
{
    return m_yLineValues.at(i);
}

double Function::maxValue() const
{
    return m_maxValue;
}

QVector<double>* Function::xCoords()
{
    return &m_xCoords;
}

QVector<double>* Function::yCoords()
{
    return &m_yCoords;
}

QVector<double>* Function::xLineCoords()
{
    return &m_xLineCoords;
}

QVector<double>* Function::yLineCoords()
{
    return &m_yLineCoords;
}

double Function::maxY() const
{
    return m_maxY;
}

double Function::minY() const
{
    return m_minY;
}

double Function::max() const
{
    return m_max;
}

double Function::min() const
{
    return m_min;
}
