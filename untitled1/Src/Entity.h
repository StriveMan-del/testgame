//
// Created by Kirill on 28.03.2022.
//

#ifndef UNTITLED1_ENTITY_H
#define UNTITLED1_ENTITY_H

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


class Entity {
private:


protected:
    sf::RectangleShape shape;
    float movementSpeed;

public:
    Entity();
    virtual ~Entity();

    //Functions
    virtual void move(const float& dt,const float x, const float y);


    virtual void update(const float& dt) ;
    virtual void render(sf::RenderTarget* target);
};


#endif //UNTITLED1_ENTITY_H
