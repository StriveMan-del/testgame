//
// Created by Kirill on 11.05.2022.
//
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y,float width,float height):
sprite(sprite),offset_x(offset_x),offset_y(offset_y)
{
    this->hitbox.setPosition(this->sprite.getPosition().x+offset_x,this->sprite.getPosition().y+offset_y);
    this->hitbox.setSize(sf::Vector2f(width,height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent() {

}

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitbox);
}

void HitboxComponent::update() {
    this->hitbox.setPosition(this->sprite.getPosition().x+this->offset_x,this->sprite.getPosition().y+this->offset_y);
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect) {
    return this->hitbox.getGlobalBounds().intersects(frect);
}

const sf::RectangleShape& HitboxComponent::getHitbox() const {
    return hitbox;
}

void HitboxComponent::setColor(const sf::Color& color) {
    this->hitbox.setOutlineColor(color);
}

const sf::Vector2f &HitboxComponent::getPosition() const {
    return this->hitbox.getPosition();
}
