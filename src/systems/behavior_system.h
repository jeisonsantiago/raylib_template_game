#ifndef BEHAVIOR_SYSTEM
#define BEHAVIOR_SYSTEM

struct GameData;
struct AssetManager;

namespace Systems {
    void behavior(float delta_time, GameData &game_data, AssetManager &asset_manager);
}

#endif //
