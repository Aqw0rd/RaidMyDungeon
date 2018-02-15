//
// Created by andershorgen on 2/9/18.
//

#ifndef RAIDMYDUNGEON_MAP_H
#define RAIDMYDUNGEON_MAP_H

#include <json/json.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "MapLayer.h"

class Map {
public:
    Map();
    ~Map();
    bool loadMap(const char * filePath);
    void draw(sf::RenderWindow &window);

protected:
    int height = 0;
    int width = 0;
    int layerCount;
    sf::Texture tileset;            // The texture cant be a local variable
    MapLayer *mapLayers = nullptr;

};


#endif //RAIDMYDUNGEON_MAP_H
