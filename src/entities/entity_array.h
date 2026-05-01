#ifndef ENTITY_ARRAY_H
#define ENTITY_ARRAY_H

#include "entity.h"

struct EntityArray{
    Entity entities[MAX_ENTITIES];
    bool used[MAX_ENTITIES] = {0}; // to keep track of used slots inside entities
    int gen[MAX_ENTITIES] = {0}; // to keep track of used slots inside entities

    int count = 1;

    // int next_empty_slot = 1; // since 0 is the (NIL) INVALID slot

    Entity& entityLastChild(EntityRef idx){
        return entities[entities[idx.idx].first_child_ref.idx];
    }

    int get_count(){
        return (count);
    }

    // return index from created entity
    EntityRef add(Kind kind){
        // entity_ref slot = {};
        int slot = find_empty();
        if(slot){
            entities[slot] = {}; // set to 0
            entities[slot].kind = kind;
            used[slot] = true;
            gen[slot] +=1;
            count++;
            return {slot,gen[slot]};

        }

        return EntityRef::nil();
    }

    EntityRef get_ref(int idx){
        return EntityRef{.idx = idx, .gen = gen[idx]};
    }

    void remove(EntityRef ref){
        int index = deref(ref);
        TraceLog(LOG_INFO,"REMOVE: %i %i %i",index, ref.idx, ref.gen);
        used[index] = false;
    }

    Entity &get(EntityRef ref){
        int idx = deref(ref);
        return entities[idx];
    }

    void clear(){
        this->count = 1;
        memset(entities,0,sizeof(entities));
        memset(used,0,sizeof(used));
        memset(gen,0,sizeof(gen));
    }

private:

    int find_empty(){
        for (int i = 1; i < MAX_ENTITIES; ++i) { // start with 1 since 0 is NIL
            if(!used[i]){
                return i; // return unused index
            }
        }

        return 0; // there all being used!
    }

    // get index and check if the reference counter is the same
    int deref(EntityRef ref){
        if(ref.idx > 0 && ref.idx < MAX_ENTITIES && used[ref.idx] && ref.gen == gen[ref.idx]){
            return ref.idx;
        }

        return 0;
    }
};


// // helpers example
// void entity_array_reset(EntityArray &entity_array){
//     entity_array = {};
// }

#endif // ENTITY_ARRAY_H
