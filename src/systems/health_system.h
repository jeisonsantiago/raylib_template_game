#ifndef HEALTH_SYSTEM_H
#define HEALTH_SYSTEM_H

struct GameData;
struct AssetManager;

namespace Systems {
    void health(GameData &game_data, AssetManager &asset_manager);
}


#endif // HEALTH_SYSTEM_H
