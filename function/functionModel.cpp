#include "functionModel.h"

#include "constants.h"
#include <QObject>

#include <QDebug>

int mygcd(int a, int b)
{
    return b ? mygcd(b, a%b) : a;
}

#if defined Q_OS_WIN || defined(Q_OS_ANDROID)

double powint(const double *p)
{
    int a = p[1];
    int b = p[2];
    int d = mygcd(a, b);
    a = a / d;
    b = b / d;

    double ratio = (double) a / b;

    int sign = 1;
    if (p[0] > 0) sign = 1;
    else if (p[0] < 0) sign = -1;
    else if (p[0] == 0) sign = 0;

    if ((int)b % 2 == 0) {
        return pow(p[0], ratio);
    } else {
        if ((int)a % 2 == 0) {
            return pow(abs(p[0]), ratio);
        } else {
            return sign * pow(abs(p[0]), ratio);
        }
    }
}
#endif

FunctionModel::FunctionModel()
{
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

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
    symbol_table.add_constant("pi", M_PI);
    symbol_table.add_constant("e", M_E);
    symbol_table.add_constants();
    parser_expression.register_symbol_table(symbol_table);

#else
    m_fparser.AddFunction("powint", powint, 3);
#endif

    requestHandler = &RequestHandler::getInstance();
    requestHandler->add(this, request_calculate);
    requestHandler->add(this, request_calculate_derivative);
    requestHandler->add(this, request_calculate_second_derivative);
    requestHandler->add(this, request_normal_mode);

    updateRequest = nullptr;
    errorRequest = nullptr;
    updateDerivativeRequest = nullptr;
}

FunctionModel::~FunctionModel()
{
    if (updateRequest != nullptr)
        delete updateRequest;
    if (errorRequest != nullptr)
        delete errorRequest;
    if (updateDerivativeRequest != nullptr)
        delete updateDerivativeRequest;
}

void FunctionModel::accept(Request *request)
{
    if (m_log)
        qDebug() << "FunctionModel used id: " << request->id << " type: " << request->description;
    if (request->type == request_calculate)
        performCalculate(static_cast<CalculateRequest*>(request));
    else if (request->type == request_calculate_derivative)
        calculateDerivative();
    else if (request->type == request_calculate_second_derivative)
        calculateSecondDerivative();
    else if (request->type == request_normal_mode)
        normalMode();
}

void FunctionModel::performCalculate(CalculateRequest *request)
{
    QString expression = request->expression;
    QString minX = request->minX;
    QString maxX = request->maxX;
    QString minY = request->minY;
    QString maxY = request->maxY;

    derivative_mode = 0;
    calculate(expression, minX, maxX, minY, maxY);

}

void FunctionModel::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    m_expression = expression;
    m_minXString = minX;
    m_maxXString = maxX;
    m_minYString = minY;
    m_maxYString = maxY;

    if ( check() ) {
        m_validExpression = true;
        calculatePoints();
        if (updateRequest == nullptr)
            updateRequest = new UpdateRequest;
        updateRequest->sender = "FunctionModel";
        updateRequest->points = &m_points;
        updateRequest->minX = m_minX;
        updateRequest->maxX = m_maxX;
        updateRequest->minY = m_minY;
        updateRequest->maxY = m_maxY;
        requestHandler->handleRequest(updateRequest);
    } else {
        m_validExpression = false;
        if (errorRequest == nullptr)
            errorRequest = new ErrorRequest();
        errorRequest->error = m_errorString;
        requestHandler->handleRequest(errorRequest);
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
        m_errorString = QObject::tr("Minimum is not a real number.");
        return false;
    }

    double maxDouble = m_maxXString.toDouble(&okMax);
    if (okMax) {
        m_maxX = maxDouble;
    }
    else {
        m_errorString = QObject::tr("Maximum is not a real number.");
        return false;
    }

    double minYDouble = m_minYString.toDouble(&okMinY);
    if (okMinY) {
        m_minY = minYDouble;
    }
    else {
        m_errorString = QObject::tr("Minimum Y is not a real number.");
        return false;
    }

    double maxYDouble = m_maxYString.toDouble(&okMaxY);
    if (okMaxY) {
        m_maxY = maxYDouble;
    }
    else {
        m_errorString = QObject::tr("Maximum Y is not a real number.");
        return false;
    }

    if (m_maxX <= m_minX) {
        m_errorString = QObject::tr("Maximum must be greater than minimum.");
        return false;
    }

    if (m_maxY <= m_minY) {
        m_errorString = QObject::tr("Maximum Y must be greater than minimum Y.");
        return false;
    }

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

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

