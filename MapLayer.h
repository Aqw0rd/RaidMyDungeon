//
// Created by andershorgen on 2/9/18.
//

#ifndef RAIDMYDUNGEON_MAPLAYER_H
#define RAIDMYDUNGEON_MAPLAYER_H


#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class MapLayer {
    friend class Map;
public:
    MapLayer(){}
    ~MapLayer() = default;

protected:
    int width, height;
    int** tileIds;
    std::vector<std::vector<sf::Sprite>> tiles;

};


#endif //RAIDMYDUNGEON_MAPLAYER_H
