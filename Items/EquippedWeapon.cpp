//
// Created by andershorgen on 9/20/26.
//

#include <cmath>
#include "EquippedWeapon.h"
#include "../ResourceManager.h"

namespace {
    float normalizeDegrees(float degrees)
    {
        float wrapped = std::fmod(degrees, 360.f);
        return wrapped < 0.f ? wrapped + 360.f : wrapped;
    }
}

EquippedWeapon::EquippedWeapon(const ItemDef &def, GameObject &wielder)
    : def(def), wielder(wielder), texture(ResourceManager::getTexture(def.spritePath)), sprite(*texture)
{
    sprite.setTexture(*texture, true);
    sprite.scale(sf::Vector2f(GameObject::spriteScale, GameObject::spriteScale));

    sf::Vector2f grip = (def.gripX >= 0.f && def.gripY >= 0.f)
        ? sf::Vector2f(def.gripX, def.gripY)
        : sf::Vector2f(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
    sprite.setOrigin(grip);
}

sf::Vector2f EquippedWeapon::socketOffsetFor(int direction)
{
    switch (direction) {
        case GameObject::right: return { 12.f, 4.f };
        case GameObject::left:  return { -12.f, 4.f };
        case GameObject::down:  return { 0.f, 10.f };
        case GameObject::up:    return { 0.f, -4.f };
        default:                return { 12.f, 4.f };
    }
}

float EquippedWeapon::restFacingAngleFor(int direction)
{
    switch (direction) {
        case GameObject::right: return 0.f;
        case GameObject::down:  return 90.f;
        case GameObject::left:  return 180.f;
        case GameObject::up:    return 270.f;
        default:                return 0.f;
    }
}

void EquippedWeapon::draw(sf::RenderWindow &window)
{
    window.draw(sprite);   // Always visible while equipped; attacking just rotates it.
}

void EquippedWeapon::strike()
{
    attacking = true;
    attackRotationProgress = 0.f;
    // Lock the rest angle in for the duration of this swing so spinning the
    // mouse mid-attack can't snap the rotation to a different direction.
    restRotation = normalizeDegrees(restFacingAngleFor(wielder.getDirection()) - def.restAngle);
}

void EquippedWeapon::update(float gametick)
{
    sprite.setPosition(wielder.getBodyCenter() + socketOffsetFor(wielder.getDirection()));

    if (attacking) {
        // The "slash" pattern: sweep swingRange degrees, centered on the
        // locked-in rest angle, at a fixed angular speed so the swing takes
        // the same real time regardless of framerate. Only pattern
        // implemented today — def.attackPattern is where a future pattern
        // (e.g. "thrust") would branch.
        attackRotationProgress += swingDegreesPerSecond * (gametick / 1000.f);
        if (attackRotationProgress >= swingRange) {
            attacking = false;
            sprite.setRotation(sf::degrees(restRotation));
        } else {
            sprite.setRotation(sf::degrees(restRotation - swingRange / 2.f + attackRotationProgress));
        }
    } else {
        restRotation = normalizeDegrees(restFacingAngleFor(wielder.getDirection()) - def.restAngle);
        sprite.setRotation(sf::degrees(restRotation));
    }
}
