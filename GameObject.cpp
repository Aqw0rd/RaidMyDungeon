//
// Created by andershorgen on 2/15/18.
//

#include <stdexcept>
#include "GameObject.h"


GameObject::GameObject(sf::Vector2f pos, int maxHp, int maxEnergy, int lvl, float speed, const char *texturePath, int width, int height)
{
    // Init stats of the gameobject, if the gameobject is f.ex a stone, stats are set to 0 or whats fitting
    this->pos = pos;
    this->maxHp = maxHp;
    this->maxEnergy = maxEnergy;
    this->hp = maxHp;
    this->energy = maxEnergy;
    this->lvl = lvl;
    this->width = width;
    this->height = height;
    this->speed = speed;

    int scale = 2;
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture: " + std::string(texturePath));
    }
    tilewidth = texture.getSize().x / width;
    tileheight = texture.getSize().y / height;

    this->sprite.resize(tilewidth);                     // Creating the spritesheet
    for(int x = 0; x < tilewidth; x++){
        this->sprite[x].reserve(tileheight);
        for(int y = 0; y < tileheight; y++){
            this->sprite[x].emplace_back(texture);
            this->sprite[x][y].setTextureRect(sf::IntRect(sf::Vector2i(x*width, y*height), sf::Vector2i(width, height)));
            this->sprite[x][y].scale(sf::Vector2f(scale, scale));
        }
    }

}

GameObject::~GameObject() = default;

sf::Vector2f GameObject::getPosition() const { return this->pos; }
sf::Vector2f GameObject::getVelocity() const { return this->vel; }
sf::Vector2f GameObject::getAcceleration() const { return this->acc; }
int GameObject::getDirection() const { return this->spriteY; }

int GameObject::getHealth() const { return this->hp; }
int GameObject::getEnergy() const { return this->energy; }
int GameObject::getLvl() const { return this->lvl; }
