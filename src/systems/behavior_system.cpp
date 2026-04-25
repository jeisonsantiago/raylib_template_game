#include "behavior_system.h"

#include "game_data.h"

#include "factories/player.h"

namespace Systems {

void behavior(float delta_time, GameData &game_data, AssetManager &asset_manager)
{
    EntityArray &e_array = game_data.entities;

    for (int i = 0; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;

        Entity &e = e_array.entities[i];

        switch (e.kind) {
        case Kind::Player:
            Player::update(e,delta_time,game_data, asset_manager);
            break;
        case Kind::Enemy:
            break;
        default:
            break;
        }
    }
}

}
