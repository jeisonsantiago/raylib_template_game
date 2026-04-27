#include "queue_free_system.h"

#include "game_data.h"

namespace Systems {
void queue_free(GameData &game_data){

    EntityArray &e_array = game_data.entities;

    for (int i = 0; i < game_data.entities.get_count(); ++i) {
        if(!e_array.used[i]) continue;
        Entity &e = e_array.entities[i];

        if(e.queue_free){
            e_array.used[i] = false;
        }
    }
}
}