#pragma once

#include "SDL2/SDL.h"
#include "Collider.h"

class Collision
{

public:
    static bool AABB(const SDL_Rect &a, const SDL_Rect &b)
    {
        return (
            (a.x + a.w >= b.x) &&
            (b.x + b.w >= a.x) &&
            (a.y + a.h >= b.y) &&
            (b.y + b.h >= a.y));
    }

    static bool AABB(const Collider &a, const Collider &b)
    {
        return AABB(a.collider, b.collider);
    }
    static bool AABB(const int &i, const int &j, const Collider &player)
    {
        bool xCollided = ((i + 1) * 16 * TileScale >= player.collider.x) && (player.collider.x + player.collider.w >= i * 16 * TileScale);
        bool yCollided = ((j + 1) * 16 * TileScale >= player.collider.y) && (player.collider.y + player.collider.h >= j * 16 * TileScale);

        // bool xCollided = ((i+1)* 16* TileScale >= (player.collider.x + player.collider.w / 2)) &&  ((player.collider.x + player.collider.w / 2)>= i* 16* TileScale);
        // bool yCollided = ((j+1)* 16* TileScale >= (player.collider.y + player.collider.h / 2)) &&  ((player.collider.y + player.collider.h / 2) >= j* 16* TileScale);
        // if (xCollided && yCollided)
        //     return 1;
        // if (xCollided)
        //     return 1;
        // if (yCollided)
        //     return 2;
        // return 0;

        return (xCollided && yCollided);
    }
};
