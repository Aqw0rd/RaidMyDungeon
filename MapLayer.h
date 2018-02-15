//
// Created by andershorgen on 2/9/18.
//

#ifndef RAIDMYDUNGEON_MAPLAYER_H
#define RAIDMYDUNGEON_MAPLAYER_H


#include <SFML/Graphics/Sprite.hpp>

class MapLayer {
    friend class Map;
public:
    MapLayer(){}
    ~MapLayer(){ delete [] tileIds;  delete [] tiles; }

protected:
    int width, height;
    int** tileIds;
    sf::Sprite** tiles;

};


#endif //RAIDMYDUNGEON_MAPLAYER_H
