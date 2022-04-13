#include "SDL2/SDL.h"
#include "Collider.h"

class Collision
{

public:
    static bool AABB(const SDL_Rect& a,const SDL_Rect& b){
        return (
            (a.x + a.w >= b.x) &&
            (b.x + b.w >= a.x) &&
            (a.y + a.h >= b.y) &&
            (b.y + b.h >= a.y) 
        );
    }

    static bool AABB(const Collider& a,const Collider& b){
        return AABB(a.collider,b.collider);
    }
};
