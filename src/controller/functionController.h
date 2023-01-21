#ifndef FUNCTIONCONTROLLER_H
#define FUNCTIONCONTROLLER_H

#include "ifaces/IFunctionModel.h"
#include "ifaces/IGui.h"
#include "ifaces/IDragZoom.h"
#include "ifaces/ICurrentPoint.h"
#include "ifaces/IAudio.h"
#include "ifaces/IAudioNotes.h"
#include "ifaces/IPointsInterest.h"
#include "ifaces/IStateMachine.h"

class FunctionModel;
class IMainWindow;
class CurrentPoint;
class DragHandler;
class FunctionZoomer;
class Audio;
class Audionotes;
class Parameters;
class PointsInterest;
class TextToSpeech;
class StateMachine;

class FunctionController:
        public IFunctionModel,
        public IGui,
        public IDragZoom,
        public ICurrentPoint,
        public IAudio,
        public IAudioNotes,
        public IPointsInterest,
        public IStateMachine
{
public:
    FunctionController();
    virtual ~FunctionController();
    void addModel(FunctionModel *model) override;
    void addGui(IMainWindow *gui) override;
    void addDragHandler(DragHandler *dragHandler) override;
    void addZoomer(FunctionZoomer *zoomer) override;
    void addCurrentPoint(CurrentPoint *currentPoint) override;
    void addAudio(Audio *audio) override;
    void addAudionotes(AudioNotes *audionotes) override;
    void addPointsInterest(PointsInterest *pointsInterest) override;
    void addStateMachine(StateMachine *tateMachine) override;
    void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY) override;
    void newGraph(Points *points, double minX, double maxX, double minY, double maxY) override;
    void error(QString error) override;
    void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY) override;
    void startDrag(int x , int y) override;
    void drag(int diffX, int diffY, int width, int height) override;
    void zoom(double delta) override;
    void newInputValues(double minX, double maxX, double minY, double maxY) override;
    void newCurrentPoint(double x, double y) override;
    void audioFinished() override;
    void audioNotesFinished() override;
    void playSound() override;
    void stopSound() override;
    void nextPoint() override;
    void previousPoint() override;
    void interestingPointsfinished() override;
    void updateLabel(QString text) override;
    void previousPointInterest() override;
    void nextPointInterest() override;
    void setDerivativeMode(int mode) override;
    void sayX() override;
    void sayY() override;
    void getX() override;
    void getY() override;
    void incStep() override;
    void decStep() override;
    void previousFast() override;
    void nextFast() override;
    void firstPoint() override;
    void lastPoint() override;
    void stopAtZeroChanged() override;
    void sayDerivative() override;
    void getDerivative() override;
    void evaluate() override;
    void newGraph() override;
    void functionError() override;
    void errorAccepted() override;
    void playPressed() override;
    void initialStateActivated() override;
    void evaluateStateActivated() override;
    void errorStateActivated() override;
    void graphStateActivated() override;
    void playSoundStateActivated() override;
    void playSoundStateDeactivated() override;
    void exploreStateActivated() override;
    void exploreStateDeactivated() override;
    void interestingPointStateActivated() override;
    void interestingPointStateDeactivated() override;
    void interestingPointStoppedStateActivated() override;
    void interestingPointStoppedStateDeactivated() override;

private:
    IMainWindow *gui;
    FunctionModel *model;
    DragHandler *dragHandler;
    FunctionZoomer *zoomer;
    CurrentPoint *currentPoint;
    Audio *audio;
    AudioNotes *audionotes;
    PointsInterest *pointsInterest;
    Parameters *parameters;
    TextToSpeech *textToSpeech;
    StateMachine *stateMachine;

    void startAudio();
    void startNotes();
    void showStep();
    QString derivative();
};

#endif // FUNCTIONCONTROLLER_H
