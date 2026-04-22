#include "game_play_scene.h"

// row    = index / width
// column = index % width
// index = (row * width) + column
// #include "asset_manager.h"

#include "game_context.h"
#include "editor.h"

#include "systems/render_system.h"

#include "factories/player.h"

void GamePlayScene::init(GameContext &context)
{
    GameData &game_data = context.game_data;
    Map &map = game_data.game_map;
    // set map
    map.create(10,10);

    // set floor
    for (int y = 0; y < map.h; ++y) {
        for (int x = 0; x < map.w; ++x) {
            int index = (y * map.w) + x;

            // create entity
            auto e_ref = game_data.entities.add(Type::Tile);
            auto &e = game_data.entities.get(e_ref);
            e.sprite.texture_asset = &context.asset_manager.world;
            e.sprite.texture_index = 103;
            e.sprite.layer = RenderLayer::BACKGROUND_TILES_GROUND;

            e.pos.x = x ; // just texture for now
            e.pos.y = y ; // just texture for now

            map.setBlock(e.pos.x,e.pos.y,Helpers::render_layer_index(RenderLayer::BACKGROUND_TILES_GROUND),e_ref);
        }
    }

    // set walls
    for (int x = 0; x < map.w; ++x) {
        auto e_ref = game_data.entities.add(Type::Tile);
        auto &e = game_data.entities.get(e_ref);
        e.sprite.texture_asset = &context.asset_manager.world;
        e.sprite.texture_index = 0;
        e.sprite.layer = RenderLayer::BACKGROUND_TILES_SOLID;

        e.collider.h = 1;
        e.collider.w = 1;
        e.collider.active = true;

        e.pos.x = x;
        e.pos.y = 0;

        map.setBlock(e.pos.x,e.pos.y,Helpers::render_layer_index(RenderLayer::BACKGROUND_TILES_SOLID),e_ref);
        {
            auto e_ref = game_data.entities.add(Type::Tile);
            auto &e = game_data.entities.get(e_ref);
            e.sprite.texture_asset = &context.asset_manager.world;
            e.sprite.texture_index = 0;
            e.sprite.layer = RenderLayer::BACKGROUND_TILES_SOLID;

            e.collider.h = 1;
            e.collider.w = 1;
            e.collider.active = true;

            e.pos.x = x;
            e.pos.y = map.h-1;

            map.setBlock(e.pos.x,e.pos.y,Helpers::render_layer_index(RenderLayer::BACKGROUND_TILES_SOLID),e_ref);
        }
    }

    for (int y = 0; y < map.h-1; ++y) {
        auto e_ref = game_data.entities.add(Type::Tile);
        auto &e = game_data.entities.get(e_ref);
        e.sprite.texture_asset = &context.asset_manager.world;
        e.sprite.texture_index = 6;
        e.sprite.layer = RenderLayer::BACKGROUND_TILES_SOLID;

        e.collider.h = 1;
        e.collider.w = 1;
        e.collider.active = true;

        e.pos.x = 0;
        e.pos.y = y;

        map.setBlock(e.pos.x,e.pos.y,Helpers::render_layer_index(RenderLayer::BACKGROUND_TILES_SOLID),e_ref);
        {
            auto e_ref = game_data.entities.add(Type::Tile);
            auto &e = game_data.entities.get(e_ref);
            e.sprite.texture_asset = &context.asset_manager.world;
            e.sprite.texture_index = 6;
            e.sprite.layer = RenderLayer::BACKGROUND_TILES_SOLID;

            e.collider.h = 1;
            e.collider.w = 1;
            e.collider.active = true;

            e.pos.x = map.w-1;
            e.pos.y = y;

            map.setBlock(e.pos.x,e.pos.y,Helpers::render_layer_index(RenderLayer::BACKGROUND_TILES_SOLID),e_ref);
        }
    }

    // create player
    Player::create(Vector2{2,2},game_data,context.asset_manager);

    TraceLog(LOG_INFO, "Entity size: %zu bytes", sizeof(Entity));

    // set camera
    game_data.camera.target = {0,0};
    game_data.camera.rotation = 0.0f;
    game_data.camera.zoom = 50.0f;
    game_data.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}

void GamePlayScene::update(float deltaTime, GameContext &context)
{
    GameData &game_data = context.game_data;

    // update block position
    // block position
    Vector2 world_pos = GetScreenToWorld2D(GetMousePosition(),game_data.camera);
    game_data.mouse_world_pos = world_pos;
    game_data.mouse_block_pos.x = (int)floor(world_pos.x);
    game_data.mouse_block_pos.y = (int)floor(world_pos.y);

    // update entities

    // toggle editor
    if(IsKeyPressed(KEY_F10)){
        game_data.editor_mode = !game_data.editor_mode;
    }

    // imgui editor
    if(game_data.editor_mode){
        Editor::processEditor(game_data,context.asset_manager);
    }
}

void GamePlayScene::render(float deltaTime, GameContext &context)
{
    BeginMode2D(context.game_data.camera);

    // render
    GameData &game_data = context.game_data;
    EntityArray &e_array = game_data.entities;


    // render system
    Systems::render_entities(game_data);
    Systems::render_debug(game_data);


    // imgui editor
    if(game_data.editor_mode){
        Editor::drawGUI(game_data,context.asset_manager);

        // draw mouse block position
        Rectangle rect = {game_data.mouse_block_pos.x, game_data.mouse_block_pos.y,1,1};
        DrawRectangleLinesEx(rect,0.05f,RED);
    }

    EndMode2D();
}

void GamePlayScene::close(GameContext &context)
{

}


