#include "gameObject.h"
#include "Texture.h"

gameObject::gameObject(const char* texture,SDL_Renderer* ren,int x,int y)
{
    renderer = ren;
    objTexture = Texture::LoadTexture(texture,ren);
    xpos = x;
    ypos = y;
}

void gameObject::update()
{
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w*2;
    destRect.h = srcRect.h*2;
}


void gameObject::render()
{
    SDL_RenderCopy(renderer,objTexture,&srcRect,&destRect);
}