#else

    m_fparser.AddConstant("pi", M_PI);
    m_fparser.AddConstant("e", M_E);
    int res = m_fparser.Parse(m_expression.toStdString(), "x");
    if (res >= 0) {
        const char *s;
        s = m_fparser.ErrorMsg();
        m_errorString = QString::fromUtf8(s);
        return false;
    }

#endif
    return true;
}

void FunctionModel::replaceConstants()
{
    QString ln = "ln";

    m_expression.replace(ln, "log");
}

void FunctionModel::calculatePoints()
{
    Point tmpPoint;

    double step;

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

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
        if (std::isfinite(y))
            tmpPoint.isValid = true;
        else
            tmpPoint.isValid = false;

        m_points.setPoint(i, tmpPoint);
    }

#else
    double x;
    double result;


    double vals[] = { 0 };
    int res;

    step = (m_maxX - m_minX) / LINE_POINTS;
    for (int i = 0; i < LINE_POINTS; i++) {
        x = m_minX + i * step;
        vals[0] = x;
        result = m_fparser.Eval(vals);
        res = m_fparser.EvalError();
        tmpPoint.x = x;
        tmpPoint.y = result;
        if (result != result)
            tmpPoint.isValid = false;
        else if (res > 0)
            tmpPoint.isValid = false;
        else if (res == 0)
            tmpPoint.isValid = true;

        m_points.setPoint(i, tmpPoint);
    }

#endif

    m_minValue = std::numeric_limits<double>::max();
    m_maxValue = -std::numeric_limits<double>::max();

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_points.validAt(i))
            continue;
        if (m_points.yAt(i) < m_minValue)
            m_minValue = m_points.yAt(i);
        if (m_points.yAt(i) > m_maxValue)
            m_maxValue = m_points.yAt(i);
    }
}

double FunctionModel::minValue() const
{
    if (derivative_mode == 0)
        return m_minValue;
    else
        return m_minDerivValue;
}

double FunctionModel::maxValue() const
{
    if (derivative_mode == 0)
        return m_maxValue;
    else
        return m_maxDerivValue;
}

double FunctionModel::maxY() const
{
    return m_maxY;
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

double FunctionModel::x(int i)
{
    return m_points.xAt(i);
}

double FunctionModel::y(int i)
{
    if (derivative_mode == 0)
        return m_points.yAt(i);
    else
        return m_derivPoints.yAt(i);
}

bool FunctionModel::isValid(int i)
{
    return m_points.validAt(i);
}

int FunctionModel::size()
{
    return LINE_POINTS;
}

void FunctionModel::calculateDerivative()
{
    Point tmpPoint;

    derivative_mode = 1;

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

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

#else

    double vals[] = { 0 };
    const double h = 0.00000001;
    const double h2 = 2 * h;
    double x_init;
    double x;
    double result;
    int res;

    double y0, y1, y2, y3;

    for (int i = 0; i < LINE_POINTS; i++) {
        x_init = m_points.xAt(i);

        vals[0] = x_init;
        tmpPoint.x = x_init;
        m_fparser.Eval(vals);
        res = m_fparser.EvalError();

        if (res > 0) {
            tmpPoint.isValid = false;
        } else {
            x = x_init + h2;
            vals[0] = x;
            y0 = m_fparser.Eval(vals);
            x = x_init + h;
            vals[0] = x;
            y1 = m_fparser.Eval(vals);
            x = x_init - h;
            vals[0] = x;
            y2 = m_fparser.Eval(vals);
            x = x_init - h2;
            vals[0] = x;
            y3 = m_fparser.Eval(vals);

            result = (-y0 + 8 * (y1 - y2) + y3) / (12 * h);

            tmpPoint.y = result;

            if (result != result)
                tmpPoint.isValid = false;
            else
                tmpPoint.isValid = true;
        }

        m_derivPoints.setPoint(i, tmpPoint);
    }

#endif

    m_minDerivValue = std::numeric_limits<double>::max();
    m_maxDerivValue = -std::numeric_limits<double>::max();

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_derivPoints.validAt(i))
            continue;
        if (m_derivPoints.yAt(i) < m_minDerivValue)
            m_minDerivValue = m_derivPoints.yAt(i);
        if (m_derivPoints.yAt(i) > m_maxDerivValue)
            m_maxDerivValue = m_derivPoints.yAt(i);
    }

    if (updateDerivativeRequest == nullptr)
        updateDerivativeRequest = new UpdateDerivativeRequest;
    updateDerivativeRequest->sender = "FunctionModel";
    updateDerivativeRequest->points = &m_derivPoints;
    updateDerivativeRequest->minX = m_minX;
    updateDerivativeRequest->maxX = m_maxX;
    updateDerivativeRequest->minY = m_minY;
    updateDerivativeRequest->maxY = m_maxY;
    requestHandler->handleRequest(updateDerivativeRequest);
}

