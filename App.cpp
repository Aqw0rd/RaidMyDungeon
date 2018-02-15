//
// Created by andershorgen on 1/30/18.
//

#include "App.h"
#include "States/IntroState.h"
#include <SFML/Window/Event.hpp>


App::App()
{
    this->config = new Config();        //Creating a new pointer of Config
    //Creating a new SFML window
    this->window.create(sf::VideoMode(800,600), "Raid My Dungeon", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);         // Setting the target(max) framerate to 60
    // Pushing the first state to the state machine
    this->machine.pushState(new IntroState(this->config, this->window, this->machine));


}

App::~App()
{
    // Delete the config pointer when app is destructed.
    delete config;
}

void App::run()
{

    sf::Time gametick = clock.restart();        //Initializing the gametick
    while(this->machine.running)
    {
        gametick = clock.restart();             // Restarting the clock

        // Sending the gametick as milliseconds to the States update function
        machine.getState()->update(gametick.asMilliseconds());
        window.clear();                 // Clearing the SFML window
        machine.getState()->draw();     // Calling the states draw function
        window.display();               // Calling the display function of the window
    }
}