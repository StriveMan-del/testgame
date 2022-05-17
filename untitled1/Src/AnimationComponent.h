#pragma  once


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



class AnimationComponent {
private:
    class Animation{
    private:
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer;
        float timer;
        bool done;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;
        int width,height;
    public:
        Animation(sf::Sprite& sprite,sf::Texture& textureSheet,
                  float animationTimer,
                  int start_frame_x,int start_frame_y,int frames_x,int frames_y,int width, int height)
        :sprite(sprite),textureSheet(textureSheet),
        animationTimer(animationTimer),width(width),height(height)
        ,timer(0.f),done(false)
        {
            this->startRect = sf::IntRect (start_frame_x*width,start_frame_y*height,width,height);
            this->currentRect = this->startRect;
            this->endRect = sf::IntRect (frames_x*width,frames_y*height,width,height);

            this->sprite.setTexture(this->textureSheet,true);
            this->sprite.setTextureRect(this->startRect);
        }

        //Functions

        const bool& isDone() const{
            return this->done;
        }
        const bool& play(const float& dt){
            this->done = false;
            this->timer += 10.0f * dt;
            if(this->timer >= this->animationTimer){
                this->timer = 0.f;
                //Animate
                if(this->currentRect != this->endRect)
                {
                    this->currentRect.left += this->width;
                }//Reset
                else
                {
                    this->done = true;
                    this->currentRect.left = this->startRect.left;
                }
                this->sprite.setTextureRect(this->currentRect);
            }
            return this->done;
        }

    void reset()
        {
            this->timer = this->animationTimer;
            this->currentRect = this->startRect;
        }

    };

    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string,Animation*> animations;
    Animation* lastAnimation;
    Animation* priorityAnimation;
public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);

    virtual ~AnimationComponent();

    //Functions
    void addAnimation(const std::string key,
                      float animationTimer,
                      int start_frame_x,int start_frame_y,int frames_x,int frames_y,int width, int height);

    const bool& play(const std::string key,const float& dt,const bool priority);
};

