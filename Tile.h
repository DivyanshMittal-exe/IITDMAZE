#pragma once

#include "SDL2/SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "Vector2D.h"
#include <iostream>
#include "maze.h"


class Tile : public Component
{

public:
    // PositionComponent *pos;
    // SpriteComponent *sprite;

    SDL_Texture* tex;
    SDL_Rect srcRect;
    SDL_Rect tile_rect;
    Vector2D location;
    // int tileID;

    Tile(){}
    // ~Tile(){SDL_DestroyTexture(tex);} // As global texture
    ~Tile(){}
    Tile(int x, int y,int w,int h, int id,SDL_Texture* tex_inp){

        tex = tex_inp;
        srcRect.x = (id % 20)*16;
        srcRect.y = (id / 20)*16;
        srcRect.w = srcRect.h = 16;
        tile_rect.x = x*TileScale;
        tile_rect.y = y*TileScale;
        tile_rect.w = w*TileScale;
        tile_rect.h = h*TileScale;
        // tileID = id;
        location.x = x*TileScale;
        location.y = y*TileScale;
    }

    void update() override {
        tile_rect.x = location.x - Maze::cam.x;
        tile_rect.y = location.y - Maze::cam.y;
    }

    void draw() override {
        Texture::Draw(tex,srcRect,tile_rect,SDL_FLIP_NONE);
    }
};





