#include "player.h"

#include "game_data.h"

namespace Player {


void create(Vector2 position, GameData &game_data, AssetManager &asset_manager)
{
    auto e_ref = game_data.entities.add(Type::Player);
    auto &e = game_data.entities.get(e_ref);
    e.sprite.texture_asset = &asset_manager.characters;
    e.sprite.texture_index = 0;
    e.sprite.layer = RenderLayer::PLAYER;

    e.collider.h = 1;
    e.collider.w = 1;
    e.collider.active = true;

    e.pos = position;
}

void update(EntityRef e_ref, float delta_time, GameData &game_data)
{

}

}
