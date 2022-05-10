
#ifndef UNTITLED1_GAMESTATE_H
#define UNTITLED1_GAMESTATE_H

#include "State.h"
class GameState : public State{
private:
    Entity player;

    //Functions
    void initKeybinds();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states);
    virtual ~GameState();

    //Functions

    void endState();


    void updateInputs(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};


#endif //UNTITLED1_GAMESTATE_H
