#include "map.h"

void Map::create(int w, int h)
{
    *this = {}; // reset all the data

    mapData[MapLayer_Ground].resize(w * h); // MapTileGround
    mapData[MapLayer_Solid].resize(w * h); // MapTileSolid
    mapData[MapLayer_Visual].resize(w * h); // MapTileVisual

    this->w = w;
    this->h = h;

    // for(auto &e: mapSolids){ e = {};} // clear all block data
    for (int i = 0; i < mapData[0].size(); ++i) {
        mapData[MapLayer_Ground][i] = EntityRef::nil();
        mapData[MapLayer_Solid][i] = EntityRef::nil();
        mapData[MapLayer_Visual][i] = EntityRef::nil();
    }
}
