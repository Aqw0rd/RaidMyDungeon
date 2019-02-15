//
// Created by andershorgen on 2/23/18.
//

#include <iostream>
#include "IronSword.h"

IronSword::IronSword(const char * path, GameObject &object) :  Weapon(path)
{
    this->object = &object;
    this->visible = true;
}

void IronSword::draw(sf::RenderWindow &window)
{

    window.draw(this->sprite);
    if(this->visible){

        if(attack)
        {
            if(this->sprite.getRotation() > (rotation + 180) % 360)
            {
                this->sprite.rotate(10.0f);
            }
            else
            {
                attack = false;
                this->sprite.setRotation(rotation);
                visible = false;
            }
        }

    }


}


void IronSword::strike()
{
    attack = true;
    visible = true;


}

void IronSword::update(float gametick)
{
    this->sprite.setPosition(this->object->getPosition().x + 32, this->object->getPosition().y + 32);

    if(!attack)
    {
        switch (this->object->getDirection()) {
            case GameObject::right:
                this->sprite.setOrigin(0, 32);
                rotation = 270;
                this->sprite.setRotation(rotation);
                break;
            case GameObject::left:
                this->sprite.setOrigin(0, 0);
                rotation = 180;
                this->sprite.setRotation(rotation);
                break;

            default:
                break;
        }
    }


}