#ifndef MAIN_MENU_SCENE
#define MAIN_MENU_SCENE

#include "game_context.h"

struct MainMenuScene{
    void init(GameContext &context);
    void update(float deltaTime, GameContext &context);
    void render(float deltaTime, GameContext &context);
    void close(GameContext &context);
};

#endif //
