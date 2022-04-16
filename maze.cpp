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
#include "SDL2/SDL_ttf.h"
#include <bits/stdc++.h>
#include "Tile.h"
#include "Collision.h"
#include "Collider.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include "map/iitd_map.h"
#include "map/iitd_bound.h"
#include "map/building.h"

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
    int packet_anim_ind;
    int packet_anim_frames;
};
// -1 used for exchanging treasure questions
// 0 for player locn and data
// 1 for GameScore
// 2 for guard locn

// In .h file
// 2 -> Yulu
// 3 Eating locations
// 1 Collision Barriers



struct gameState
{
    char gameS;
};

Manager manager;
Entity &player1(manager.addEntity());
Entity &player2(manager.addEntity());

Entity &flag1(manager.addEntity());
Entity &flag2(manager.addEntity());

Entity &guard1(manager.addEntity());

SDL_Event Maze::event;
SDL_Renderer *Maze::renderer;
ENetPeer *Maze::peer;

SDL_Rect Maze::cam = {0, 0, gameW, gameH};

SDL_Texture *w8page = Texture::LoadTexture("assets/Waiting.png");
SDL_Texture *testing = Texture::LoadTexture("assets/maze.png");
SDL_Texture *mazePage = Texture::LoadTexture("assets/maze.png");
SDL_Texture *instrPage = Texture::LoadTexture("assets/general_image.png");
SDL_Rect strtsrc = {0, 0, gameW, gameH};

Tile *map_tiles[84][225];
Tile *build_tiles[84][225];

TTF_Font *abd, *blx, *krm, *prt;

int game2state = 0;
bool objectiveComplete = false;
float myMarks;
float oppMarks;
int find1, find2;

//For Objectives in mode 2
//Objective and the number corresponding to the location in .h file
std::vector<std::pair<std::string, int>> objectives{
    {"Go to Shivalik to meet Divyanis",11},
    {"Go to Shivalik to meet Divyanis2",11},
    {"Go to Shivalik to meet Divyanis",12},
    {"Go to Shivalik to meet Divyanis",13},
    {"Go to Shivalik to meet Divyanis",14},
    {"Go to Shivalik to meet Divyanis",15},
    {"Go to Shivalik to meet Divyanis",16},
    {"Go to Shivalik to meet Divyanis",17},
    {"Go to Shivalik to meet Divyanis",18}
};


//For GeoGuesser
std::vector<std::pair<std::string, std::pair<float, float>>> questions{
    {"The unofficial pizza \n place of IIT Delhi", {72, 48}},
    {"Your first photo was \n probably taken here ", {150, 20}},
    {"The department where you \n will see fancy suits", {72, 75}},
    {"People sitting outside, cant find a spot.\n But the seats are empty inside and you got no money", {143, 25}},
    {"Married to the idea of staying \n on campus a bit more. Or in general", {55, 52}},
    {"The coolest building in town", {131, 59}},
    {"Finally, I can hope \n for an empty court", {112, 43}},
    {"Highest yet youngest of the 13", {92, 11}},
    {"Shakes ?", {42, 15}},
    {"Weaving dreams into reality", {66, 27}},
    {"IC", {41, 36}},
    {"The vintage car that everyone loves", {136, 23}},
    {"Guests stay here. New faculty doesn't", {200, 21}},
    {"Got hurt ?", {101, 28}},
    {"Where do these young kids study?\n They can barely speak, let alone give JEE!", {95, 18}}};

std::vector<std::string> instrPgText;


SDL_Texture *coin = Texture::LoadTexture("assets/coin.png");
SDL_Texture *heart = Texture::LoadTexture("assets/heart.png");
SDL_Texture *trim = Texture::LoadTexture("assets/trim.png");
SDL_Texture *coin_bar = Texture::LoadTexture("assets/money.png");
SDL_Texture *stamina_bar = Texture::LoadTexture("assets/stamina.png");


Maze::Maze() {}
Maze::~Maze() {}

