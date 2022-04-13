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

#define gMap 0
#define gPlayer 1
#define gEntities 2
// #define PORT 5050

// Add group is different, not entity based, but manager based


// struct packet{
//     float packet_x;
//     float packet_y;
//     int packet_sprite;
//     int packet_orientation;
// };

Manager manager;
Entity& player1(manager.addEntity());
// manager.addGroup(player1,gPlayer);
Entity& player2(manager.addEntity());
// manager.addGroup(player2,gPlayer);
SDL_Event Maze::event;
SDL_Renderer* Maze::renderer;

SDL_Rect Maze::cam = {0,0,gameW,gameH};

Maze::Maze(){}
Maze::~Maze(){}

// enum groupName: std::size_t{
//     gMap,gPlayer,gEntities
// }

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

    Map *tileMap = new Map("Maze.txt",25,22,&manager,gMap);

    player1.addComponent<PositionComponent>();
    player1.addComponent<SpriteComponent>("assets/player1.png");
    player1.addComponent<Controller>();
    player1.addGroup(gPlayer);

    // me->packet_x = player1.getComponenet<PositionComponent>().position.x;
    // me->packet_y = player1.getComponenet<PositionComponent>().position.y;

    player2.addComponent<PositionComponent>();
    player2.addComponent<SpriteComponent>("assets/player1.png");
    player2.addGroup(gPlayer);

    player1.getComponenet<PositionComponent>().position.x = gameW/2;
    player1.getComponenet<PositionComponent>().position.y = gameH/2;

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
    manager.refresh();
    manager.update();

    cam.x = player1.getComponenet<PositionComponent>().position.x - gameW/2;
    cam.y = player1.getComponenet<PositionComponent>().position.y - gameH/2;
    if(cam.x < 0){
        cam.x = 0;
    }
    if(cam.y < 0){
        cam.y = 0;
    }
    if (cam.x > cam.w){
        cam.x = cam.w;
    }
     if (cam.y > cam.h){
        cam.y = cam.h;
    }
}

auto& mapTile(manager.getGroup(gMap));
auto& playerTile(manager.getGroup(gPlayer));

void Maze::render(){
    SDL_RenderClear(renderer);
    // std::cout <<mapTile.size();
    for(auto& x : mapTile){
        x->draw();   
    }
    for(auto& x : playerTile){
        x->draw();
    }
    // manager.draw();
    SDL_RenderPresent(renderer);
}
void Maze::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game quit succesful\n";
}

