//
// Created by andershorgen on 1/29/18.
//

#include "Config.h"


Config::Config()
{
    resourcePath = "Resource/";
    imagePath = resourcePath + "Images/";
    spritePath = resourcePath + "Sprites/";

}

Config::~Config()
{

}

sf::Vector2u Config::getResolution() const
{
    return resolution;
}

void Config::setResolution(unsigned int x, unsigned int y)
{
    this->resolution = sf::Vector2u(x, y);
}

std::string Config::getImagePath() const
{
    this->imagePath;
}

std::string Config::getSpritePath() const
{
    this->spritePath;
}

/**
 * Setting the current map for the game,
 * Maybe needs to reset or null variables if overwriting
 * doesnt work
 * @param path
 */
void Config::setMap(const char *path)
{
    this->mapPath = path;
}

const char* Config::getMapPath() const
{
    return this->mapPath;
}