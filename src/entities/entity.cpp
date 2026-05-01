#include "entity.h"

namespace EntityHelpers {

Vector2 center(Entity &e)
{
    Vector2 res = e.pos + e.collider.offset + Vector2{e.collider.width/2,e.collider.height/2};
    // Vector2 res = e.pos + e.collider.offset + Vector2{e.collider.w/2,e.collider.h/2};
    return res;
}

Vector2 top_left(Entity &e)
{
    // Vector2 res = e.pos + e.collider.offset + Vector2{e.collider.w/2,e.collider.h/2};
    Vector2 res = e.pos + e.collider.offset;
    return res;
}

Rectangle rect(Entity &e)
{
    Vector2 res = e.pos + e.collider.offset;
    return Rectangle{res.x, res.y, e.collider.width, e.collider.height};
}

void on_hit_damage(Entity &e, float amount){
    e.health.current_health -= amount;
}

}


