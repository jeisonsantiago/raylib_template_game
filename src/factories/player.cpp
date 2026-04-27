#include "player.h"

#include "game_data.h"

#include "melee_attack.h"

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
    // e.collider.offset = Vector2{0.5,0.5};
    // e.collider.offset = {1.f,0};
    // e.collider.offset = {0,0};
    // e.collider.offset = {-1,1};


    // physics
    e.physics.move_force = 100.0f;
    e.physics.max_speed = 3.0f;
    // e.physics.transform.w = 0.5f;
    // e.physics.transform.h = 0.75f;

    e.pos = position;

    // animation
    e.animation.active = true;
    e.animation.startFrame = 0;
    e.animation.currentFrame = e.animation.startFrame;
    e.animation.frameOffset = 16;
    e.animation.idleDuration = 1.0f;
    e.animation.runDuration = 0.2f;
    // e.animation.deactivateOnFinish = true;


    e.on_collision_enter = [](int e, int other, EntityArray &e_array){
        TraceLog(LOG_INFO,"ENTER: %i %i",e,other);
    };
    e.on_collision_stay = [](int e, int other, EntityArray &e_array){
        // TraceLog(LOG_INFO,"STAY: %i %i",e,other);
    };
    e.on_collision_exit = [](int e, int other, EntityArray &e_array){
        TraceLog(LOG_INFO,"EXIT: %i %i",e,other);
    };

    // first child attack!
    e.first_child_ref = MeleeAttack::create(e.pos,game_data,asset_manager);

    // get it and set active to false
    Entity &e_attack = game_data.entities.get(e.first_child_ref);
    e_attack.on_collision_enter = [](int e_idx, int other_idx, EntityArray &e_array){

        Entity &self = e_array.entities[e_idx];
        Entity &other = e_array.entities[other_idx];

        TraceLog(LOG_INFO,"ATTACK ENTER: %i %i %f", e_idx, other_idx, GetTime());
    };
}

void update(Entity &e, float delta_time, GameData &game_data, AssetManager &asset_manager)
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
    // e.physics.acceleration = Vector2Normalize(e.physics.acceleration) * e.physics.move_force;
    if (e.physics.acceleration.x != 0.f && e.physics.acceleration.y != 0.f) {
        e.physics.acceleration *= 0.7071f;
    }

    // attack with cooldown
    e.attack.cooldown_counter += delta_time;
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(e.attack.cooldown_counter > e.attack.cooldown){
            Vector2 center = EntityHelpers::center(e);
            // MeleeAttack::create(center,game_data, asset_manager);
            //e.attack.cooldown_counter = 0.0f;

            Entity &e_attack = game_data.entities.get(e.first_child_ref);
            e_attack.pos = center;

            e_attack.active = true;
            e_attack.animation.active = true;

            e_attack.collider.active = true;
            // e.animation.defaultAnimation = true;
            // e_attack.collider.active = true;

            // move attack away from postion
            Vector2 direction_normalized = Vector2Normalize(game_data.mouse_world_pos - e_attack.pos);
            e_attack.pos += (direction_normalized * 0.8f);
            float angle = Helpers::angle_from_a_to_b(e_attack.pos,game_data.mouse_world_pos);
            e_attack.sprite.angle = angle + 145;

        }
    }
}


}
