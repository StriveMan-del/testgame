//
// Created by Kirill on 15.05.2022.
//

#ifndef UNTITLED1_TILEMAP_H
#define UNTITLED1_TILEMAP_H
#include "Tile.h"

class TileMap {
private:
    std::string textureFile;
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;
    sf::Vector2u maxSize;
    std::vector< std::vector< std::vector<Tile*> > >  map;
    sf::Texture tileSheet;
    int size_x;
    int size_y;

public:
    TileMap(std::string texture_file);

    virtual ~TileMap();
    void update(Entity& entity,const float& dt);
    void render(sf::RenderTarget& target);
    void loadFromFile(std::string level);
};


#endif //UNTITLED1_TILEMAP_H
