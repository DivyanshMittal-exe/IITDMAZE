#include <string>
#include <fstream>
#include "ECS.h"
#include "Tile.h"
#include "maze.h"
#include "map/iitd_map.h"

class Map
{

public:
    Map(int x,int y,Manager *manager,size_t g){

        int tileID;
        for(int i = 0;i < x; i++){
            for(int j = 0; j < y; j++){
                tileID = iit_map[i][j];
                auto& tile (manager->addEntity());
                tile.addComponent<Tile>(i*16,j*16,16,16,tileID);
                // manager->addGroup(&tile,g);
                tile.addGroup(g);
            }
        }
    }
    Map();
    ~Map();
};

