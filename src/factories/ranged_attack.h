#ifndef RANGED_ATTACK
#define RANGED_ATTACK

struct GameData;
struct AssetManager;
struct EntityRef;

namespace RangedAttack {
    EntityRef create(Vector2 position, Vector2 direction, float angle, float amount,GameData &game_data, AssetManager &asset_manager);
}

#endif //
