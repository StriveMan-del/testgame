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
    this->keybinds.emplace("WORK",this->supportedKeys->at("SPACE"));
    this->keybinds.emplace("CREATE",this->supportedKeys->at("C"));

}


GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states):State(window,supportedKeys,states) {
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
    this->initVariables();
}

GameState::~GameState() {
    delete this->player;
    for (int i=0;i<this->enemy.size();i++) {
        delete this->enemy[i];
    }for (int i=0;i<this->tower.size();i++) {
        delete this->tower[i];
    }
    delete this->map;
}

void GameState::update(const float& dt) {

    this->gameTimer += dt;
    this->updateMousePosition();
    this->updateInputs(dt);
    this->map->update(*this->player,dt);
    this->player->update(dt);
    for (int i=0;i<this->tower.size();i++) {
        dynamic_cast<Turret*>(this->tower.at(i))->update(dt,this->enemy);
    }
    for(std::vector<Entity*>::iterator it = this->enemy.begin(); it != this->enemy.end();) {
        if(this->enemy.empty()){
            this->enemy.clear();
            break;
        }
        dynamic_cast<Enemy*>(*it)->update(dt,this->player);
        if(dynamic_cast<Enemy*>(*it)->isKill() && !this->enemy.empty()) {
            this->player->setCoin(5);
            delete *it;
            it = this->enemy.erase(it);
        }else{
            it++;
        }
    }
    if( this->player->checkCollision(this->enemy,dt)){
        if(this->dammageTimer >= 20.f && this->player->getDammage(5,this->dammageTimer))
            this->dammageTimer = 0;
        this->dammageTimer += 10.f * dt;
    }

}

void GameState::render(sf::RenderTarget* target) {
    if(!target){
        target=this->window;
    }
    this->map->render(*target);

    for (int i=0;i<this->enemy.size();i++) {
        this->enemy[i]->render(*target);
    }
    for (int i=0;i<this->tower.size();i++) {
        this->tower[i]->render(*target);
    }
    this->player->render(*target);
   // this->player->renderUI(*target,this->font);
    if(floor(this->gameTimer)>this->currentTime){
        this->currentTime = static_cast<int>(floor(this->gameTimer));
    }
    std::stringstream times;
    times << this->currentTime/60<<":"<<this->currentTime%60;
    sf::Text inGameTimer;
    inGameTimer.setFillColor(sf::Color::White);
    inGameTimer.setCharacterSize(30);
    inGameTimer.setFont(this->font);
    inGameTimer.setPosition(target->getSize().x/2,10);
    inGameTimer.setString(times.str());
    target->draw(inGameTimer);
}

void GameState::updateInputs(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CREATE")))){
        this->timer += 10.f * dt;
        if(this->mousePosView.x >=0 && this->mousePosView.y >=0 && this->timer >= 3.f) {
            this->timer = 0;
            this->enemy.push_back(new Enemy(this->mousePosView.x, this->mousePosView.y, this->textures["ENEMY_IDLE"]));
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("EXIT")))){
        this->endState();
    }
    if(this->player->getHP()<=0)
        return;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("WORK")))){
        this->player->setWork(true);
        if(!this->player->checkCollision(this->tower) && this->player->getCoin()>=10) {
            this->tower.push_back(new Turret(this->player->getPosition().x, this->player->getPosition().y,
                                             this->textures["TOWER_IDLE"], this->textures["BULLLET_IDLE"]));
            this->player->setCoin(-10);
        }
    }else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
            this->player->setVelocity(-1.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
            this->player->setVelocity(1.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
            this->player->setVelocity(0.f, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
            this->player->setVelocity(0.f, 1.f);
        }
    }

}

void GameState::initTextures() {
    sf::Texture temp;
    temp.loadFromFile("assets/image/player/MiniWorker.png");
    this->textures["PLAYER_IDLE"]=temp;
    temp.loadFromFile("assets/image/enemy/slime_run.png");
    this->textures["ENEMY_IDLE"]=temp;
    temp.loadFromFile("assets/image/tower/toweIdle.png");
    this->textures["TOWER_IDLE"]=temp;
    temp.loadFromFile("assets/image/bullet/bullet.png");
    this->textures["BULLLET_IDLE"]=temp;
    temp.loadFromFile("assets/image/tileset/1.png");
    this->textures["TILESET"]=temp;
}

void GameState::initPlayers() {
    this->player = new Player(400,300,this->textures["PLAYER_IDLE"]);
}

void GameState::initVariables() {
   this->map = new TileMap("assets/image/tileset/1.png");
   this->map->loadFromFile("level/1.txt");
   this->dammageTimer = 3.f;
   if(!this->font.loadFromFile("assets/fonts/retrocycles_regular.ttf")){
       throw("ERROR::GAMESTATE::FONTSLOAD");
   }
}
