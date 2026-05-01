#include "camera_system.h"

#include "game_data.h"

namespace Systems {

void ajust_camera_zoom(GameData &game_data){
    const float TARGET_W = 1280.f;
    const float TARGET_H = 720.f; // 16:9

    // actual window size
    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();

    // calculate zoom to fit target resolution into window
    float zoom_x = (int)(screen_w / TARGET_W * 32);
    float zoom_y = (int)(screen_h / TARGET_H * 32);

    game_data.camera.zoom = std::min(zoom_x, zoom_y);
}

void camera(float delta_time, GameData &game_data)
{
    // check if window was resized
    if(IsWindowResized()){
        game_data.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

        // use the smaller zoom to fit without stretching (letterbox)
        ajust_camera_zoom(game_data);
    }

    // get player referece from game_data
    Entity &e = game_data.entities.get(game_data.player_ref);
    Camera2D &camera = game_data.camera;
    if(!e) return;

    camera.target.x += (e.pos.x - camera.target.x) * 5.0f * delta_time;
    camera.target.y += (e.pos.y - camera.target.y) * 5.0f * delta_time;
}

}