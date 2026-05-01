#include "helpers.h"


#include "game_data.h"

namespace Helpers {
int render_layer_index(RenderLayer rl){
    return static_cast<int>(rl);
}

int render_layer_size()
{
    return static_cast<int>(RenderLayer::MAX_LAYERS);
}

void update_solid_tiles(GameData &game_data)
{
    EntityArray &e_array = game_data.entities;

    memset(&game_data.solid_tiles,0,sizeof(game_data.solid_tiles));

    for (int i = 0; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;

        Entity &e = e_array.entities[i];
        if(e.kind == Kind::Tile && e.collider.active){
            game_data.solid_tiles[game_data.solid_tiles_count++] = i;
        }
    }
}

float angle_from_a_to_b(Vector2 a, Vector2 b)
{
    Vector2 direction = Vector2Subtract(b, a);
    // float length = Vector2Length(direction);

    float angle = atan2f(direction.y, direction.x); // radians
    // or in degrees
    float angleDeg = atan2f(direction.y, direction.x) * RAD2DEG;
    return angleDeg;
}

Vector2 direction_from_angle_deg(float degrees) {
    float rad = degrees * DEG2RAD; // raylib has DEG2RAD
    return { cosf(rad), sinf(rad) };
}

bool has_mask(uint16_t mask, uint16_t has_mask){
    return (mask & has_mask) != 0;
}

bool has_all_masks(uint16_t mask, uint16_t required) {
    return (mask & required) == required;
}

}
