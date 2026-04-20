#ifndef EDITOR_H
#define EDITOR_H

#include "game_data.h"

namespace Editor {

void drawGUI(GameData &game_data, AssetManager& assetManager);
void processEditor(GameData &gameData);

}


#endif // EDITOR_H
