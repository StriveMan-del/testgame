
#ifndef UNTITLED1_GAMESTATE_H
#define UNTITLED1_GAMESTATE_H

#include "State.h"
#include "TileMap.h"

#include <random>

class GameState : public State{
private:
    sf::Font font;
    Player* player;
    std::default_random_engine random_place;
    //std::vector<Entity*> enemy;
    List enemy;
    std::vector<Entity*> tower;
    TileMap* map;
    float timer = 0;
    float dammageTimer = 0;
    float gameTimer = 0;
    int currentTime  = 0;
    //Functions
    void initKeybinds();
    void initTextures();
    void initPlayers();
    void initVariables();
    void saveState();
    void loadState();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states);
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states,short load);
    virtual ~GameState();

    //Functions


    void updateInputs(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};


#endif //UNTITLED1_GAMESTATE_H