void FunctionModel::calculateSecondDerivative()
{
    Point tmpPoint;

    derivative_mode = 2;

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

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
        m_derivPoints.setPoint(i, tmpPoint);
    }

#else

    double vals[] = { 0 };
    const double h = 0.00001;
    const double h2 = 2 * h;
    double x_init;
    double x;
    double result;
    double y, y0, y1, y2, y3;
    double Pow;
    int res;

    for (int i = 0; i < LINE_POINTS; i++) {
        x_init = m_points.xAt(i);
        x = x_init;
        tmpPoint.x = x_init;

        vals[0] = x;
        y = m_fparser.Eval(vals);
        res = m_fparser.EvalError();

        if (res > 0) {
            tmpPoint.isValid = false;
        } else {
            x = x_init + h2;
            vals[0] = x;
            y0 = m_fparser.Eval(vals);
            x = x_init + h;
            vals[0] = x;
            y1 = m_fparser.Eval(vals);
            x = x_init - h;
            vals[0] = x;
            y2 = m_fparser.Eval(vals);
            x = x_init - h2;
            vals[0] = x;
            y3 = m_fparser.Eval(vals);

            result = (-y0 + 16 * (y1 + y2) - 30 * y - y3) / (12 * h * h);

            Pow = pow(10.0, 2);
            result = round (result * Pow) / Pow;

            tmpPoint.y = result;

            if (result != result)
                tmpPoint.isValid = false;
            else
                tmpPoint.isValid = true;
        }

        m_derivPoints.setPoint(i, tmpPoint);
    }
#endif

    m_minDerivValue = std::numeric_limits<double>::max();
    m_maxDerivValue = -std::numeric_limits<double>::max();

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_derivPoints.validAt(i))
            continue;
        if (m_derivPoints.yAt(i) < m_minDerivValue)
            m_minDerivValue = m_derivPoints.yAt(i);
        if (m_derivPoints.yAt(i) > m_maxDerivValue)
            m_maxDerivValue = m_derivPoints.yAt(i);
    }

    if (updateDerivativeRequest == nullptr)
        updateDerivativeRequest = new UpdateDerivativeRequest;
    updateDerivativeRequest->points = &m_derivPoints;
    updateDerivativeRequest->minX = m_minX;
    updateDerivativeRequest->maxX = m_maxX;
    updateDerivativeRequest->minY = m_minY;
    updateDerivativeRequest->maxY = m_maxY;
    requestHandler->handleRequest(updateDerivativeRequest);
}

void FunctionModel::refreshDerivative()
{
    //    if (m_points.size() <= 0)
    //        return;

    Point tmpPoint;

    //m_derivPoints.clear();

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

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
        m_firstDerivPoints.setPoint(i, tmpPoint);
    }

#else

    double vals[] = { 0 };
    const double h = 0.00000001;
    const double h2 = 2 * h;
    double x_init;
    double x;
    double result;
    int res;

    double y0, y1, y2, y3;

    for (int i = 0; i < LINE_POINTS; i++) {
        x_init = m_points.xAt(i);

        vals[0] = x_init;
        tmpPoint.x = x_init;
        m_fparser.Eval(vals);
        res = m_fparser.EvalError();

        if (res > 0) {
            tmpPoint.isValid = false;
        } else {
            x = x_init + h2;
            vals[0] = x;
            y1 = m_fparser.Eval(vals);
            x = x_init - h;
            vals[0] = x;
            y2 = m_fparser.Eval(vals);
            x = x_init - h2;
            vals[0] = x;
            y3 = m_fparser.Eval(vals);

            result = (-y0 + 8 * (y1 - y2) + y3) / (12 * h);

            tmpPoint.y = result;

            if (result != result)
                tmpPoint.isValid = false;
            else
                tmpPoint.isValid = true;
        }

        m_firstDerivPoints.setPoint(i, tmpPoint);
    }
#endif
}

double FunctionModel::y0(int i)
{
    return m_points.yAt(i);
}

double FunctionModel::derivative(int i)
{
#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

    m_x = m_points.xAt(i);
    if (derivative_mode == 0 || derivative_mode == 1)
        return  exprtk::derivative(parser_expression, m_x);
    else
        return exprtk::second_derivative(parser_expression, m_x);
#else

#endif
}

double FunctionModel::firstDerivative(int i)
{
    return m_firstDerivPoints.yAt(i);
}

void FunctionModel::normalMode()
{
    derivative_mode = 0;
}

bool FunctionModel::validExpression() const
{
    return m_validExpression;
}
