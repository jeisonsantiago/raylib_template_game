#include "render_system.h"

#include "game_data.h"

namespace Systems {


void render_entities(GameData &game_data){

    EntityArray &e_array = game_data.entities;

    // -----------------------------------------------
    // all entities render begin

    // iterate over entities and put inside render_bucket
    for (int i = 1; i < e_array.get_count(); ++i) { // awalys start with 1
        Entity &e = e_array.entities[i];
        if(!e) continue;
        game_data.render_bucket[Helpers::render_layer_index(e.sprite.layer)].push_back(i);
    }

    // then render by layer
    for (auto &layer_items:game_data.render_bucket) {
        for (int &idx : layer_items) {
            Entity &e = e_array.entities[idx];
            DrawTexturePro(
                        e.sprite.texture_asset->texture, // texture
                        getSourceRectangleByIndex(e.sprite.texture_index,*e.sprite.texture_asset),
                        {e.pos.x,e.pos.y, 1,1}, // destination
                        {0,0}, // origin (top-left corner)
                        0.f, // rotation
                        WHITE // tint
                        );
        }
    }

    // all entities render end
    // -----------------------------------------------

    // clear render bucket after use (clear keeps capacity)
    game_data.render_bucket->clear();
}

void render_debug(GameData &game_data)
{
    EntityArray &e_array = game_data.entities;

    // -----------------------------------------------
    // all entities render begin

    // iterate over entities and put inside render_bucket
    for (int i = 1; i < e_array.get_count(); ++i) { // awalys start with 1
        Entity &e = e_array.entities[i];
        if(!e) continue;
        //game_data.render_bucket[e.sprite.layer].push_back(i);

        Rectangle rect = {e.pos.x, e.pos.y,1,1};

        if(e.collider.active){
            DrawRectanglePro(rect,{0,0},0,ColorAlpha(GREEN,0.2f));
        }

    }
}

}
