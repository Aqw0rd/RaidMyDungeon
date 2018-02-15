//
// Created by andershorgen on 1/30/18.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include "IntroState.h"
#include "MainMenuState.h"

/**
 * Constructor used for initializing the introstate, setting the background etc
 * @param config
 * @param window
 * @param machine
 */
IntroState::IntroState(Config* &config, sf::RenderWindow &window, StateMachine &machine)
{
    std::cout << "Introstate" << std::endl;
    this->config = config;
    this->window = &window;
    this->machine = &machine;
    backGroundTexture.loadFromFile("Resources/Images/intro.jpg");
    backGround.setTexture(backGroundTexture, true);
    backGround.setScale( (float) (config->getResolution().x) / (float) (backGroundTexture.getSize().x) ,
                         (float) (config->getResolution().y) / (float) (backGroundTexture.getSize().y) );
}

IntroState::~IntroState() = default;

void IntroState::draw()
{
    this->window->draw(backGround);
}

void IntroState::update(float gametick)
{

    sf::Event event;
    while( window->pollEvent( event ))
    {
        switch( event.type )
        {
            case sf::Event::Closed:
                machine->running = false;
                break;

            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Space)
                    machine->pushState(new MainMenuState(config, *window, *machine));
            default:
                break;
        }
    }

}
