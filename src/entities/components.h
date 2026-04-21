#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "asset_manager.h"

struct TransformComponent{
    Vector2 pos;
    float angle;
};

struct ColliderComponent{
    bool active = false;
    float w;
    float h;
    Vector2 offset;
};

struct SpriteComponent{
    TextureAsset *textureAsset = nullptr;
    int textureIndex;
    Vector2 renderOrigin = {0};
    RenderLayer layer = RenderLayer::DEFAULT;
};

#endif //
