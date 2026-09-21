//
// Created by andershorgen on 9/20/26.
//

#ifndef RAIDMYDUNGEON_EQUIPPEDWEAPON_H
#define RAIDMYDUNGEON_EQUIPPEDWEAPON_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "../GameObject.h"
#include "../ItemDef.h"

// One generic weapon controller for every weapon in the game: what it looks
// like and its stats come entirely from an ItemDef, never from a per-weapon
// subclass. Replaces the old Weapon/IronSword class hierarchy.
//
// The icon's rotation pivots on ItemDef::gripX/gripY (where the hand holds
// it) rather than the sprite's default corner, and is aimed using
// ItemDef::restAngle (which way the art points at 0 degrees) — both
// measured from the actual art. This is what lets any weapon icon rotate
// and position correctly with zero per-weapon code.
class EquippedWeapon {
public:
    EquippedWeapon(const ItemDef &def, GameObject &wielder);

    void draw(sf::RenderWindow &window);
    void update(float gametick);
    void strike();

private:
    // Hand position relative to the wielder's body center, in world pixels.
    // Property of the wielder's body, not the weapon, so it's the same for
    // every item. A first pass — tune once real character art exists.
    static sf::Vector2f socketOffsetFor(int direction);

    // Compass angle (0=right, 90=down, 180=left, 270=up, clockwise) the
    // wielder should hold a weapon pointing at rest, per facing direction.
    static float restFacingAngleFor(int direction);

    const ItemDef &def;
    GameObject &wielder;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;

    bool attacking = false;
    float restRotation = 0.f;           // locked in at strike() so mid-swing mouse movement can't snap it
    float attackRotationProgress = 0.f;

    static constexpr float swingRange = 110.f;            // degrees swept, centered on restRotation
    static constexpr float swingDegreesPerSecond = 850.f; // framerate-independent, ~130ms per swing
};

#endif //RAIDMYDUNGEON_EQUIPPEDWEAPON_H
