//
// Created by andershorgen on 1/30/18.
//

#include "StateMachine.h"

StateMachine::StateMachine()
{

}

StateMachine::~StateMachine() {}


/**
 * Takes a pointer of State and pushes it to the top of the state stack
 * @param *state
 */
void StateMachine::pushState(State *state)
{
    this->state.push_back(state);
}

/**
 * Takes the top of state stack, removes it from stack
 * and deletes the pointer.
 */
void StateMachine::popState()
{
    auto temp = this->state[this->state.size() - 1];
    this->state.pop_back();
    delete temp;
}


/**
 * Finds the last element of the state stack and
 * returns it
 * @return *state
 */
State* StateMachine::getState() const
{
    return this->state[this->state.size() - 1];
}

