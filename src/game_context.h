#ifndef GAME_CONTEXT
#define GAME_CONTEXT


#include "game_data.h"

#include "asset_manager.h"

enum class Scene{
    GamePlay,
    MainMenu
};

struct GameContext {
    GameContext();

    bool is_running{true};
    uint64_t previous_frame{0};

    AssetManager asset_manager;

    Vector2 mouse_pos = {};
    Vector2 logical_mouse_pos = {};

    Camera camera;

    // gameplay related struct
    GameData game_data;

    Scene current_scene = Scene::GamePlay;
};


#endif //
