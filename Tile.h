#include "SDL2/SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include <iostream>

class Tile : public Component
{

public:
    // PositionComponent *pos;
    // SpriteComponent *sprite;

    SDL_Texture* tex;
    SDL_Rect srcRect;
    SDL_Rect tile_rect;
    // int tileID;

    Tile(){}
    ~Tile(){SDL_DestroyTexture(tex);}
    Tile(int x, int y,int w,int h, int id){

        tex = Texture::LoadTexture("Test_Map.png");
        srcRect.x = (id % 15)*16;
        srcRect.y = (id / 15);
        std::cout << id<<" ";
        // std::cout << srcRect.y;
        srcRect.y *= 16;
        srcRect.w = srcRect.h = 16;
        tile_rect.x = x;
        tile_rect.y = y;
        tile_rect.w = w;
        tile_rect.h = h;
        // tileID = id;
    }

    void draw() override {
        Texture::Draw(tex,srcRect,tile_rect,SDL_FLIP_NONE);
        // std::cout << srcRect.x << " ";
        // std::cout << srcRect.y<< "\n";
    }
};





