#ifndef ENTITY
#define ENTITY


#include "components.h"

struct EntityArray;

struct EntityRef{
    int idx;
    int gen;

    static EntityRef nil(){return EntityRef{0,0};};

    bool is_nil(){return idx == 0 && gen == 0;};
};

enum class Kind{
    Nil,
    Player,
    Enemy,
    Weapon,
    Particle,
    Item,
    Tile,
};

// colision layers
enum class ColliderLayer: uint16_t{
    Nil =       (1 << 0),
    Player =    (1 << 1),
    Enemy =     (1 << 2),
    Weapon =    (1 << 3),
    Particle =  (1 << 4),
    Item =      (1 << 5),
    Tile =      (1 << 6),
};

// // Fixed size NOT DYNAMIC!
struct Entity{
    Kind kind  = Kind::Nil;
    Vector2 pos;
    bool active = true;
    bool queue_free = false;

    // components
    ColliderComponent collider;
    SpriteComponent sprite;
    HealthComponent health;
    AttackComponent attack;
    PhysicsComponent physics;
    AnimationComponent animation;

    // int parent_idx;
    // int first_item; // the first item that the entity owns
    // int next_item; // the sibling item to ourselves

    EntityRef parent_ref;
    EntityRef first_child_ref;
    EntityRef next_sibling_ref;
    EntityRef previous_sibling_ref;

    // collision related
    std::function<void(int,int, EntityArray&)> on_collision_enter = nullptr;
    std::function<void(int,int, EntityArray&)> on_collision_stay = nullptr;
    std::function<void(int,int, EntityArray&)> on_collision_exit = nullptr;

    operator bool() const{
        return kind != Kind::Nil;
    }

    // bool has_child(int idx);
};


namespace EntityHelpers {
    // center of the entity return the center of the collider not the position of the entity
    Vector2 center(Entity &e);
    Vector2 top_left(Entity &e);
    Rectangle rect(Entity &e);
    void on_hit_damage(Entity &e, float amount);
}

#endif //
