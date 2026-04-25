#ifndef ENEMY
#define ENEMY


struct GameData;
struct AssetManager;
struct Entity;

namespace Enemy {
    void create(Vector2 position, GameData &game_data, AssetManager &asset_manager);
    void update(Entity &e, float delta_time, GameData &game_data);
}


#endif //
