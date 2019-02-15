//
// Created by andershorgen on 2/23/18.
//

#ifndef RAIDMYDUNGEON_IRONSWORD_H
#define RAIDMYDUNGEON_IRONSWORD_H


#include "../Weapon.h"

class IronSword : public Weapon {
public:
    IronSword(const char * path, GameObject &object);
    ~IronSword() = default;
    void draw(sf::RenderWindow &window) override;
    void strike() override;
    void update(float gametick) override;

protected:
    int itemlevel, damage;
    GameObject *object = nullptr;
    bool visible = false;
    sf::Vector2f pos;
    bool attack = false;
    int rotation = 0;
    int direction = GameObject::right;

};


#endif //RAIDMYDUNGEON_IRONSWORD_H
