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
            : State(config, window, machine), backGround(backGroundTexture), title(title_font)
{
    std::cout << "Introstate" << std::endl;
    //this->config = config;
    //this->window = &window;
    //this->machine = &machine;
    if (!backGroundTexture.loadFromFile("Resources/Images/intro.jpg"))
        std::cerr << "Failed to load intro background image" << std::endl;
    backGround.setTexture(backGroundTexture, true);
    backGround.setScale( sf::Vector2f((float) (config->getResolution().x) / (float) (backGroundTexture.getSize().x) ,
                         (float) (config->getResolution().y) / (float) (backGroundTexture.getSize().y)) );
}

IntroState::~IntroState()
{
    std::cout << "Deleting IntroState" << std::endl;
}

void IntroState::draw()
{
    this->window->draw(backGround);
}

void IntroState::update(float gametick)
{

    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            machine->running = false;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Space)
                machine->pushState(new MainMenuState(config, *window, *machine));
        }
    }

}
