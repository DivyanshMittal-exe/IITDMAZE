#pragma once

#include "Component.h"
#include "PositionComponent.h"
#include "Texture.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
    private:
        PositionComponent *position;
        SDL_Texture *texture;
        SDL_Rect srcRect,destRect;

    public:
        void setText(const char* path){
            std::cout << "Texture laga diya ";
            texture = Texture::LoadTexture(path);
        }
        SpriteComponent(){}
        SpriteComponent(const char* path){
            std::cout << "Made";
            texture = Texture::LoadTexture(path);            
        }
        
        void init() override{
            position = &entity -> getComponenet<PositionComponent>();
            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = 16;
            destRect.w = destRect.h = 32;
            // Change Collider too if you decide to change these values
        }
        void update() override{
            destRect.x = position->position.x;
            destRect.y = position->position.y;

        }
        void draw() override{
            Texture::Draw(texture,srcRect,destRect, SDL_FLIP_NONE);
        }

};