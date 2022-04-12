#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "maze.h"

class Texture
{
public:
     static SDL_Texture* LoadTexture(const char* filename);
     static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest,SDL_RendererFlip flip);
     // static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* ren);
private:
 
};

#endif