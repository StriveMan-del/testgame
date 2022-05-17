#include "Game.h"
//Static function

//Initialize functions
void Game::initWindow() {

    std::ifstream ifs("./config/window.ini");

    sf::VideoMode window_bouds(800,600);

    std::string title = "None";
    unsigned  fps_lock = 120;
    bool vertical_sync = true;

    if(ifs.is_open()){
        std::getline(ifs,title);
        ifs >> window_bouds.width >> window_bouds.height;
        ifs >> fps_lock;
        ifs >> vertical_sync;
    }

    ifs.close();

    this->window = new sf::RenderWindow(sf::VideoMode(window_bouds),"Tower Craft",sf::Style::Close);
    this->window->setFramerateLimit(fps_lock);
    this->window->setVerticalSyncEnabled(vertical_sync);

}
void Game::initKeys() {
    this->supportedKeys.emplace("ESC",sf::Keyboard::Key::Escape);
    this->supportedKeys.emplace("A",sf::Keyboard::Key::A);
    this->supportedKeys.emplace("D",sf::Keyboard::Key::D);
    this->supportedKeys.emplace("W",sf::Keyboard::Key::W);
    this->supportedKeys.emplace("S",sf::Keyboard::Key::S);
    this->supportedKeys.emplace("SPACE",sf::Keyboard::Key::Space);
    this->supportedKeys.emplace("C",sf::Keyboard::Key::C);
}
void Game::initStates() {
    this->states.push(new MainMenuState(this->window, &this->supportedKeys,&this->states));
}

//Constructors/Desctructors functions
Game::Game(){
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game:: ~Game(){
    delete this->window;
    while(!this->states.empty())
        delete this->states.top();
}
void Game::updateDt() {
    /*Update the dt variables with the time it takes to update and render 1 frame*/
    this->dt = this->dtClock.restart().asSeconds();
}


//Functions

void Game::endApplication() {

}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLEvents();
    if(!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if(this->states.top()->getQuit()){
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render() {

        this->window->clear();

        //Render items
        if(!this->states.empty())
        {
            this->states.top()->render();
        }
        this->window->display();
}

void Game::run() {
    sf::err().rdbuf(NULL);
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::initVariables() {
    this->window = NULL;
    this->dt = 0.f;
}

