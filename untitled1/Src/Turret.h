//
// Created by Kirill on 11.05.2022.
//

#ifndef UNTITLED1_TURRET_H
#define UNTITLED1_TURRET_H
#include "Bullet.h"

class Turret:public Entity {
private:
    Enemy* target;
    std::vector<Bullet*> bullet;
    sf::Texture& textureBullet;
    float attackSpeed;
    float attackTimer;
    //Init Funct
    void initVariables();
    void initComponents();
public:
    Turret(float x, float y, sf::Texture& textureSheet, sf::Texture& textureBullet);
    Turret(sf::Texture& textureBullet);
    virtual ~Turret();
    //Function
    void createHitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y,float width, float height);
    void update(const float & dt,List& entity);
    void render(sf::RenderTarget& target);
    bool findTarget(Entity*& enemy);
    bool findTarget(Enemy*& enemy);
    void shoot(const float& dt);
};


#endif //UNTITLED1_TURRET_H
