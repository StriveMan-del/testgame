
//
// Created by Kirill on 11.05.2022.
//


#ifndef UNTITLED1_TILE_H
#define UNTITLED1_TILE_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

#include "Player.h"

class Tile {
private:
protected:
    sf::RectangleShape shape;
    bool colision;
    const sf::Vector2f getCenter();
public:
    Tile();
    Tile(float x, float y,float gridSizeF,const sf::Texture* texture,const sf::IntRect& texture_rect,bool colision);
    void checkCollision(Entity& entity,const float& dt);
    virtual ~Tile();
    void update();
    void render(sf::RenderTarget& target);
    bool draw(sf::RenderTarget& target);
};




#endif //UNTITLED1_TILE_H

