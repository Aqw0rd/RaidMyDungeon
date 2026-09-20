//
// Created by andershorgen on 2/9/18.
//

#include "Map.h"
#include <fstream>
#include <SFML/Graphics/Texture.hpp>

Map::Map() {}

Map::~Map()
{
    for(int i = 0; i < layerCount; i++) {
        for (int x = 0; x < this->mapLayers[i].width; x++) {
            delete [] this->mapLayers[i].tileIds[x];
        }
        delete [] this->mapLayers[i].tileIds;
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


    if (!tileset.loadFromFile(root["tilesets"][0]["source"].asString())) { // Setting the texture
        return false;
    }
    height = root["height"].asInt();
    width = root["width"].asInt();
    layerCount = (int)root["layers"].size();

    int tilewidth = root["tilewidth"].asInt();
    int tileheight= root["tileheight"].asInt();

    this->mapLayers = new MapLayer[layerCount];

    Json::Value &layers = root["layers"];   //Helping variable
    for(size_t j = 0; j < layers.size(); j++){

        int &layerWidth = this->mapLayers[(int)j].width;
        int &layerHeight = this->mapLayers[(int)j].height;
        layerHeight = layers[(int)j]["height"].asInt();
        layerWidth = layers[(int)j]["width"].asInt();
        this->mapLayers[(int)j].tileIds = new int*[layerWidth];      // Initializing the pointer
        this->mapLayers[(int)j].tiles.resize(layerWidth);

        for(int x = 0; x < layerWidth; x++){
            this->mapLayers[(int)j].tileIds[x] = new int[layerHeight];       // Initializing the pointer
            this->mapLayers[(int)j].tiles[x].assign(layerHeight, sf::Sprite(tileset)); // Initializing the tiles
        }

        Json::Value &data = layers[(int)j]["data"]; //Helping variable
        for (size_t i = 0; i < data.size(); i++){
            int x =  (int)i % layerWidth;
            int y = (int)i / layerWidth;
            int id = data[(int)i].asInt() - 1;    // Tiled gid 0 means "empty", giving id -1 here

            this->mapLayers[(int)j].tileIds[x][y] = id;
            this->mapLayers[(int)j].tiles[x][y].setPosition(sf::Vector2f(x*tilewidth, y*tileheight));

            if (id < 0) {
                // Empty tile: give it a zero-area texture rect so nothing is drawn,
                // instead of feeding a negative id into the tileset lookup below.
                this->mapLayers[(int)j].tiles[x][y].setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(0, 0)));
                continue;
            }

            int tileX = id % (tileset.getSize().x / tilewidth);
            int tileY = id / (tileset.getSize().y / tileheight);
            this->mapLayers[(int)j].tiles[x][y].setTextureRect(sf::IntRect(sf::Vector2i(tileX*tilewidth, tileY*tileheight), sf::Vector2i(tilewidth, tilewidth)));
        }
    }
    return true;
}


void Map::draw(sf::RenderWindow &window)
{

    for(int i = 0; i < layerCount; i++) {
        for (int y = 0; y < this->mapLayers[i].height; y++) {
            for (int x = 0; x < this->mapLayers[i].width; x++) {
                window.draw(this->mapLayers[i].tiles[x][y]);
            }
        }
    }
}