#ifndef HELPERS
#define HELPERS

struct GameData;

namespace Helpers {
    int render_layer_index(RenderLayer rl);
    int render_layer_size();

    void update_solid_tiles(GameData &game_data);

    float angle_from_a_to_b(Vector2 a, Vector2 b);

    Vector2 direction_from_angle_deg(float degrees);

    bool has_mask(uint16_t mask, uint16_t has_mask);

    bool has_all_masks(uint16_t mask, uint16_t required);
}



#endif //
