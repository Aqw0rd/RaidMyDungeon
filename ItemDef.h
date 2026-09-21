//
// Created by andershorgen on 9/20/26.
//

#ifndef RAIDMYDUNGEON_ITEMDEF_H
#define RAIDMYDUNGEON_ITEMDEF_H

#include <string>

// Which body slot an item goes in. Head/Chest/Legs map onto a
// GameObject::GearLayer; Weapon is handled separately by EquippedWeapon
// since it needs rotation, not layering.
enum class EquipSlot { Weapon, Head, Chest, Legs };

EquipSlot parseEquipSlot(const std::string &value);   // throws std::runtime_error on an unrecognized value

// Static definition of one kind of loot (e.g. "iron_sword"). Loaded from
// Resources/Items/*.json by ItemDatabase — adding a new item never requires
// a new C++ class, only a new entry here plus matching art.
struct ItemDef {
    std::string id;
    std::string name;
    EquipSlot slot = EquipSlot::Weapon;

    // Stat bonuses applied while this item is equipped.
    int attackBonus = 0;
    int defenseBonus = 0;
    int maxHpBonus = 0;
    int maxEnergyBonus = 0;
    float speedBonus = 0.f;

    // Sprite used both as the inventory icon and to render the item on the
    // character: a gear layer texture (Head/Chest/Legs, must share the
    // body's frame grid) or a held weapon icon (Weapon).
    std::string spritePath;

    // Weapon only: which shared swing routine EquippedWeapon should use.
    // Only "slash" exists today; the field exists so items can already be
    // tagged for future patterns (e.g. "thrust", "ranged").
    std::string attackPattern;

    // Weapon only: where EquippedWeapon should pivot/aim this icon. Both are
    // measured from the art itself, not guessed — see
    // docs/plans/weapon-and-gear-system.md for how to measure them for new
    // weapon art. Without this, every weapon would need its own hand-tuned
    // rotation code, defeating the point of a generic weapon system.
    //
    // gripX/gripY: pixel coordinates (in the icon's own texture space) of
    // where the hand holds it. Left at -1 (the default), EquippedWeapon
    // falls back to the icon's center.
    float gripX = -1.f;
    float gripY = -1.f;
    // restAngle: the compass direction the icon's art points toward at 0
    // degrees sprite rotation (0=right, 90=down, 180=left, 270=up,
    // clockwise) — e.g. a blade drawn pointing up-and-left from its grip is
    // 225. Used to work out how far to rotate the icon so it visibly points
    // the way the wielder is facing.
    float restAngle = 0.f;
};

#endif //RAIDMYDUNGEON_ITEMDEF_H
