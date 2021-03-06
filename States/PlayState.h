//
// Created by andershorgen on 2/13/18.
//

#ifndef RAIDMYDUNGEON_PLAYSTATE_H
#define RAIDMYDUNGEON_PLAYSTATE_H


#include "../State.h"
#include "../Objects/Player.h"

class PlayState : public State {
public:
    PlayState(Config* &config, sf::RenderWindow &window, StateMachine &machine);
    ~PlayState();
    void draw() override ;
    void update(float gametick) override;

protected:
    Map map;
    Player* player;
};


#endif //RAIDMYDUNGEON_PLAYSTATE_H
