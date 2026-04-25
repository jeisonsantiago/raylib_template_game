#include "melee_attack.h"

#include "game_data.h"

namespace MeleeAttack {


void create(Vector2 position, GameData &game_data, AssetManager &asset_manager)
{
    auto e_ref = game_data.entities.add(Kind::Particle);
    auto &e = game_data.entities.get(e_ref);

    e.collider.height = 0.5f;
    e.collider.width = 0.5f;
    e.collider.offset = Vector2{e.collider.width * 0.5f,e.collider.height * 0.5f} * -1; // set to center
    // e.collider.height = 1;
    // e.collider.width = 1;
    e.collider.active = true;

    e.sprite.texture_asset = &asset_manager.fxAltered;
    e.sprite.texture_index = 97;
    e.sprite.layer = RenderLayer::PARTICLES;
    e.sprite.render_origin = Vector2{e.collider.width,e.collider.height};

    e.pos = (position);
    e.sprite.angle = -135;
}

}