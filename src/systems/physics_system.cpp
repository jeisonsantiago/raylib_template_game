#include "physics_system.h"

#include "game_data.h"

namespace Systems {

void physics(float delta_time, GameData &game_data)
{
    float drag = 0.85f;
    float speed = 0.0f;

    EntityArray &e_array = game_data.entities;
    for (int i = 1; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;

        Entity &entity_a = e_array.entities[i];

        if(entity_a.kind != Kind::Player) continue;

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


// void physics(float delta_time, GameData &game_data)
// {
//     float drag = 0.85f;
//     float speed = 0.0f;

//     EntityArray &e_array = game_data.entities;
//     for (int i = 1; i < e_array.get_count(); ++i) {
//         if(!e_array.used[i]) continue;

//         Entity &e = e_array.entities[i];

//         if(e.kind != Kind::Player) continue;

//         //--------------- X ---------------
//         // apply acceleration
//         e.physics.velocity.x += e.physics.acceleration.x * delta_time;

//         //apply drag
//         e.physics.velocity.x *= drag;

//         // clamp to max speed
//         speed = std::sqrt(e.physics.velocity.x * e.physics.velocity.x + e.physics.velocity.y * e.physics.velocity.y);
//         if(speed > e.physics.max_speed){
//             float scale = e.physics.max_speed / speed;
//             e.physics.velocity.x *= scale;
//         }

//         // integrate position
//         e.pos.x += e.physics.velocity.x * delta_time;


//         //--------------- Y ---------------
//         // apply acceleration
//         e.physics.velocity.y += e.physics.acceleration.y * delta_time;

//         //apply drag
//         e.physics.velocity.y *= drag;

//         // clamp to max speed
//         speed = std::sqrt(e.physics.velocity.x * e.physics.velocity.x + e.physics.velocity.y * e.physics.velocity.y);
//         if(speed > e.physics.max_speed){
//             float scale = e.physics.max_speed / speed;
//             e.physics.velocity.y *= scale;
//         }

//         // integrate position
//         e.pos.y += e.physics.velocity.y * delta_time;

//     }
// }

}
