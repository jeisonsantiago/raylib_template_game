#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

struct TextureAsset {
  Texture2D texture;
  int tileSizeW = 16;
  int tileSizeH = 16;
  int tileCountRows = 0;
  int tileCountCols = 0;
  int tileCount = 0;
};

struct AssetManager {
  TextureAsset world;
  TextureAsset interface; // 16 rows 16 cols
  TextureAsset characters; // 16 rows 16 cols
  TextureAsset fx;
  TextureAsset fxAltered;
  TextureAsset itemsNoShadow;
  void loadAll();

  Font pixelFont;
};

Rectangle getSourceRectangleByIndex(int index, TextureAsset &textureAsset);

#endif // ASSETMANAGER_H