void Maze::init(const char *title, int xpos, int ypos, int w, int h, bool fs)
{
    srand(time(NULL));

    gameMode = 2;

    // initialising SDL,enet, and stuff
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

    if (enet_initialize() != 0)
    {
        std::cout << "Initialization failed" << std::endl;
    }

    TTF_Init();
    abd = TTF_OpenFont("fonts/abduct.ttf", 16);
    blx = TTF_OpenFont("fonts/Blox.ttf", 16);
    krm = TTF_OpenFont("fonts/Karma.ttf", 16);
    prt = TTF_OpenFont("fonts/Prototype.ttf", 16);

    w8page = Texture::LoadTexture("assets/Waiting.png");
    mazePage = Texture::LoadTexture("assets/maze.png");
    instrPage = Texture::LoadTexture("assets/general_image.png");
    
    //Reloading some more assets, not sure why this is required
    coin = Texture::LoadTexture("assets/coin.png");
    heart = Texture::LoadTexture("assets/heart.png");
    trim = Texture::LoadTexture("assets/trim.png");
    coin_bar = Texture::LoadTexture("assets/money.png");
    stamina_bar = Texture::LoadTexture("assets/stamina.png");

    if (gameMode == 1)
    {
        instrPgText.push_back("Your goal is simple\n Look at the hints below and try locating these famous locations on campus\n Press i to place the flag for q1 and o to place flag for q2.\n Once you are satisfied, press Enter to finish your attempt");
    }
    // else if (gameMode == 2)
    // {
    //     instrPgText.push_back("GAME MODE 2");
    // }

    strtsrc = {0, 0, gameW, gameH};

    if (!am_i_server)
    {
        client_server = enet_host_create(NULL, 1, 1, 0, 0);
        if (client_server == NULL)
        {
            std::cout << "client_server Not made" << std::endl;
        }

        enet_address_set_host(&address, Server_IP.c_str());
        address.port = PORT;

        peer = enet_host_connect(client_server, &address, 1, 0);
        if (peer == NULL)
        {
            std::cout << "Peer not available" << std::endl;
        }

        if (enet_host_service(client_server, &enet_event, 1000) > 0 && enet_event.type == ENET_EVENT_TYPE_CONNECT)
        {
            std::cout << "Connected" << std::endl;
        }
    }
    else
    {
        SDL_RenderClear(renderer);
        Texture::Draw(w8page, strtsrc, strtsrc, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);

        address.host = ENET_HOST_ANY;
        address.port = PORT;
        client_server = enet_host_create(&address, 4, 1, 0, 0);
        if (client_server == NULL)
        {
            std::cout << "client_server failed"
                      << std::endl;
        }
        else
        {
            std::cout << "client_server made"
                      << std::endl;
        }
        if (enet_host_service(client_server, &enet_event, 50000) > 0 && enet_event.type == ENET_EVENT_TYPE_CONNECT)
        {
            peer = enet_event.peer;
            std::cout << "Connected\n"
                      << std::endl;
        }

        if (gameMode == 1)
        {
            find1 = rand() % (questions.size());
            find2 = rand() % (questions.size());
            while (find1 == find2)
            {
                find1 = rand() % (questions.size());
                find2 = rand() % (questions.size());
            }
            pack tr_locs = {-1,
                            find1,
                            find2,
                            0,
                            0,
                            0};

            ENetPacket *packet = enet_packet_create(&tr_locs, sizeof(tr_locs), 0);
            enet_peer_send(peer, 0, packet);
            instrPgText.push_back(questions[find1].first);
            instrPgText.push_back(questions[find2].first);
        }
    }

    player1.addComponent<PositionComponent>();
    player1.addGroup(gPlayer);
    player2.addComponent<PositionComponent>();
    player2.addGroup(gPlayer);

    // Start from main gate
    
    player1.getComponent<PositionComponent>().position.x = 167 * 16 * TileScale + 8 * TileScale;
    player1.getComponent<PositionComponent>().position.y = 5 * 16 * TileScale + 8 * TileScale;

    player1.addComponent<Collider>("Me");


    //Guard
    guard1.addComponent<PositionComponent>();
    guard1.addComponent<SpriteComponent>("assets/player1animated.png", true);
    guard1.addComponent<Collider>("Guard");
    guard1.addGroup(gPlayer);
    if (am_i_server)
    {
        guard1.getComponent<PositionComponent>().position.x = 167 * 16 * TileScale + 8 * TileScale;
        guard1.getComponent<PositionComponent>().position.y = 7 * 16 * TileScale + 8 * TileScale;
        guard1.getComponent<SpriteComponent>().Play(3);
        std::cout << "Initially " << guard1.getComponent<SpriteComponent>().animationInd << " " << guard1.getComponent<SpriteComponent>().frames << std::endl;
        guard1.getComponent<PositionComponent>().velocity.x = 1;
    }

    

    flag1.addGroup(gEntities);
    flag2.addGroup(gEntities);

    if (am_i_server)
    {

        player1.addComponent<SpriteComponent>("assets/player1animated.png", true);
        player2.addComponent<SpriteComponent>("assets/player2animated.png", true);
    }
    else
    {
        player1.addComponent<SpriteComponent>("assets/player2animated.png", true);
        player2.addComponent<SpriteComponent>("assets/player1animated.png", true);
    }
    player1.addComponent<Controller>();

    myState = 0;
    opState = 0;
}

