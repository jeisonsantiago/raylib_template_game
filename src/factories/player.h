#ifndef CREATE_PLAYER
#define CREATE_PLAYER


struct GameData;
struct AssetManager;
struct EntityRef;

namespace Player {
    void create(Vector2 position, GameData &game_data, AssetManager &asset_manager);
    void update(EntityRef e_ref, float delta_time, GameData &game_data);
}


#endif //
