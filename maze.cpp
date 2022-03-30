#include "maze.h"



gameObject* player1; 

Maze::Maze()
{

}

Maze::~Maze()
{

}


void Maze::init(const char* title, int xpos,int ypos,int w,int h, bool fs){


    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Maze initialised \n";
        window = SDL_CreateWindow(title,xpos,ypos,w,h,fs==true?SDL_WINDOW_FULLSCREEN:0);
        if(window){
        std::cout << "Made window\n";
        }
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            std::cout << "Renderer made\n";
        }
        is_running = true;
    }else{
        is_running = false;
    }
    
    player1 = new gameObject("assets/player1.png",renderer,0,0);

}
void  Maze::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    
    default:
        break;
    }
}

void Maze::update(){
    player1->update();
}
void Maze::render(){
    SDL_RenderClear(renderer);

    player1->render();

    SDL_RenderPresent(renderer);
}
void Maze::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game quit succesful\n";
}

