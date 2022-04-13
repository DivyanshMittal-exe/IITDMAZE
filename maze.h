#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include "Collider.h"
#include <enet/enet.h>

// #include "SDL2/SDL_net.h"

// Collider nhi chalte 
// Unko sort karlena

#define gameH 600
#define gameW 800
#define PORT 6667

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
    // ENetHost* client;
    ENetAddress address;
    ENetEvent enet_event;
    static ENetPeer* peer;

    int gameMode;

    bool am_i_ready = false;
    bool is_opp_ready = false;

    bool am_i_done = false;
    bool is_opp_done = false;

    // // IPaddress IP;
    // // TCPsocket server;
    // // TCPsocket client;

    // packet* me;
    // packet* opponent;

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