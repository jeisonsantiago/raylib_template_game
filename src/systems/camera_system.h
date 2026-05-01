#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

struct GameData;

namespace Systems {
    void camera(float delta_time, GameData &game_data);
    void ajust_camera_zoom(GameData &game_data);
}

#endif // CAMERA_SYSTEM_H
