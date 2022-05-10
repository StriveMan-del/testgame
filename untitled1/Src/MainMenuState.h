//
// Created by Kirill on 09.05.2022.
//

#ifndef UNTITLED1_MAINMENUSTATE_H
#define UNTITLED1_MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"
class MainMenuState : public State{
private:
    //Variables
    sf::RectangleShape background;
    sf::Font font;
    sf::Texture backgroundTexture;

    std::map <std::string, Button*> buttons;
    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButton();
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions


    void updateInputs(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = NULL);
    void render(sf::RenderTarget* target = NULL);
};


#endif //UNTITLED1_MAINMENUSTATE_H
