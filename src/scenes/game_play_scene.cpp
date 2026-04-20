#include "game_play_scene.h"


// row    = index / width
// column = index % width
// index = (row * width) + column

#include "game_context.h"



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
            auto e_ref = game_data.entities.add(Type::MapTileGround);
            auto &e = game_data.entities.get(e_ref);
            e.sprite.textureAsset = &context.asset_manager.world;
            e.sprite.textureIndex = 103;

            e.pos.x = x ; // just texture for now
            e.pos.y = y ; // just texture for now
        }
    }


    game_data.camera.target = {0,0};
    game_data.camera.rotation = 0.0f;
    game_data.camera.zoom = 50.0f;
    game_data.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}

void GamePlayScene::update(float deltaTime, GameContext &context)
{


}

void GamePlayScene::render(float deltaTime, GameContext &context)
{
    BeginMode2D(context.game_data.camera);

    // render
    GameData &game_data = context.game_data;
    EntityArray &e_array = game_data.entities;

    for (int i = 1; i < e_array.get_count(); ++i) { // awalys start with 1
        Entity &e = e_array.entities[i];
        if(!e) continue;
        DrawTexturePro(
                    e.sprite.textureAsset->texture, // texture
                    getSourceRectangleByIndex(e.sprite.textureIndex,*e.sprite.textureAsset),
                    {e.pos.x,e.pos.y, 1,1}, // destination
                    {0,0}, // origin (top-left corner)
                    0.f, // rotation
                    WHITE // tint
                    );
    }

    EndMode2D();
}

void GamePlayScene::close(GameContext &context)
{

}


