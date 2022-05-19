//
// Created by Kirill on 28.03.2022.
//

#include "Entity.h"

void Entity::initVariables() {

    this->animationComponent=NULL;
    this->hitboxComponent=NULL;
    this->movementSpeed = 100.f;
    this->velocity_x = 0;
    this->velocity_y = 0;
    this->work = false;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
        delete this->animationComponent;
        delete this->hitboxComponent;
}

void Entity::move(const float& dt) {
    if(this->velocity_x != 0 || this->velocity_y !=0){
        if(this->velocity_x != 0 && this->velocity_y !=0){
            this->velocity_x = this->velocity_x/2;
            this->velocity_y = this->velocity_y/2;
        }
        if(this->velocity_x < 0.f){
            this->sprite.move(this->velocity_x * this->movementSpeed * dt, this->velocity_y * this->movementSpeed * dt);
        }
        if(this->velocity_x > 0.f){
            this->sprite.move(this->velocity_x * this->movementSpeed * dt, this->velocity_y * this->movementSpeed * dt);
        }
        if(this->velocity_y > 0.f){
            this->sprite.move(this->velocity_x * this->movementSpeed * dt, this->velocity_y * this->movementSpeed * dt);
        }
        if(this->velocity_y < 0.f){
            this->sprite.move(this->velocity_x * this->movementSpeed * dt, this->velocity_y * this->movementSpeed * dt);
        }
    }
    velocity_x = velocity_y = 0;
}



void Entity::update(const float &dt) {
    this->move(dt);
}

void Entity::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
    if(this->hitboxComponent)
        this->hitboxComponent->render(target);

}

void Entity::createSprite(sf::Texture &texture) {
    this->sprite.setTexture(texture);
}

void Entity::setPosition(const float x, const float y) {
        this->sprite.setPosition(x,y);
}

void Entity::createAnimationComponent(sf::Texture &textureSheet) {
    this->animationComponent = new AnimationComponent(this->sprite,textureSheet);
}

void Entity::playAnim(const std::string& key,const float& dt, const bool& priority) {
    this->animationComponent->play(key,dt,priority);
}

void Entity::setVelocity(const float& velocity_x, const float& velocity_y) {
    this->velocity_x += velocity_x;
    this->velocity_y += velocity_y;
}
void Entity::Velocity(const float& velocity_x, const float& velocity_y) {
    this->velocity_x = velocity_x;
    this->velocity_y = velocity_y;
}

bool Entity::getState(const int& state) {
    switch (state) {
        case IDLE:
            if(this->velocity_x == 0.f && this->velocity_y == 0.f)
                return true;
        break;
        case MOVE:
            if(this->velocity_x != 0.f || this->velocity_y != 0.f)
                return true;
            break;
        case MOVE_LEFT:
            if(this->velocity_x < 0.f)
                return true;
            break;
        case MOVE_RIGHT:
            if(this->velocity_x > 0.f)
                return true;
            break;
        case WORK:
            if(this->work)
                return true;
            break;
        default:
            return false;
            break;
    }
    return false;
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
                                   float offset_x, float offset_y,
                                   float width, float height) {
    this->hitboxComponent = new HitboxComponent(sprite,offset_x,offset_y,width,height);
}

void Entity::setWork(bool work) {
    this->work = work;
}

bool Entity::checkCollision(std::vector<Entity*>& entity) {
    if(!entity.empty()) {
        for(int i = 0; i<entity.size();i++) {
            if (this->hitboxComponent->checkIntersect(entity[i]->hitboxComponent->getHitbox().getGlobalBounds())) {
                this->hitboxComponent->setColor(sf::Color::Red);
                return true;
            }
        }
    }
    this->hitboxComponent->setColor(sf::Color::Green);
    return false;
}
bool Entity::checkCollision(Entity* entity) {
    if(entity != NULL) {
            if (this->hitboxComponent->checkIntersect(entity->hitboxComponent->getHitbox().getGlobalBounds())) {
                this->hitboxComponent->setColor(sf::Color::Red);
                return true;
            }
    }
    this->hitboxComponent->setColor(sf::Color::Green);
    return false;
}
const sf::Vector2f &Entity::getPosition() const {
    return this->hitboxComponent->getPosition();
}

const sf::FloatRect Entity::getHitbox(){
    return this->hitboxComponent->getHitbox().getGlobalBounds();
}

void Entity::move(const float &x, const float &y, const float &dt) {
    if(this->sprite.getPosition().x && this->sprite.getPosition().y)
        this->sprite.move(x*dt*movementSpeed,y*dt*movementSpeed);
}
const sf::Vector2f Entity::getCenter() const
{
    if (this->hitboxComponent)
        return
                this->hitboxComponent->getHitbox().getPosition() +
                sf::Vector2f
                        (
                                this->hitboxComponent->getHitbox().getGlobalBounds().width / 2.f,
                                this->hitboxComponent->getHitbox().getGlobalBounds().height / 2.f
                        );

    return
            this->sprite.getPosition() +
            sf::Vector2f
                    (
                            this->sprite.getGlobalBounds().width / 2.f,
                            this->sprite.getGlobalBounds().height / 2.f
                    );
}


/*const sf::Vector2f Entity::getCenter() const
{
    if (this->hitboxComponent)
        return
                this->hitboxComponent->getHitbox().getPosition() +
                sf::Vector2f
                        (
                                this->hitboxComponent->getHitbox().getGlobalBounds().width / 2.f,
                                this->hitboxComponent->getHitbox().getGlobalBounds().height / 2.f
                        );

    return
            this->sprite.getPosition() +
            sf::Vector2f
                    (
                            this->sprite.getGlobalBounds().width / 2.f,
                            this->sprite.getGlobalBounds().height / 2.f
                    );
}*/
