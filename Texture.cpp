#include "Texture.h"
#include "maze.h"
#include <iostream>

SDL_Texture* Texture::LoadTexture(const char* filename){
    SDL_Surface* surf =  IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Maze::renderer,surf);
    SDL_FreeSurface(surf);
    return texture;
}

void Texture::Draw(SDL_Texture * texture, SDL_Rect source_rect, SDL_Rect destination_rect)
{
    // std::cout << "Drawing";

	SDL_RenderCopyEx(Maze::renderer, texture, &source_rect, &destination_rect, NULL, NULL,SDL_FLIP_NONE);
}

// SDL_Texture* Texture::LoadTexture(const char* filename, SDL_Renderer* ren){
//     SDL_Surface* surf =  IMG_Load(filename);
//     SDL_Texture* texture = SDL_CreateTextureFromSurface(ren,surf);
//     SDL_FreeSurface(surf);
//     return texture;
// }