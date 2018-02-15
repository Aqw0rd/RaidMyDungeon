//
// Created by andershorgen on 1/30/18.
//

#ifndef RAIDMYDUNGEON_STATEMACHINE_H
#define RAIDMYDUNGEON_STATEMACHINE_H


#include "State.h"

class StateMachine {
public:
    StateMachine();
    ~StateMachine();
    void pushState(State* state);
    void popState();
    bool running = true;        // If the machine is currently running
    State* getState() const;
protected:
    std::vector<State*> state;  // State stack

};



#endif //RAIDMYDUNGEON_STATEMACHINE_H