float calcuatePoint()
{
    float p1, p2;
    if (flag1.hasComponent<PositionComponent>() == true)
    {
        Vector2D f1loc = flag1.getComponent<PositionComponent>().position;
        std::pair<float, float> l1 = questions[find1].second;
        float l1x = l1.first * 16 * TileScale + 8 * TileScale - f1loc.x;
        float l1y = l1.second * 16 * TileScale + 8 * TileScale - f1loc.y;

        p1 = 100 / ((l1x * l1x + l1y * l1y) + 10);
    }
    else
    {
        p1 = 0;
    }

    if (flag2.hasComponent<PositionComponent>() == true)
    {
        Vector2D f2loc = flag2.getComponent<PositionComponent>().position;
        std::pair<float, float> l2 = questions[find2].second;
        float l2x = l2.first * 16 * TileScale + 8 * TileScale - f2loc.x;
        float l2y = l2.second * 16 * TileScale + 8 * TileScale - f2loc.y;

        p2 = 100 / ((l2x * l2x + l2y * l2y) + 10);
    }
    else
    {
        p2 = 0;
    }

    return p1 + p2;
}

float getDist(const Vector2D& v1,const Vector2D& v2){
    return (v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y);
}

void DisplayParameters(float stamina, float money ,int x = 8*gameW/10,int y = gameH/40 ){
    SDL_Rect src = {0,0,100,16};
    SDL_Rect hdest = {x+gameH/40+16,y,100, 16};
    SDL_Rect cdest = {x+gameH/40+16,y + 25,100, 16};
    SDL_Rect hdest2 = {x+gameH/40+16,y,100*stamina,16};
    SDL_Rect cdest2 = {x+gameH/40+16,y + 25,100*money,16};
    SDL_Rect heart_src = {0,0,64,64};
    SDL_Rect coin_src = {0,0,32,32};
    SDL_Rect heart_dest = {x,y,16,16};
    SDL_Rect coin_dest = {x - 8,y + 25 - 8,32,32};
    
    //icons
    Texture::Draw(heart, heart_src, heart_dest, SDL_FLIP_NONE);
    Texture::Draw(coin, coin_src, coin_dest, SDL_FLIP_NONE);
    //bar
    Texture::Draw(stamina_bar, src, hdest2, SDL_FLIP_NONE);
    Texture::Draw(coin_bar, src, cdest2, SDL_FLIP_NONE);
    //outline
    Texture::Draw(trim, src, hdest, SDL_FLIP_NONE);
    Texture::Draw(trim, src, cdest, SDL_FLIP_NONE);
}

