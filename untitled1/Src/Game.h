
#ifndef GAME_H
#define GAME_H
#include "MainMenuState.h"

class Game {
private:
//Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;

    //Test
    float lasttime=0;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

//Inizilization
void initVariables();
    void initWindow();
    void initKeys();
    void initStates();
public:
    //Constructors/Desctructors
    Game();
    virtual ~Game();

    //Functions

    //Regular
    void endApplication();

    //Update
    void updateDt();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();


};


#endif GAME_H
