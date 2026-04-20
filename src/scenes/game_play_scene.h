#ifndef GAME_PLAY_SCENE
#define GAME_PLAY_SCENE

// #include "game_context.h"

struct GameContext;

struct GamePlayScene{

    void init(GameContext &context);
    void update(float deltaTime, GameContext &context);
    void render(float deltaTime, GameContext &context);
    void close(GameContext &context);
};

#endif //
