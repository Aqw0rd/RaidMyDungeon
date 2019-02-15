//
// Created by andershorgen on 1/29/18.
//

#ifndef RAIDMYDUNGEON_CONFIG_H
#define RAIDMYDUNGEON_CONFIG_H

#include <string>
#include <SFML/System/Vector2.hpp>
#include "Map.h"

class Config {
public:
    Config();
    ~Config();
    sf::Vector2u getResolution() const;
    void setResolution(unsigned int x, unsigned int y);
    std::string getSpritePath() const;
    std::string getImagePath() const;
    void setMap(const char* path);
    const char* getMapPath() const;



protected:
    sf::Vector2u resolution = sf::Vector2u(800,600);
    std::string spritePath;
    std::string imagePath;
    std::string resourcePath;
    const char* mapPath;

};


#endif //RAIDMYDUNGEON_CONFIG_H
