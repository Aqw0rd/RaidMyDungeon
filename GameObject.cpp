//
// Created by andershorgen on 2/15/18.
//

#include "GameObject.h"
#include "ResourceManager.h"


GameObject::GameObject(sf::Vector2f pos, int maxHp, int maxEnergy, int lvl, float speed, const char *texturePath, int width, int height)
: pos(pos),
  maxHp(maxHp),
  maxEnergy(maxEnergy),
  hp(maxHp),
  energy(maxEnergy),
  lvl(lvl),
  speed(speed),
  width(width),
  height(height)
{
    body.texture = ResourceManager::getTexture(texturePath);
    tilewidth = body.texture->getSize().x / width;
    tileheight = body.texture->getSize().y / height;
    body.frames = sliceFrames(body.texture);
}

GameObject::~GameObject() = default;

/**
 * Slices a texture into the body's [animation frame][direction] grid. Used
 * for the body itself and for every gear layer, so any layer texture that
 * matches the body's tile size/row/column layout drops straight in.
 */
std::vector<std::vector<sf::Sprite>> GameObject::sliceFrames(const std::shared_ptr<sf::Texture> &tex) const
{
    std::vector<std::vector<sf::Sprite>> frames(tilewidth);
    for(int x = 0; x < tilewidth; x++){
        frames[x].reserve(tileheight);
        for(int y = 0; y < tileheight; y++){
            frames[x].emplace_back(*tex);
            frames[x][y].setTextureRect(sf::IntRect(sf::Vector2i(x*width, y*height), sf::Vector2i(width, height)));
            frames[x][y].scale(sf::Vector2f(spriteScale, spriteScale));
        }
    }
    return frames;
}

GameObject::SpriteLayer GameObject::buildLayer(const std::string &texturePath) const
{
    SpriteLayer layer;
    layer.texture = ResourceManager::getTexture(texturePath);
    layer.frames = sliceFrames(layer.texture);
    return layer;
}

void GameObject::setLayerTexture(GearLayer layer, const std::string &texturePath)
{
    gearLayers[layer] = buildLayer(texturePath);
}

void GameObject::clearLayerTexture(GearLayer layer)
{
    gearLayers[layer] = SpriteLayer{};
}

void GameObject::drawLayers(sf::RenderWindow &window) const
{
    window.draw(body.frames[spriteX][spriteY]);
    for(const auto &layer : gearLayers){
        if(layer.texture){
            window.draw(layer.frames[spriteX][spriteY]);
        }
    }
}

void GameObject::setLayersPosition(sf::Vector2f position)
{
    body.frames[spriteX][spriteY].setPosition(position);
    for(auto &layer : gearLayers){
        if(layer.texture){
            layer.frames[spriteX][spriteY].setPosition(position);
        }
    }
}

sf::Vector2f GameObject::getBodyCenter() const
{
    return pos + sf::Vector2f(width * spriteScale / 2.f, height * spriteScale / 2.f);
}

sf::Vector2f GameObject::getPosition() const { return this->pos; }
sf::Vector2f GameObject::getVelocity() const { return this->vel; }
sf::Vector2f GameObject::getAcceleration() const { return this->acc; }
int GameObject::getDirection() const { return this->spriteY; }

int GameObject::getHealth() const { return this->hp; }
int GameObject::getEnergy() const { return this->energy; }
int GameObject::getLvl() const { return this->lvl; }
