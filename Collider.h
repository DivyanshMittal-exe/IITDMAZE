#include <string>
#include "SDL2/SDL.h"
#include "Vector2D.h"
#include "PositionComponent.h"



class Collider
{

public:

    SDL_Rect collider;
    std::string tag;

    PositionComponent *pos;
    void init override {
        if (entity->hasComponent<PositionComponent>() == false)
        {
           entity-> addComponent<PositionComponent>();
        }
        pos = entity-> getComponenet<PositionComponent>();
        
    }
    void update() override {
        collider.x = pos->position.x;
        collider.y = pos->position.y;
        collider.w = 16;
        collider.h = 16;
    }
    
};

