//
// Created by Kirill on 10.05.2022.
//

#ifndef UNTITLED1_PLAYER_H
#define UNTITLED1_PLAYER_H

#include "Entity.h"

class Player:public Entity{

private:
    //Variables
    //init Functions
    void initVariables();
    void initComponents();
public:
Player(float x, float y,sf::Texture* texture);
virtual ~Player();

//Functions
};


#endif //UNTITLED1_PLAYER_H
