//
// Created by Kirill on 28.03.2022.
//

#include "Entity.h"

void Entity::initVariables() {
    this->texture = NULL;
    this->sprite = NULL;
    this->movementSpeed = 100.f;
}

Entity::Entity() {
    this->initVariables();

}

Entity::~Entity() {
 delete this->sprite;
}

void Entity::move(const float& dt,const float dir_x, const float dir_y) {
    if(this->sprite) {
        this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
    }
}

void Entity::update(const float &dt) {

}

void Entity::render(sf::RenderTarget* target) {
    if(this->sprite)
    target->draw(*this->sprite);
}

void Entity::createSprite(sf::Texture *texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);
    this->sprite->setTextureRect(sf::IntRect(0,0,32,32));
    this->sprite->scale(2,2);
}

void Entity::setPosition(const float x, const float y) {
    if(this->sprite) {
        this->sprite->setPosition(x,y);
    }
}
