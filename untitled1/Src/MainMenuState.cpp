
#include "MainMenuState.h"

void MainMenuState::initKeybinds() {

/*    this->keybinds.emplace("MOVE_LEFT",this->supportedKeys->at("A"));
    this->keybinds.emplace("MOVE_RIGHT",this->supportedKeys->at("D"));
    this->keybinds.emplace("MOVE_UP",this->supportedKeys->at("W"));
    this->keybinds.emplace("MOVE_DOWN",this->supportedKeys->at("S"));*/

}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states):State(window,supportedKeys,states) {
    this->initVariables();
    this->initBackground();
    this->initKeybinds();
    this->initFonts();
    this->initButton();
    /*
*/
}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for(it = this->buttons.begin();it != this->buttons.end();it++){
        delete it->second;
    }
//delete gamestate_btn;
}

void MainMenuState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInputs(dt);
    this->updateButtons();

}

void MainMenuState::render(sf::RenderTarget* target) {
    if(!target){
        target=this->window;
    }

    target->draw(this->background);
    this->renderButtons(target);

    //remove later
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x,this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss<<this->mousePosView.x<<" "<<this->mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}

void MainMenuState::updateInputs(const float &dt) {

}
void MainMenuState::initFonts(){
    if(!this->font.loadFromFile("assets/fonts/EmpathogenesisRegular.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::FONTSLOAD");
    }
}

void MainMenuState::initButton() {
    this->buttons["GAME_STATE_BTN"] =new Button(100,100,150,50,
    &this->font,"New Game",
    sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200));
    this->buttons["CONTINUE"] =new Button(100,200,150,50,
    &this->font,"Continue",
    sf::Color(70,70,70,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200));
    this->buttons["EXIT"] =new Button(100,300,150,50,
                                                &this->font,"Quit",
                                                sf::Color(100,100,100,200),sf::Color(150,150,150,255),sf::Color(20,20,20,200));


}

void MainMenuState::updateButtons() {
    for(auto &it : this->buttons){
        it.second->update(this->mousePosView);
    }

    //NewGame
    if(this->buttons["GAME_STATE_BTN"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys,this->states));
    }
    if(this->buttons["CONTINUE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys,this->states));
    }
    //Quit game
    if(this->buttons["EXIT"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
    for(auto &it : this->buttons){
        it.second->render(*target);
    }
}

//init function
void MainMenuState::initBackground() {
    this->background.setSize(sf::Vector2f(
            static_cast<float>(this->window->getSize().x),
            static_cast<float>(this->window->getSize().y)
            )
            );
    if(!this->backgroundTexture.loadFromFile("assets/image/main_background.jpg")){
       // throw "ERROR::MAIN_MENU_STATES::FALIED_TO_LOAD_BACKGROUND_TEXTURE";
    }
    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initVariables() {

}
