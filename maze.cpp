#include "maze.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "Texture.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "Vector2D.h"
#include "ECS.h"
#include "Controller.h"

#define PORT 5050




Manager manager;
Entity& player1(manager.addEntity());
Entity& player2(manager.addEntity());
SDL_Event Maze::event;
SDL_Renderer* Maze::renderer;



Maze::Maze(){}
Maze::~Maze(){}

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
    std::cout << is_running;

    SDLNet_Init();



    player1.addComponent<PositionComponent>();
    player1.addComponent<SpriteComponent>("assets/player1.png");
    player1.addComponent<Controller>();

    me->packet_x = player1.getComponenet<PositionComponent>().position.x;
    me->packet_y = player1.getComponenet<PositionComponent>().position.y;

    player2.addComponent<PositionComponent>();
    player2.addComponent<SpriteComponent>("assets/player1.png");
    if(am_i_server = true){
        SDLNet_ResolveHost(&IP,NULL,PORT);
        server = SDLNet_TCP_Open(&IP);

        client = SDL_Net_TCP_Accept(server);

        
    }else{
        SDLNet_ResolveHost(&IP,Server_IP,PORT);
        client = SDLNet_TCP_Open(&IP);
        client = SDL_Net_TCP_Accept(server);


    }
    

    // player2.getComponenet<PositionComponent>().SetPosition(5,15);

}
void  Maze::handleEvents(){
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
    if(am_i_server){
        if(client){
                
        }
    }else{

    }
    manager.refresh();
    manager.update();
}
void Maze::render(){
    SDL_RenderClear(renderer);
    manager.draw();
    SDL_RenderPresent(renderer);
}
void Maze::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game quit succesful\n";
}

