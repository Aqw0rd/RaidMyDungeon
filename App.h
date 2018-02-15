//
// Created by andershorgen on 1/30/18.
//

#ifndef RAIDMYDUNGEON_APP_H
#define RAIDMYDUNGEON_APP_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Config.h"
#include "StateMachine.h"

class App {
public:
    App();
    ~App();
    void run();

protected:
    Config* config;             // Pointer to Config
    sf::RenderWindow window;    // Window object
    StateMachine machine;       // State Machine object
    sf::Clock clock;            //SFML clock
};


#endif //RAIDMYDUNGEON_APP_H
