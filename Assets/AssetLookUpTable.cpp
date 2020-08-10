#include "AssetLookupTable.h"
#include <string.h>


// Note: Spritesheets are organized based on x & y coordinates in the FIRST QUADRANT
//   (0, 0) --> Bottom left
//   (1, 1) --> Top Right
// If the texture isn't a spritesheet, spriteRows == sprite Columns
const tableElement AssetLookupTable[] = {
  {"DefaultObj"     , "Assets/Art/DefaultObject.png"              , Vector2D(0, 0), 1, 1, 1, 1 },
  {"StartScreen"    , "Assets/Art/Emerald_StartScreen.png"        , Vector2D(0, 0), 1, 1, 1, 1 },
  {"EndScreen"      , "Assets/Art/GameOverScreen.png"             , Vector2D(0, 0), 1, 1, 1, 1 },
  {"Loading"        , "Assets/Art/Loading.png"                    , Vector2D(0, 0), 1, 1, 1, 1 },
  {"GrassBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(0, 2), 3, 6, 1, 1 },
  {"DirtBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(1, 2), 3, 6, 1, 1 },
  {"StoneBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(2, 2), 3, 6, 1, 1 },
  {"WaterBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(3, 2), 3, 6, 1, 1 },
  {"SandBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(4, 2), 3, 6, 1, 1 },
  {"TreeBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(5, 2), 3, 6, 1, 1 },
  {"LeafBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(0, 1), 3, 6, 1, 1 },
  {"TNTBlock"       , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(1, 1), 3, 6, 1, 1 },
  {"GlassBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(2, 1), 3, 6, 1, 1 },
  {"GoldBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(3, 1), 3, 6, 1, 1 },
  {"DiamondBlock"   , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(4, 1), 3, 6, 1, 1 },
  {"RedStoneBlock"  , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(5, 1), 3, 6, 1, 1 },
  {"WoodBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(0, 0), 3, 6, 1, 1 },
  {"CoalBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(1, 0), 3, 6, 1, 1 },
  {"Hilda_F_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 3), 4, 4, 1, 1 },
  {"Hilda_F_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 2), 4, 4, 1, 1 },
  {"Hilda_F_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 1), 4, 4, 1, 1 },
  {"Hilda_F_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 0), 4, 4, 1, 1 },
  {"Hilda_L_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 3), 4, 4, 1, 1 },
  {"Hilda_L_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 2), 4, 4, 1, 1 },
  {"Hilda_L_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 1), 4, 4, 1, 1 },
  {"Hilda_L_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 0), 4, 4, 1, 1 },
  {"Hilda_R_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 3), 4, 4, 1, 1 },
  {"Hilda_R_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 2), 4, 4, 1, 1 },
  {"Hilda_R_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 1), 4, 4, 1, 1 },
  {"Hilda_R_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 0), 4, 4, 1, 1 },
  {"Hilda_B_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 3), 4, 4, 1, 1 },
  {"Hilda_B_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 2), 4, 4, 1, 1 },
  {"Hilda_B_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 1), 4, 4, 1, 1 },
  {"Hilda_B_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 0), 4, 4, 1, 1 },
  {"Miku"           , "Assets/Art/Trainer_Miku.png"               , Vector2D(0, 0), 1, 1, 1, 1 },
  {"Trees"          , "Assets/Art/Tree_Spritesheet.png"           , Vector2D(0, 0), 1, 1, 1, 1 },  // TODO: Enable sheet
  {"Tyranitar"      , "Assets/Art/Tyranitar.png"                  , Vector2D(0, 0), 1, 1, 1, 1 }
};


namespace AssetLT
{
  // Returns the asset's path and sheet index
  assetInfo findAsset(std::string assetName)
  {
    // Prepare the return value
    assetInfo ret_val;
  
    // Find the number of elements in the lookup table
    int num_elements = sizeof(AssetLookupTable) / sizeof(tableElement);
  
    // Iterate through the lookup table
    for (int i = 0; i < num_elements; i++)
    {
      if (assetName == AssetLookupTable[i].assetName)
      {
        // Found the asset in the lookup table!
        ret_val.assetPath = AssetLookupTable[i].assetPath;
        ret_val.sheetIndex = AssetLookupTable[i].sheetIndex;
        ret_val.spriteRows = AssetLookupTable[i].spriteRows;
        ret_val.spriteColumns = AssetLookupTable[i].spriteColumns;
        ret_val.unitsHigh = AssetLookupTable[i].unitsHigh;
        ret_val.unitsWide = AssetLookupTable[i].unitsWide;
      }
    }
  
    // Couldn't find the asset, so return the default ret_val
    return ret_val;
  }
}
