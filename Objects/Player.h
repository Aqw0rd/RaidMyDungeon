//
// Created by andershorgen on 2/17/18.
//

#ifndef RAIDMYDUNGEON_PLAYER_H
#define RAIDMYDUNGEON_PLAYER_H


#include <SFML/Window/Event.hpp>
#include "../GameObject.h"
#include "../Items/Weapon.h"

class Player : public GameObject{
public:
    Player(sf::Vector2f pos, int maxHp, int maxEnergy, int lvl, float speed, const char *texturePath, int width, int height);
    //virtual ~Player();
    void draw(sf::RenderWindow &window) override;
    void update(float gametick) override;
    void eventHandler(sf::Event event);
    void movement();
    void animation(float gametick);

protected:
    bool keys[4] = {false,false,false,false};
    int animationTime = 80, animationCounter = 0;
    bool walking = false;
    Weapon *weapon;
};


#endif //RAIDMYDUNGEON_PLAYER_H
