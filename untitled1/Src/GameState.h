
#ifndef UNTITLED1_GAMESTATE_H
#define UNTITLED1_GAMESTATE_H

#include "State.h"
#include "TileMap.h"

class GameState : public State{
private:
    sf::Font font;
    Player* player;
    std::vector<Entity*> enemy;
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
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states);
    virtual ~GameState();

    //Functions


    void updateInputs(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};


#endif //UNTITLED1_GAMESTATE_H
