#include "enemy.h"

#include "game_data.h"

namespace Enemy {

void create(Vector2 position, GameData &game_data, AssetManager &asset_manager)
{
    auto e_ref = game_data.entities.add(Kind::Enemy);
    auto &e = game_data.entities.get(e_ref);

    e.sprite.asset_texture_index = 2;
    e.sprite.texture_asset = &asset_manager.characters;
    e.sprite.texture_index = 4;
    e.sprite.layer = RenderLayer::ENEMIES;
    e.sprite.render_origin = {0.5f, 1};

    e.collider.height = 0.8f;
    e.collider.width = 0.5f;
    // e.collider.height = 1;
    // e.collider.width = 1;
    e.collider.active = true;

    e.collider.offset = Vector2{e.collider.width/2,e.collider.height} * -1;
    // e.collider.offset = Vector2{0.5,0.5};
    // e.collider.offset = {1.f,0};
    // e.collider.offset = {0,0};
    // e.collider.offset = {-1,1};

    // health
    e.health.active = true;
    e.health.max_health = 10;
    e.health.current_health = e.health.max_health;

    // Entity belongs to
    e.collider.layer |= (uint16_t)ColliderLayer::Enemy;

    // Entity interacts with
    e.collider.mask |= (uint16_t)ColliderLayer::Particle;


    // physics
    e.physics.move_force = 100.0f;
    e.physics.max_speed = 3.0f;
    // e.physics.transform.w = 0.5f;
    // e.physics.transform.h = 0.75f;

    e.pos = position;

    // e.on_collision_enter = [](int e, int other, EntityArray &e_array){
    //     // TraceLog(LOG_INFO,"ENTER");
    // };
}


}