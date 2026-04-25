#ifndef MELEE_ATTACK
#define MELEE_ATTACK

struct GameData;
struct AssetManager;
struct Entity;

namespace MeleeAttack {
    void create(Vector2 position, GameData &game_data, AssetManager &asset_manager);
}

#endif //
