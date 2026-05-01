#include "serialization_map.h"


#include "game_data.h"

const int VERSION = 1;

namespace Serialization {

bool save_map_to_file(GameData &game_data)
{

    std::error_code errorCode;
    std::filesystem::create_directory(RESOURCES_PATH "../saves",errorCode);

    std::ofstream f(RESOURCES_PATH "../saves/map.bin.tmp", std::ios::binary);

    if(!f.is_open()) {return false;}

    // map size
    // int w = game_data.game_map.w;
    // int h = game_data.game_map.h;

    // permaAssertDevelopement(blocks.size() == w * h);
    // permaAssertDevelopement(blocks.size() != 0);

    // if(blocks.size() != w * h) {return false;}
    // if(blocks.size() == 0) {return false;}

    // write version
    // f.write((const char *)&VERSION, sizeof(VERSION));
    // // write map size w and h
    // f.write((const char*)&w,sizeof(w));
    // f.write((const char*)&h,sizeof(w));

    // go over map layers and save reference


    // write vector of blocks
    //f.write((const char*)blocks.data(),sizeof(Block) * blocks.size());
    // for (int i = 0; i < blocks.size(); ++i) {
    //     auto b = toBlockRepresentation(blocks[i]);
    //     f.write((const char*)&b, sizeof(b));
    // }

    // save every entity...boom

    EntityArray &e_array = game_data.entities;

    f.write((const char*)&e_array,sizeof(EntityArray));

    // for (int i = 0; i < e_array.get_count(); ++i) {

    // }

    f.close();

    std::filesystem::rename(RESOURCES_PATH "../saves/map.bin.tmp",RESOURCES_PATH "../saves/map.bin",errorCode);

    return true;
}

bool load_map(GameData &game_data, AssetManager &asset_manager)
{
    game_data.entities.clear();

    // load from file
    std::ifstream f(RESOURCES_PATH "../saves/map.bin", std::ios::binary);

    if(!f.is_open()) {return false;}

    f.read((char *)&game_data.entities, sizeof(EntityArray));

    // fix texture
    for (int i = 0; i < game_data.entities.get_count(); ++i) {
        Entity &e = game_data.entities.entities[i];
        e.sprite.texture_asset = asset_manager.textures[e.sprite.asset_texture_index];
    }

    f.close();

    return true;
}

}
