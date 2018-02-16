//
// Created by andershorgen on 2/13/18.
//

#include <iostream>
#include "PlayState.h"
#include "../StateMachine.h"

PlayState::PlayState(Config* &config, sf::RenderWindow &window, StateMachine &machine)
        : State(config, window, machine)
{
    //this->config = config;
    //this->window = &window;
    //this->machine = &machine;

    // Could be its own state, loadstate
    if(!this->map.loadMap(this->config->getMapPath())){
        std::cout << "Couldnt load map" << std::endl;
    }


    std::cout << "Playstate" << std::endl;
}

PlayState::~PlayState() = default;

void PlayState::draw()
{
    this->map.draw(*window);
}

void PlayState::update(float gametick)
{
    sf::Event event;
    while( window->pollEvent(event ))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                machine->running = false;
                break;

            default:
                break;
        }
    }

}