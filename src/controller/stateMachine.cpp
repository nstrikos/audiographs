#include "stateMachine.h"
#include "ifaces/IStateMachine.h"

#include <QDebug>

StateMachine::StateMachine(IStateMachine &iface) : iface(iface)
{
    iface.addStateMachine(this);
    initStateMachine();
}

void StateMachine::initStateMachine()
{
    createInitialState();
    createEvaluateState();
    createErrorState();
    createGraphState();
    createPlaySoundState();
    createExploreState();
    createInterestingPointState();
    createInterestingPointStoppedState();

    machine.setInitialState(&initialState);
    machine.start();
}

void StateMachine::createInitialState()
{
    initialState.addTransition(this, &StateMachine::evaluate, &evaluateState);
    initialState.addTransition(this, &StateMachine::newGraph, &graphState);
    initialState.addTransition(this, &StateMachine::playPressed, &errorDisplayState);
    connect(&initialState, &QState::entered, this, &StateMachine::initialStateActivated);

    machine.addState(&initialState);
}

void StateMachine::initialStateActivated()
{
    qDebug() << "state machine: initial state";
    iface.initialStateActivated();
}

void StateMachine::createEvaluateState()
{
    evaluateState.addTransition(this, &StateMachine::functionError, &initialState);
    evaluateState.addTransition(this, &StateMachine::newGraph, &graphState);
    connect(&evaluateState, &QState::entered, this, &StateMachine::evaluateStateActivated);

    machine.addState(&evaluateState);
}

void StateMachine::evaluateStateActivated()
{
    qDebug() << "state machine: evaluate state";
    iface.evaluateStateActivated();
}

void StateMachine::createErrorState()
{
    errorDisplayState.addTransition(this, &StateMachine::errorAccepted, &initialState);
    connect(&errorDisplayState, &QState::entered, this, &StateMachine::errorDisplayStateActivated);

    machine.addState(&errorDisplayState);
}

void StateMachine::errorDisplayStateActivated()
{
    qDebug() << "state machine: error display state";
    iface.errorStateActivated();
}

void StateMachine::createGraphState()
{
    graphState.addTransition(this, &StateMachine::functionError, &initialState);
    graphState.addTransition(this, &StateMachine::evaluate, &evaluateState);
    graphState.addTransition(this, &StateMachine::newGraph, &graphState);
    graphState.addTransition(this, &StateMachine::playPressed, &playSoundState);

    graphState.addTransition(this, &StateMachine::nextPoint, &exploreState);
    graphState.addTransition(this, &StateMachine::previousPoint, &exploreState);
    graphState.addTransition(this, &StateMachine::sayX, &exploreState);
    graphState.addTransition(this, &StateMachine::sayY, &exploreState);
    graphState.addTransition(this, &StateMachine::previousPointInterest, &interestingPointState);
    graphState.addTransition(this, &StateMachine::nextPointInterest, &interestingPointState);
    graphState.addTransition(this, &StateMachine::previousFast, &exploreState);
    graphState.addTransition(this, &StateMachine::nextFast, &exploreState);
    graphState.addTransition(this, &StateMachine::firstPoint, &exploreState);
    graphState.addTransition(this, &StateMachine::lastPoint, &exploreState);

    connect(&graphState, &QState::entered, this, &StateMachine::graphStateActivated);

    machine.addState(&graphState);
}

void StateMachine::graphStateActivated()
{
    qDebug() << "state machine: graph state";
    iface.graphStateActivated();
}

void StateMachine::createPlaySoundState()
{
    playSoundState.addTransition(this, &StateMachine::evaluate, &evaluateState);
    playSoundState.addTransition(this, &StateMachine::functionError, &initialState);
    playSoundState.addTransition(this, &StateMachine::playPressed, &graphState);
    playSoundState.addTransition(this, &StateMachine::newGraph, &graphState);
    playSoundState.addTransition(this, &StateMachine::audioFinished, &graphState);

    playSoundState.addTransition(this, &StateMachine::nextPoint, &exploreState);
    playSoundState.addTransition(this, &StateMachine::previousPoint, &exploreState);
    playSoundState.addTransition(this, &StateMachine::previousPointInterest, &interestingPointState);
    playSoundState.addTransition(this, &StateMachine::nextPointInterest, &interestingPointState);
    playSoundState.addTransition(this, &StateMachine::previousFast, &exploreState);
    playSoundState.addTransition(this, &StateMachine::nextFast, &exploreState);
    playSoundState.addTransition(this, &StateMachine::sayX, &exploreState);
    playSoundState.addTransition(this, &StateMachine::sayY, &exploreState);
    playSoundState.addTransition(this, &StateMachine::firstPoint, &exploreState);
    playSoundState.addTransition(this, &StateMachine::lastPoint, &exploreState);

    connect(&playSoundState, &QState::entered, this, &StateMachine::playSoundStateActivated);
    connect(&playSoundState, &QState::exited, this, &StateMachine::playSoundStateDeactivated);

    machine.addState(&playSoundState);
}

