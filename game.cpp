#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "maze.h"


using namespace std;

const int FPS = 1;
const int frameDelay = 1000/60;

int frameTime;

Maze *maze = nullptr;

int main(int argc, char* argv[]){

    maze = new Maze();
    // if(argc = 1){
    //     maze->am_i_server = true;
    // }
    // else {
    //     maze->am_i_server = false;
    // }

    maze -> init("IITD Maze",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);

    

    while(maze->running()){
        // std::cout << "Hello Game";
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