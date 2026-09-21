//
// Created by andershorgen on 2/13/18.
//

#include <iostream>
#include "PlayState.h"
#include "../StateMachine.h"
#include "../ItemDatabase.h"

namespace {
    // Equips an item by id if it's in the database, so a missing/typo'd id
    // just skips the slot instead of crashing.
    void equipGearById(Player &player, GameObject::GearLayer layer, const std::string &id)
    {
        if (const ItemDef *def = ItemDatabase::get(id)) {
            player.setLayerTexture(layer, def->spritePath);
        }
    }
}

PlayState::PlayState(Config* &config, sf::RenderWindow &window, StateMachine &machine)
        : State(config, window, machine)
{
    if(!this->map.loadMap(this->config->getMapPath())){
        std::cout << "Couldnt load map" << std::endl;
    }

    player = new Player(sf::Vector2f(100,100), 100,100,1, 1.5f,"Resources/Sprites/Squarey.png", 16, 16);

    // Temporary: hardcoded test equips (item ids come from Resources/Items/items.json)
    // until Inventory/Equipment (pickups + UI) replaces this.
    equipGearById(*player, GameObject::Legs, "leather_legs");
    equipGearById(*player, GameObject::Chest, "leather_chest");
    equipGearById(*player, GameObject::Head, "leather_helm");
    player->equipWeapon(ItemDatabase::get("iron_sword"));

    std::cout << "Playstate" << std::endl;
}

PlayState::~PlayState()
{
    std::cout << "Deleted PlayState" << std::endl;
    delete player;
}

void PlayState::draw()
{
    this->map.draw(*window);
    this->player->draw(*window);
}

void PlayState::update(float gametick)
{
    this->player->update(gametick);

    while (const std::optional event = window->pollEvent())
    {
        this->player->eventHandler(*event);

        if (event->is<sf::Event::Closed>())
        {
            machine->running = false;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if(keyPressed->code == sf::Keyboard::Key::Escape){
                // popState() deletes this PlayState, so nothing after it may touch `this`.
                this->machine->popState();
                return;
            }
        }
    }
}