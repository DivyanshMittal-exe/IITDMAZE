#pragma once

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "maze.h"
#include <string>

using namespace std;

const int FPS = 60;
const int frameDelay = 1000 / FPS;

int frameTime;

Maze *maze = nullptr;

int main(int argc, char *argv[])
{

    if(argc != 2){
        std::cout << "Incorrect input";
        return EXIT_FAILURE;
    }
    maze = new Maze();
    if (!(strcmp(argv[1], "1") && strcmp(argv[1], "2")))
    {

        maze->am_i_server = true;
        maze->gameMode = atoi(argv[1]);
    }
    else
    {
        maze->am_i_server = false;
        maze->Server_IP = argv[1];
    }

    maze->init("IITD Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameW, gameH, false);

    while (maze->running())
    {
        frameTime = SDL_GetTicks();
        maze->handleEvents();
        maze->recievePackets();
        maze->update();
        maze->render();
        frameTime = SDL_GetTicks() - frameTime;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    maze->clean();

    return 0;
}