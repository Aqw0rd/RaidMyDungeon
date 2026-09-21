//
// Created by andershorgen on 2/17/18.
//

#include <math.h>
#include "Player.h"

# define M_PI           3.14159265358979323846

Player::Player(sf::Vector2f pos, int maxHp, int maxEnergy, int lvl, float speed, char const* texturePath, int width, int height)
    : GameObject(pos, maxHp, maxEnergy, lvl, speed, texturePath, width, height)
{
}

Player::~Player() = default;

void Player::equipWeapon(const ItemDef *def)
{
    this->weapon = def ? std::make_unique<EquippedWeapon>(*def, *this) : nullptr;
}

void Player::draw(sf::RenderWindow &window)
{
    this->drawLayers(window);
    if(this->weapon) this->weapon->draw(window);


    /** Temporary mouse handler **/

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float targetY = mousePos.y - this->pos.y;
    float targetX = mousePos.x - this->pos.x;
    float angle = atan2f(targetY, targetX) * 180 / M_PI;

    if(angle <= 45 && angle > -45)          this->spriteY = right;
    else if(angle <= 135 && angle > 45)     this->spriteY = down;
    else if(angle > 135 || angle <= -135)   this->spriteY = left;
    else if(angle <= -45 && angle > -135)   this->spriteY = up;

    /** ----------------------- **/
}

/**
 * Players update function, gametick used to make speed
 * independent of framerate, as the baseframerate should be 60
 * if it drops below, the speed will increase to compencate
 * @param gametick
 */
void Player::update(float gametick)
{

    float multiplier = (gametick/1000) * 60;            // Gametick multiplier based of 60fps

    movement();
    animation(gametick);
    this->pos.x += this->vel.x * multiplier;
    this->pos.y += this->vel.y * multiplier;
    this->setLayersPosition(this->pos);

    if(this->weapon) this->weapon->update(gametick);
}

/**
 * Used for handling keyboard and mouse events related to the player
 * @param event
 */
void Player::eventHandler(sf::Event event)
{
    if(const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        switch(keyPressed->code)
        {
            case sf::Keyboard::Key::W:
                this->keys[1] = true;   // Up
                break;

            case sf::Keyboard::Key::A:
                this->keys[0] = true;   // Left
                break;

            case sf::Keyboard::Key::S:
                this->keys[3] = true;   // Down
                break;

            case sf::Keyboard::Key::D:
                this->keys[2] = true;   // Right
                break;


            default:
                break;
        }
    }

    if(const auto* keyReleased = event.getIf<sf::Event::KeyReleased>())
    {
        switch(keyReleased->code)
        {
            case sf::Keyboard::Key::W:
                this->keys[1] = false;
                break;

            case sf::Keyboard::Key::A:
                this->keys[0] = false;
                break;

            case sf::Keyboard::Key::S:
                this->keys[3] = false;
                break;

            case sf::Keyboard::Key::D:
                this->keys[2] = false;
                break;

            default:
                break;
        }
    }

    if(const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        switch (mousePressed->button)
        {
            case sf::Mouse::Button::Left:
                if(this->weapon) this->weapon->strike();
                break;


            default:
                break;
        }
    }
}

/**
 * Handling the movement in a dedicated function
 * Only for code tidiness
 */
void Player::movement()
{
    ///Left and Right ///
    if(keys[0])         this->vel.x = -this->speed;
    else if(keys[2])    this->vel.x = this->speed;
    else                this->vel.x = 0;

    /// Up and down ///
    if(keys[1])         this->vel.y = -this->speed;
    else if(keys[3])    this->vel.y = this->speed;
    else                this->vel.y = 0;

    if(this->vel != sf::Vector2f(0,0))  this->walking = true;
    else                                this->walking = false;

    /// Diagonal handler ///
    double newspeed = sqrt((this->speed * this->speed) / 2);

    if(keys[0] && keys[3])
    {
        this->vel.x = (float) newspeed * (-1);
        this->vel.y = (float) newspeed;;
    }

    else if(keys[0] && keys[1])
    {
        this->vel.x = (float) newspeed * (-1);
        this->vel.y = (float) newspeed * (-1);
    }

    else if(keys[2] && keys[3])
    {
        this->vel.x = (float) newspeed;
        this->vel.y = (float) newspeed;
    }

    else if(keys[2] && keys[1])
    {
        this->vel.x = (float) newspeed;
        this->vel.y = (float) newspeed * (-1);
    }
}


/**
 * Animation handler for the player object
 * @param gametick
 */
void Player::animation(float gametick)
{
    if(this->walking)
    {
        this->animationCounter += gametick;
        if(this->animationCounter >= this->animationTime)
        {
            this->animationCounter = 0;
            if(++this->spriteX >= this->tilewidth) this->spriteX = 0;
        }
    }

    else this->spriteX = 0;      // Reset the animation to the start tile

}