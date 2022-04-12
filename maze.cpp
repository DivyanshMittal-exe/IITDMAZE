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
#include "Map.h"
#include <bits/stdc++.h>


// #define PORT 5050

// Add group is different, not entity based, but manager based


struct packet{
    float packet_x;
    float packet_y;
    int packet_sprite;
    int packet_orientation;
};

Manager manager;
Entity& player1(manager.addEntity());
// manager.addGroup(player1,gPlayer);
Entity& player2(manager.addEntity());
// manager.addGroup(player2,gPlayer);
// SDL_Event Maze::event;
// SDL_Renderer* Maze::renderer;



Maze::Maze(){}
Maze::~Maze(){}

enum groupName: std::size_t{
    gMap,gPlayer,gEntities
};

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

    // SDLNet_Init();

    Map *tileMap = new Map("Maze.txt",25,22,manager,gMap);

    player1.addComponent<PositionComponent>();
    player1.addComponent<SpriteComponent>("assets/player1.png");
    player1.addComponent<Controller>();
    player1.addGroup(gPlayer);

    // me->packet_x = player1.getComponenet<PositionComponent>().position.x;
    // me->packet_y = player1.getComponenet<PositionComponent>().position.y;

    player2.addComponent<PositionComponent>();
    player2.addComponent<SpriteComponent>("assets/player1.png");
    player2.addGroup(gPlayer);

    // if(am_i_server = true){
    //     SDLNet_ResolveHost(&IP,NULL,PORT);
    //     server = SDLNet_TCP_Open(&IP);

    //     client = SDL_Net_TCP_Accept(server);

        
    // }else{
    //     SDLNet_ResolveHost(&IP,Server_IP,PORT);
    //     client = SDLNet_TCP_Open(&IP);
    //     client = SDL_Net_TCP_Accept(server);


    // }
    

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
    // if(am_i_server){
    //     if(client){
                
    //     }
    // }else{

    // }
    manager.refresh();
    manager.update();
}

auto& mapTile(manager.getGroup(gMap));
auto& playerTile(manager.getGroup(gPlayer));

void Maze::render(){
    SDL_RenderClear(renderer);
    for(auto& x : mapTile){
        x->draw();
    }
    for(auto& x : playerTile){
        x->draw();
    }
    manager.draw();
    SDL_RenderPresent(renderer);
}
void Maze::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game quit succesful\n";
}

