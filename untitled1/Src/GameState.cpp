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
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*>* states,short load = 0):State(window,supportedKeys,states) {
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
    this->initVariables();
    this->loadState();
}
GameState::~GameState() {
    this->saveState();
    delete this->player;
    this->enemy.clear();
    for (int i=0;i<this->tower.size();i++) {
        delete this->tower[i];
    }
    delete this->map;
}

void GameState::update(const float& dt) {
    if(this->player->getHP()>0)
        this->gameTimer += dt;
    this->updateMousePosition();
    this->updateInputs(dt);
    this->map->update(*this->player,dt);
    this->player->update(dt);
    for (int i=0;i<this->tower.size();i++) {
        dynamic_cast<Turret*>(this->tower.at(i))->update(dt,this->enemy);
    }
    Entity* p = this->enemy.getHead();
    while(this->enemy.size() != 0 && this->enemy.getNext(p) != NULL){
        dynamic_cast<Enemy*>(p)->update(dt,this->player);
        if(dynamic_cast<Enemy*>(p)->isKill() && !this->enemy.empty()) {
            this->player->setCoin(1);
            p = this->enemy.remove(p);
        }else{
            p = this->enemy.getNext(p);
        }
    }

   /* for(std::vector<Entity*>::iterator it = this->enemy.begin(); it != this->enemy.end();) {
        if(this->enemy.empty()){
            this->enemy.clear();
            break;
        }
        dynamic_cast<Enemy*>(*it)->update(dt,this->player);
        if(dynamic_cast<Enemy*>(*it)->isKill() && !this->enemy.empty()) {
            this->player->setCoin(1);
            delete *it;
            it = this->enemy.erase(it);
        }else{
            it++;
        }
    }*/
    if(this->player->getHP() > 0 && this->enemy.size()!=0) {
        if (this->player->checkCollision(this->enemy, dt)) {
            if (this->dammageTimer >= 20.f && this->player->getDammage(5, this->dammageTimer))
                this->dammageTimer = 0;
        }
        this->dammageTimer += 10.f * dt;
    }

}

void GameState::render(sf::RenderTarget* target) {
    if(!target){
        target=this->window;
    }
    this->map->render(*target);
    Entity* p = this->enemy.getHead();
    for (int i=0;i<this->enemy.size();i++) {
        p->render(*target);
        p = this->enemy.getNext(p);
    }
    for (int i=0;i<this->tower.size();i++) {
        this->tower[i]->render(*target);
    }
    this->player->render(*target);
    this->player->renderUI(*target,this->font);
    if(floor(this->gameTimer)>this->currentTime){
        this->currentTime = static_cast<int>(floor(this->gameTimer));
    }
    std::stringstream times;
    times << this->currentTime/60<<" : "<<this->currentTime%60;
    sf::Text inGameTimer;
    inGameTimer.setFillColor(sf::Color::White);
    inGameTimer.setCharacterSize(30);
    inGameTimer.setFont(this->font);

    inGameTimer.setString(times.str());
    inGameTimer.setPosition(target->getSize().x/2 -inGameTimer.getLocalBounds().width/2,10);
    target->draw(inGameTimer);
    if(this->player->getHP() <=0){
        std::stringstream DED;
        DED << "THE END";
        sf::Text DEDTEXT;
        DEDTEXT.setFillColor(sf::Color::Red);
        DEDTEXT.setCharacterSize(70);
        DEDTEXT.setFont(this->font);
        DEDTEXT.setString(DED.str());
        DEDTEXT.setPosition(target->getSize().x/2 - DEDTEXT.getLocalBounds().width/2,target->getSize().y/2-DEDTEXT.getLocalBounds().height);
        target->draw(DEDTEXT);
    }
}

