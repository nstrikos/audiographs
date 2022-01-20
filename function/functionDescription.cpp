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

            if (!model->isValid(prev) && !model->isValid(next)) {
                tmp.x = i;
                tmp.y = model->y(i);
                tmp.label += " edge";
            } else if (!model->isValid(prev) && model->isValid(next)) {

                if (!model->validLimit(model->x(prev))) {

                    if (model->y(i) > model->y(next)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label += " maximum";
                    }
                }
            } else if (model->isValid(prev) && !model->isValid(next)) {

                if (!model->validLimit(model->x(next))) {

                    if (model->y(i) > model->y(prev)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label += " maximum";
                    }
                }
            } else if (model->isValid(prev) && model->isValid(next)) {
                if (model->y(i) > model->y(prev) && model->y(i) > model->y(next)) {
                    tmp.x = i;
                    tmp.y = model->y(i);
                    tmp.label += " local maximum";
                }

                if (derivativeMode == 2) {
                    if ( (model->firstDerivative(i) < model->firstDerivative(prev)) &&
                         (model->firstDerivative(i) < model->firstDerivative(next)) ) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label += " point of inflection";
                    } else if ( (model->firstDerivative(i) > model->firstDerivative(prev)) &&
                                (model->firstDerivative(i) > model->firstDerivative(next)) ) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label += " point of inflection";
                    }
                }
            }

            if (!model->isValid(prev) && model->isValid(next)) {
                if (!model->validLimit(model->x(prev))) {

                    if (model->y(i) < model->y(next)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label += " minimum";
                    }
                }
            } else if (model->isValid(prev) && !model->isValid(next)) {
                if (!model->validLimit(model->x(next))) {

                    if (model->y(i) < model->y(prev)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label += " minimum";
                    }
                }
            } else if (model->isValid(prev) && model->isValid(next)) {
                if (model->y(i) < model->y(prev) && model->y(i) < model->y(next)) {
                    tmp.x = i;
                    tmp.y = model->y(i);
                    tmp.label += " local minimum";
                }
            }

            if (tmp.label != "")
                m_points.append(tmp);
        }

        tmp.x = model->size() - 1;
        tmp.y = model->y(tmp.x);
        tmp.label = "ending point";
        m_points.append(tmp);

        return m_points;
    }
}
