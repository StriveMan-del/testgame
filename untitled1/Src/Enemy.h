//
// Created by Kirill on 11.05.2022.
//

#ifndef UNTITLED1_ENEMY_H
#define UNTITLED1_ENEMY_H
#include "Player.h"
#include <cmath>
class Enemy:public Entity {

private:
    bool kill;
    short hp;
    //Init Funct
    void initVariables();
    void initComponents();
public:
    Enemy(float x, float y, sf::Texture& textureSheet);
    virtual ~Enemy();
    //Function
    void update(const float & dt, Entity* player);
    void setKill(bool kill);
    const bool& isKill() const;
    unsigned short Dammage(const short& dammage);
};


#endif //UNTITLED1_ENEMY_H
