//
// Created by andershorgen on 2/9/18.
//

#include "Map.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>

Map::Map() {}

Map::~Map()
{
    for(int i = 0; i < layerCount; i++) {
        for (int y = 0; y < height; y++) {
            delete [] this->mapLayers[i].tiles[y];
        }
        delete [] this->mapLayers[i].tiles;
    }
    delete [] this->mapLayers;
}

bool Map::loadMap(const char *filePath)
{
    std::ifstream ifs(filePath);    //Loading the file
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(ifs, root);   // Parsing the file with jsoncpp
    if(!parsingSuccessful) return false;                // Failed to parse the file


    tileset.loadFromFile(root["tilesets"][0]["source"].asString()); //Setting the texture
    height = root["height"].asInt();
    width = root["width"].asInt();
    layerCount = (int)root["layers"].size();

    int tilewidth = root["tilewidth"].asInt();
    int tileheight= root["tileheight"].asInt();

    this->mapLayers = new MapLayer[layerCount];

    Json::Value &layers = root["layers"];   //Helping variable
    for(size_t j = 0; j < layers.size(); j++){

        this->mapLayers[(int)j].height = layers[(int)j]["height"].asInt();
        this->mapLayers[(int)j].width = layers[(int)j]["width"].asInt();
        this->mapLayers[(int)j].tileIds = new int*[this->mapLayers[(int)j].width];      // Initializing the pointer
        this->mapLayers[(int)j].tiles = new sf::Sprite*[this->mapLayers[(int)j].width]; // Initializing the pointer

        for(size_t x = 0; x < this->mapLayers[(int)j].width; x++){
            this->mapLayers[(int)j].tileIds[(int)x] = new int[this->mapLayers[(int)j].width];       // Initializing the pointer
            this->mapLayers[(int)j].tiles[(int)x] = new sf::Sprite[this->mapLayers[(int)j].width];  // Initializing the pointer
        }

        Json::Value &data = layers[(int)j]["data"]; //Helping variable
        for (size_t i = 0; i < data.size(); i++){
            int x =  (int)i % width;
            int y = (int)i / height;
            int id = data[(int)i].asInt() - 1;
            int tileX = id % (tileset.getSize().x / tilewidth);
            int tileY = id / (tileset.getSize().y / tileheight);

            this->mapLayers[(int)j].tileIds[x][y] = id;
            this->mapLayers[(int)j].tiles[x][y].setTexture(tileset);
            this->mapLayers[(int)j].tiles[x][y].setTextureRect(sf::IntRect(tileX*tilewidth, tileY*tileheight, tilewidth, tilewidth));
            this->mapLayers[(int)j].tiles[x][y].setPosition(x*tilewidth, y*tileheight);
        }
    }
    return true;
}


void Map::draw(sf::RenderWindow &window)
{

    for(int i = 0; i < layerCount; i++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                window.draw(this->mapLayers[i].tiles[x][y]);
            }
        }
    }
}