#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "asset_manager.h"

struct TransformComponent{
    Vector2 pos;
    float angle;
};

struct ColliderComponent{
    bool active = false;
    float width;
    float height;
    Vector2 offset;
};

struct SpriteComponent{
    TextureAsset *texture_asset = nullptr;
    int texture_index;
    Vector2 render_origin = {0};
    RenderLayer layer = RenderLayer::DEFAULT;
};

struct PhysicsComponent{
    Vector2 velocity = {};
    Vector2 acceleration = {};
    float max_speed = 0;
    float move_force = 0;
};

struct HealthComponent{
    float max_health;
    float current_health;
};

struct AttackComponent{
    float cooldown = 1.0f; // 1 attack per second
    float cooldown_counter = 0.0f;
};



#endif //
