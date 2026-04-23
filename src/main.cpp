#include "game_context.h"

#include "scenes/game_play_scene.h"

int main()
{

#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_NONE); // no log raylib
#endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int screenW = SCREEN_W*2;
    int screenH = SCREEN_H*2;

    InitWindow(screenW, screenH, "ElemenTled");
    SetExitKey(KEY_NULL); // disable exit key
    SetTargetFPS(240);

    int monitorW = GetMonitorWidth(0);
    int monitorH = GetMonitorHeight(0);

    rlImGuiSetup(true);

{ /** IMGUI REGION **/
    // make Imgui bigger
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.FontGlobalScale = 2;
}
    // start GameState
    // GameState *gameState = new GameState();
    // MenuScene *menuScene = new MenuScene();
    // GameScene *gameScene = new GameScene();

    // gameState->currentScene = gameScene;
    // gameState->currentScene->Init(gameState);

    // gameState->assetManager.loadAll();
    GameContext *game_context = new GameContext();
    GamePlayScene game_play; // can be in teh stack since it's just functions

    // init
    switch (game_context->current_scene) {
    case Scene::GamePlay:
        // init
        game_play.init(*game_context);
        break;
    case Scene::MainMenu:
        // init
        break;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        // check delta and fix
        float deltaTime = GetFrameTime();
        if(deltaTime > 1.f / 5){deltaTime = 1 /5.f;}

        {/** IMGUI REGION DOCKING **/
            rlImGuiBegin();
            //docking stuff
            ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
            ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            ImGui::PopStyleColor(2);
        }

        switch (game_context->current_scene) {
        case Scene::GamePlay:
            // update
            // render
            game_play.update(deltaTime,*game_context);
            game_play.render(deltaTime,*game_context);
            break;
        case Scene::MainMenu:
            // update
            // render
            break;
        }

        // gameState->currentScene->Update(deltaTime,gameState);
        // gameState->currentScene->Render(gameState);

        rlImGuiEnd();

        DrawFPS(10,10);

        EndDrawing();
    }

    rlImGuiShutdown();

    CloseWindow();

    delete game_context;

    return 0;
}
