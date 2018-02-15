//
// Created by andershorgen on 2/4/18.
//

#include <iostream>
#include "MainMenuState.h"
#include "../Map.h"
#include "PlayState.h"

/**
 * Constructor of MainMenuState,
 * Used as the init of the state.
 * @param config    Pointer and reference to config object
 * @param window    Reference to main window
 * @param machine   Reference to state machine
 */
MainMenuState::MainMenuState(Config* &config, sf::RenderWindow &window, StateMachine &machine)
{
    std::cout << "MainMenu" << std::endl;
    this->config = config;
    this->window = &window;
    this->machine = &machine;

    this->menuIndex = 0;

    if(!this->title_font.loadFromFile("Resources/Fonts/AmaticSC-Regular.ttf")) {}

    this->title.setFont(title_font);
    this->title.setString("Main Menu");
    this->title.setColor(sf::Color::Yellow);
    this->title.setPosition((this->config->getResolution().x/2) - this->title.getCharacterSize(), 20);

    this->options[0].setFont(title_font);
    this->options[0].setString("Play");
    this->options[0].setColor(sf::Color::Yellow);
    this->options[0].setPosition((this->config->getResolution().x/2) - this->title.getCharacterSize(), 200);

    this->options[1].setFont(title_font);
    this->options[1].setString("Exit");
    this->options[1].setColor(sf::Color::Yellow);
    this->options[1].setPosition((this->config->getResolution().x/2) - this->title.getCharacterSize(), 300);


}

/**
 * Draw function, where all the MainMenu items are drawn
 */
void MainMenuState::draw()
{
    this->window->draw(title);


    //Draw the options elements
    for(auto &opt: options) {
        this->window->draw(opt);
    }

}

/**
 * Update function, used for updating which selection of the menu items are
 * currently active.
 * @param gametick
 */
void MainMenuState::update(float gametick)
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
                if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    options[menuIndex].setColor(sf::Color::Yellow);
                    this->menuIndex--;
                    if(this->menuIndex < 0 )
                        this->menuIndex = sizeof(options)/sizeof(*options) - 1;
                }

                if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    options[menuIndex].setColor(sf::Color::Yellow);
                    this->menuIndex++;
                    if(this->menuIndex >= sizeof(options)/sizeof(*options))
                        this->menuIndex = 0;
                }

                if(event.key.code == sf::Keyboard::Return)
                {
                    switch(menuIndex){
                        case 0:
                            this->config->setMap("Resources/Levels/Dungeon 1.json");
                            machine->pushState(new PlayState(config, *window, *machine));
                            std::cout << "Play" << std::endl;
                            break;
                        case 1:
                            machine->running = false;
                            break;

                        default:
                            break;
                    }
                }

        }
    }


    options[menuIndex].setColor(sf::Color::Red);

}
