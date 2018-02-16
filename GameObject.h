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
    virtual void draw(sf::RenderWindow &window);
    virtual void update(float gametick);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;

    int getHealth() const;
    int getEnergy() const;
    int getLvl() const;

protected:
    sf::Vector2f pos, vel, acc;      // Position, velocity and acceleration of object
    int hp, energy, lvl;            // Stats of object
    sf::Texture texture;            // Texture of object
    sf::Sprite sprite;              // Sprite
};


#endif //RAIDMYDUNGEON_GAMEOBJECT_H
