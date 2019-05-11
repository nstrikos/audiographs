#ifndef GENPARAMETERS_H
#define GENPARAMETERS_H

#include <QString>

class GenParameters
{
public:
    GenParameters(double *functionValues,
                  QString expression,
                  unsigned long long int length,
                  double start,
                  double step,
                  double clip,
                  double *cs,
                  double kf,
                  double sampleRate,
                  double *phi,
                  double *modulationValues,
                  double fc);

    double *functionValues();
    QString expression();
    double start();
    double step();
    unsigned long long length();
    double clip();
    double *cs();
    void setkf(double kf);
    double kf();
    double sampleRate();
    double *phi();
    double *modulationValues();
    void setfc(double fc);
    double fc();

private:
    double *m_functionValues;
    QString m_expression;
    double m_start;
    double m_step;
    unsigned long long int m_length;
    double m_clip;
    double *m_cs;
    double m_kf;
    double m_sampleRate;
    double *m_phi;
    double *m_modulationValues;
    double m_fc;
};

#endif // GENPARAMETERS_H
