//
// Created by andershorgen on 2/23/18.
//

#ifndef RAIDMYDUNGEON_MELEE_H
#define RAIDMYDUNGEON_MELEE_H


#include "../Ability.h"

class Melee : public Ability{
public:
    Melee(const char * path);
    virtual ~Melee() {};

protected:
    int baseDmg, energyCost;
};


#endif //RAIDMYDUNGEON_MELEE_H
