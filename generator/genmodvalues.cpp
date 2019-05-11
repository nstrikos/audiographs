#include "genmodvalues.h"
#include <QDebug>

GenModValues::GenModValues(double *modulationValues,
                           QString expression,
                           double start,
                           double end,
                           unsigned long long int timeLength,
                           int fmin,
                           int fmax,
                           int sampleRate)
{
    m_modulationValues = modulationValues;
    m_expression = expression;
    m_start = start;
    m_end = end;
    m_timeLength = timeLength;
    m_fmin = fmin;
    m_fmax = fmax;
    m_sampleRate = sampleRate;
}

double *GenModValues::modulationValues()
{
    double step = (m_end - m_start) / (m_timeLength);
    double max;


    qDebug() << "Generator timeLength:" << m_timeLength;

    double *functionValues = new double[m_timeLength];
    double *cs = new double[m_timeLength];
    double *phi = new double[m_timeLength];

    int fc = m_fmin;
    int fdev = m_fmax - m_fmin;


    double clip = 10.0;
    double kf = 0.0;

    GenParameters *params = new GenParameters(functionValues,
                                              m_expression,
                                              m_timeLength,
                                              m_start,
                                              step,
                                              clip,
                                              cs,
                                              kf,
                                              m_sampleRate,
                                              phi,
                                              m_modulationValues,
                                              fc);

    GenFunctionCalculator *functionCalculator = new GenFunctionCalculator(params);

    GenClipper *genClipper = new GenClipper(params);
    genClipper->clip();

    GenMinFinder *minFinder = new GenMinFinder(params);
    minFinder->minOffset();

    GenMaxFinder *maxFinder = new GenMaxFinder(params);
    max = maxFinder->max();

    if (max == 0.0) {
        params->setfc((m_fmax + m_fmin) / 2.0);
        params->setkf(0);
    } else {
        params->setkf(fdev / max);
    }

    qDebug() << "kf:" << params->kf();

    GenSum *genSum = new GenSum(params);
    genSum->sum();

    GenPhiCalculator *phiCalculator = new GenPhiCalculator(params);

    GenMod *genMod = new GenMod(params);
    genMod->mod();

    delete[] functionValues;
    delete[] cs;
    delete[] phi;
    delete params;
    delete functionCalculator;
    delete genClipper;
    delete minFinder;
    delete maxFinder;
    delete genSum;
    delete phiCalculator;
    delete genMod;

    return m_modulationValues;
}
