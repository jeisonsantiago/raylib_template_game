#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "asset_manager.h"

// struct TransformComponent{
//     Vector2 pos;
//     float angle;
// };

struct ColliderComponent{
    bool active = false;
    float width;
    float height;
    bool is_trigger = false;

    Vector2 offset;


    // float radius;
    // bool is_circle;

    std::array<int,10> current_collisions;
    int current_collisions_count = 0;
    std::array<int,10> previous_collisions;
    int previous_collisions_count = 0;

    bool was_colliding(int id){
        for (int i = 0; i < previous_collisions_count; ++i) {
            if(previous_collisions[i] == id){
                return true;
            }
        }
        return false;
    }

    bool is_colliding(int id) const{
        for (int i = 0; i < current_collisions_count; ++i) {
            if(current_collisions[i] == id) return true;
        }

        return false;
    }
};

struct SpriteComponent{
    TextureAsset *texture_asset = nullptr;
    int texture_index;
    float angle;
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

struct AnimationComponent{
    bool active = false;
    int startFrame = {};
    int lastFrame = {};
    int currentFrame = {};
    int frameOffset = {};
    int frameCount = 2; // for now

    // counter for any animation
    float animationCounter = 0;

    // specific animation type (loop)
    float idleDuration = 0;// duration per frame
    float runDuration = 0;

    // sets for default animation
    bool defaultAnimation = false;
    float defaultDuration = 0;

    // deactivate entity when animation is finished
    bool deactivateOnFinish = false;

    // queue free when animation is finished
    bool deleteOnFinish = false;
};




#endif //
