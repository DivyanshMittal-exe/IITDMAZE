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
            pos = &entity-> getComponent<PositionComponent>();
            sprite = &entity-> getComponent<SpriteComponent>();
            }
        void update() override {
            if (Maze::event.type == SDL_KEYDOWN)
            {
                switch (Maze::event.key.keysym.sym )
                {
                case SDLK_w:
                    pos->velocity.y = -1 * (sprite-> speedFactor);
                    //North
                    // sprite-> Play(2);
                    break;
                case SDLK_a:
                    pos->velocity.x = -1 * (sprite-> speedFactor);
                    //West
                    // sprite-> Play(4);
                    break;
                case SDLK_s:
                    pos->velocity.y = 1 * (sprite-> speedFactor);
                    //South
                    // sprite-> Play(1);
                    break;
                case SDLK_d:
                    pos->velocity.x = 1 * (sprite-> speedFactor);
                    //East
                    // sprite-> Play(3);
                    break;
                // Picking yulu
                
                // case SDLK_j:
                //     sprite-> hasyulu = true;
                //     break;
                // case SDLK_k:
                //     sprite-> hasyulu = false;
                //     break;
                default:
                    break;
                }
            }
            if(Maze::event.type == SDL_KEYUP){
                switch (Maze::event.key.keysym.sym )
                {
                case SDLK_w:
                    pos->velocity.y = 0;
                    //// sprite-> Play(0);
                    sprite->frames = 1;
                    break;
                case SDLK_a:
                    pos->velocity.x = 0;
                    //// sprite-> Play(0);
                    sprite->frames = 1;
                    break;
                case SDLK_s:
                    pos->velocity.y = 0;
                    //// sprite-> Play(0);
                    sprite->frames = 1;
                    break;
                case SDLK_d:
                    pos->velocity.x = 0;
                    //// sprite-> Play(0);
                    sprite->frames = 1;
                    break;
                
                default:
                    break;
                }
            }
        }
    };
// #pragma once


// #include "SDL2/SDL.h"
// #include "ECS.h"
// #include "PositionComponent.h"
// #include "maze.h"

// class Controller : public Component
// {
// private:
//     bool is_walking;

// public:
//     PositionComponent *pos;
//     SpriteComponent *sprite;

//     void init() override
//     {
//         pos = &entity->getComponent<PositionComponent>();
//         sprite = &entity->getComponent<SpriteComponent>();
//         is_walking = false;
//     }
//     void update() override
//     {
//         if (pos->velocity.x != 0 || pos->velocity.y != 0)
//         {
//             if (!is_walking)
//             {
//                 is_walking = true;

//                 if (pos->velocity.x > 0)
//                 {
//                     sprite->Play(3);
//                 }
//                 else if (pos->velocity.x < 0)
//                 {
//                     sprite->Play(4);
//                 }
//                 else if (pos->velocity.y > 0)
//                 {
//                     sprite->Play(1);
//                 }
//                 else if (pos->velocity.y < 0)
//                 {
//                     sprite->Play(2);
//                 }
//                 std::cout << "Walking";
//                 Mix_PlayChannel(0,Maze::walk,-1);
//             }
//             else
//             {
//                 is_walking = false;
//                 sprite->frames = 1;
//             }
//         }
//         if (Maze::event.type == SDL_KEYDOWN && Maze::event.key.repeat == 0)
//         {
//             switch (Maze::event.key.keysym.sym)
//             {
//             case SDLK_w:
//                 if(!pos->velocity.y){
//                     is_walking = false;
//                 }
//                 pos->velocity.y = -1 * (sprite->speedFactor);
//                 // North
//                 // sprite->Play(2);
//                 break;
//             case SDLK_a:
//             if(!pos->velocity.x){
//                     is_walking = false;
//                 }
//                 pos->velocity.x = -1 * (sprite->speedFactor);
//                 // West
//                 // sprite->Play(4);
                

//                 break;
//             case SDLK_s:
//             if(!pos->velocity.y){
//                     is_walking = false;
//                 }
//                 pos->velocity.y = 1 * (sprite->speedFactor);
//                 // South
//                 // sprite->Play(1);
                

//                 break;
//             case SDLK_d:
//             if(!pos->velocity.x){
//                     is_walking = false;
//                 }
//                 pos->velocity.x = 1 * (sprite->speedFactor);
//                 // East
//                 // sprite->Play(3);
                

//                 break;
//             // Picking yulu

//             // case SDLK_j:
//             //     sprite-> hasyulu = true;
//             //     break;
//             // case SDLK_k:
//             //     sprite-> hasyulu = false;
//             //     break;
//             default:
//                 break;
//             }
//         }
//         if (Maze::event.type == SDL_KEYUP)
//         {
//             switch (Maze::event.key.keysym.sym)
//             {
//             case SDLK_w:
//                 pos->velocity.y = 0;
//                 // // sprite-> Play(0);
//                 sprite->frames = 1;
//                 break;
//             case SDLK_a:
//                 pos->velocity.x = 0;
//                 // // sprite-> Play(0);
//                 sprite->frames = 1;
//                 break;
//             case SDLK_s:
//                 pos->velocity.y = 0;
//                 // // sprite-> Play(0);
//                 sprite->frames = 1;
//                 break;
//             case SDLK_d:
//                 pos->velocity.x = 0;
//                 // // sprite-> Play(0);
//                 sprite->frames = 1;
//                 break;

//             default:
//                 break;
//             }
//         }
//     }
// };