//
// Created by andershorgen on 2/23/18.
//

#include "Weapon.h"

Weapon::Weapon(const char * spritePath)
{
    texture.loadFromFile(spritePath);
    sprite.setTexture(texture);
}