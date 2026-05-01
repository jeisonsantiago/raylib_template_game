#include "asset_manager.h"

void updateTileCount(TextureAsset& textureAsset){
    if(textureAsset.texture.id != -1){
        textureAsset.tileCountRows = (int)textureAsset.texture.height / textureAsset.tileSizeH;
        textureAsset.tileCountCols = (int)textureAsset.texture.width / textureAsset.tileSizeW;
        textureAsset.tileCount =  textureAsset.tileCountRows * textureAsset.tileCountCols;
    }
}
void AssetManager::loadAll()
{
    this->world.texture = LoadTexture(RESOURCES_PATH "/images/tiny_dungeon_world.png");
    updateTileCount(this->world);

    this->interface.texture = LoadTexture(RESOURCES_PATH "/images/tiny_dungeon_interface.png"); // 16 rows 16 cols
    updateTileCount(this->interface);

    this->characters.texture = LoadTexture(RESOURCES_PATH "/images/tiny_dungeon_monsters.png"); // 16 rows 16 cols
    updateTileCount(this->characters);

    this->fxAltered.texture = LoadTexture(RESOURCES_PATH "/images/tiny_dungeon_fx_altered.png"); // 16 rows 16 cols
    updateTileCount(this->fxAltered);

    this->fx.texture = LoadTexture(RESOURCES_PATH "/images/tiny_dungeon_fx.png"); // 16 rows 16 cols
    updateTileCount(this->fx);

    this->itemsNoShadow.texture = LoadTexture(RESOURCES_PATH "/images/tiny_dungeon_items_no_shadow.png"); // 16 rows 16 cols
    updateTileCount(this->itemsNoShadow);

    this->pixelFont = LoadFont(RESOURCES_PATH "/fonts/pixantiqua.ttf");

    // workaround for serialization
    this->textures.push_back(&this->world);
    this->textures.push_back(&this->interface);
    this->textures.push_back(&this->characters);
    this->textures.push_back(&this->fxAltered);
    this->textures.push_back(&this->fx);
    this->textures.push_back(&this->itemsNoShadow);
}

Rectangle getSourceRectangleByIndex(int index, TextureAsset &textureAsset)
{
    Rectangle rect = {};
    int txRow = index / (textureAsset.texture.width / textureAsset.tileSizeW);
    int txCol = index % (textureAsset.texture.width / textureAsset.tileSizeH);

    // TraceLog(LOG_INFO,"%i %i",txCol, txRow);

    rect = {
        (float)txCol * textureAsset.tileSizeW,
        (float)txRow *  textureAsset.tileSizeH,
        (float)textureAsset.tileSizeW,
        (float)textureAsset.tileSizeH
    };

    return rect;
}
