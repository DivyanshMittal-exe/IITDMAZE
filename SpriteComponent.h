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
        SpriteComponent() = default;
        SpriteComponent(const char* path){
            setText(path);            
        }
        
        void init() override{
            position = &entity -> getComponenet<PositionComponent>();
            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.y = 16;
            destRect.w = destRect.y = 32;
        }
        void update() override{
            destRect.x = position->position.x;
            destRect.y = position->position.y;

        }
        void draw() override{
            // std::cout << "Drawing";
            Texture::Draw(texture,srcRect,destRect);
        }

};