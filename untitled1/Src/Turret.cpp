//
// Created by Kirill on 11.05.2022.
//

#include "Turret.h"

Turret::Turret(float x, float y, sf::Texture& textureSheet,sf::Texture& textureBullet):attackSpeed(10.f),attackTimer(attackSpeed),textureBullet(textureBullet){
    this->initVariables();
    this->initComponents();

    this->setPosition(x,y);
    this->sprite.scale(2,2);
    this->createHitboxComponent(this->sprite,0.f,0.f,32.f,32.f);
    this->createAnimationComponent(textureSheet);
    this->animationComponent->addAnimation("IDLE",2.f,0,0,3,0,16,16);

}
Turret::Turret(sf::Texture& textureBullet):textureBullet(textureBullet) {

}
Turret::~Turret() {
    for(auto &i : this->bullet)
        delete i;
    this->bullet.clear();
}
void Turret::update(const float &dt,List& entity) {
    if(this->target == NULL) {
        Entity* p = entity.getHead();
        while(entity.getNext(p) != NULL){
            if (findTarget(p))
                break;
            p = entity.getNext(p);
        }
    }
    else
    {
        if(!this->target->isKill() && this->target) {
            findTarget(this->target);
            shoot(dt);
        }else{
            this->target = NULL;
            for(auto &i : this->bullet)
                delete i;
            this->bullet.clear();
        }
    }
    this->animationComponent->play("IDLE",dt,false);
    Entity::update(dt);
    this->hitboxComponent->update();

    for(std::vector<Bullet*>::iterator it = bullet.begin(); it != bullet.end(); ++it) {
        if(bullet.size()==0)
            break;
            bullet.erase(
                    std::remove_if(
                            bullet.begin(),
                            bullet.end(),
                            [](Bullet*& b) {
                                if(b && b->getKill())
                                {
                                    delete b;
                                    return true;
                                }
                                return false;
                            }
                    ),
                    bullet.end()
            );
    }
    if(bullet.size() > 0) {
        for (auto i: bullet) {
            if(this->target == NULL || this->target->isKill()) {
                i->setTarget();
                i->setKill();
            }
            i->update(dt);
        }
    }
}

void Turret::initVariables() {
    this->target = NULL;
}

void Turret::initComponents() {

}
void Turret::createHitboxComponent(sf::Sprite& sprite,
                                   float offset_x, float offset_y,
                                   float width, float height) {
    this->hitboxComponent = new HitboxComponent(sprite,offset_x,offset_y,width,height);
}
bool Turret::findTarget(Entity*& enemy) {
    sf::Vector2f moveVec;
    moveVec.x = enemy->getPosition().x - this->getPosition().x;
    moveVec.y = enemy->getPosition().y - this->getPosition().y;

    float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

    moveVec /= vecLength;

    if ((this->getPosition().x != enemy->getPosition().x) && std::abs(vecLength) < 200.f) {
        this->target = dynamic_cast<Enemy*>(enemy);
        return true;
    }
    this->target = NULL;
    return false;
}
bool Turret::findTarget(Enemy*& enemy) {
        sf::Vector2f moveVec;
        if(enemy != NULL) {
            moveVec.x = enemy->getPosition().x - this->getPosition().x;
            moveVec.y = enemy->getPosition().y - this->getPosition().y;

            float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

            moveVec /= vecLength;

            if ((this->getPosition().x != enemy->getPosition().x) && std::abs(vecLength) < 200.f) {
                this->target = enemy;
                return true;
            }
        }
    this->target = NULL;
    return false;
}

void Turret::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
    if(this->hitboxComponent)
        this->hitboxComponent->render(target);

   /* for(auto &i : bullet){
        i->render(target);
    }*/
   for(size_t i =0;i<bullet.size();++i)
       bullet.at(i)->render(target);
}

void Turret::shoot(const float& dt){
    this->attackTimer += 10.f * dt;
    if(this->attackTimer >= this->attackSpeed) {
        this->attackTimer = 0;
        bullet.push_back(new Bullet(this->getPosition().x, this->getPosition().y - 20,this->textureBullet, this->target));
    }
}