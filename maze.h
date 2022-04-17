#pragma once

#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <vector>
#include <string>
#include "Collider.h"
#include <enet/enet.h>
#include "Texture.h"


#define TileScale 5
#define gameH 600
#define gameW 800
#define PORT 6666

class Maze
{
private:
    bool is_running;
    SDL_Window* window;

public:
    static SDL_Event event;
    static SDL_Renderer *renderer;
    static std::vector<Collider*> maze_colliders;

    static SDL_Rect cam;
    bool am_i_server;
    std::string Server_IP;
    ENetHost* client_server;
    ENetAddress address;
    ENetEvent enet_event;
    static ENetPeer* peer;
    static Mix_Chunk *walk;

    int gameMode;
    char opState;
    char myState;


    Maze();
    ~Maze();

    void init(const char* title, int xpos,int ypos,int w,int h, bool fs);
    void handleEvents();
    void recievePackets();
    void update();
    void render();
    void clean();
    bool running(){return is_running;}



};

#endif