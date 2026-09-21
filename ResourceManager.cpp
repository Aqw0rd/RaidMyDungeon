//
// Created by andershorgen on 9/20/26.
//

#include <stdexcept>
#include <unordered_map>
#include "ResourceManager.h"

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string &path)
{
    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> cache;

    auto found = cache.find(path);
    if (found != cache.end()) {
        return found->second;
    }

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    cache.emplace(path, texture);
    return texture;
}
