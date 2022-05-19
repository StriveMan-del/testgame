//
// Created by Kirill on 10.05.2022.
//

#ifndef UNTITLED1_PLAYER_H
#define UNTITLED1_PLAYER_H

#include "List.h"
class Player:public Entity{

private:
    //Variables
    float frameInvincibility;
    float timerDammage;
    float hp;
    float coin;
    bool dammaged;
    //init Functions
    void initVariables();
    void initComponents();
public:
Player(float x, float y,sf::Texture& textureSheet,float hp = 100,float coin = 20);
Player();
virtual ~Player();

//Functions
void update(const float & dt);
bool checkCollision(List& entity,const float&dt);
bool checkCollision(std::vector<Entity *>& entity);
bool getDammage(const float& dammage,const float& timerDammage);
const float getCoin();
void setCoin(const float& coin);
const float& getHP();
void renderUI(sf::RenderTarget& target,sf::Font& font);
};


#endif //UNTITLED1_PLAYER_H
