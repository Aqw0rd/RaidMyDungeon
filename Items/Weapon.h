//
// Created by andershorgen on 2/23/18.
//

#ifndef RAIDMYDUNGEON_WEAPON_H
#define RAIDMYDUNGEON_WEAPON_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../GameObject.h"

class Weapon {
public:
    Weapon(const char * spritePath);
    virtual ~Weapon() = default;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float gametick, GameObject &object) = 0;

protected:
    sf::Texture texture;
    sf::Sprite sprite;
};


#endif //RAIDMYDUNGEON_WEAPON_H
