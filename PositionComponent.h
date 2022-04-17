#pragma once

#include "ECS.h"
#include "Vector2D.h"
#include "map/iitd_bound.h"

// int iitd_bound[84][225] = IITBOUND;

class PositionComponent : public Component
{

public:
    // Can we define it somewhere else
    int bound[84][225] = IITBOUND;

    Vector2D position;
    Vector2D velocity;
    float speed = 5;

    void SetPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    PositionComponent()
    {
        position.x = 0;
        position.y = 0;
        velocity.x = 0;
        velocity.y = 0;
    }
    PositionComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
        velocity.x = 0;
        velocity.y = 0;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override
    {
        if (bound[(int)((position.y + velocity.y * speed + 24) / (16 * 5))][(int)((position.x + 24) / (16 * 5))] != 1)
        {
            position.y += velocity.y * speed;
        }
        if (bound[(int)((position.y + 24) / (16 * 5))][(int)((position.x + velocity.x * speed + 24) / (16 * 5))] != 1)
        {
            position.x += velocity.x * speed;
        }

        // position.x += velocity.x *speed;

        // if (bound[(int) (position.y / (16 * 5))][(int)(position.x / (16 * 5))] == 1) {
        //     std::cout << "C\n";
        //     position.x -= velocity.x *speed;
        //     position.y -= velocity.y *speed;
        //     // velocity.x = 0;
        //     // velocity.y = 0;
        // }
    }
};
