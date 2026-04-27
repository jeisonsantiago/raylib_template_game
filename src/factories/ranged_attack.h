#ifndef RANGED_ATTACK
#define RANGED_ATTACK

struct GameData;
struct AssetManager;
struct EntityRef;

namespace RangedAttack {
    EntityRef create(Vector2 position, GameData &game_data, AssetManager &asset_manager);
}

#endif //
