#include "render_system.h"

#include "game_data.h"

namespace Systems {


void render_entities(GameData &game_data){

    EntityArray &e_array = game_data.entities;

    // -----------------------------------------------
    // all entities render begin

    // iterate over entities and put inside render_bucket
    for (int i = 1; i < e_array.get_count(); ++i) { // awalys start with 1

        if(!e_array.used[i]) continue;

        Entity &e = e_array.entities[i];
        if(!e || !e.active) continue;

        game_data.render_bucket[Helpers::render_layer_index(e.sprite.layer)][game_data.render_bucket_count[Helpers::render_layer_index(e.sprite.layer)]] = i;
        game_data.render_bucket_count[Helpers::render_layer_index(e.sprite.layer)]+=1;
    }

    for (int i = 0; i < Helpers::render_layer_index(RenderLayer::MAX_LAYERS); ++i) {
        for (int j = 0; j < game_data.render_bucket_count[i]; ++j) {
            int idx = game_data.render_bucket[i][j];
            Entity &e = e_array.entities[idx];

            DrawTexturePro(
                        e.sprite.texture_asset->texture, // texture
                        getSourceRectangleByIndex(e.sprite.texture_index,*e.sprite.texture_asset),
                        {e.pos.x,e.pos.y, 1,1}, // destination
                        e.sprite.render_origin, // origin (top-left corner)
                        e.sprite.angle, // rotation
                        WHITE // tint
                        );
        }
    }

    // clear bucket (FAST!)
    memset(game_data.render_bucket_count, 0, sizeof(game_data.render_bucket_count));
}

void render_debug(GameData &game_data)
{
    EntityArray &e_array = game_data.entities;

    // -----------------------------------------------
    // all entities render begin

    // iterate over entities and put inside render_bucket
    for (int i = 1; i < e_array.get_count(); ++i) { // awalys start with 1

        if(!e_array.used[i]) continue;

        Entity &e = e_array.entities[i];
        if(!e) continue;

        Rectangle rect = {e.pos.x+e.collider.offset.x, e.pos.y+e.collider.offset.y,e.collider.width,e.collider.height};

        if(e.collider.active){
            DrawRectanglePro(rect,{0,0},0,ColorAlpha(GREEN,0.2f));
            DrawCircleV(e.pos,0.05f,RED);
            DrawCircleV(EntityHelpers::center(e),0.05f,GREEN);
        }

        if(e.kind == Kind::Player){
            // DrawLineEx(EntityHelpers::center(e),game_data.mouse_world_pos,0.01f,WHITE);

        }
    }

    // mouse pos
    // DrawCircleV(game_data.mouse_world_pos,0.05f,BLUE);
}

void render_ui(GameData &game_data)
{
    float barLenght = 0.4f;

    EntityArray &e_array = game_data.entities;
    for (int i = 1; i < e_array.get_count(); ++i){ // awalys start with 1
        if(!e_array.used[i]) continue;
        Entity &e = e_array.entities[i];
        if(!e) continue;

        if(e.health.active){
            Vector2 position = EntityHelpers::top_left(e) - Vector2{0,0.3f};
            Rectangle rect{position.x, position.y,0.5f,0.2f};
            DrawRectangleRec(rect,BLACK);

            float health_percentage = (e.health.current_health/e.health.max_health);
            float health_width = health_percentage*barLenght;

            rect = {position.x+0.05f,position.y+0.05f,health_width,0.1f};

            DrawRectangleRec(rect,RED);
        }
    }
}

}
