#include "functionModel.h"
#include "ifaces/IFunctionModel.h"
#include "utils/constants.h"
#include "utils/util.h"

FunctionModel::FunctionModel(IFunctionModel &iface) :
    iface(iface)
{
    iface.addModel(this);

    symbol_table.add_function(
                "powint",
                [](double v0, double v1, double v2) -> double
    {

        int a = (int) v1;
        int b = (int) v2;

        int d = mygcd(a, b);

        a = a / d;
        b = b / d;

        double ratio = (double) a / b;

        int sign = 1;
        if (v0 > 0) sign = 1;
        else if (v0 < 0) sign = -1;
        else if (v0 == 0) sign = 0;

        if ((int)b % 2 == 0) {
            return pow(v0, ratio);
        } else {
            if ((int)a % 2 == 0) {
                return pow(abs(v0), ratio);
            } else {
                return sign * pow(abs(v0), ratio);
            }
        }
    });

    symbol_table.add_variable("x",m_x);
    symbol_table.add_constant("pi", PI);
    symbol_table.add_constant("e", E);
    symbol_table.add_constants();
    parser_expression.register_symbol_table(symbol_table);
}

void FunctionModel::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    m_expression = expression;
    m_minXString = minX;
    m_maxXString = maxX;
    m_minYString = minY;
    m_maxYString = maxY;

    m_derivativeMode = 0;

    if ( check() ) {
        m_validExpression = true;
        calculatePoints();
        iface.newGraph(&m_points, m_minX, m_maxX, m_minY, m_maxY);
    } else {
        m_validExpression = false;
        iface.error(m_errorString);
    }
}

bool FunctionModel::check()
{
    bool okMin, okMax, okMinY, okMaxY;

    replaceConstants();

    double minDouble = m_minXString.toDouble(&okMin);
    if (okMin) {
        m_minX = minDouble;
    }
    else {
        m_errorString = "Minimum is not a real number.";
        return false;
    }

    double maxDouble = m_maxXString.toDouble(&okMax);
    if (okMax) {
        m_maxX = maxDouble;
    }
    else {
        m_errorString = "Maximum is not a real number.";
        return false;
    }

    double minYDouble = m_minYString.toDouble(&okMinY);
    if (okMinY) {
        m_minY = minYDouble;
    }
    else {
        m_errorString = "Minimum Y is not a real number.";
        return false;
    }

    double maxYDouble = m_maxYString.toDouble(&okMaxY);
    if (okMaxY) {
        m_maxY = maxYDouble;
    }
    else {
        m_errorString = "Maximum Y is not a real number.";
        return false;
    }

    if (m_maxX <= m_minX) {
        m_errorString = "Maximum must be greater than minimum.";
        return false;
    }

    if (m_maxY <= m_minY) {
        m_errorString = "Maximum Y must be greater than minimum Y.";
        return false;
    }

    typedef exprtk::parser<double>::settings_t settings_t;

    std::size_t compile_options = settings_t::e_joiner            +
            settings_t::e_commutative_check +
            settings_t::e_strength_reduction;

    parser_t parser(compile_options);
    parser.compile(m_expression.toStdString(), parser_expression);

    if (!parser.compile(m_expression.toStdString(),parser_expression))
    {
        for (std::size_t i = 0; i < 1; ++i)
        {
            typedef exprtk::parser_error::type error_t;
            error_t error = parser.get_error(i);
            std::string s = error.diagnostic.c_str();
            m_errorString = QString::fromStdString(s);
            int n = m_errorString.indexOf("-");
            m_errorString = m_errorString.right(m_errorString.size() - n - 2);
        }
        return false;
    }
    return true;
}

void FunctionModel::replaceConstants()
{
    QString piString = QString::number(PI);
    QString eString = QString::number(E);
    QString ln = "ln";

    m_expression.replace(ln, "log");
}

void FunctionModel::calculatePoints()
{
    Point tmpPoint;
    double step;

    typedef exprtk::parser<double>::settings_t settings_t;

    std::size_t compile_options = settings_t::e_joiner            +
            settings_t::e_commutative_check +
            settings_t::e_strength_reduction;

    parser_t parser(compile_options);
    parser.compile(m_expression.toStdString(), parser_expression);

    step = (m_maxX - m_minX) / LINE_POINTS;
    double y;
    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_minX + i * step;
        y = parser_expression.value();
        tmpPoint.x = m_x;
        tmpPoint.y = y;
        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_points.setPoint(i, tmpPoint);
    }

    m_minValue = std::numeric_limits<double>::max();//m_linePoints[0].y;
    m_maxValue = -std::numeric_limits<double>::max();//m_linePoints[0].y;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_points.validAt(i))
            continue;
        if (m_points.yAt(i) < m_minValue)
            m_minValue = m_points.yAt(i);
        if (m_points.yAt(i) > m_maxValue)
            m_maxValue = m_points.yAt(i);
    }
}