void Maze::handleEvents()
{
    SDL_PollEvent(&event);
    int ypos, xpos;
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;

    case SDL_KEYDOWN:

        switch (Maze::event.key.keysym.sym)
        {
        case SDLK_RETURN:
            if (gameMode == 1)
            {
                if (myState == 0)
                {
                    myState += 1;
                }
                else if (myState == 2 && opState >= 2)
                {
                    myState += 1;
                    myMarks = calcuatePoint();
                    pack points = {1, myMarks, 0, 0, 0};
                    ENetPacket *packet = enet_packet_create(&points, sizeof(points), 0);
                    enet_peer_send(peer, 0, packet);
                }
                gameState g = {(char)myState};
                ENetPacket *packet = enet_packet_create(&g, sizeof(g), 0);
                enet_peer_send(peer, 0, packet);
            }
            break;
        case SDLK_TAB:
            if (gameMode == 1)
            {
                if (myState == 1)
                {
                    myState += 1;
                }
                gameState g = {(char)myState};
                ENetPacket *packet = enet_packet_create(&g, sizeof(g), 0);
                enet_peer_send(peer, 0, packet);
            }
            break;
        case SDLK_i:
            if (gameMode == 1 && myState == 2)
            {
                if (flag1.hasComponent<PositionComponent>() == false)
                {
                    flag1.addComponent<PositionComponent>();
                    flag1.addComponent<SpriteComponent>("assets/flag1.png");
                }

                flag1.getComponent<PositionComponent>().position = player1.getComponent<PositionComponent>().position;
            }
            break;
        case SDLK_o:
            if (gameMode == 1 && myState == 2)
            {
                if (flag2.hasComponent<PositionComponent>() == false)
                {
                    flag2.addComponent<PositionComponent>();
                    flag2.addComponent<SpriteComponent>("assets/flag2.png");
                }

                flag2.getComponent<PositionComponent>().position = player1.getComponent<PositionComponent>().position;
            }
            break;
        case SDLK_j:
            ypos = (cam.y + gameH / 2) / (16 * TileScale);
            xpos = (cam.x + gameW / 2) / (16 * TileScale);
            if (xpos < 225 && ypos < 84 && xpos >= 0 && ypos >= 0)
            {
                if (iit_bound[ypos][xpos] == 2)
                {
                    // Yulu Stands
                    bool col = Collision::AABB(xpos, ypos, player1.getComponent<Collider>());
                    std::cout << "ColYulu " << col << std::endl;
                    if (col)
                    {
                        player1.getComponent<SpriteComponent>().hasyulu = true;
                    }
                }
                else if (iit_bound[ypos][xpos] == 3)
                {
                    // Eating Shops
                    bool col = Collision::AABB(xpos, ypos, player1.getComponent<Collider>());
                    std::cout << "ColEat " << col << std::endl;
                    if (col and player1.getComponent<SpriteComponent>().money >= 50)
                    {
                        player1.getComponent<SpriteComponent>().stamina = 1;
                        player1.getComponent<SpriteComponent>().money -= 50;
                    }
                }

                else if (gameMode == 2 && iit_bound[ypos][xpos] == objectives[game2state].second)
                {
                    // Game Mode 2 objectives
                    bool col = Collision::AABB(xpos, ypos, player1.getComponent<Collider>());
                    std::cout << "ColObjective " << col << std::endl;
                    game2state += 1;
                }

            }
            break;
        case SDLK_k:
            ypos = (cam.y + gameH / 2) / (16 * TileScale);
            xpos = (cam.x + gameW / 2) / (16 * TileScale);
            if (xpos < 225 && ypos < 84 && xpos >= 0 && ypos >= 0)
            {
                if (iit_bound[ypos][xpos] == 2)
                {
                    // Yulu Stands
                    bool col = Collision::AABB(xpos, ypos, player1.getComponent<Collider>());
                    std::cout << "ColYulu " << col << std::endl;
                    if (col)
                    {
                        player1.getComponent<SpriteComponent>().hasyulu = false;
                    }
                }
            }
            
            if (gameMode == 2)
            {
                
            }
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Maze::recievePackets()
{
    pack *pack_data;
    gameState *gameState_data;
    while (enet_host_service(client_server, &enet_event, 0) > 0)
    {
        switch (enet_event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            
            if (pack_data->type == 2)
            {
                guard1.getComponent<PositionComponent>().position.x = pack_data->packet_x;
                guard1.getComponent<PositionComponent>().position.y = pack_data->packet_y;
                guard1.getComponent<SpriteComponent>().animationInd = pack_data->packet_anim_ind;
                guard1.getComponent<SpriteComponent>().frames = pack_data->packet_anim_frames;
                guard1.getComponent<SpriteComponent>().animated = true;
                guard1.getComponent<SpriteComponent>().speed = 100;
            } else if (gameMode == 1)
            {
                if (enet_event.packet->dataLength == 1)
                {
                    gameState_data = (gameState *)(enet_event.packet->data);
                    opState = ((gameState *)(enet_event.packet->data))->gameS;
                }
                else
                {
                    pack_data = (pack *)(enet_event.packet->data);
                    if (pack_data->type == -1)
                    {
                        find1 = (int)(pack_data->packet_x);
                        find2 = (int)(pack_data->packet_y);
                        instrPgText.push_back(questions[find1].first);
                        instrPgText.push_back(questions[find2].first);
                    }
                    else if (pack_data->type == 1)
                    {
                        oppMarks = pack_data->packet_x;
                    }
                    else if (pack_data->type == 0 && myState == 2 && opState == 2)
                    {
                        player2.getComponent<PositionComponent>().position.x = pack_data->packet_x;
                        player2.getComponent<PositionComponent>().position.y = pack_data->packet_y;
                        player2.getComponent<SpriteComponent>().animationInd = pack_data->packet_anim_ind;
                        player2.getComponent<SpriteComponent>().frames = pack_data->packet_anim_frames;
                        player2.getComponent<SpriteComponent>().animated = true;
                        player2.getComponent<SpriteComponent>().speed = 100;
                    }
                }
            }
            else if (gameMode == 2)
            {
                if (enet_event.packet->dataLength == 1)
                {
                }
                else
                {
                    pack_data = (pack *)(enet_event.packet->data);
                    if (pack_data->type == 0)
                    {
                        player2.getComponent<PositionComponent>().position.x = pack_data->packet_x;
                        player2.getComponent<PositionComponent>().position.y = pack_data->packet_y;
                        player2.getComponent<SpriteComponent>().animationInd = pack_data->packet_anim_ind;
                        player2.getComponent<SpriteComponent>().frames = pack_data->packet_anim_frames;
                        player2.getComponent<SpriteComponent>().animated = true;
                        player2.getComponent<SpriteComponent>().speed = 100;
                    }
                }
            } else if (gameMode == 3)
            {
                if (enet_event.packet->dataLength == 1)
                {
                }
                else
                {
                    pack_data = (pack *)(enet_event.packet->data);
                    if (pack_data->type == 0)
                    {
                        player2.getComponent<PositionComponent>().position.x = pack_data->packet_x;
                        player2.getComponent<PositionComponent>().position.y = pack_data->packet_y;
                        player2.getComponent<SpriteComponent>().animationInd = pack_data->packet_anim_ind;
                        player2.getComponent<SpriteComponent>().frames = pack_data->packet_anim_frames;
                        player2.getComponent<SpriteComponent>().animated = true;
                        player2.getComponent<SpriteComponent>().speed = 100;
                    }
                }
            }
            break;
        default:
            break;
        }
    }
}

void Maze::update()
{

    pack playerData = {0,
                       player1.getComponent<PositionComponent>().position.x,
                       player1.getComponent<PositionComponent>().position.y,
                       0,
                       player1.getComponent<SpriteComponent>().animationInd,
                       player1.getComponent<SpriteComponent>().frames};
    ENetPacket *packet = enet_packet_create(&playerData, sizeof(playerData), 0);
    enet_peer_send(peer, 0, packet);

    cam.x = player1.getComponent<PositionComponent>().position.x - gameW / 2;
    cam.y = player1.getComponent<PositionComponent>().position.y - gameH / 2;

    if (cam.x < 0)
    {
        cam.x = 0;
    }
    if (cam.y < 0)
    {
        cam.y = 0;
    }
    if (cam.x > 225 * 16 * TileScale - gameW)
    {
        cam.x = 225 * 16 * TileScale - gameW;
    }
    if (cam.y > 84 * 16 * TileScale - gameH)
    {
        cam.y = 84 * 16 * TileScale - gameH;
    }

    if(am_i_server){
        Vector2D p1 = player1.getComponent<PositionComponent>().position;
        Vector2D p2 = player2.getComponent<PositionComponent>().position;
        Vector2D g = guard1.getComponent<PositionComponent>().position;
        float dist1 = getDist(player1.getComponent<PositionComponent>().position,guard1.getComponent<PositionComponent>().position);
        float dist2 = getDist(player2.getComponent<PositionComponent>().position,guard1.getComponent<PositionComponent>().position);
        if(dist1 < dist2 && dist1 < 20000){
            Vector2D dirn = p1 - g;
            if (dirn.x*dirn.x + dirn.y*dirn.y != 0) {
                guard1.getComponent<PositionComponent>().velocity.x = dirn.x / sqrt(dirn.x*dirn.x + dirn.y*dirn.y);
                guard1.getComponent<PositionComponent>().velocity.y = dirn.y / sqrt(dirn.x*dirn.x + dirn.y*dirn.y);
            }
            
        }else if(dist2 < dist1 && dist2 < 20000){
            Vector2D dirn = p2 - g;
            guard1.getComponent<PositionComponent>().velocity.x = dirn.x / sqrt(dirn.x*dirn.x + dirn.y*dirn.y);
            guard1.getComponent<PositionComponent>().velocity.y = dirn.y / sqrt(dirn.x*dirn.x + dirn.y*dirn.y);
        }

        //Animating Guard
        if (guard1.getComponent<PositionComponent>().velocity.x > 0) {
            guard1.getComponent<SpriteComponent>().Play(3);
        } else if (guard1.getComponent<PositionComponent>().velocity.x < 0)
        {
            guard1.getComponent<SpriteComponent>().Play(4);
        }
        else {
            if (guard1.getComponent<PositionComponent>().velocity.y > 0) {
            guard1.getComponent<SpriteComponent>().Play(1);
            } else if (guard1.getComponent<PositionComponent>().velocity.y < 0)
            {
                guard1.getComponent<SpriteComponent>().Play(2);
            }
        }
    }

    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            int ypos = (player1.getComponent<PositionComponent>().position.y ) / (16 * TileScale) + j;
            int xpos = (player1.getComponent<PositionComponent>().position.x ) / (16 * TileScale) + i;
            if (xpos < 225 && ypos < 84 && xpos >= 0 && ypos >= 0)
            {

                if (iit_bound[ypos][xpos] == 1)
                {
                    bool col = Collision::AABB(xpos, ypos, player1.getComponent<Collider>());
                    // std::cout << "Col " << i << " " << j << " " <<  col << std::endl;
                    if (col)
                    {
                        player1.getComponent<PositionComponent>().position.x += -1 * i * abs(player1.getComponent<PositionComponent>().velocity.x * player1.getComponent<PositionComponent>().speed);
                        player1.getComponent<PositionComponent>().position.y += -1 * j * abs(player1.getComponent<PositionComponent>().velocity.y * player1.getComponent<PositionComponent>().speed);
                    }
                }
            }
            if (am_i_server)
            {
                int gypos = (guard1.getComponent<PositionComponent>().position.y) / (16 * TileScale) + j;
                int gxpos = (guard1.getComponent<PositionComponent>().position.x) / (16 * TileScale) + i;

                if (gxpos < 225 && gypos < 84 && gxpos >= 0 && gypos >= 0)
                {

                    if (iit_bound[gypos][gxpos] == 1)
                    {
                        bool col = Collision::AABB(gxpos, gypos, guard1.getComponent<Collider>());
                        // std::cout << "Col " << i << " " << j << " " <<  col << std::endl;
                        if (col)
                        {
                            guard1.getComponent<PositionComponent>().position.x += -1 * i * abs(guard1.getComponent<PositionComponent>().velocity.x * guard1.getComponent<PositionComponent>().speed);
                            guard1.getComponent<PositionComponent>().position.y += -1 * j * abs(guard1.getComponent<PositionComponent>().velocity.y * guard1.getComponent<PositionComponent>().speed);
                            if(abs(guard1.getComponent<PositionComponent>().velocity.x)>abs(guard1.getComponent<PositionComponent>().velocity.y)){
                                guard1.getComponent<PositionComponent>().velocity.x = 0;
                                guard1.getComponent<PositionComponent>().velocity.y = std::rand() % 2 ? -1: 1;
                            }else{
                                guard1.getComponent<PositionComponent>().velocity.y = 0;
                                guard1.getComponent<PositionComponent>().velocity.x = std::rand() % 2 ? -1: 1;
                            }
                        }
                    }
                }
                //std::cout << "sending " << guard1.getComponent<SpriteComponent>().animationInd << " " << guard1.getComponent<SpriteComponent>().frames << " " << guard1.getComponent<SpriteComponent>().speed << " " << guard1.getComponent<SpriteComponent>().animated<< std::endl;
                pack guard1Data = {2,
                                   guard1.getComponent<PositionComponent>().position.x,
                                   guard1.getComponent<PositionComponent>().position.y,
                                   0,
                                   guard1.getComponent<SpriteComponent>().animationInd,
                                   guard1.getComponent<SpriteComponent>().frames};
                ENetPacket *packet = enet_packet_create(&guard1Data, sizeof(guard1Data), 0);
                enet_peer_send(peer, 0, packet);
            }
        }
    }

    manager.refresh();
    manager.update();
}

