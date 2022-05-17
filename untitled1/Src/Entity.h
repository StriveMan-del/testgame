//
// Created by Kirill on 28.03.2022.
//

#ifndef UNTITLED1_ENTITY_H
#define UNTITLED1_ENTITY_H
#include "AnimationComponent.h"
#include "HitboxComponent.h"
enum MOVE{IDLE = 1,MOVE,MOVE_LEFT,MOVE_RIGHT,WORK};
class Entity {
private:
    void initVariables();

protected:

    float velocity_x;
    float velocity_y;

    sf::Sprite sprite;

    bool work;
    bool colision;

    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;
    float movementSpeed;

public:
    Entity();
    virtual ~Entity();
    //Components Functions
    void createSprite(sf::Texture& texture);
    void createAnimationComponent(sf::Texture& textureSheet);
    void createHitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y,float width, float height);
    //Functions
    void setWork(bool work);
    virtual void move(const float& dt);
    virtual void move(const float& x, const float& y,const float& dt);
    virtual void setPosition(const float x, const float y);
    virtual void setVelocity(const float& velocity_x, const float& velocity_y);
    virtual void Velocity(const float& velocity_x, const float& velocity_y);
    virtual bool getState(const int& state);
    virtual const sf::FloatRect getHitbox();
    virtual bool checkCollision(std::vector<Entity*>& entity);
    virtual bool checkCollision(Entity* entity);
    virtual const sf::Vector2f& getPosition();
    const sf::Vector2f getCenter() const;
    //virtual const sf::Vector2f getCenter() const;

    virtual void update(const float& dt) ;
    virtual void render(sf::RenderTarget& target);
    virtual void playAnim(const std::string& key,const float& dt, const bool& priority);
};


#endif //UNTITLED1_ENTITY_H
