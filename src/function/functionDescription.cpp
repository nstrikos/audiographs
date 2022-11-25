#include "functionDescription.h"

#include <QDebug>

FunctionDescription::FunctionDescription(FunctionModel &model) : m_model(model)
{

}

QVector<InterestingPoint> FunctionDescription::points()
{
    int derivativeMode = m_model.derivativeMode();
    InterestingPoint tmp;
    m_points.clear();

    tmp.x = 0;
    tmp.y = m_model.y(0);
    tmp.label = "starting point";
    m_points.append(tmp);


    if (derivativeMode == 2)
        m_model.updateFirstDerivative();

    int prev = 0;
    int next = 0;
    for (int i = 0; i < m_model.size(); i++) {
        tmp.label = "";
        if (!m_model.isValidAt(i))
            continue;
        prev = i - 1;
        if (prev < 0)
            prev = 0;
        next = i + 1;
        if (next >= m_model.size())
            next = m_model.size() - 1;

        tmp.x = i;
        tmp.y = m_model.y(i);

        if (!m_model.isValidAt(prev) && m_model.isValidAt(next)) {
            if (m_model.y_0(i) > m_model.y_0(next))
                tmp.label += " maximum after undefined point";
            else if (m_model.y_0(i) < m_model.y_0(next))
                tmp.label += " minimum after undefined point";

        } else if (m_model.isValidAt(prev) && !m_model.isValidAt(next)) {
            if (m_model.y_0(i) > m_model.y_0(prev))
                tmp.label += " maximum before undefined point";
            else if (m_model.y_0(i) < m_model.y_0(prev))
                tmp.label += " minimum before undefined point";

        } else if (m_model.isValidAt(prev) && m_model.isValidAt(next)) {



            if (m_model.y(i) == 0) {
                QString text;
                if (derivativeMode == 0)
                    text = " zero crossing";
                else if (derivativeMode == 1)
                    text = " first derivative zero crossing";
                else if (derivativeMode == 2)
                    text = " second derivative zero crossing";
                tmp.label += text;
            } else if (m_model.y(i) * m_model.y(next) < 0) {
                QString text;
                if (derivativeMode == 0)
                    text = " zero crossing";
                else if (derivativeMode == 1)
                    text = " first derivative zero crossing";
                else if (derivativeMode == 2)
                    text = " second derivative zero crossing";
                tmp.label += text;
            }



            if (m_model.y_0(i) > m_model.y_0(prev) && m_model.y_0(i) > m_model.y_0(next))
                tmp.label += " local maximum";
            else if (m_model.y_0(i) < m_model.y_0(prev) && m_model.y_0(i) < m_model.y_0(next))
                tmp.label += " local minimum";


            if (derivativeMode == 1 || derivativeMode == 2) {
                if (m_model.y(i) > m_model.y(prev) && m_model.y(i) > m_model.y(next)) {
                    QString text;
                    if (derivativeMode == 1)
                        text = " first derivative maximum";
                    else if (derivativeMode == 2)
                        text = " second derivative maximum";
                    tmp.label += text;
                }
                else if (m_model.y(i) < m_model.y(prev) && m_model.y(i) < m_model.y(next)) {
                    QString text;
                    if (derivativeMode == 1)
                        text = " first derivative minimum";
                    else if (derivativeMode == 2)
                        text = " second derivative minimum";
                    tmp.label += text;
                }
            }



            //local minimum and local maximum cannot be point of inflection
            else if (derivativeMode == 2) {
                if ( (m_model.y_1(i) < m_model.y_1(prev)) &&
                     (m_model.y_1(i) < m_model.y_1(next)) ) {
                    tmp.label += " point of inflection";
                } else if ( (m_model.y_1(i) > m_model.y_1(prev)) &&
                            (m_model.y_1(i) > m_model.y_1(next)) ) {
                    tmp.label += " point of inflection";
                }
            }
        }

        if (tmp.label != "") {
            tmp.label = tmp.label.trimmed();
            m_points.append(tmp);
        }
    }

    tmp.x = m_model.size() - 1;
    tmp.y = m_model.y(tmp.x);
    tmp.label = "ending point";
    m_points.append(tmp);

    return m_points;
}
