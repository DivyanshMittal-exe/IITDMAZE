#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "Texture.h"
#include "gameObject.h"

#pragma once

class Maze
{
public:
    Maze();
    ~Maze();

    void init(const char* title, int xpos,int ypos,int w,int h, bool fs);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running(){return is_running;}

    SDL_Renderer *renderer;


private:
    bool is_running;
    SDL_Window* window;
};

#endif