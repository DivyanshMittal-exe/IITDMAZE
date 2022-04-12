#include "SDL2/SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

class Tile
{

public:
    PositionComponent *pos;
    SpriteComponent *sprite;

    SDL_Rect tile_rect;
    int tileID;

    Tile(){}
    Tile(int x, int y,int w,int h, int id){
        tile_rect.x = x;
        tile_rect.y = y;
        tile_rect.w = w;
        tile_rect.h = h;
        tileID = id;
    }
    void init override{
        entity-> addComponent<PositionComponent>(tile_rect.x,tile_rect.y);
        pos = &entity -> getComponenet<PositionComponent>();

        entity-> addComponent<SpriteComponent>();
        sprite = &entity -> getComponenet<SpriteComponent>();
    }
};





