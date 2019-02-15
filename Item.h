//
// Created by andershorgen on 17/11/18.
//

#ifndef RAIDMYDUNGEON_ITEM_H
#define RAIDMYDUNGEON_ITEM_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Item {
public:
    Item();
    ~Item();
    virtual void draw(sf::RenderWindow &window) = 0;        //Needs to be pure virtual, e.g = 0
    virtual void update(float gametick) = 0;

protected:
    sf::Texture texture;                    // Texture of object
    sf::Sprite sprite;                    // Sprite
};


#endif //RAIDMYDUNGEON_ITEM_H
