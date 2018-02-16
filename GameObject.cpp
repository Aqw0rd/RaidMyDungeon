//
// Created by andershorgen on 2/15/18.
//

#include "GameObject.h"


sf::Vector2f GameObject::getPosition() const { return this->pos; }
sf::Vector2f GameObject::getVelocity() const { return this->vel; }
sf::Vector2f GameObject::getAcceleration() const { return this->acc; }

int GameObject::getHealth() const { return this->hp; }
int GameObject::getEnergy() const { return this->energy; }
int GameObject::getLvl() const { return this->lvl; }