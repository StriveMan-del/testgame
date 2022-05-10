#ifndef UNTITLED1_STATE_H
#define UNTITLED1_STATE_H

#include "Entity.h"

class State {

private:

protected:
        std::stack<State*>* states;

        sf::RenderWindow* window;
        std::map<std::string, int>* supportedKeys;
        std::map<std::string, int> keybinds;
        std::vector<sf::Texture> textures;
        bool quit;

        sf::Vector2i mousePosScreen;
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        virtual void initKeybinds() = 0;
public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states);
    virtual ~State();

    const bool& getQuit() const;

    virtual void endState() = 0;
    virtual void chechForQuit();
    virtual void updateMousePosition();
    virtual void updateInputs(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = NULL) = 0;
};


#endif //UNTITLED1_STATE_H
