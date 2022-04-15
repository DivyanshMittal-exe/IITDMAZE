#include "Texture.h"
#include "maze.h"
#include <iostream>

SDL_Texture *Texture::LoadTexture(const char *filename)
{
    SDL_Surface *surf = IMG_Load(filename);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Maze::renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

SDL_Texture *Texture::TextTexture(TTF_Font *font, std::string text, int r, int g, int b)
{
    SDL_Surface *surf = TTF_RenderText_Blended_Wrapped(font, text.c_str(), {r, g, b},700);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Maze::renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

void Texture::render_text(TTF_Font *font, std::string  text, float y, int r = 255, int g = 255, int b = 255)
{

        SDL_Texture *text_texture = Texture::TextTexture(font, text ,r,g,b);
        int w, h;
        // if (!TTF_SizeText(font, (text).c_str(), &w, &h))
        if(!SDL_QueryTexture(text_texture,NULL,NULL,&w,&h))
        {
            SDL_Rect textBox;
            textBox.x = (gameW - w)/2;
            textBox.y = y;
            textBox.w = w;
            textBox.h = h;
            SDL_RenderCopy(Maze::renderer,text_texture,NULL,&textBox);
        }
}


void Texture::render_text(TTF_Font *font, std::vector < std::string > texts, float y, int r = 255, int g = 255, int b = 255)
{
    int ypos = y;
    for (auto it = texts.begin(); it != texts.end(); it++)
    {
        SDL_Texture *text_texture = Texture::TextTexture(font, *it ,r,g,b);
        int w, h;
        if (!TTF_SizeText(font, (*it).c_str(), &w, &h))
        {
            SDL_Rect textBox;
            textBox.x = (gameW - w)/2;
            textBox.y = ypos;
            textBox.w = w;
            textBox.h = h;
            ypos += h + 32;
            SDL_RenderCopy(Maze::renderer,text_texture,NULL,&textBox);
            // Texture::Draw(text_texture,textBox,NULL, SDL_FLIP_NONE);
        }
    }
}

void Texture::Draw(SDL_Texture *texture, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    SDL_RenderCopyEx(Maze::renderer, texture, &source_rect, &destination_rect, NULL, NULL, flip);
}
