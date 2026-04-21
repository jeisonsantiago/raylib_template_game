#include "map.h"

void Map::create(int w, int h)
{
    *this = {}; // reset all the data

    mapData[MapLayer_Ground].resize(w * h); // MapTileGround
    mapData[MapLayer_Solid].resize(w * h); // MapTileSolid
    mapData[MapLayer_Decorations].resize(w * h); // MapTileVisual

    this->w = w;
    this->h = h;

    // for(auto &e: mapSolids){ e = {};} // clear all block data
    for (int i = 0; i < mapData[0].size(); ++i) {
        mapData[MapLayer_Ground][i] = EntityRef::nil();
        mapData[MapLayer_Solid][i] = EntityRef::nil();
        mapData[MapLayer_Decorations][i] = EntityRef::nil();
    }
}

EntityRef Map::getBlock(int x, int y, int layer)
{
    // layer -1 = because in the render layer they are offseted by DEFAULT layer
    return mapData[(layer-1)][x + y * this->w];
}

void Map::setBlock(int x, int y, int layer, EntityRef ref)
{
    mapData[(layer-1)][x + y * this->w] = ref;
}

void Map::createBlock(int x, int y, int layer, int texture_index)
{

}
