//
// Created by andershorgen on 2/22/18.
//

#ifndef RAIDMYDUNGEON_ABILITY_H
#define RAIDMYDUNGEON_ABILITY_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"

class Ability {
public:
    Ability(const char * path);
    virtual ~Ability() {}
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float gametick, GameObject &object) = 0;

protected:
    sf::Texture iconTexture;
    sf::Sprite  icon;
};


#endif //RAIDMYDUNGEON_ABILITY_H
