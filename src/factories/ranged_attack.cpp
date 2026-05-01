#include "ranged_attack.h"

#include "game_data.h"

namespace RangedAttack {

EntityRef create(Vector2 position, Vector2 direction, float angle, float amount,GameData &game_data, AssetManager &asset_manager)
{
    auto e_ref = game_data.entities.add(Kind::Particle);
    auto &e = game_data.entities.get(e_ref);

    e.collider.height = 0.5f;
    e.collider.width = 0.5f;
    e.collider.offset = Vector2{e.collider.width * 0.5f,e.collider.height * 0.5f} * -1; // set to center
    // e.collider.height = 1;
    // e.collider.width = 1;
    e.collider.active = true;
    e.collider.is_trigger = true;

    // Entity belongs to
    e.collider.layer |= (uint16_t)ColliderLayer::Particle;

    // Entity interacts with
    e.collider.mask |= (uint16_t)ColliderLayer::Tile | (uint16_t)ColliderLayer::Enemy;

    e.attack.damage = amount;

    e.sprite.asset_texture_index = 3;
    e.sprite.texture_asset = &asset_manager.fxAltered;
    e.sprite.texture_index = 0; //97
    e.sprite.layer = RenderLayer::PARTICLES;
    e.sprite.render_origin = Vector2{e.collider.width,e.collider.height};
    e.sprite.angle = angle;

    e.pos = (position);
    e.active = true;

    e.physics.move_force = 5.0f;
    e.physics.max_speed = 10.0f;

    // e.physics.acceleration = direction * e.physics.move_force;
    // e.physics.acceleration = direction;
    e.physics.velocity = direction * e.physics.move_force;

    // TraceLog(LOG_INFO,"RANGED:%f %f",e.physics.acceleration);

    // animations setup
    // e.animation.animationCounter = 0;
    // e.animation.defaultAnimation = true;
    // e.animation.active = true;
    // e.animation.startFrame = 120;
    // e.animation.frameCount = 4;
    // e.animation.defaultDuration = 0.02f;
    // e.animation.deactivateOnFinish = true;

    return e_ref;
}

}