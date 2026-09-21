//
// Created by andershorgen on 9/20/26.
//

#ifndef RAIDMYDUNGEON_ITEMDATABASE_H
#define RAIDMYDUNGEON_ITEMDATABASE_H

#include <string>
#include <unordered_map>
#include "ItemDef.h"

// Loads every ItemDef from a JSON manifest at startup and hands out lookups
// by id. This is the entire "content pipeline" for loot: new items are
// authored as data (see Resources/Items/items.json), never as new classes.
class ItemDatabase {
public:
    // Throws std::runtime_error if the file can't be parsed.
    static void loadFromFile(const std::string &path);

    // Returns nullptr if no item with that id was loaded.
    static const ItemDef* get(const std::string &id);

    ItemDatabase() = delete;

private:
    static std::unordered_map<std::string, ItemDef> items;
};

#endif //RAIDMYDUNGEON_ITEMDATABASE_H
