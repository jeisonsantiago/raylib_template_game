#include "physics_system.h"

#include "game_data.h"

namespace Systems {

void physics(float delta_time, GameData &game_data)
{
    float drag = .95f;
    float speed = 0.0f;

    EntityArray &e_array = game_data.entities;

    for (int i = 1; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;

        Entity &entity_a = e_array.entities[i];

        if(entity_a.kind == Kind::Tile || !entity_a.collider.active) continue;

        //--------------- X ---------------
        // apply acceleration
        entity_a.physics.velocity.x += entity_a.physics.acceleration.x * delta_time;

        //apply drag
        entity_a.physics.velocity.x *= drag;

        // clamp to max speed
        speed = std::sqrt(entity_a.physics.velocity.x * entity_a.physics.velocity.x + entity_a.physics.velocity.y * entity_a.physics.velocity.y);
        if(speed > entity_a.physics.max_speed){
            float scale = entity_a.physics.max_speed / speed;
            entity_a.physics.velocity.x *= scale;
        }

        // integrate position
        entity_a.pos.x += entity_a.physics.velocity.x * delta_time;
        Rectangle rect_a = EntityHelpers::rect(entity_a);

        // see if entity_a collides with entity_b
        for (int j = 0; j < game_data.solid_tiles_count; ++j) {
            int solid_idx = game_data.solid_tiles[j];

            Entity &entity_b = game_data.entities.entities[solid_idx];
            Rectangle rect_b = EntityHelpers::rect(entity_b);

            if(CheckCollisionRecs(rect_a,rect_b)){
                if(entity_a.physics.velocity.x > 0){
                    entity_a.pos.x = rect_b.x - (rect_a.width + entity_a.collider.offset.x) - 0.01f;;
                }else{
                    entity_a.pos.x = (rect_b.x + rect_b.width) - (entity_a.collider.offset.x) + 0.01f;
                }
            }
        }

        //--------------- Y ---------------
        // apply acceleration
        entity_a.physics.velocity.y += entity_a.physics.acceleration.y * delta_time;

        //apply drag
        entity_a.physics.velocity.y *= drag;

        // clamp to max speed
        speed = std::sqrt(entity_a.physics.velocity.x * entity_a.physics.velocity.x + entity_a.physics.velocity.y * entity_a.physics.velocity.y);
        if(speed > entity_a.physics.max_speed){
            float scale = entity_a.physics.max_speed / speed;
            entity_a.physics.velocity.y *= scale;
        }

        // integrate position
        entity_a.pos.y += entity_a.physics.velocity.y * delta_time;
        rect_a = EntityHelpers::rect(entity_a);

        // see if entity_a collides with entity_b
        for (int j = 0; j < game_data.solid_tiles_count; ++j) {
            int solid_idx = game_data.solid_tiles[j];

            Entity &entity_b = game_data.entities.entities[solid_idx];
            Rectangle rect_b = EntityHelpers::rect(entity_b);

            if(CheckCollisionRecs(rect_a,rect_b)){
                if(entity_a.physics.velocity.y > 0){
                    entity_a.pos.y = rect_b.y - (rect_a.height + entity_a.collider.offset.y) - 0.01f;;
                }else{
                    entity_a.pos.y = (rect_b.y + rect_b.height) - (entity_a.collider.offset.y) + 0.01f;
                }
            }
        }
    }
}

void physics_collision_calls(float delta_time, GameData &game_data){

    EntityArray &e_array = game_data.entities;

    for (int i = 1; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;
        Entity &e = e_array.entities[i];
        if(e.kind == Kind::Tile || !e.collider.active) continue;

        e.collider.previous_collisions = e.collider.current_collisions;
        e.collider.previous_collisions_count = e.collider.current_collisions_count;

        //clear current collisions
        e.collider.current_collisions = {};
        e.collider.current_collisions_count = 0;
    }

    // CORRECT — only check each pair once
    for(size_t i = 1; i < e_array.get_count(); i++){
        if(!e_array.used[i]) continue;
        Entity &e_a = e_array.entities[i];
        if(e_a.kind == Kind::Tile || !e_a.collider.active) continue;

        Rectangle rect_a = EntityHelpers::rect(e_a);

        for(size_t j = i+1; j < e_array.get_count(); j++){
            if(!e_array.used[j]) continue;
            Entity &e_b = e_array.entities[j];
            if(e_b.kind == Kind::Tile || !e_b.collider.active) continue;

            Rectangle rect_b = EntityHelpers::rect(e_b);

            if(!CheckCollisionRecs(rect_a, rect_b)) continue;

            // //register contact
            if(e_a.collider.current_collisions_count < 10) e_a.collider.current_collisions[e_a.collider.current_collisions_count++] = j;
            if(e_b.collider.current_collisions_count < 10) e_b.collider.current_collisions[e_b.collider.current_collisions_count++] = i;
        }
    }

    // fire events
    for (int i = 1; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;
        Entity &e = e_array.entities[i];
        if(e.kind == Kind::Tile || !e.collider.active) continue;

        for (int j = 0; j < e.collider.current_collisions_count; ++j) {
            int other = e.collider.current_collisions[j];
            if(!e.collider.was_colliding(other)){
                // on collision enter, check if the function is nullptr before
                if(e.on_collision_enter){
                    e.on_collision_enter(i, other,game_data.entities);
                }
            }else{
                // on collision stay, check if the function is nullptr before
                if(e.on_collision_stay){
                    e.on_collision_stay(i, other,game_data.entities);
                }
            }
        }

        for (int j = 0; j < e.collider.previous_collisions_count; ++j) {
            int other = e.collider.previous_collisions[j];
            if(!e.collider.is_colliding(other)){
                // on collision exit, check if the function is nullptr before
                if(e.on_collision_exit){
                    e.on_collision_exit(i, other,game_data.entities);
                }
            }
        }
    }


}

}
