#pragma once

#include "SDL2/SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "maze.h"

class Controller : public Component{
    public:
        PositionComponent *pos;
        SpriteComponent *sprite;

        void init() override{
            pos = &entity-> getComponenet<PositionComponent>();
            sprite = &entity-> getComponenet<SpriteComponent>();
            }
        void update() override {
            if (Maze::event.type == SDL_KEYDOWN)
            {
                switch (Maze::event.key.keysym.sym )
                {
                case SDLK_w:
                    pos->velocity.y = -1;
                    sprite-> Play("WalkN");
                    break;
                case SDLK_a:
                    pos->velocity.x = -1;
                    sprite-> Play("WalkW");
                    break;
                case SDLK_s:
                    pos->velocity.y = 1;
                    sprite-> Play("WalkS");
                    break;
                case SDLK_d:
                    pos->velocity.x = 1;
                    sprite-> Play("WalkE");
                    break;
                
                default:
                    break;
                }
            }
            if(Maze::event.type == SDL_KEYUP){
                switch (Maze::event.key.keysym.sym )
                {
                case SDLK_w:
                    pos->velocity.y = 0;
                    sprite-> Play("Idle");
                    break;
                case SDLK_a:
                    pos->velocity.x = 0;
                    sprite-> Play("Idle");
                    break;
                case SDLK_s:
                    pos->velocity.y = 0;
                    sprite-> Play("Idle");
                    break;
                case SDLK_d:
                    pos->velocity.x = 0;
                    sprite-> Play("Idle");
                    break;
                
                default:
                    break;
                }
            }
        }
    };
