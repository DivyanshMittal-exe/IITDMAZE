#pragma once

#include "maze.h"
#include "Component.h"
#include "PositionComponent.h"
#include "Texture.h"
#include "SDL2/SDL.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
    private:
        PositionComponent *position;
        SDL_Texture *texture;
        SDL_Rect srcRect,destRect;

        // bool animated = false;
        //int frames = 0;
        //int speed = 200; //Delay in ms

        

    public:
        bool animated = false;
        int frames = 1;
        int speed = 200; //Delay in ms


        float speedFactor = 1;
        float stamina = 1;
        float money = 1000;
        bool hasyulu = false;
        int animationInd = 0;

        std::map<int, Animation> animations;

        void setText(const char* path){
            texture = Texture::LoadTexture(path);
        }
        SpriteComponent(){}
        SpriteComponent(const char* path){
            texture = Texture::LoadTexture(path);            
        }

        SpriteComponent(const char* path, bool isAnim){
            animated = isAnim;

            Animation idle = Animation(0, 1, 100);
            Animation walkSouth = Animation(0, 4, 100);
            Animation walkNorth = Animation(3, 4, 100);
            Animation walkEast = Animation(2, 4, 100);
            Animation walkWest = Animation(1, 4, 100);

            animations.emplace(0, idle);
            animations.emplace(1, walkSouth);
            animations.emplace(2, walkNorth);
            animations.emplace(3, walkEast);
            animations.emplace(4, walkWest);

            Play(0);

            texture = Texture::LoadTexture(path);            
        }

        ~SpriteComponent(){
            SDL_DestroyTexture(texture);           
        }
        
        void init() override{
            position = &entity -> getComponent<PositionComponent>();
            srcRect.x = srcRect.y = 0;
            // srcRect.w = srcRect.h = 16;
            srcRect.w = srcRect.h = 64;
            destRect.w = destRect.h = 32;
            // Change Collider too if you decide to change these values
        }
        void update() override{

            if (animated) {
                srcRect.x = srcRect.w * (int) ((SDL_GetTicks()/ speed) % frames);
            }
            srcRect.y = animationInd * srcRect.h;

            destRect.x = position->position.x - Maze::cam.x;
            destRect.y = position->position.y - Maze::cam.y;

            //Decresing stamina with time
            // if (stamina > 0) {
            //     stamina -= 0.0002;
            // }
            
            //Stamina and yulu determines speed multiplier
            if (hasyulu) {
                speedFactor = 1 + 0.5 * stamina + 0.5;
                money -= 0.1;
            } else {
                speedFactor = 0.5 * stamina + 0.5;
            }
        }
        void draw() override{
            Texture::Draw(texture,srcRect,destRect, SDL_FLIP_NONE);
        }

        void Play(int animationName) {
            if (hasyulu) {
                animationName += 5;
            }

            //Remember to remove this !!!!!!
            animationName = animationName % 5;
            //end Remember

            frames = animations[animationName].frames;
            animationInd = animations[animationName].index;
            speed = animations[animationName].speed;
        }

};