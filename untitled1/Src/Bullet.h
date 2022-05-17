//
// Created by Kirill on 11.05.2022.
//

#ifndef UNTITLED1_BULLET_H
#define UNTITLED1_BULLET_H
#include "Enemy.h"

class Bullet:public Entity {
private:
    Enemy* target;
    unsigned short dammage;
    bool kill;
    //Init Funct
    void initVariables();
    void initComponents();
public:
    Bullet(float x, float y,sf::Texture& textureSheet,Enemy*& target);

    virtual ~Bullet();
    //Function
    void update(const float & dt);
    void render(sf::RenderTarget& target);
    bool getKill();
    void setTarget();
    void setKill();
};


#endif //UNTITLED1_BULLET_H
