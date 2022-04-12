#include <string>
#include <fstream>
#include "ECS.h"
#include "Tile.h"
#include "maze.h"

class Map
{

public:
    Map(std::string map_path,int x,int y,Manager manager,size_t g){
        std::fstream map;
        map.open(map_path);
        int tileID;
        for(int i = 0;i < x; i++){
            for(int j = 0; j < y; j++){
                map >> tileID;
                auto& tile (manager.addEntity());
                tile.addComponent<Tile>(x*16,y*16,16,16,tileID);
                tile.addGroup(g);
            }
        }
        map.close();
    }
    Map();
    ~Map();
};

