#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include <QStateMachine>

class IStateMachine;

class StateMachine : public QObject
{
    Q_OBJECT
public:
    StateMachine(IStateMachine &iface);

signals:
    void evaluate();
    void functionError();
    void errorAccepted();
    void newGraph();
    void playPressed();
    void audioFinished();
    void nextPoint();
    void previousPoint();
    void sayX();
    void sayY();
    void previousPointInterest();
    void nextPointInterest();
    void interestingPointFinished();
    void previousFast();
    void nextFast();
    void firstPoint();
    void lastPoint();

private:
    IStateMachine &iface;
    QStateMachine machine;
    QState initialState, errorDisplayState, evaluateState, graphState,
    playSoundState, exploreState, interestingPointState, interestingPointStoppedState;

    void initStateMachine();
    void createInitialState();
    void initialStateActivated();
    void createEvaluateState();
    void evaluateStateActivated();
    void createErrorState();
    void errorDisplayStateActivated();
    void createGraphState();
    void graphStateActivated();
    void createPlaySoundState();
    void playSoundStateActivated();
    void playSoundStateDeactivated();
    void createExploreState();
    void exploreStateActivated();
    void exploreStateDeactivated();
    void createInterestingPointState();
    void interestingPointStateActivated();
    void interestingPointStateDeactivated();
    void createInterestingPointStoppedState();
    void interestingPointStoppedStateActivated();
    void interestingPointStoppedStateDeactivated();
};

#endif // STATEMACHINE_H
