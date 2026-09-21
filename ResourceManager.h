//
// Created by andershorgen on 9/20/26.
//

#ifndef RAIDMYDUNGEON_RESOURCEMANAGER_H
#define RAIDMYDUNGEON_RESOURCEMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>

// Loads each texture file at most once and hands every caller a shared
// reference to the same sf::Texture, so gear layers, weapons, and entities
// that reuse the same art don't each load their own copy.
class ResourceManager {
public:
    // Throws std::runtime_error if the file can't be loaded.
    static std::shared_ptr<sf::Texture> getTexture(const std::string &path);

    ResourceManager() = delete;
};


#endif //RAIDMYDUNGEON_RESOURCEMANAGER_H
