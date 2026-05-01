#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "entities/entity_array.h"
#include "map.h"

struct GameData{
    Map game_map;
    Camera2D camera;
    float camera_speed = 0;

    Vector2 mouse_pos = {};
    Vector2 mouse_world_pos = {};
    Vector2 mouse_block_pos = {};

    // edits
    int selected_texture_block = 0;
    Vector2 selection_start = {};
    Vector2 selection_ends = {};

    int map_layer_selected = -1;
    int selected_block = -1;

    bool editor_mode = false;
    bool mouse_over_editor_ui = false;

    bool is_selecting = false;
    bool mouse_click_selection = false;
    bool is_paste_structure_event  = false;

    Rectangle on_selection_rect;
    Rectangle last_selection;
    // Structure copyStructure;

    char save_map_name[100] = {};

    // inventory related
    // bool insideInventory = false;
    // bool isDragging = false;
    // int slotBeingDraged = -1;
    // int slotToDrop = -1;

    // entities
    EntityArray entities;

    // render bucket
    // std::vector<int> render_bucket[static_cast<int>(RenderLayer::MAX_LAYERS)];
    int render_bucket[static_cast<int>(RenderLayer::MAX_LAYERS)][MAX_ENTITIES];
    int render_bucket_count[static_cast<int>(RenderLayer::MAX_LAYERS)] = {};

    int solid_tiles[MAX_ENTITIES];
    int solid_tiles_count;


    // std::vector<std::uint64_t> toRemoveEntities;
    // std::vector<std::unique_ptr<UIElement>> uiElements;

    // entity_idx player_id;
    EntityRef player_ref;

    // collision update
    float collision_callback_update = 0.05f;
    float collision_callback_update_count = 0.0f;
};


#endif // GAME_DATA_H
