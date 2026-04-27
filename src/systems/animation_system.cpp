#include "animation_system.h"

struct GameData;

namespace Systems {

void animation(float deltaTime, GameData &game_data)
{
    EntityArray &e_array = game_data.entities;

    // for(auto &e:game_data.entities.entities){
    for (int i = 0; i < e_array.get_count(); ++i) {
        if(!e_array.used[i]) continue;

        Entity &e = e_array.entities[i];

        // if it's moving is run otherwise idle (for now)
        if(!e.animation.active) continue;

        // change star frame based on direction
        int startFrame = e.animation.lastFrame;

        if(e.physics.acceleration.x < 0){
            startFrame = e.animation.startFrame+3;
        }
        if(e.physics.acceleration.x > 0){
            startFrame = e.animation.startFrame;
        }
        if(e.physics.acceleration.y < 0){
            startFrame = e.animation.startFrame+2;
        }
        if(e.physics.acceleration.y > 0){
            startFrame = e.animation.startFrame+1;
        }

        e.animation.animationCounter += deltaTime;



        // playing default animation or actor animation?
        if(e.animation.defaultAnimation){

            // TraceLog(LOG_INFO,"entity: %i",i);

            // TraceLog(LOG_INFO,"frame:%u last_frame:%u",e.animation.currentFrame, e.animation.lastFrame);
            // TraceLog(LOG_INFO,"frame:%u last_frame:%u",e.animation.currentFrame, e.animation.lastFrame);

            // if(e.animation.currentFrame == (e.animation.startFrame+e.animation.frameCount)){
            //     if(e.animation.deactivateOnFinish){
            //         e.animation.active = false;
            //         e.active = false;
            //     }
            // }

            if(e.animation.animationCounter >= e.animation.defaultDuration){
                if(e.animation.currentFrame == (e.animation.frameCount-1)){
                    e.animation.active = false;

                    if(e.animation.deactivateOnFinish){
                        e.active = false;
                        e.collider.active = false;
                    }

                }

                e.animation.currentFrame = ((e.animation.currentFrame+1) % e.animation.frameCount);
                e.animation.animationCounter = 0.0f;
            }

            size_t index = e.animation.currentFrame + e.animation.startFrame;
            e.sprite.texture_index = index;
        }else{
            if(Vector2Length(e.physics.acceleration) > 0){

                if(e.animation.animationCounter >= e.animation.runDuration){
                    e.animation.animationCounter = 0.0f;

                    // index = (index + 1) % size; (WRAP AROUND INDEX)
                    // e.animation.currentFrame = (e.animation.currentFrame+1) % e.animation.frameCount;
                    e.animation.currentFrame =
                            ((e.animation.currentFrame + e.animation.frameOffset) %
                             (e.animation.frameCount * e.animation.frameOffset)) + e.animation.startFrame;
                }
            }else{
                if(e.animation.animationCounter >= e.animation.idleDuration){
                    e.animation.animationCounter = 0.0f;

                    // index = (index + 1) % size; (WRAP AROUND INDEX)
                    // e.animation.currentFrame = (e.animation.currentFrame+1) % e.animation.frameCount;
                    e.animation.currentFrame =
                            ((e.animation.currentFrame + e.animation.frameOffset) %
                             (e.animation.frameCount * e.animation.frameOffset)) + e.animation.startFrame;

                }
            }

            e.animation.lastFrame = startFrame;
            e.sprite.texture_index = (e.animation.currentFrame + startFrame);
        }
    }
}

}
