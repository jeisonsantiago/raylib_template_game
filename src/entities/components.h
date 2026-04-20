#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "asset_manager.h"

struct TransformComponent{
    Vector2 pos;
    float angle;
};

struct ColliderComponent{
    float w;
    float h;
    Vector2 offset;
};


// layer 0  → background tiles
// layer 1  → background decorations
// layer 2  → items on ground
// layer 3  → y-sort
// layer 4  → enemies
// layer 5  → player
// layer 6  → projectiles
// layer 7  → particles
// layer 8  → UI

enum RenderLayer{
    DEFAULT             = 0,
    BACKGROUND_TILES_GROUND,
    BACKGROUND_TILES_WALL,
    BACKGROUND_DECORATIONS,
    Y_SORT,
    ENEMIES,
    PLAYER,
    PROJECTILES,
    PARTICLES,
    UI,
    MAX_LAYERS,
};

struct SpriteComponent{
    TextureAsset *textureAsset = nullptr;
    int textureIndex;
    Vector2 renderOrigin = {0};
    RenderLayer layer = DEFAULT;
};

#endif //
