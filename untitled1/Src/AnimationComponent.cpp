//
// Created by Kirill on 10.05.2022.
//

#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet):
sprite(sprite),textureSheet(textureSheet),lastAnimation(NULL),priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent() {
 for(auto &i : this->animations)
 {
     delete i.second;
 }
}
const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
    if (this->priorityAnimation) //If there is a priority animation
    {
        if (this->priorityAnimation == this->animations[key])
        {
            if (this->lastAnimation != this->animations[key])
            {
                if (this->lastAnimation == NULL)
                    this->lastAnimation = this->animations[key];
                else
                {
                    this->lastAnimation->reset();
                    this->lastAnimation = this->animations[key];
                }
            }

            //If the priority animation is done, remove it
            if (this->animations[key]->play(dt))
            {
                this->priorityAnimation = NULL;
            }
        }
    }
    else //Play animation of no other priority animation is set
    {
        //If this is a priority animation, set it.
        if (priority)
        {
            this->priorityAnimation = this->animations[key];
        }

        if (this->lastAnimation != this->animations[key])
        {
            if (this->lastAnimation == NULL)
                this->lastAnimation = this->animations[key];
            else
            {
                this->lastAnimation->reset();
                this->lastAnimation = this->animations[key];
            }
        }

        this->animations[key]->play(dt);
    }

    return this->animations[key]->isDone();
}
void AnimationComponent::addAnimation(const std::string key,
                                      float animationTimer,
                                      int start_frame_x,int start_frame_y,int frames_x,int frames_y,int width, int height) {

    this->animations[key] = new Animation(
            this->sprite,this->textureSheet,
            animationTimer,
            start_frame_x,start_frame_y,frames_x,frames_y,width,height);
}
