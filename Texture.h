#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "maze.h"
#include "SDL2/SDL_ttf.h"

class Texture
{
public:
     static SDL_Texture *LoadTexture(const char *filename);
     static SDL_Texture *TextTexture(TTF_Font *font, std::string text, int r, int g, int b);
     static void render_text(TTF_Font *font, std::vector < std::string > texts, float y, int r , int g , int b );
     static void render_text(TTF_Font *font, std::string  text, float y, int r , int g , int b );
     static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);

private:
};

#endif