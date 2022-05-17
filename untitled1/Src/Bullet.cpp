//
// Created by Kirill on 11.05.2022.
//

#include "Bullet.h"

Bullet::Bullet(float x, float y,sf::Texture& textureSheet,Enemy*& target):target(target),kill(false),dammage(5) {
    this->setPosition(x,y);
    this->sprite.scale(1.f,1.f);
    this->createHitboxComponent(this->sprite,0.f,0.f,16.f,16.f);
    this->createAnimationComponent(textureSheet);
    this->animationComponent->addAnimation("IDLE",1.f,0,14,4,14,16,16);
}

Bullet::~Bullet() {
}
void Bullet::update(const float &dt) {
    if(this->target != NULL) {
        sf::Vector2f moveVec;
        moveVec.x = this->target->getPosition().x - this->getPosition().x;
        moveVec.y = this->target->getPosition().y - this->getPosition().y;

        float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

        moveVec /= vecLength;

        if ((this->getPosition() != this->target->getPosition()))
            this->move(moveVec.x, moveVec.y, dt);
        this->hitboxComponent->update();
        if (this->checkCollision(target)) {
            this->target->Dammage(this->dammage);
            this->kill = true;
        }
        this->animationComponent->play("IDLE", dt, false);
    }
}

void Bullet::initVariables() {
    this->movementSpeed= 200.f;
}

void Bullet::initComponents() {

}
void Bullet::render(sf::RenderTarget& target){
    target.draw(this->sprite);
    if(this->hitboxComponent)
        this->hitboxComponent->render(target);
}

bool Bullet::getKill(){
    return this->kill;
}

void Bullet::setTarget() {
    this->target = NULL;
}

void Bullet::setKill(){
    this->kill = true;
}