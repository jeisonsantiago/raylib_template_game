#ifndef RENDER_SYSTEM
#define RENDER_SYSTEM

struct GameData;

namespace Systems {
void render_entities(GameData &game_data);
void render_debug(GameData &game_data);
void render_ui(GameData &game_data);
}

#endif //
