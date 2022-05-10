//
// Created by Kirill on 10.05.2022.
//

#include "Player.h"

Player::Player(float x, float y,sf::Texture* texture) {
    this->initVariables();
    this->initComponents();

    this->createSprite(texture);
    this->setPosition(x,y);


}

Player::~Player() {

}

void Player::initVariables() {

}

void Player::initComponents() {
}
