#ifndef ISTATEMACHINE_H
#define ISTATEMACHINE_H

class StateMachine;

class IStateMachine
{
public:
    virtual void addStateMachine(StateMachine *stateMachine) = 0;
    virtual void initialStateActivated() = 0;
    virtual void evaluateStateActivated() = 0;
    virtual void errorStateActivated() = 0;
    virtual void graphStateActivated() = 0;
    virtual void playSoundStateActivated() = 0;
    virtual void playSoundStateDeactivated() = 0;
    virtual void exploreStateActivated() = 0;
    virtual void exploreStateDeactivated() = 0;
    virtual void interestingPointStateActivated() = 0;
    virtual void interestingPointStateDeactivated() = 0;
    virtual void interestingPointStoppedStateActivated() = 0;
    virtual void interestingPointStoppedStateDeactivated() = 0;
};

#endif // ISTATEMACHINE_H