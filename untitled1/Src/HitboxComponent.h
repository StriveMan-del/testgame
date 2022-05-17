//
// Created by Kirill on 11.05.2022.
//

#ifndef UNTITLED1_HITBOXCOMPONENT_H
#define UNTITLED1_HITBOXCOMPONENT_H
#include<iostream>
#include<ctime>
#include<stack>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

class HitboxComponent {
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
public:
    const sf::RectangleShape &getHitbox() const;

private:
    float offset_x;
    float offset_y;

public:
    HitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y,float width,float height);

    virtual ~HitboxComponent();
    //Function
    bool checkIntersect(const sf::FloatRect& frect);
    void update();
    void render(sf::RenderTarget& target);
    void setColor(const sf::Color& color);
};


#endif //UNTITLED1_HITBOXCOMPONENT_H
