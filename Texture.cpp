#include "Texture.h"

SDL_Texture* Texture::LoadTexture(const char* filename, SDL_Renderer* ren){
    SDL_Surface* surf =  IMG_Load(filename);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,surf);
    SDL_FreeSurface(surf);
    return tex;
}