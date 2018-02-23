//
// Created by andershorgen on 2/23/18.
//

#ifndef RAIDMYDUNGEON_IRONSWORD_H
#define RAIDMYDUNGEON_IRONSWORD_H


#include "../Weapon.h"

class IronSword : Weapon {
public:
    IronSword(const char * path, GameObject &object);
    ~IronSword() = default;
    void draw(sf::RenderWindow &window) override;
    void update(float gametick, GameObject &object) override;

protected:
    int itemlevel, damage;
    bool visible = false;
    float x = 0, y = 0;

};


#endif //RAIDMYDUNGEON_IRONSWORD_H
