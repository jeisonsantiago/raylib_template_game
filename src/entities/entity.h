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

// // Fixed size NOT DYNAMIC!
struct Entity{
    Kind kind  = Kind::Nil;
    Vector2 pos;

    // components
    ColliderComponent collider;
    SpriteComponent sprite;
    HealthComponent health;
    AttackComponent attack;
    PhysicsComponent physics;

    // int parent_idx;
    // int first_item; // the first item that the entity owns
    // int next_item; // the sibling item to ourselves

    EntityRef parent_idx;
    EntityRef first_child_idx;
    EntityRef next_sibling_idx;
    EntityRef previous_sibling_idx;

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
}

#endif //