void StateMachine::playSoundStateActivated()
{
    qDebug() << "state machine: play sound state";
    iface.playSoundStateActivated();
}

void StateMachine::playSoundStateDeactivated()
{
    qDebug() << "state machine: play sound state deactivated";
    iface.playSoundStateDeactivated();
}

void StateMachine::createExploreState()
{
    exploreState.addTransition(this, &StateMachine::evaluate, &evaluateState);
    exploreState.addTransition(this, &StateMachine::newGraph, &graphState);
    exploreState.addTransition(this, &StateMachine::playPressed, &playSoundState);
    exploreState.addTransition(this, &StateMachine::previousPointInterest, &interestingPointState);
    exploreState.addTransition(this, &StateMachine::nextPointInterest, &interestingPointState);
    connect(&exploreState, &QState::entered, this, &StateMachine::exploreStateActivated);
    connect(&exploreState, &QState::exited, this, &StateMachine::exploreStateDeactivated);

    machine.addState(&exploreState);
}

void StateMachine::exploreStateActivated()
{
    qDebug() << "state machine: explore state";
    iface.exploreStateActivated();

}

void StateMachine::exploreStateDeactivated()
{
    qDebug() << "state machine: explore state deactivated";
    iface.exploreStateDeactivated();
}

void StateMachine::createInterestingPointState()
{
    interestingPointState.addTransition(this, &StateMachine::evaluate, &evaluateState);
    interestingPointState.addTransition(this, &StateMachine::functionError, &initialState);
    interestingPointState.addTransition(this, &StateMachine::playPressed, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::newGraph, &graphState);

    interestingPointState.addTransition(this, &StateMachine::nextPoint, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::previousPoint, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::sayX, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::sayY, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::previousFast, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::nextFast, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::firstPoint, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::lastPoint, &exploreState);
    interestingPointState.addTransition(this, &StateMachine::interestingPointFinished, &interestingPointStoppedState);

    connect(&interestingPointState, &QState::entered, this, &StateMachine::interestingPointStateActivated);
    connect(&interestingPointState, &QState::exited, this, &StateMachine::interestingPointStateDeactivated);

    machine.addState(&interestingPointState);
}

void StateMachine::interestingPointStateActivated()
{
    qDebug() << "state machine: interesting point state";
    iface.interestingPointStateActivated();
}

void StateMachine::interestingPointStateDeactivated()
{
    qDebug() << "state machine: interesting point state deactivated";
    iface.interestingPointStateDeactivated();
}

void StateMachine::createInterestingPointStoppedState()
{
    interestingPointStoppedState.addTransition(this, &StateMachine::evaluate, &evaluateState);
    interestingPointStoppedState.addTransition(this, &StateMachine::functionError, &initialState);
    interestingPointStoppedState.addTransition(this, &StateMachine::playPressed, &playSoundState);
    interestingPointStoppedState.addTransition(this, &StateMachine::newGraph, &graphState);

    interestingPointStoppedState.addTransition(this, &StateMachine::nextPoint, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::previousPoint, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::sayX, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::sayY, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::previousPointInterest, &interestingPointState);
    interestingPointStoppedState.addTransition(this, &StateMachine::nextPointInterest, &interestingPointState);
    interestingPointStoppedState.addTransition(this, &StateMachine::previousFast, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::nextFast, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::firstPoint, &exploreState);
    interestingPointStoppedState.addTransition(this, &StateMachine::lastPoint, &exploreState);


    connect(&interestingPointStoppedState, &QState::entered, this, &StateMachine::interestingPointStoppedStateActivated);
    connect(&interestingPointStoppedState, &QState::exited, this, &StateMachine::interestingPointStoppedStateDeactivated);

    machine.addState(&interestingPointStoppedState);
}

void StateMachine::interestingPointStoppedStateActivated()
{
    qDebug() << "state machine: interesting point stopped state";
    iface.interestingPointStoppedStateActivated();
}

void StateMachine::interestingPointStoppedStateDeactivated()
{
    qDebug() << "state machine: interesting point stopped state deactivated";
    iface.interestingPointStoppedStateDeactivated();
}
