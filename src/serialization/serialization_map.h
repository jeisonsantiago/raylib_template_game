#ifndef SERIALIZATION_MAP_H
#define SERIALIZATION_MAP_H

struct GameData;
struct AssetManager;

namespace Serialization {
    bool save_map_to_file(GameData &game_data);
    bool load_map(GameData &game_data, AssetManager &asset_manager);

}

#endif // SERIALIZATION_MAP_H


// bool saveBlockDataToFile(std::vector<Block> blocks, int w, int h, const char *fileName);
// bool loadBlockDataFromFile(std::vector<Block> &blocks, int &w, int &h, const char *fileName);

// struct GameMap;
// struct Player;
// struct EntityHolder;

// void saveWorld(GameMap &gameMap, EntityHolder &entityHolder, Player &player);
// bool loadWorld(GameMap &gameMap, EntityHolder &entityHolder, Player &player);

