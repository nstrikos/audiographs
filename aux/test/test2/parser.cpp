#include "parser.h"

#include <QDebug>

Parser::Parser()
{
    m_functionString = "sin(x)";
    m_xStart = -10;
    m_xEnd = 10;
    m_yStart = -10;
    m_yEnd = 10;
    m_h = 0.1;
    run();
}

Parser::~Parser()
{

}

void Parser::run()
{
    int i;
    double a;
    double start, end;

    size_t err = atmspParser.parse(byteCode, m_functionString, "x");

    if ( err  )
        qDebug() << "Parsing failed with: " ;//<< parser.errMessage(err);

    qDebug() << "Thread is running";

    if (m_XPoints.size() > 0)
        m_XPoints.clear();

    if (m_YPoints.size() > 0)
        m_YPoints.clear();

    start = m_xStart / m_h;
    end = m_xEnd / m_h;
    for (i = start; i <= end ; ++i) // a = -0.2 to 0.2 step 0.01
    {
        a = i * m_h;

        //a = round_to_digits(a, 0.001);

        byteCode.var[0] = a;   // x is 1st in the above variables list, so it has index 0

        const double result = byteCode.run();
        size_t check = byteCode.fltErr;

        if (check == 1)
            printf("Not defined at: %.20f\n", a);
        //else if (result == 0)
        //    printf("%.20f %.20f\n", a, result);
        //else if (isnan(result) || isinf(result))
        //    printf("%.20f %.20f\n", a, result);
        else
        {
            byteCode.var[0] = a - 1e-10;
            const double result0 = byteCode.run();
            byteCode.var[0] = a + 1e-10;
            const double result1 = byteCode.run();

            //if ( result0 * result1 < 0)
            //    printf("%.20f %.20f %.20f\n", a, result0, result1);
        }
        //printf("%.20f %.20f\n", a, result);
        m_XPoints.append(a);
        m_YPoints.append(result);


        //const double next = a  + 1e-10;
        //byteCode.var[0] = next;
        //const long double fnext = byteCode.run();
        //const long double fn = (fnext - result)/(next - a);

        //        size_t check = byteCode.fltErr;

        //        if ( abs(a*a - 0.01) < 1e-6)
        //        {
        //            double t = round ( a / 0.0001) * 0.0001;
        //            qDebug() << "a^2 - 0.01:" << t << a*a - 0.01;
        //        }
        //        if ( abs(a*a - 0.0001) < 1e-6)
        //        {
        //            double t = round ( a / 0.0001) * 0.0001;
        //            qDebug() << "a^2 - 0.0001:" << t << a*a - 0.01;
        //        }
        //        //if ( abs(a*a - 0.0001) < 1e-6)
        //        //    qDebug() << a << a*a - 0.0001;
        //        if ( abs(sin(a*a - 0.09)) < 1e-6)
        //        {
        //            double t = round ( a / 0.0001) * 0.0001;
        //            qDebug() << "sin(a^2 - 0.09):" << t << sin(a*a - 0.09);
        //        }
        //        //if (abs (sin(a*a - 0.0009)) < 1e-6)
        //        //    qDebug() << a << sin(a*a - 0.0009);
        //        if (abs (log(a) - 0.5) < 1e-6)
        //        {
        //            double t = round ( a / 0.001) * 0.001;
        //            qDebug() << "log(a) - 0.5: " << t << log(a) - 0.5;
        //        }

        //        if (check == 1)
        //            qDebug() << a;


        //if (check == 1)
        //    printf("check : %d %.20Lf %.20Lf %.20Lf\n", i, a, result, fn);
        //if (abs(fn) > 1e10)
        //    printf("%.20Lf %.20Le %.20Lf %.20Le\n", a, std::numeric_limits<long double>::epsilon(), result, fn);

        //printf("%d %.20f %.30f %.30f\n", i, 0.04, a, result);
    }
    qDebug() << "Calculation finished";
    emit calculationFinished();
}

void Parser::setFunctionString(QString arg1)
{
    m_functionString = arg1.toStdString();
}

QString Parser::functionString()
{
    return QString::fromStdString(m_functionString);
}

void Parser::setXStart(double arg1)
{
    m_xStart = arg1;
}

double Parser::xStart()
{
    return m_xStart;
}

void Parser::setXEnd(double arg1)
{
    m_xEnd = arg1;
}

double Parser::xEnd()
{
    return m_xEnd;
}

void Parser::setYStart(double arg1)
{
    m_yStart = arg1;
}

double Parser::yStart()
{
    return m_yStart;
}

void Parser::setYEnd(double arg1)
{
    m_yEnd = arg1;
}

double Parser::yEnd()
{
    return m_yEnd;
}

void Parser::setH(double arg1)
{
    m_h = arg1;
}

double Parser::h()
{
    return m_h;
}

QList<double> Parser::yPoints()
{
    return m_YPoints;
}

QList<double> Parser::xPoints()
{
    return m_XPoints;
}

void Parser::receiveGraphSignal()
{
    qDebug() << "Graph signal received";
    qDebug() << "Input function is: " << QString::fromStdString(m_functionString);
    qDebug() << "x start is: " << m_xStart;
    qDebug() << "x end is: " << m_xEnd;
    qDebug() << "y start is: " << m_yStart;
    qDebug() << "y end is: " << m_yEnd;
    run();
}