void FunctionModel::calculateFirstDerivative()
{
    Point tmpPoint;

    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_points.xAt(i);
        double y = exprtk::derivative(parser_expression, m_x);
        tmpPoint.x = m_x;
        tmpPoint.y = y;
        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_derivPoints.setPoint(i, tmpPoint);
    }
}

void FunctionModel::calculateSecondDerivative()
{
    Point tmpPoint;

    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_points.xAt(i);
        double y = exprtk::second_derivative(parser_expression, m_x);

        double Pow = pow(10.0, 2);
        y = round (y * Pow) / Pow;

        tmpPoint.x = m_x;
        tmpPoint.y = y;

        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_deriv2Points.setPoint(i, tmpPoint);
    }
}

void FunctionModel::calculateDerivativeMaxima()
{
    m_minDerivValue = std::numeric_limits<double>::max();//m_linePoints[0].y;
    m_maxDerivValue = -std::numeric_limits<double>::max();//m_linePoints[0].y;

    Points *tmpPoints;
    if (m_derivativeMode == 2)
        tmpPoints = &m_deriv2Points;
    else
        tmpPoints = &m_derivPoints;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!tmpPoints->validAt(i))
            continue;
        if (tmpPoints->yAt(i) < m_minDerivValue)
            m_minDerivValue = tmpPoints->yAt(i);
        if (tmpPoints->yAt(i) > m_maxDerivValue)
            m_maxDerivValue = tmpPoints->yAt(i);
    }
}

int FunctionModel::derivativeMode() const
{
    return m_derivativeMode;
}

double FunctionModel::minValue() const
{
    if (m_derivativeMode == 0)
        return m_minValue;
    else
        return m_minDerivValue;
}

double FunctionModel::maxValue() const
{
    if (m_derivativeMode == 0)
        return m_maxValue;
    else
        return m_maxDerivValue;
}

double FunctionModel::maxY() const
{
    return m_maxY;
}

void FunctionModel::updateFirstDerivative()
{
    calculateFirstDerivative();
}

double FunctionModel::minY() const
{
    return m_minY;
}

double FunctionModel::maxX() const
{
    return m_maxX;
}

double FunctionModel::minX() const
{
    return m_minX;
}

QString FunctionModel::expression() const
{
    return m_expression;
}

double FunctionModel::x(int i) const
{
    return m_points.xAt(i);
}

double FunctionModel::y(int i) const
{
    if (m_derivativeMode == 0)
        return m_points.yAt(i);
    else if (m_derivativeMode == 1)
        return m_derivPoints.yAt(i);
    else
        return m_deriv2Points.yAt(i);
}

double FunctionModel::y_0(int i) const
{
    return m_points.yAt(i);
}

bool FunctionModel::isValidAt(int i) const
{
    return m_points.validAt(i);
}

int FunctionModel::size() const
{
    return LINE_POINTS;
}

void FunctionModel::setDerivativeMode(int mode)
{
    m_derivativeMode = mode;
    if (m_derivativeMode == 1) {
        calculateFirstDerivative();
        calculateDerivativeMaxima();
        iface.updateDerivative(&m_derivPoints, m_minX, m_maxX, m_minY, m_maxY);
    }
    if (m_derivativeMode == 2) {
        calculateSecondDerivative();
        calculateDerivativeMaxima();
        iface.updateDerivative(&m_deriv2Points, m_minX, m_maxX, m_minY, m_maxY);
    }
}

double FunctionModel::derivative(int i)
{
    m_x = m_points.xAt(i);
    if (m_derivativeMode == 0 || m_derivativeMode == 1)
        return  exprtk::derivative(parser_expression, m_x);
    else
        return exprtk::second_derivative(parser_expression, m_x);
}

double FunctionModel::y_1(int i) const
{
    return m_derivPoints.yAt(i);
}

bool FunctionModel::validExpression() const
{
    return m_validExpression;
}
