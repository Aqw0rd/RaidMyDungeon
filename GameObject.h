//
// Created by andershorgen on 2/15/18.
//

#ifndef RAIDMYDUNGEON_GAMEOBJECT_H
#define RAIDMYDUNGEON_GAMEOBJECT_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
public:
    GameObject(sf::Vector2f pos, int maxHp, int maxEnergy, int lvl , float speed, const char * texturePath, int width, int height);
    ~GameObject();
    virtual void draw(sf::RenderWindow &window) = 0;        //Needs to be pure virtual, e.g = 0
    virtual void update(float gametick) = 0;

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;

    int getHealth() const;
    int getEnergy() const;
    int getLvl() const;

protected:
    sf::Vector2f pos, vel, acc;             // Position, velocity and acceleration of object
    int maxHp, maxEnergy;                   // Stats
    int hp, energy, lvl;                    // stats of object
    float speed;
    sf::Texture texture;                    // Texture of object
    sf::Sprite** sprite;                    // Sprite
    enum direction { left = 0, right = 2, up = 1, down = 3};
    int spriteX = 0, spriteY = 0;           // Spritesheet coords
    int width, height;
    int tileheight, tilewidth;

};


#endif //RAIDMYDUNGEON_GAMEOBJECT_H
