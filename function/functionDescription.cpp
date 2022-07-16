#include "functionDescription.h"

#include <QDebug>

FunctionDescription::FunctionDescription(FunctionModel &model) : m_model(model)
{

}

QVector<InterestingPoint> FunctionDescription::points(int derivativeMode)
{
    InterestingPoint tmp;
    m_points.clear();

    tmp.x = 0;
    tmp.y = m_model.y(0);
    tmp.label = "starting point";
    m_points.append(tmp);


    if (derivativeMode == 2 || derivativeMode == 1)
        m_model.refreshDerivative();

    int prev = 0;
    int next = 0;
    for (int i = 0; i < m_model.size(); i++) {
        tmp.label = "";
        if (!m_model.isValid(i))
            continue;
        prev = i - 1;
        if (prev < 0)
            prev = 0;
        next = i + 1;
        if (next >= m_model.size())
            next = m_model.size() - 1;

        tmp.x = i;
        tmp.y = m_model.y(i);
        //tmp.label = "";

        if (!m_model.isValid(prev) && m_model.isValid(next)) {
            if (m_model.y_0(i) > m_model.y_0(next))
                tmp.label += " maximum after undefined point";
            else if (m_model.y_0(i) < m_model.y_0(next))
                tmp.label += " minimum after undefined point";

        } else if (m_model.isValid(prev) && !m_model.isValid(next)) {
            if (m_model.y_0(i) > m_model.y_0(prev))
                tmp.label += " maximum before undefined point";
            else if (m_model.y_0(i) < m_model.y_0(prev))
                tmp.label += " minimum before undefined point";
        } else if (m_model.isValid(prev) && m_model.isValid(next)) {
            if (m_model.y_0(i) > m_model.y_0(prev) && m_model.y_0(i) > m_model.y_0(next))
                tmp.label += " local maximum";
            else if (m_model.y_0(i) < m_model.y_0(prev) && m_model.y_0(i) < m_model.y_0(next))
                tmp.label += " local minimum";

            //local minimum and local maximum cannot be point of inflection
            else if (derivativeMode == 2) {
                if ( (m_model.firstDerivative(i) < m_model.firstDerivative(prev)) &&
                     (m_model.firstDerivative(i) < m_model.firstDerivative(next)) ) {
                    tmp.label += " point of inflection";
                } else if ( (m_model.firstDerivative(i) > m_model.firstDerivative(prev)) &&
                            (m_model.firstDerivative(i) > m_model.firstDerivative(next)) ) {
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
