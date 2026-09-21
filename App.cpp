//
// Created by andershorgen on 1/30/18.
//

#include "App.h"
#include "States/IntroState.h"
#include "ItemDatabase.h"
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <iostream>


App::App()
{
    this->config = new Config();        //Creating a new pointer of Config
    ItemDatabase::loadFromFile("Resources/Items/items.json");   // Load all item/gear/weapon definitions once at startup
    //Creating a new SFML window
    this->window.create(sf::VideoMode(sf::Vector2u(800, 600)), "Raid My Dungeon", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);         // Setting the target(max) framerate to 60
    // Pushing the first state to the state machine
    this->machine.pushState(new IntroState(this->config, this->window, this->machine));


}

App::~App()
{
    std::cout << "Deleting App" << std::endl;
    // Delete the config pointer when app is destructed.
    delete config;

}

void App::run()
{

    sf::Time gametick = clock.restart();        //Initializing the gametick
    while(this->machine.running)
    {
        gametick = clock.restart();             // Restarting the clock
        float fps = 1.0f / (gametick.asSeconds());

        std::stringstream ss;
        ss << "Raid My Dungeon - FPS: " << (int)fps;
        window.setTitle(ss.str());

        State* state = machine.getState();
        if (!state) break;              // State stack ran out; nothing left to run

        // Sending the gametick as milliseconds to the States update function
        state->update(gametick.asMilliseconds());

        // update() may have popped (and deleted) that very state, so re-fetch
        // the current top of the stack rather than reusing the old pointer.
        state = machine.getState();
        if (!state) break;

        window.clear();                 // Clearing the SFML window
        state->draw();                  // Calling the states draw function
        window.display();               // Calling the display function of the window
    }
}