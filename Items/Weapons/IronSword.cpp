//
// Created by andershorgen on 2/23/18.
//

#include "IronSword.h"

IronSword::IronSword(const char * path, GameObject &object) : Weapon(path)
{
    this->x = object.getPosition().x;
    this->y = object.getPosition().y;
}

void IronSword::draw(sf::RenderWindow &window)
{
    if(this->visible){
        window.draw(this->sprite);
    }
}

void IronSword::update(float gametick, GameObject &object)
{
    this->x = object.getPosition().x;
    this->y = object.getPosition().y;
}
