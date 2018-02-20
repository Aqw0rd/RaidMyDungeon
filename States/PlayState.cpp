//
// Created by andershorgen on 2/13/18.
//

#include <iostream>
#include "PlayState.h"
#include "../StateMachine.h"

PlayState::PlayState(Config* &config, sf::RenderWindow &window, StateMachine &machine)
        : State(config, window, machine)
{
    if(!this->map.loadMap(this->config->getMapPath())){
        std::cout << "Couldnt load map" << std::endl;
    }

    player = new Player(sf::Vector2f(100,100), 100,100,1, 1.5f,"Resources/Sprites/Anders.png", 16, 16);

    std::cout << "Playstate" << std::endl;
}

PlayState::~PlayState()
{
    delete player;
}

void PlayState::draw()
{
    this->map.draw(*window);
    this->player->draw(*window);
}

void PlayState::update(float gametick)
{
    sf::Event event;
    while( window->pollEvent(event ))
    {
        this->player->eventHandler(event);
        switch (event.type)
        {
            case sf::Event::Closed:
                machine->running = false;
                break;

            default:
                break;
        }
    }

    this->player->update(gametick);


}