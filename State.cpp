//
// Created by andershorgen on 1/30/18.
//

#include "State.h"

State::State(Config *&config, sf::RenderWindow &window, StateMachine &machine)
{
    this->config = config;
    this->window = &window;
    this->machine = &machine;
}