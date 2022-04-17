#include "functionDescription.h"

#include <QDebug>

FunctionDescription::FunctionDescription()
{

}

QVector<InterestingPoint> FunctionDescription::points(FunctionModel *model, int derivativeMode)
{
    InterestingPoint tmp;
    m_points.clear();

    tmp.x = 0;
    tmp.y = model->y(0);
    tmp.label = "starting point";
    m_points.append(tmp);

    if (model == nullptr)
        return m_points;
    else {

        if (derivativeMode == 2 || derivativeMode == 1)
            model->refreshDerivative();

        int prev = 0;
        int next = 0;
        for (int i = 0; i < model->size(); i++) {
            tmp.label = "";
            if (!model->isValid(i))
                continue;
            prev = i - 1;
            if (prev < 0)
                prev = 0;
            next = i + 1;
            if (next >= model->size())
                next = model->size() - 1;

            tmp.x = i;
            tmp.y = model->y(i);
            tmp.label = "";

            if (!model->isValid(prev) && model->isValid(next)) {
                if (model->y(i) > model->y(next))
                    tmp.label += " maximum after undefined point";
                else if (model->y(i) < model->y(next))
                    tmp.label += " minimum after undefined point";

            } else if (model->isValid(prev) && !model->isValid(next)) {
                if (model->y(i) > model->y(prev))
                    tmp.label += " maximum before undefined point";
                else if (model->y(i) < model->y(prev))
                    tmp.label += " minimum before undefined point";
            } else if (model->isValid(prev) && model->isValid(next)) {
                if (model->y(i) > model->y(prev) && model->y(i) > model->y(next))
                    tmp.label += " local maximum";
                else if (model->y(i) < model->y(prev) && model->y(i) < model->y(next))
                    tmp.label += " local minimum";

                if (derivativeMode == 2) {
                    if ( (model->firstDerivative(i) < model->firstDerivative(prev)) &&
                         (model->firstDerivative(i) < model->firstDerivative(next)) ) {
                        tmp.label += " point of inflection";
                    } else if ( (model->firstDerivative(i) > model->firstDerivative(prev)) &&
                                (model->firstDerivative(i) > model->firstDerivative(next)) ) {
                        tmp.label += " point of inflection";
                    }
                }
            }


            if (tmp.label != "") {
                tmp.label = tmp.label.trimmed();
                m_points.append(tmp);
            }
        }
    }

    tmp.x = model->size() - 1;
    tmp.y = model->y(tmp.x);
    tmp.label = "ending point";
    m_points.append(tmp);

    return m_points;
}
