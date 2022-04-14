#pragma once

#include "ECS.h"
#include "Vector2D.h"

class PositionComponent: public Component
{

    public:

    Vector2D position;
    Vector2D velocity;
    float speed = 5;

    void SetPosition(float x, float y){
        position.x  = x;
        position.y =  y;
    }
    
    PositionComponent(){
        position.x  = 0;
        position.y =  0;
        velocity.x = 0;
        velocity.y = 0;
    }
    PositionComponent(float x, float y){
        position.x  = x;
        position.y =  y;
        velocity.x = 0;
        velocity.y = 0;
    }
    
    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override{
        position.x += velocity.x *speed;
        position.y += velocity.y *speed;
    }

    
};

