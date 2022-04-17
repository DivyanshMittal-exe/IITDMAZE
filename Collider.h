#pragma once

#include <string>
#include "maze.h"
#include "SDL2/SDL.h"
#include "Vector2D.h"
#include "PositionComponent.h"

class Collider : public Component
{

public:
    SDL_Rect collider;
    std::string tag;
    PositionComponent *pos;

    Collider(std::string tagname)
    {
        tag = tagname;
    }

    void init() override
    {
        if (entity->hasComponent<PositionComponent>() == false)
        {
            entity->addComponent<PositionComponent>();
        }
        pos = &entity->getComponent<PositionComponent>();

        // Maze::maze_colliders.push_back(this);
    }
    void update() override
    {
        collider.x = pos->position.x;
        collider.y = pos->position.y;
        collider.w = 16;
        collider.h = 16;
    }
};
