//
// Created by Kirill on 09.03.2022.
//

#include "State.h"

State::State(sf::RenderWindow* window,std::map<std::string, int>* supportedKeys,std::stack<State*>* states){
this->window = window;
this->supportedKeys = supportedKeys;
this->states = states;
this->quit = false;

}

State::~State(){

}

void State::chechForQuit() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        this->quit = true;
    }
}

const bool & State::getQuit() const {
    //return statement
    return this->quit;
}

void State::updateMousePosition() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}