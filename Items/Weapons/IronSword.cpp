//
// Created by andershorgen on 2/23/18.
//

#include "IronSword.h"

IronSword::IronSword(const char * path, GameObject &object) :  Weapon(path)
{
    this->object = &object;
    this->visible = true;
}

void IronSword::draw(sf::RenderWindow &window)
{

    if(this->visible){

        window.draw(this->sprite);

        if(attack)
        {
            if(this->sprite.getRotation().asDegrees() > (rotation + 180) % 360)
            {
                this->sprite.rotate(sf::degrees(10.0f));
            }
            else
            {
                attack = false;
                this->sprite.setRotation(sf::degrees(rotation));
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
    this->sprite.setPosition(sf::Vector2f(this->object->getPosition().x + 32, this->object->getPosition().y + 32));

    if(!attack)
    {
        switch (this->object->getDirection()) {
            case GameObject::right:
                this->sprite.setOrigin(sf::Vector2f(0, 32));
                rotation = 270;
                this->sprite.setRotation(sf::degrees(rotation));
                break;
            case GameObject::left:
                this->sprite.setOrigin(sf::Vector2f(0, 0));
                rotation = 180;
                this->sprite.setRotation(sf::degrees(rotation));
                break;

            default:
                break;
        }
    }


}