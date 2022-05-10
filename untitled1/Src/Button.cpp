//
// Created by Kirill on 09.05.2022.
//

#include "Button.h"

Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string text,
               sf::Color  idleColor,sf::Color  hoverColor,sf::Color  activeColor)
               {
    this->button_states = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x,y));
 this->shape.setSize(sf::Vector2f(width,height));
 this->font = font;
 this->text.setFont(*this->font);
 this->text.setString(text);
 this->text.setFillColor(sf::Color::White);
 this->text.setCharacterSize(32);
    this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
            );

 this->idleColor = idleColor;
 this->hoverColor = hoverColor;
 this->activeColor = activeColor;

 this->shape.setFillColor(this->idleColor);

}

Button::~Button() {

}

void Button::render(sf::RenderTarget *target) {
    target->draw(this->shape);
    target->draw(this->text);
}
void Button::update(const sf::Vector2f mousePos) {
    //Idle
    this->button_states = BTN_IDLE;
    //Hover
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->button_states = BTN_HOVER;
    //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->button_states = BTN_PRESSED;
        }
    }

    switch (this->button_states) {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;
        case BTN_PRESSED:
            this->shape.setFillColor(this->activeColor);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
    }
}

const bool Button::isPressed() const {
    if(this->button_states == BTN_PRESSED) {
        return true;
    }
    return false;
}
