//
// Created by andershorgen on 2/23/18.
//

#include <stdexcept>
#include <string>
#include "Weapon.h"

Weapon::Weapon(const char * spritePath)
    : sprite(texture)
{
    if (!texture.loadFromFile(spritePath)) {
        throw std::runtime_error("Failed to load weapon texture: " + std::string(spritePath));
    }
    sprite.setTexture(texture, true);
}