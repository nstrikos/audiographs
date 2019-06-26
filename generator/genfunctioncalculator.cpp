#include "genfunctioncalculator.h"
#include "atmsp.h"
#include <limits>
#include <QDebug>
#include <QElapsedTimer>
#include <QVector>

GenFunctionCalculator::GenFunctionCalculator(GenParameters *params)
{
    m_params = params;
    unsigned long long int length = params->length();

    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int interval = length / numThreads;


    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_tmpThread = new GenFunctionCalculatorThread(m_params,
                                                      i * interval,
                                                      (i+1)* interval);
        m_threads.push_back(m_tmpThread);
        connect(m_tmpThread, SIGNAL(finished()),
                m_tmpThread, SLOT(deleteLater()));
        m_tmpThread->start();
    }

    m_tmpThread = new GenFunctionCalculatorThread(m_params,
                                                  (numThreads - 1) * interval,
                                                  length);
    m_threads.push_back(m_tmpThread);
    connect(m_tmpThread, SIGNAL(finished()),
            m_tmpThread, SLOT(deleteLater()));
    m_tmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_threads.at(i)->wait();
    }
}

GenFunctionCalculatorThread::GenFunctionCalculatorThread(GenParameters *params,
                                                         unsigned long long first,
                                                         unsigned long long last)
{
    m_params = params;
    m_first = first;
    m_last = last;

}

void GenFunctionCalculatorThread::run()
{
    double x;
    double start = m_params->start();
    double step = m_params->step();
    double *functionValues = m_params->functionValues();
    unsigned long long int i = 0;

    std::string exp = m_params->expression().toStdString();

    ATMSP<double> parser;
    ATMSB<double> byteCode;

    double result;

    size_t err = parser.parse(byteCode, exp, "x");
    if ( err  )
        qDebug() << "Parsing failed";

    for (i = m_first; i < m_last; i++) {
        x = start + i * step;
        byteCode.var[0] = x;   // x is 1st in the above variables list, so it has index 0
        result = byteCode.run();
//        if (x > -4.0 && x < -3.0)
//            result = 440.0;
//        if (x >= -3.0 && x < -2.0)
//            result = 493.88;
//        if (x >= -2.0 && x < -1.0)
//            result = 523.25;
//        if (x >= -1.0 && x < 0.0)
//            result = 587.33;
//        if (x >= 0.0 && x < 1.0)
//            result = 659.25;
//        if (x >= 1.0 && x < 2.0)
//            result = 698.46;
//        if (x >= 2.0 && x < 3.0)
//            result = 783.99;
//        if (x >= 3.0 && x <= 4.0)
//            result = 880.00;

        functionValues[i] = result;

        if (is_positive_infinite(result)) {
            functionValues[i] = std::numeric_limits<double>::max();
//            qDebug() << "Positive infinity at i: " << i;
        }

        if (is_negative_infinite(result)) {
            functionValues[i] = -std::numeric_limits<double>::max();
//            qDebug() << "Negative infinity at i: " << i;
        }

        if (is_nan(result)) {
            functionValues[i] = 0;
//            qDebug() << "Not a number at i: " << i;
        }
        //        qDebug() << "x: " << x << ", " << functionValues[i];
        //        m_functionValues[i] = sin(x)*x*x*x - x*x*sin(x);
        //        functionValues[i] = -5/(x*x + 1);
        //        m_functionValues[i] = x;
        //        m_functionValues[i] = 5 - x;
        //        functionValues[i] = 5;
        //         functionValues[i] = sin(x)*log(x)*cos(x/3)*x^3
        //          functionValues[i] = sin(x)*log(abs(x))*x;
        //        if (x != 0.0)
        //            functionValues[i] = sin(x*x) / x;
        //        functionValues[i] = sin(x*x*x) / x;
        //        m_functionValues[i] = cos(x*x) / x;
        //        functionValues[i] = 1 / abs(x);
        //            functionValues[i] = 1 / x;

    }
}

bool GenFunctionCalculatorThread::is_positive_infinite(const double &value)
{
    double max_value = std::numeric_limits<double>::max();

    return ! ( value <= max_value );
}

bool GenFunctionCalculatorThread::is_negative_infinite(const double &value)
{
    double min_value = - std::numeric_limits<double>::max();

    return ! ( min_value <= value  );
}

bool GenFunctionCalculatorThread::is_nan(const double &value)
{
    // True if NAN
    return value != value;
}

bool GenFunctionCalculatorThread::is_valid(const double &value)
{
    return ! is_positive_infinite(value) && is_negative_infinite(value) && ! is_nan(value);
}
