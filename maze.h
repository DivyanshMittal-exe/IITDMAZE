#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"


#pragma once

class Maze
{
private:
    bool is_running;
    SDL_Window* window;

public:
    static SDL_Event event;
    static SDL_Renderer *renderer;

    Maze();
    ~Maze();

    void init(const char* title, int xpos,int ypos,int w,int h, bool fs);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running(){return is_running;}



};

#endif