// auto &mapTile(manager.getGroup(gMap));
auto &playerTile(manager.getGroup(gPlayer));
auto &entTile(manager.getGroup(gEntities));

void Maze::render()
{
    SDL_RenderClear(renderer);
    if (gameMode == 1)
    {
        if (myState == 0)
        {
            Texture::Draw(mazePage, strtsrc, strtsrc, SDL_FLIP_NONE);

        }
        else if (myState == 1)
        {
            Texture::Draw(instrPage, strtsrc, strtsrc, SDL_FLIP_NONE);
            Texture::render_text(prt, instrPgText, 30, 255, 255, 255);
        }
        else if (opState == 0 || opState == 1)
        {
            Texture::Draw(w8page, strtsrc, strtsrc, SDL_FLIP_NONE);
        }
        else if (myState == 2 && opState >= 2)
        {
            for (int j = 0; j <= gameH / (16 * TileScale) + 1; j++)
            {
                for (int i = 0; i <= gameW / (16 * TileScale) + 1; i++)
                {
                    int ypos = cam.y / (16 * TileScale) + j;
                    int xpos = cam.x / (16 * TileScale) + i;
                    if (xpos < 225 && ypos < 84)
                    {
                        if (!map_tiles[ypos][xpos])
                        {
                            map_tiles[ypos][xpos] = new Tile(xpos * 16, ypos * 16, 16, 16, iit_map[ypos][xpos]);
                        }
                        

                        map_tiles[ypos][xpos]->update();
                        map_tiles[ypos][xpos]->draw();

                        if(iit_build[ypos][xpos] != -1){
                            if (!build_tiles[ypos][xpos])
                            {
                                build_tiles[ypos][xpos] = new Tile(xpos * 16, ypos * 16, 16, 16, iit_build[ypos][xpos]);
                            }
                            build_tiles[ypos][xpos]->update();
                            build_tiles[ypos][xpos]->draw();
                        }
                    }
                }
            }

            for (auto &x : playerTile)
            {
                x->draw();
            }
            for (auto &x : entTile)
            {
                x->draw();
            }
        }
        else if (myState == 3 && opState == 2)
        {
            Texture::Draw(w8page, strtsrc, strtsrc, SDL_FLIP_NONE);
        }
        else if (myState == 3 && opState == 3)
        {
            Texture::Draw(instrPage, strtsrc, strtsrc, SDL_FLIP_NONE);

            if (myMarks > oppMarks)
            {
                Texture::render_text(blx, "You won!", 50, 255, 255, 255);
            }
            else if (myMarks == oppMarks)
            {
                Texture::render_text(blx, "Its a tie!", 50, 255, 255, 255);
            }
            else
            {
                Texture::render_text(blx, "You lost,better luck next time", 50, 255, 255, 255);
            }
        }
    }
    else if (gameMode == 2)
    {

        for (int j = 0; j <= gameH / (16 * TileScale) + 1; j++)
        {
            for (int i = 0; i <= gameW / (16 * TileScale) + 1; i++)
            {
                int ypos = cam.y / (16 * TileScale) + j;
                int xpos = cam.x / (16 * TileScale) + i;
                if (xpos < 225 && ypos < 84)
                {
                    if (!map_tiles[ypos][xpos])
                    {
                        map_tiles[ypos][xpos] = new Tile(xpos * 16, ypos * 16, 16, 16, iit_map[ypos][xpos]);
                    }

                    map_tiles[ypos][xpos]->update();
                    map_tiles[ypos][xpos]->draw();

                    if(iit_build[ypos][xpos] != -1){
                            if (!build_tiles[ypos][xpos])
                            {
                                build_tiles[ypos][xpos] = new Tile(xpos * 16, ypos * 16, 16, 16, iit_build[ypos][xpos]);
                            }
                            build_tiles[ypos][xpos]->update();
                            build_tiles[ypos][xpos]->draw();
                        }
                }
            }
        }

        for (auto &x : playerTile)
        {
            x->draw();
        }
        for (auto &x : entTile)
        {
            x->draw();
        }
        
        Texture::render_text(prt, objectives[game2state].first, 30, 255, 255, 255);

        DisplayParameters(player1.getComponent<SpriteComponent>().stamina, player1.getComponent<SpriteComponent>().money/1000);

        
    }else if (gameMode == 3)
    {

        for (int j = 0; j <= gameH / (16 * TileScale) + 1; j++)
        {
            for (int i = 0; i <= gameW / (16 * TileScale) + 1; i++)
            {
                int ypos = cam.y / (16 * TileScale) + j;
                int xpos = cam.x / (16 * TileScale) + i;
                if (xpos < 225 && ypos < 84)
                {
                    if (!map_tiles[ypos][xpos])
                    {
                        map_tiles[ypos][xpos] = new Tile(xpos * 16, ypos * 16, 16, 16, iit_map[ypos][xpos]);
                    }

                    map_tiles[ypos][xpos]->update();
                    map_tiles[ypos][xpos]->draw();

                    if(iit_build[ypos][xpos] != -1){
                            if (!build_tiles[ypos][xpos])
                            {
                                build_tiles[ypos][xpos] = new Tile(xpos * 16, ypos * 16, 16, 16, iit_build[ypos][xpos]);
                            }
                            build_tiles[ypos][xpos]->update();
                            build_tiles[ypos][xpos]->draw();
                        }
                }
            }
        }

        for (auto &x : playerTile)
        {
            x->draw();
        }
        for (auto &x : entTile)
        {
            x->draw();
        }
    }

    SDL_RenderPresent(renderer);
}
void Maze::clean()
{
    TTF_CloseFont(abd);
    TTF_CloseFont(blx);
    TTF_CloseFont(krm);
    TTF_CloseFont(prt);

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
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            std::cout << "Disconnected client_server\n";
            break;
        default:
            break;
        }
    }

    enet_host_destroy(client_server);
    enet_deinitialize();

    std::cout << "Game quit succesful\n";
}
