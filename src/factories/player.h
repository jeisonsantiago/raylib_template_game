#ifndef CREATE_PLAYER
#define CREATE_PLAYER


struct GameData;
struct AssetManager;
struct Entity;
struct EntityRef;

namespace Player {
    EntityRef create(Vector2 position, GameData &game_data, AssetManager &asset_manager);
    void update(Entity &e, float delta_time, GameData &game_data, AssetManager &asset_manager);
}


#endif //
