#include "player.h"

#include "game_data.h"

namespace Player {


void create(Vector2 position, GameData &game_data, AssetManager &asset_manager)
{
    auto e_ref = game_data.entities.add(Kind::Player);
    auto &e = game_data.entities.get(e_ref);
    e.sprite.texture_asset = &asset_manager.characters;
    e.sprite.texture_index = 0;
    e.sprite.layer = RenderLayer::PLAYER;
    e.sprite.render_origin = {0.5f, 1};

    e.collider.height = 0.8f;
    e.collider.width = 0.5f;
    // e.collider.height = 1;
    // e.collider.width = 1;
    e.collider.active = true;

    e.collider.offset = Vector2{e.collider.width/2,e.collider.height} * -1;
    // e.collider.offset = Vector2{1,1};
    // e.collider.offset = {1.f,0};
    // e.collider.offset = {0,0};
    // e.collider.offset = {-1,1};


    // physics
    e.physics.move_force = 150.0f;
    e.physics.max_speed = 2.0f;
    // e.physics.transform.w = 0.5f;
    // e.physics.transform.h = 0.75f;

    e.pos = position;
}

void update(Entity &e, float delta_time, GameData &game_data)
{

    // move player
    e.physics.acceleration = {0,0};

    if(IsKeyDown(KEY_W)) {e.physics.acceleration.y -=     e.physics.move_force;}
    if(IsKeyDown(KEY_S)) {e.physics.acceleration.y +=     e.physics.move_force;}
    if(IsKeyDown(KEY_A)) {e.physics.acceleration.x -=     e.physics.move_force;}
    if(IsKeyDown(KEY_D)) {e.physics.acceleration.x +=     e.physics.move_force;}

    // // get player
    // Entity *p = gameData.entities.getEntity(gameData.playerId);


    // // /** MOVE PLAYER **/
    // p->physics.acceleration = {0.0f};
    // if(IsKeyDown(KEY_W)) {p->physics.acceleration.y -=     p->physics.moveForce;}
    // if(IsKeyDown(KEY_S)) {p->physics.acceleration.y +=     p->physics.moveForce;}
    // if(IsKeyDown(KEY_A)) {p->physics.acceleration.x -=     p->physics.moveForce;}
    // if(IsKeyDown(KEY_D)) {p->physics.acceleration.x +=     p->physics.moveForce;}

    // // Normalize if non-zero to keep diagonal speed consistent
    const float dx = e.physics.acceleration.x;
    const float dy = e.physics.acceleration.y;
    const float len2 = dx*dx + dy*dy;
    if (e.physics.acceleration.x != 0.f && e.physics.acceleration.y != 0.f) {
        e.physics.acceleration *= 0.7071f;
    }

}

}
