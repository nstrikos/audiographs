#include "functionController.h"
#include "mainwindow.h"
#include "function/functionModel.h"
#include "function/dragHandler.h"
#include "function/functionZoomer.h"
#include "function/currentPoint.h"
#include "generator/audio.h"
#include "audionotes/audionotes.h"
#include "parameters.h"
#include "function/pointsInterest.h"

FunctionController::FunctionController()
{
    derivMode = 0;

    parameters = &Parameters::getInstance();
    textToSpeech = &TextToSpeech::getInstance();
}

FunctionController::~FunctionController()
{

}

void FunctionController::addModel(FunctionModel *model)
{
    this->model = model;
}

void FunctionController::addGui(MainWindow *gui)
{
    this->gui = gui;
}

void FunctionController::addDragHandler(DragHandler *dragHandler)
{
    this->dragHandler = dragHandler;
}

void FunctionController::addZoomer(FunctionZoomer *zoomer)
{
    this->zoomer = zoomer;
}

void FunctionController::addCurrentPoint(CurrentPoint *currentPoint)
{
    this->currentPoint = currentPoint;
}

void FunctionController::addAudio(Audio *audio)
{
    this->audio = audio;
}

void FunctionController::addAudionotes(AudioNotes *audionotes)
{
    this->audionotes = audionotes;
}

void FunctionController::addPointsInterest(PointsInterest *pointsInterest)
{
    this->pointsInterest = pointsInterest;
}

void FunctionController::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    currentPoint->reset();
    pointsInterest->setUpdated(false);

    model->calculate(expression, minX, maxX, minY, maxY);

    if (derivMode == 1)
        model->calculateDerivative();
    else if (derivMode == 2)
        model->calculateSecondDerivative();
}

void FunctionController::newGraph(Points *points, double minX, double maxX, double minY, double maxY)
{
    gui->updateGraph(points, minX, maxX, minY, maxY);
}

void FunctionController::error(QString error)
{
    gui->error(error);
}

void FunctionController::updateDerivative(Points *points, double minX, double maxX, double minY, double maxY)
{
    gui->updateDerivative(points, minX, maxX, minY, maxY);
}

void FunctionController::startDrag(int x, int y)
{
    currentPoint->reset();
    pointsInterest->setUpdated(false);
    dragHandler->startDrag(x, y);
}

void FunctionController::drag(int diffX, int diffY, int width, int height)
{
    dragHandler->drag(diffX, diffY, width, height, derivMode);
}

void FunctionController::zoom(double delta)
{
    currentPoint->reset();
    pointsInterest->setUpdated(false);
    zoomer->zoom(delta, derivMode);
}

void FunctionController::newInputValues(double minX, double maxX, double minY, double maxY)
{
    gui->newInputValues(minX, maxX, minY, maxY);
}

void FunctionController::newCurrentPoint(double x, double y)
{
    gui->newCurrentPoint(x, y);
}

void FunctionController::audioFinished()
{
    gui->audioFinished();
}

void FunctionController::playSound()
{
    if (parameters->useNotes())
        startNotes();
    else
        startAudio();

    currentPoint->startMoving(parameters->duration());
}

void FunctionController::startAudio()
{
    audio->start(model->expression(),
                 model->minX(),
                 model->maxX(),
                 model->minY(),
                 model->maxY(),
                 parameters->duration(),
                 parameters->minFreq(),
                 parameters->maxFreq(),
                 derivMode);
}

void FunctionController::startNotes()
{
    audionotes->startNotes(parameters->maxFreq(),
                           parameters->minFreq(),
                           parameters->duration(),
                           derivMode,
                           parameters->useNegativeNotes());
}

void FunctionController::stopSound()
{
    audio->stop();
    audionotes->stopNotes();
    currentPoint->stop();
    pointsInterest->stop();
}

void FunctionController::nextPoint()
{
    currentPoint->next();
    audionotes->setNote(currentPoint->point(),
                        parameters->minFreq(),
                        parameters->maxFreq(),
                        parameters->useNotes(),
                        derivMode,
                        parameters->useNegativeNotes());
}

void FunctionController::previousPoint()
{
    currentPoint->previous();
    audionotes->setNote(currentPoint->point(),
                        parameters->minFreq(),
                        parameters->maxFreq(),
                        parameters->useNotes(),
                        derivMode,
                        parameters->useNegativeNotes());
}

void FunctionController::interestingPointsfinished()
{
    gui->interestingPointFinished();
}

void FunctionController::updateLabel(QString text)
{
    gui->updateLabelText(text);
}

void FunctionController::previousPointInterest()
{
    pointsInterest->previousPoint();
}

void FunctionController::nextPointInterest()
{
    pointsInterest->nextPoint();
}

void FunctionController::setDerivativeMode(int mode)
{
    derivMode = mode;
    if (derivMode == 1)
        model->calculateDerivative();
    else if (derivMode == 2)
        model->calculateSecondDerivative();

    currentPoint->setDerivativeMode(derivMode);
    pointsInterest->setDerivativeMode(derivMode);
}

void FunctionController::sayX()
{
    double x = model->x(currentPoint->point());

    double Pow = pow(10.0, parameters->precisionDigits());
    x = round (x * Pow) / Pow;

    char c = 'f';
    QString value = QString::number(x, c, parameters->precisionDigits());
    textToSpeech->speak(value);
}

void FunctionController::sayY()
{
    if (model->isValid(currentPoint->point())) {
        double y = model->y(currentPoint->point());

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, parameters->precisionDigits());
        textToSpeech->speak(value);
    } else {
        textToSpeech->speak("Not defined");
    }
}

void FunctionController::getX()
{
    double x = model->x(currentPoint->point());

    double Pow = pow(10.0, parameters->precisionDigits());
    x = round (x * Pow) / Pow;

    char c = 'f';
    QString value = QString::number(x, c, parameters->precisionDigits());
    gui->updateLabelText(value);
}

void FunctionController::getY()
{
    if (model->isValid(currentPoint->point())) {
        double y = model->y(currentPoint->point());

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, parameters->precisionDigits());
        gui->updateLabelText(value);
    } else {
        gui->updateLabelText("Not defined");
    }
}

void FunctionController::incStep()
{
    currentPoint->incStep();
    showStep();
}

void FunctionController::decStep()
{
    currentPoint->decStep();
    showStep();
}

void FunctionController::showStep()
{
    double realStep = (double) currentPoint->step() / model->size() * (model->maxX() - model->minX());
    QString text = "Step is " + QString::number(realStep);
    textToSpeech->speak(text);
    updateLabel(text);
}

void FunctionController::previousFast()
{
    pointsInterest->previousPointFast();
}

void FunctionController::nextFast()
{
    pointsInterest->nextPointFast();
}

void FunctionController::firstPoint()
{
    stopSound();
    currentPoint->reset();
    textToSpeech->speak("starting point");
}

void FunctionController::lastPoint()
{
    stopSound();
    currentPoint->endPoint();
    textToSpeech->speak("ending point");
}

void FunctionController::sayDerivative()
{
    textToSpeech->speak(derivative());
}

void FunctionController::getDerivative()
{
    updateLabel(derivative());
}

QString FunctionController::derivative()
{
    QString value;
    if (model->isValid(currentPoint->point())) {

        if (derivMode == 0)
            model->refreshDerivative();

        double y = model->derivative(currentPoint->point());

        double Pow = pow(10.0, parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        value = QString::number(y, c, parameters->precisionDigits());
    } else {
       value = "Not defined";
    }

    return value;
}
