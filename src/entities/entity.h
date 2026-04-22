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

enum class Type{
    Nil,
    Player,
    Enemy,
    Weapon,
    Item,
    Tile,
};

// // Fixed size NOT DYNAMIC!
struct Entity{
    Type kind  = Type::Nil;
    Vector2 pos;

    // components
    ColliderComponent collider;
    SpriteComponent sprite;
    HealthComponent health;
    AttackComponent attack;

    // int parent_idx;
    // int first_item; // the first item that the entity owns
    // int next_item; // the sibling item to ourselves

    EntityRef parent_idx;
    EntityRef first_child_idx;
    EntityRef next_sibling_idx;
    EntityRef previous_sibling_idx;

    // collision related
    std::function<void(std::uint64_t,std::uint64_t, EntityArray&)> on_collision_enter = nullptr;
    std::function<void(std::uint64_t,std::uint64_t, EntityArray&)> on_collision_stay = nullptr;
    std::function<void(std::uint64_t,std::uint64_t, EntityArray&)> on_collision_exit = nullptr;

    operator bool() const{
        return kind != Type::Nil;
    }
};


#endif //
