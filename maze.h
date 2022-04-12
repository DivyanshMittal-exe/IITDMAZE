#pragma once

#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include <vector>
#include "Collider.h"
#include "SDL2/SDL_net.h"

// Collider nhi chalte 
// Unko sort karlena



class Maze
{
private:
    bool is_running;
    SDL_Window* window;

public:
    static SDL_Event event;
    static SDL_Renderer *renderer;
    static std::vector<Collider*> maze_colliders;
    static bool am_i_server;
    static IPaddress ip_add;

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