//
// Created by Kirill on 15.05.2022.
//

#include "TileMap.h"



TileMap::TileMap( std::string texture_file) {

    this->textureFile = texture_file;
    this->gridSizeF = 50.f;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSize.x = 16;
    this->maxSize.y = 12;

    this->layers = 1;

    this->map.resize(this->maxSize.x,  std::vector< std::vector<Tile*> > ());
    for(size_t x = 0; x < this->maxSize.x;x++){
        for(size_t y = 0; y < this->maxSize.y;y++){
            this->map[x].resize(this->maxSize.y,  std::vector<Tile*> ());

            for(size_t z = 0; z < this->layers; z++){
                this->map[x][y].resize(this->layers,NULL);

            }
        }
    }

    this->tileSheet.loadFromFile(texture_file);
}

TileMap::~TileMap() {
    for(size_t x = 0; x < this->size_x;x++){
        for(size_t y = 0; y < this->size_y;y++){
            for(size_t z = 0; z < this->layers; z++){
                delete this->map[x][y][z];
            }
        }
    }
}

//Functions

void TileMap::update(Entity& entity,const float& dt){
    for(size_t x = 0; x < this->size_x;x++){
        for(size_t y = 0; y < this->size_y;y++){
            for(size_t z = 0; z < this->layers; z++){
                this->map[x][y][z]->checkCollision(entity,dt);
            }
        }
    }
}
void TileMap::render(sf::RenderTarget& target){
    for(size_t x = 0; x < this->size_x;x++){
        for(size_t y = 0; y < this->size_y;y++){
            for(size_t z = 0; z < this->layers; z++){
                this->map[x][y][z]->render(target);
            }
        }
    }
}

void TileMap::loadFromFile(std::string level) {

    std::ifstream file;

    file.open(level);

    char type = 0;
    int size_x = 0;
    int size_y = 0;

    file>>size_x>>size_y;
    this->size_x = static_cast<int>(size_x);
    this->size_y = static_cast<int>(size_y);
    if(file.is_open()){
        for(size_t y = 0; y < size_y;y++){
            for(size_t x = 0; x < size_x;x++){
                for(size_t z = 0; z < this->layers; z++){
                    file>>type;
                    switch(type){
                        case '0':
                            this->map[x][y][z] = new Tile(x*this->gridSizeF,y*this->gridSizeF,this->gridSizeF,&this->tileSheet,sf::IntRect(180,40,32,32),1);
                            break;
                        case '1':
                            this->map[x][y][z] = new Tile(x*this->gridSizeF,y*this->gridSizeF,this->gridSizeF,&this->tileSheet,sf::IntRect(40,40,32,32),0);
                            break;
                        case '2':
                            this->map[x][y][z] = new Tile(x*this->gridSizeF,y*this->gridSizeF,this->gridSizeF,&this->tileSheet,sf::IntRect(320,40,32,32),0);
                            break;
                        default:
                            this->map[x][y][z] = new Tile(x*this->gridSizeF,y*this->gridSizeF,this->gridSizeF,&this->tileSheet,sf::IntRect(40,40,32,32),0);
                            break;
                    }

                }
            }
        }
    }
}