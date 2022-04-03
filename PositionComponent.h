#pragma once

#include "ECS.h"

class PositionComponent: public Component
{
private:
    int xpos = 0;
    int ypos = 0;

    public:
    void SetPosition(int x, int y){
        xpos = x;
        ypos = y;
    }
    
    PositionComponent(){
        SetPosition(0,0);
    }
    PositionComponent(int x, int y){
        SetPosition(x,y);
    }
    int x(){return xpos;}
    int x(int a){xpos = a;}
    int y(){return ypos;}
    int y(int a){ypos = a;}

    
};

