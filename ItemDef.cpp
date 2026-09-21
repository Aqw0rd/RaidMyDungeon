//
// Created by andershorgen on 9/20/26.
//

#include <stdexcept>
#include "ItemDef.h"

EquipSlot parseEquipSlot(const std::string &value)
{
    if (value == "weapon") return EquipSlot::Weapon;
    if (value == "head")   return EquipSlot::Head;
    if (value == "chest")  return EquipSlot::Chest;
    if (value == "legs")   return EquipSlot::Legs;

    throw std::runtime_error("Unknown equip slot: " + value);
}
