//
// Created by andershorgen on 2/15/18.
//

#ifndef RAIDMYDUNGEON_GAMEOBJECT_H
#define RAIDMYDUNGEON_GAMEOBJECT_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>
#include <memory>
#include <string>
#include <vector>

class GameObject {
public:
    GameObject(sf::Vector2f pos, int maxHp, int maxEnergy, int lvl , float speed, const char * texturePath, int width, int height);
    virtual ~GameObject();
    virtual void draw(sf::RenderWindow &window) = 0;        //Needs to be pure virtual, e.g = 0
    virtual void update(float gametick) = 0;

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    int getDirection() const;

    // World-space center of the body's on-screen bounding box (pos is its
    // top-left corner). Held items (e.g. EquippedWeapon) anchor to this
    // rather than to pos directly, so attachment points don't need to know
    // the body's tile size.
    sf::Vector2f getBodyCenter() const;

    int getHealth() const;
    int getEnergy() const;
    int getLvl() const;

    enum direction { left = 0, right = 2, up = 1, down = 3};

    // Equipable sprite layers drawn on top of the body, in this z-order (Legs
    // first, Head last). Every layer texture must share the body's frame grid
    // (same tile size, same direction/animation layout) — see sliceFrames().
    enum GearLayer { Legs = 0, Chest = 1, Head = 2, GearLayerCount = 3 };

    void setLayerTexture(GearLayer layer, const std::string &texturePath);
    void clearLayerTexture(GearLayer layer);

    // Uniform pixel-art scale applied to the body/gear layers; held items
    // (e.g. EquippedWeapon) match it so everything renders at a consistent size.
    static constexpr int spriteScale = 2;

protected:
    struct SpriteLayer {
        std::shared_ptr<sf::Texture> texture;                  // nullptr => layer not equipped
        std::vector<std::vector<sf::Sprite>> frames;            // frames[animation frame][direction]
    };

    std::vector<std::vector<sf::Sprite>> sliceFrames(const std::shared_ptr<sf::Texture> &tex) const;
    SpriteLayer buildLayer(const std::string &texturePath) const;
    void drawLayers(sf::RenderWindow &window) const;            // draws body, then every equipped gear layer
    void setLayersPosition(sf::Vector2f position);

    sf::Vector2f pos, vel, acc;             // Position, velocity and acceleration of object
    int maxHp, maxEnergy;                   // Stats
    int hp, energy, lvl;                    // stats of object
    float speed;

    SpriteLayer body;                                  // Base character sprite (always present)
    std::array<SpriteLayer, GearLayerCount> gearLayers; // Optional equipped gear, drawn over the body

    int spriteX = 0, spriteY = 0;           // Spritesheet coords
    int width, height;
    int tileheight, tilewidth;

};


#endif //RAIDMYDUNGEON_GAMEOBJECT_H