void GameState::updateInputs(const float &dt) {
    if(this->player->getHP() > 0) {
        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CREATE")))){
        /*this->timer += 10.f * dt;
        if(this->mousePosView.x >=0 && this->mousePosView.y >=0 && this->timer >= 3.f) {
            this->timer = 0;
            this->enemy.push_back(new Enemy(this->mousePosView.x, this->mousePosView.y, this->textures["ENEMY_IDLE"]));
        }*/
        if (this->enemy.size() <= 80 && (this->currentTime) < floor(this->gameTimer)) {
            std::uniform_int_distribution<int> distribution(1, 2);
            switch (distribution(random_place)) {
                case 1:
                    this->enemy.push_back(
                            new Enemy(-100, this->player->getPosition().y - 20, this->textures["ENEMY_IDLE"],
                                      this->currentTime / 60 + 10));
                    break;
                case 2:
                    this->enemy.push_back(
                            new Enemy(this->window->getSize().x + 100, this->player->getPosition().y + 20,
                                      this->textures["ENEMY_IDLE"], this->currentTime / 60 + 10));
                    break;
                default:
                    this->enemy.push_back(new Enemy(0, 0 + this->enemy.size() * 40, this->textures["ENEMY_IDLE"],
                                                    this->currentTime / 60 * 5 + 10));
                    break;
            }
        }
        //}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("WORK")))) {
            this->player->setWork(true);
            if (!this->player->checkCollision(this->tower) && this->player->getCoin() >= 10) {
                this->tower.push_back(new Turret(this->player->getPosition().x, this->player->getPosition().y,
                                                 this->textures["TOWER_IDLE"], this->textures["BULLLET_IDLE"]));
                this->player->setCoin(-10);
            }
        } else {
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("EXIT")))) {
        this->endState();
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
   this->dammageTimer = 20.f;
   if(!this->font.loadFromFile("assets/fonts/EmpathogenesisRegular.ttf")){
       throw("ERROR::GAMESTATE::FONTSLOAD");
   }

}
void GameState::saveState() {
    std::ofstream data;
    data.open("./config/GameState.txt");
    if(!data.is_open()){

    }else{
        size_t size;
        size =this->enemy.size();
        float x;
        float y;
        bool dead;
        short hp;
        float playerHp;
        float coin;
        data<<size<<"\n";
        Entity* p = this->enemy.getHead();
        for(size_t i = 0; i < this->enemy.size(); i++){
            hp = dynamic_cast<Enemy*>(p)->getHp();
            data<<hp<<"\n";
            x=dynamic_cast<Enemy*>(p)->getPosition().x;
            y=dynamic_cast<Enemy*>(p)->getPosition().y;
            data<<x<<"\n";
            data<<y<<"\n";
            dead =dynamic_cast<Enemy*>(p)->isKill();
            data<<dead<<"\n";
            p = this->enemy.getNext(p);
        }
        size =this->tower.size();
        data<<size<<"\n";
        for(size_t i = 0; i < this->tower.size(); i++){
            data<<dynamic_cast<Turret*>(this->tower[i])->getPosition().x<<"\n";
            data<<dynamic_cast<Turret*>(this->tower[i])->getPosition().y<<"\n";
        }
        data<<this->player->getHP()<<"\n";
        data<<this->player->getCoin()<<"\n";
        data<<this->player->getPosition().x<<"\n";
        data<<this->player->getPosition().y<<"\n";
        data<<this->gameTimer;
    }
    data.close();
}
void GameState::loadState() {
    std::ifstream data;
    data.open("./config/GameState.txt",std::ios::binary);
    if(!data.is_open()){

    }else{
        size_t size;

        float x;
        float y;
        bool dead;
        short hp;
        float playerHp;
        float coin;

        data>>size;
        for(size_t i = 0; i < size; i++){
            data>>hp;
            data>>x;
            data>>y;
            data>>dead;
            this->enemy.push_back(new Enemy(x, y, this->textures["ENEMY_IDLE"],hp,dead));
        }
        data>>size;
        for(size_t i = 0; i < size; i++){
            data>>x;
            data>>y;
            this->tower.push_back(new Turret(x, y,this->textures["TOWER_IDLE"], this->textures["BULLLET_IDLE"]));
        }
        data >> playerHp;
        data >> coin;
        data >> x;
        data >> y;
        this->player = new Player(x-32,y-56,this->textures["PLAYER_IDLE"],playerHp,coin);
        data >> this->gameTimer;
    }
    data.close();
}