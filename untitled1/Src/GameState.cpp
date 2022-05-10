//
// Created by Kirill on 09.03.2022.
//

#include "GameState.h"

void GameState::initKeybinds() {

    this->keybinds.emplace("EXIT",this->supportedKeys->at("ESC"));
    this->keybinds.emplace("MOVE_LEFT",this->supportedKeys->at("A"));
    this->keybinds.emplace("MOVE_RIGHT",this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP",this->supportedKeys->at("W"));
    this->keybinds.emplace("MOVE_DOWN",this->supportedKeys->at("S"));

}


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states):State(window,supportedKeys,states) {
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState() {
    delete this->player;
}

void GameState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInputs(dt);

    this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target) {
    if(!target){
        target=this->window;
    }
    this->player->render(target);
}

void GameState::updateInputs(const float &dt) {

    //Player Input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))){
        this->player->move(dt,-1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))){
        this->player->move(dt,1.f,0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))){
        this->player->move(dt,0.f,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))){
        this->player->move(dt,0.f,1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("EXIT")))){
        this->endState();
    }
}

void GameState::initTextures() {
    sf::Texture temp;
    temp.loadFromFile("assets/image/player/MiniWorker.png");
    this->textures["PLAYER_IDLE"]=temp;
}

void GameState::initPlayers() {
    this->player = new Player(0,0,&this->textures["PLAYER_IDLE"]);
}
