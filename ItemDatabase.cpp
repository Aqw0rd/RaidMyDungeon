//
// Created by andershorgen on 9/20/26.
//

#include <fstream>
#include <stdexcept>
#include <json/json.h>
#include "ItemDatabase.h"

std::unordered_map<std::string, ItemDef> ItemDatabase::items;

void ItemDatabase::loadFromFile(const std::string &path)
{
    std::ifstream ifs(path);
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(ifs, root)) {
        throw std::runtime_error("Failed to parse item database: " + path);
    }

    for (const auto &entry : root) {
        ItemDef def;
        def.id = entry["id"].asString();
        def.name = entry["name"].asString();
        def.slot = parseEquipSlot(entry["slot"].asString());

        def.attackBonus = entry.get("attackBonus", 0).asInt();
        def.defenseBonus = entry.get("defenseBonus", 0).asInt();
        def.maxHpBonus = entry.get("maxHpBonus", 0).asInt();
        def.maxEnergyBonus = entry.get("maxEnergyBonus", 0).asInt();
        def.speedBonus = entry.get("speedBonus", 0.0).asFloat();

        def.spritePath = entry["sprite"].asString();
        def.attackPattern = entry.get("attackPattern", "").asString();
        def.gripX = entry.get("gripX", -1.0).asFloat();
        def.gripY = entry.get("gripY", -1.0).asFloat();
        def.restAngle = entry.get("restAngle", 0.0).asFloat();

        items[def.id] = def;
    }
}

const ItemDef* ItemDatabase::get(const std::string &id)
{
    auto found = items.find(id);
    return found != items.end() ? &found->second : nullptr;
}
