//
// Created by Kirill on 09.05.2022.
//

#ifndef UNTITLED1_BUTTON_H
#define UNTITLED1_BUTTON_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

enum button_states{BTN_IDLE = 0,BTN_HOVER,BTN_PRESSED};

class Button {

private:
    short unsigned button_states;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;


public:
    Button(float x, float y, float width, float height,
           sf::Font* font, std::string text,
           sf::Color  idleColor,sf::Color  hoverColor,sf::Color  activeColor);
    virtual ~Button();


    const bool isPressed() const;

    //Function
    void render(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos);
};


#endif //UNTITLED1_BUTTON_H
