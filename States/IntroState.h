//
// Created by andershorgen on 1/30/18.
//

#ifndef RAIDMYDUNGEON_INTROSTATE_H
#define RAIDMYDUNGEON_INTROSTATE_H


#include "../State.h"
#include "../StateMachine.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>

class IntroState : public State {
public:
    IntroState(Config* &config, sf::RenderWindow &window, StateMachine &machine);
    ~IntroState();
    void draw() override;
    void update(float gametick) override;

protected:
    sf::Texture backGroundTexture;
    sf::Sprite backGround;
    sf::Text title;
    sf::Font title_font;
};


#endif //RAIDMYDUNGEON_INTROSTATE_H
