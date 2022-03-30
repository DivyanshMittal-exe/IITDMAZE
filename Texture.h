#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

class Texture
{
public:
     static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);
private:
 
};

#endif