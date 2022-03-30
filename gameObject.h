#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class gameObject
{
public:
    gameObject(const char* texture,SDL_Renderer* ren,int x,int y);
    ~gameObject();

    void render();
    void update();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect,destRect;
    SDL_Renderer* renderer;

};

#endif