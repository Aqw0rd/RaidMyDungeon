//
// Created by andershorgen on 2/23/18.
//

#ifndef RAIDMYDUNGEON_NORMALATTACK_H
#define RAIDMYDUNGEON_NORMALATTACK_H


#include "../Melee.h"

class NormalAttack : public Melee{
public:
    NormalAttack(const char * path);
    ~NormalAttack();
    void draw(sf::RenderWindow &window) override ;
    void update(float gametick, GameObject &object) override;

};


#endif //RAIDMYDUNGEON_NORMALATTACK_H
