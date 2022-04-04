#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "maze.h"


using namespace std;

const int FPS = 60;
const int frameDelay = 1000/60;

int frameTime;

Maze *maze = nullptr;

int main(){

    maze = new Maze();
    maze -> init("IITD Maze",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);

    while(maze->running()){

        frameTime = SDL_GetTicks();
        maze->handleEvents();
        maze->update();
        maze->render();
        frameTime = SDL_GetTicks() - frameTime ;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    maze->clean();

    return 0;
}