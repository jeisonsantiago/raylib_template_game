#include "editor.h"
// #include "SaveLoadMap.h"
#include "game_data.h"

void Editor::drawGUI(GameData &game_data, AssetManager& assetManager)
{
    // GameData &gameData = gameState.gameScene.gameData;

    ImGui::Begin("Editor");

    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows))
    {
        game_data.mouse_over_editor_ui = true;
    }else{
        game_data.mouse_over_editor_ui = false;
    }

    ImGui::Text("Camera:");
    ImGui::SliderFloat("Camera Speed",&game_data.camera_speed,10,100);
    ImGui::SliderFloat("Camera Zoom",&game_data.camera.zoom,1,100);


    ImGui::Separator();
    ImGui::Text("Map:");

    ImGui::Text("Map Layer:");
    ImGui::SameLine();

    const char* items[] = { "LAYER_GROUND", "LAYER_SOLID", "LAYER_VISUALS"};
    static const char* currentItem = nullptr;
    // gameData.mapLayerSelected = -1;
    if (ImGui::BeginCombo("##combo", currentItem)) {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
            bool isSelected = (currentItem == items[n]);
            if (ImGui::Selectable(items[n], isSelected)) {
                currentItem = items[n];
                // game_data.mapLayerSelected = n;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();

            }
        }
        ImGui::EndCombo();
    }

    // if(game_data.mapLayerSelected != -1){
    //     size_t numberOfTiles = assetManager.world.tileCount;

    //     for (int i = 0; i < numberOfTiles; i++) {
    //         auto atlas = getSourceRectangleByIndex(i,assetManager.world);
    //         atlas.x /= assetManager.world.texture.width;
    //         atlas.width /= assetManager.world.texture.width;
    //         atlas.y /= assetManager.world.texture.height;
    //         atlas.height /= assetManager.world.texture.height;

    //         ImGui::PushID(i);
    //         ImTextureID tex = (ImTextureID)(intptr_t)assetManager.world.texture.id;
    //         if(ImGui::ImageButton(tex,{32,32},{atlas.x, atlas.y},{atlas.x + atlas.width,atlas.y + atlas.height}))
    //         {
    //             game_data.creativeSelectedBlock = i;
    //         }
    //         ImGui::PopID();

    //         if((i+1) % 16 != 0){
    //             ImGui::SameLine();
    //         }
    //     }
    // }

    // ImGui::Separator();
    // // save and load map
    // ImGui::InputText("File Name:",game_data.saveMapName,sizeof(game_data.saveMapName));
    // if(ImGui::Button("Save Map to file")){
    //     std::string path = RESOURCES_PATH "maps/";
    //     path += game_data.saveMapName;
    //     path += ".bin";


    //     // saveBlockDataToFile(gameData.copyStructure.mapData,gameData.copyStructure.w,gameData.copyStructure.h,path.c_str());
    //     SaveMap(game_data.gameMap,path.c_str());
    // }

    // if(ImGui::Button("Load Map from file")){
    //     std::string path = RESOURCES_PATH "maps/";
    //     path += game_data.saveMapName;
    //     path += ".bin";

    //     // saveBlockDataToFile(gameData.copyStructure.mapData,gameData.copyStructure.w,gameData.copyStructure.h,path.c_str());
    //     LoadMap(game_data.gameMap,path.c_str());
    // }

    ImGui::End();

    // draw map lines
    Rectangle mapRect = {0,0,(float)game_data.game_map.w,(float)game_data.game_map.h};
    DrawRectangleLinesEx(mapRect,0.05,GREEN);
}

void Editor::processEditor(GameData &game_data)
{

    // GameData &gameData = gameState.gameScene.gameData;

    // if the mouse is off map return!
    if(game_data.mouse_block_pos.x < 0 || game_data.mouse_block_pos.y < 0) return;

    if(game_data.mouse_block_pos.x > game_data.game_map.w-1 || game_data.mouse_block_pos.y > game_data.game_map.h-1) return;

    // insert/replace block in the map
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && game_data.selected_texture_block != -1){
        int x = (int)game_data.mouse_block_pos.x;
        int y = (int)game_data.mouse_block_pos.y;

        int mapLayerSelected = game_data.map_layer_selected;

        // Block *b = gameData.game_map.getBlockSafe(x,y,mapLayerSelected);

        // if(b){
        //     int textureIndex = gameData.creativeSelectedBlock;
        //     b->textureIndex = textureIndex;
        //     b->type = mapLayerSelected;
        // }
    }

    // remove block in the map
    if(IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)){
        int x = (int)game_data.mouse_block_pos.x;
        int y = (int)game_data.mouse_block_pos.y;

        int map_layer_selected = game_data.map_layer_selected;

        // Block *b = gameData.gameMap.getBlockSafe(x,y,mapLayerSelected);

        // if(b){
        //     b->clear();
        // }
    }
}
