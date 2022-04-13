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

#define MULTIMODE

#define gMap 0
#define gPlayer 1
#define gEntities 2
// #define PORT 5050

// Add group is different, not entity based, but manager based

struct pack
{
    int type;
    float packet_x;
    float packet_y;
    int packet_sprite;
    int packet_orientation;
};

Manager manager;
Entity &player1(manager.addEntity());
Entity &player2(manager.addEntity());

Entity &flag1(manager.addEntity());
Entity &flag2(manager.addEntity());

SDL_Event Maze::event;
SDL_Renderer* Maze::renderer;
ENetPeer* Maze::peer;

SDL_Rect Maze::cam = {0, 0, gameW, gameH};

Maze::Maze() {}
Maze::~Maze() {}

void Maze::init(const char *title, int xpos, int ypos, int w, int h, bool fs)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Maze initialised \n";
        window = SDL_CreateWindow(title, xpos, ypos, w, h, fs == true ? SDL_WINDOW_FULLSCREEN : 0);
        if (window)
        {
            std::cout << "Made window\n";
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer made\n";
        }

        is_running = true;
    }
    else
    {
        is_running = false;
    }
    std::cout << is_running;

    // SDLNet_Init();

    if (enet_initialize() != 0)
    {
        std::cout << "Initialization failed";
    }

    if (!am_i_server)
    {
        client_server = enet_host_create(NULL, 1, 1, 0, 0);
        if (client_server == NULL)
        {
            std::cout << "client_server Not made";
        }

        enet_address_set_host(&address, Server_IP.c_str());
        address.port = PORT;

        peer = enet_host_connect(client_server, &address, 1, 0);
        if (peer == NULL)
        {
            std::cout << "Peer not available";
        }

        if (enet_host_service(client_server, &enet_event, 50000) > 0 && enet_event.type == ENET_EVENT_TYPE_CONNECT)
        {
            std::cout << "Connected";
        }
    }
    else
    {
        address.host = ENET_HOST_ANY;
        address.port = PORT;
        client_server = enet_host_create(&address, 4, 1, 0, 0);
        if (client_server == NULL)
        {
            std::cout << "client_server failed";
        }
        else
        {
            std::cout << "client_server made";
        }
        if (enet_host_service(client_server, &enet_event, 50000) > 0 && enet_event.type == ENET_EVENT_TYPE_CONNECT)
        {
            peer = enet_event.peer;
            std::cout << "Connected";
        }
    }

    Map *tileMap = new Map("Maze.txt", 25, 22, &manager, gMap);

    player1.addComponent<PositionComponent>();
    player1.addComponent<Controller>();
    player1.addGroup(gPlayer);
    player2.addComponent<PositionComponent>();
    player2.addGroup(gPlayer);

    if (am_i_server)
    {
        player1.addComponent<SpriteComponent>("assets/player1.png");
        player2.addComponent<SpriteComponent>("assets/player2.png");
    }
    else
    {
        player1.addComponent<SpriteComponent>("assets/player2.png");
        player2.addComponent<SpriteComponent>("assets/player1.png");
    }

    player1.getComponenet<PositionComponent>().position.x = gameW / 2;
    player1.getComponenet<PositionComponent>().position.y = gameH / 2;

    player2.getComponenet<PositionComponent>().position.x = gameW / 2;
    player2.getComponenet<PositionComponent>().position.y = gameH / 2;

    gameMode = 1;
}
void Maze::handleEvents()
{
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

void computeWinnerGameMode1()
{
    // implement
}

void gameMode1(bool am_i_done,bool is_opp_done)
{
    if (am_i_done)
    {
        if (is_opp_done)
        {
            computeWinnerGameMode1();
        }
    }
    else
    {
        if (Maze::event.type == SDL_KEYDOWN)
        {
            switch (Maze::event.key.keysym.sym)
            {
            case SDLK_1:
                if (flag1.hasComponent<PositionComponent>() == false)
                {
                    flag1.addComponent<PositionComponent>();
                    flag1.addComponent<SpriteComponent>("assets/flag1.png");
                }

                flag1.getComponenet<PositionComponent>().position = player1.getComponenet<PositionComponent>().position;
                break;
            case SDLK_2:
                if (flag2.hasComponent<PositionComponent>() == false)
                {
                    flag2.addComponent<PositionComponent>();
                    flag2.addComponent<SpriteComponent>("assets/flag2.png");
                }

                flag2.getComponenet<PositionComponent>().position = player1.getComponenet<PositionComponent>().position;
                break;
            default:
                break;
            }
        }
    }
}

void Maze::update()
{
    pack *dat;
    while (enet_host_service(client_server, &enet_event, 0) > 0)
    {
        switch (enet_event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            dat = (pack *)(enet_event.packet->data);
            if (dat->type == 0)
            {
                player2.getComponenet<PositionComponent>().position.x = dat->packet_x;
                player2.getComponenet<PositionComponent>().position.y = dat->packet_y;
            }

            // std::cout << dat->packet_x;

            break;
        default:
            break;
        }
    }

    pack playerData = {0,
                       player1.getComponenet<PositionComponent>().position.x,
                       player1.getComponenet<PositionComponent>().position.y,
                       0,
                       0};
    ENetPacket *packet = enet_packet_create(&playerData, sizeof(playerData), 0);
    enet_peer_send(peer, 0, packet);

    cam.x = player1.getComponenet<PositionComponent>().position.x - gameW / 2;
    cam.y = player1.getComponenet<PositionComponent>().position.y - gameH / 2;
    if (cam.x < 0)
    {
        cam.x = 0;
    }
    if (cam.y < 0)
    {
        cam.y = 0;
    }
    if (cam.x > cam.w)
    {
        cam.x = cam.w;
    }
    if (cam.y > cam.h)
    {
        cam.y = cam.h;
    }

    if (gameMode == 1)
    {
        gameMode1(am_i_done,is_opp_done);
    }

    manager.refresh();
    manager.update();
}

auto &mapTile(manager.getGroup(gMap));
auto &playerTile(manager.getGroup(gPlayer));

void Maze::render()
{
    SDL_RenderClear(renderer);
    // std::cout <<mapTile.size();
    for (auto &x : mapTile)
    {
        x->draw();
    }
    for (auto &x : playerTile)
    {
        x->draw();
    }
    // manager.draw();
    SDL_RenderPresent(renderer);
}
void Maze::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    enet_peer_disconnect(peer, 0);

    while (enet_host_service(client_server, &enet_event, 3000) > 0)
    {
        switch (enet_event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(enet_event.packet);
            /* code */
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "Disconnected client_server";
            break;
        default:
            break;
        }
    }

    enet_host_destroy(client_server);
    enet_deinitialize();

    std::cout << "Game quit succesful\n";
}
