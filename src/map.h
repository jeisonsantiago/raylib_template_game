#ifndef MAP
#define MAP

#include "entities/entity.h"

enum MapLayer{
    MapLayer_Ground = 0,
    MapLayer_Solid,
    MapLayer_Visual,
    MapLayer_Count,
};

struct Map{
    int w = 0;
    int h = 0;

    std::vector<EntityRef> mapData[MapLayer_Count]; // number of MapTile[Ground/Solid/Visual]

    void create(int w, int h);

    EntityRef getBlock(int x, int y, int layer);
};

#endif //
