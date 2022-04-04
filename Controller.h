#pragma once

#include "SDL2/SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "maze.h"

class Controller : public Component{
    public:
        PositionComponent *pos;

        void init() override{
            pos = &entity-> getComponenet<PositionComponent>();

            }
        void update() override {
            if (Maze::event.type == SDL_KEYDOWN)
            {
                switch (Maze::event.key.keysym.sym )
                {
                case SDLK_w:
                    pos->velocity.y = -1;
                    break;
                case SDLK_a:
                    pos->velocity.x = -1;
                    break;
                case SDLK_s:
                    pos->velocity.y = 1;
                    break;
                case SDLK_d:
                    pos->velocity.x = 1;
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
                    break;
                case SDLK_a:
                    pos->velocity.x = 0;
                    break;
                case SDLK_s:
                    pos->velocity.y = 0;
                    break;
                case SDLK_d:
                    pos->velocity.x = 0;
                    break;
                
                default:
                    break;
                }
            }
        }
    };
