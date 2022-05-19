//
// Created by Kirill on 10.05.2022.
//

#include "Player.h"

Player::Player(float x, float y,sf::Texture& textureSheet,float hp,float coin):hp(hp),coin(coin) {
    this->initVariables();
    this->initComponents();

    this->setPosition(x,y);
    this->sprite.scale(3,3);
    this->createHitboxComponent(this->sprite,32.f,56.f,32.f,40.f);
    this->createAnimationComponent(textureSheet);
    this->animationComponent->addAnimation("WORK",2.f,0,4,3,4,32,32);
    this->animationComponent->addAnimation("MOVE",2.f,0,1,5,1,32,32);
    this->animationComponent->addAnimation("IDLE_LEFT",4.f,0,0,3,0,32,32);
}
Player::Player() {

}
Player::~Player() {

}

void Player::initVariables() {
    this->work = false;
    this->frameInvincibility = 10.f;
    this->timerDammage = this->frameInvincibility;
    this->dammaged = false;
}

void Player::initComponents() {
}

void Player::update(const float &dt) {
    if(this->getState(WORK))
    {
        this->work = !this->animationComponent->play("WORK", dt,true);
    }else if(this->getState(IDLE))
    {
        this->animationComponent->play("IDLE_LEFT", dt,false);
    }
    else if(this->getState(MOVE_LEFT)) {
        this->sprite.setOrigin(32.f,0.f);
        this->sprite.setScale(-3.f,3.f);
        this->animationComponent->play("MOVE", dt, false);
    }
    else if(this->getState(MOVE_RIGHT))
    {
        this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(3.f,3.f);
        this->animationComponent->play("MOVE", dt,false);
    }else if(this->getState(MOVE))
    {
        this->animationComponent->play("MOVE", dt,false);
    }
    Entity::update(dt);
    this->hitboxComponent->update();
}


bool Player::getDammage(const float &dammage,const float& timerDammage) {
    std::cout<<this->hp<<"\n";
    if(this->hp >= 0) {
            this->hp -= dammage;
    }
    if(this->hp <= 0)
        return false;
    return  true;
}

const float Player::getCoin() {
    return this->coin;
}

void Player::setCoin(const float &coin) {
    this->coin += coin;
}
bool Player::checkCollision(std::vector<Entity *> &entity) {
    return Entity::checkCollision(entity);

}
bool Player::checkCollision(List &entity,const float&dt) {
    if(!entity.empty()) {
        Entity* p = entity.getHead();
        while(entity.getNext(p) != NULL) {
            if (this->hitboxComponent->checkIntersect(p->getHitbox())) {
                this->hitboxComponent->setColor(sf::Color::Red);
                return true;
            }
            p = entity.getNext(p);
        }
    }
    this->hitboxComponent->setColor(sf::Color::Green);
    return false;
}

const float &Player::getHP() {
    return this->hp;
}

void Player::renderUI(sf::RenderTarget& target,sf::Font& font){
    sf::Text hp;
    sf::Text coin;
    sf::RectangleShape hpBar;
    sf::RectangleShape coinBackground;
    //HpBar
    hpBar.setPosition(40,40);
    hpBar.setSize(sf::Vector2f(((this->hp>=0?this->hp:0)/100)*90,10));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setOutlineColor(sf::Color::Black);
    hpBar.setOutlineThickness(2);
    //Hp
    hp.setPosition(40,20);
    hp.setFont(font);
    hp.setCharacterSize(15);
    hp.setFillColor(sf::Color::Green);
    std::stringstream s1;
    s1<<"HP:";

    //Coin
    coin.setPosition(45,60);
    coin.setFont(font);
    coin.setCharacterSize(15);
    coin.setFillColor(sf::Color::Yellow);
    std::stringstream s2;
    s2<<"Coin:" <<this->coin;
    hp.setString(s1.str());
    coin.setString(s2.str());
    //Coin back
    coinBackground.setPosition(40,55);
    coinBackground.setSize(sf::Vector2f(coin.getGlobalBounds().width+10,25));
    coinBackground.setSize(sf::Vector2f(60,25));
    coinBackground.setFillColor(sf::Color(0,0,0,150));

    target.draw(hp);
    target.draw(coinBackground);
    target.draw(coin);
    target.draw(hpBar);

}
