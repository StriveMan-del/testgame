//
// Created by Kirill on 11.05.2022.
//

#include "Enemy.h"

Enemy::Enemy(float x, float y,sf::Texture& textureSheet):kill(false),hp(20){
    this->initVariables();
    this->initComponents();

    this->setPosition(x,y);
    this->sprite.scale(2,2);
    this->createHitboxComponent(this->sprite,0.f,0.f,32.f,32.f);
    this->createAnimationComponent(textureSheet);
    this->animationComponent->addAnimation("IDLE",1.f,0,0,5,0,16,16);

}

Enemy::~Enemy() {

}
void Enemy::initVariables() {
this->movementSpeed = 110.f;
}

void Enemy::initComponents() {
}
void Enemy::update(const float &dt,Entity* player) {
    sf::Vector2f moveVec;
    moveVec.x = player->getPosition().x - this->getPosition().x;
    moveVec.y = player->getPosition().y - this->getPosition().y;

    float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

    moveVec /= vecLength;

    if ((this->getPosition().x != player->getPosition().x) && std::abs(vecLength) < 500.f)
        this->move(moveVec.x, moveVec.y, dt);
    this->animationComponent->play("IDLE",dt,false);
    Entity::update(dt);
    this->hitboxComponent->update();
}
void Enemy::setKill(bool kill) {
        this->kill = kill;

}

const bool& Enemy::isKill() const {
    return kill;
}

unsigned short Enemy::Dammage(const short& dammage) {
    this->hp -= dammage;
    if(this->hp <= 0)
        this->setKill(true);
    return this->hp;
}

