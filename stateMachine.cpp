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

    //    exploreState.addTransition(this, &MainWindow::evaluate, &evaluateState);
    //    exploreState.addTransition(this, &MainWindow::newgraph, &graphReadyState);
    //    exploreState.addTransition(this, &MainWindow::playPressed, &playSoundState);
    //    exploreState.addTransition(this, &MainWindow::previousPointInterest, &interestingPointState);
    //    exploreState.addTransition(this, &MainWindow::nextPointInterest, &interestingPointState);
    //    //exploreState.addTransition(this, &MainWindow::previousFast, &exploreState);
    //    //exploreState.addTransition(this, &MainWindow::nextFast, &exploreState);
    //    connect(&exploreState, &QState::entered, this, &MainWindow::exploreStateActivated);
    //    connect(&exploreState, &QState::exited, this, &MainWindow::exploreStateDeactivated);


    //    interestingPointState.addTransition(this, &MainWindow::evaluate, &evaluateState);
    //    interestingPointState.addTransition(this, &MainWindow::functionError, &initialState);
    //    interestingPointState.addTransition(this, &MainWindow::playPressed, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::newgraph, &graphReadyState);

    //    interestingPointState.addTransition(this, &MainWindow::nextPoint, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::previousPoint, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::sayX, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::sayY, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::previousFast, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::nextFast, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::firstPoint, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::lastPoint, &exploreState);
    //    interestingPointState.addTransition(this, &MainWindow::interestingPointFinished, &interestingPointStoppedState);

    //    connect(&interestingPointState, &QState::entered, this, &MainWindow::interestingPointStateActivated);
    //    connect(&interestingPointState, &QState::exited, this, &MainWindow::interestingPointStateDeactivated);

    //    interestingPointStoppedState.addTransition(this, &MainWindow::evaluate, &evaluateState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::functionError, &initialState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::playPressed, &playSoundState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::newgraph, &graphReadyState);

    //    interestingPointStoppedState.addTransition(this, &MainWindow::nextPoint, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::previousPoint, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::sayX, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::sayY, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::previousPointInterest, &interestingPointState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::nextPointInterest, &interestingPointState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::previousFast, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::nextFast, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::firstPoint, &exploreState);
    //    interestingPointStoppedState.addTransition(this, &MainWindow::lastPoint, &exploreState);


    //    connect(&interestingPointStoppedState, &QState::entered, this, &MainWindow::interestingPointStoppedStateActivated);
    //    connect(&interestingPointStoppedState, &QState::exited, this, &MainWindow::interestingPointStoppedStateDeactivated);


    machine.addState(&exploreState);
    machine.addState(&interestingPointState);
    machine.addState(&interestingPointStoppedState);
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
