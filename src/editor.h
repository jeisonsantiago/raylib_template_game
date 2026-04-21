#ifndef EDITOR_H
#define EDITOR_H


#include "game_data.h"
#include "asset_manager.h"

namespace Editor {

void drawGUI(GameData &game_data, AssetManager& asset_manager);
void processEditor(GameData &game_state, AssetManager& asset_manager);

}


#endif // EDITOR_H
