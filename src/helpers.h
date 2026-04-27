#ifndef HELPERS
#define HELPERS

struct GameData;

namespace Helpers {
    int render_layer_index(RenderLayer rl);
    int render_layer_size();

    void update_solid_tiles(GameData &game_data);

    float angle_from_a_to_b(Vector2 a, Vector2 b);
}



#endif //
