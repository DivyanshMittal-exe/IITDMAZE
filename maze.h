#ifndef MAZE_H
#define MAZE_H

#include "SDL2/SDL.h"
#include <vector>
#include <string>
#include "Collider.h"
// #include "SDL2/SDL_net.h"

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
    // bool am_i_server;
    // std::string Server_IP;
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