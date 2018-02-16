//
// Created by andershorgen on 1/30/18.
//

#ifndef RAIDMYDUNGEON_STATE_H
#define RAIDMYDUNGEON_STATE_H


#include "Config.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class StateMachine;     // Since State needs to know of StateMachine, and StateMachine needs to know of State
                        // This had to been done.
class State {
public:
    State(Config* &config, sf::RenderWindow &window, StateMachine &machine);
    ~State() = default;
    virtual void update(float gametick) = 0;    // Update function for the states
    virtual void draw() = 0;                    // Draw function for the states
protected:
    // These Objects/variables needs to be accessed for all states, and not recreated.
    //Hence pointers
    Config* config;
    sf::RenderWindow* window;
    StateMachine* machine;

};


#endif //RAIDMYDUNGEON_STATE_H
