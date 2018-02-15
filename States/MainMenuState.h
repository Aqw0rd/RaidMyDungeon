//
// Created by andershorgen on 2/4/18.
//

#ifndef RAIDMYDUNGEON_MAINMENUSTATE_H
#define RAIDMYDUNGEON_MAINMENUSTATE_H

#include "../State.h"
#include "../StateMachine.h"
#include "../Map.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

class MainMenuState : public State {
public:
    MainMenuState(Config* &config, sf::RenderWindow &window, StateMachine &machine);
    ~MainMenuState() = default;
    void draw() override;                       // See state.h
    void update(float gametick) override;       // See state.h

protected:
    sf::Text title;         // Menu Title
    sf::Text options[2];    // Menu options
    sf::Font title_font;    // Font of title
    sf::Font optionsFont;   // Options Font
    int menuIndex;          // Helping variable, which option is selected.
};


#endif //RAIDMYDUNGEON_MAINMENUSTATE_H
