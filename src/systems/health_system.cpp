#include "health_system.h"

#include "game_data.h"

namespace Systems {
void health(GameData &game_data, AssetManager &asset_manager){
    EntityArray &e_array = game_data.entities;

    for (int i = 0; i < e_array.get_count(); ++i) {

        if(!e_array.used[i]) continue;
        Entity &e = e_array.entities[i];

        if(e.kind == Kind::Player || e.kind == Kind::Enemy){
            if(e.health.current_health <= 0){
                e_array.used[i] = false;
            }
        }
    }
}
}