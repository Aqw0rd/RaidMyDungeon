//
// Created by andershorgen on 2/4/18.
//

#include <iostream>
#include "MainMenuState.h"
#include "PlayState.h"

/**
 * Constructor of MainMenuState,
 * Used as the init of the state.
 * @param config    Pointer and reference to config object
 * @param window    Reference to main window
 * @param machine   Reference to state machine
 */
MainMenuState::MainMenuState(Config* &config, sf::RenderWindow &window, StateMachine &machine)
        : State(config, window, machine), title(title_font), options{sf::Text(title_font), sf::Text(title_font)}
{
    std::cout << "MainMenu" << std::endl;
    //this->config = config;
    //this->window = &window;
    //this->machine = &machine;

    this->menuIndex = 0;

    if(!this->title_font.openFromFile("Resources/Fonts/AmaticSC-Regular.ttf")) {}

    this->title.setString("Main Menu");
    this->title.setFillColor(sf::Color::Yellow);
    this->title.setPosition(sf::Vector2f((this->config->getResolution().x / 2.0f) - this->title.getCharacterSize(), 20));

    this->options[0].setString("Play");
    this->options[0].setFillColor(sf::Color::Yellow);
    this->options[0].setPosition(sf::Vector2f((this->config->getResolution().x / 2.0f) - this->title.getCharacterSize(), 200));

    this->options[1].setString("Exit");
    this->options[1].setFillColor(sf::Color::Yellow);
    this->options[1].setPosition(sf::Vector2f((this->config->getResolution().x / 2.0f) - this->title.getCharacterSize(), 300));


}

MainMenuState::~MainMenuState()
{
    std::cout << "Deleting MainMenuState" << std::endl;
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
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            machine->running = false;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if(keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::Up)
            {
                options[menuIndex].setFillColor(sf::Color::Yellow);
                this->menuIndex--;
                if(this->menuIndex < 0 )
                    this->menuIndex = sizeof(options)/sizeof(*options) - 1;
            }

            if(keyPressed->code == sf::Keyboard::Key::S || keyPressed->code == sf::Keyboard::Key::Down)
            {
                options[menuIndex].setFillColor(sf::Color::Yellow);
                this->menuIndex++;
                if(this->menuIndex >= (int)(sizeof(options)/sizeof(*options)))
                    this->menuIndex = 0;
            }

            if(keyPressed->code == sf::Keyboard::Key::Enter)
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


    options[menuIndex].setFillColor(sf::Color::Red);

}
