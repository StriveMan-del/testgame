
//
// Created by Kirill on 11.05.2022.
//

#include "Tile.h"
Tile::Tile(){}
Tile::Tile(float x, float y,float gridSizeF,const sf::Texture* texture,const sf::IntRect& texture_rect, bool colision = false):
colision(colision){
    this->shape.setSize(sf::Vector2f(gridSizeF,gridSizeF));

    //this->shape.setFillColor(sf::Color::Green);

    this->shape.setPosition(x,y);
    this->shape.setTexture(texture);
    this->shape.setTextureRect(texture_rect);
}

Tile::~Tile() {

}

bool Tile::draw(sf::RenderTarget& target) {


    return true;
}
//Functions
void Tile::update(){
}
void Tile::render(sf::RenderTarget& target){
    target.draw(this->shape);
}
void Tile::checkCollision(Entity& entity,const float& dt) {
    if(this->colision) {
        if (this->shape.getGlobalBounds().intersects(entity.getHitbox())) {
            sf::Vector2f moveRight;
            moveRight = this->getCenter() - entity.getCenter();
            if(moveRight.x < 0){
                entity.setVelocity(2.f,0.f);
            }
            if(moveRight.x > 0){
                entity.setVelocity(-2.f,0.f);
            }
            if(moveRight.y < 0){
                entity.setVelocity(0.f,2.f);
            }
            if(moveRight.y > 0){
                entity.setVelocity(0.f,-2.f);
            }
        }
    }
}

const sf::Vector2f Tile::getCenter() {
    if (this->colision)
        return
                this->shape.getPosition() +
                sf::Vector2f
                        (
                                this->shape.getGlobalBounds().width / 2.f,
                                this->shape.getGlobalBounds().height / 2.f
                        );


}