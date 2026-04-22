#include "create_player.h"

#include "game_context.h"

void create_player(Vector2 position, GameData &game_data, AssetManager &asset_manager)
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
