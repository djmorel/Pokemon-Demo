#include "AssetLookupTable.h"
#include <string.h>


// Note: Spritesheets are organized based on x & y coordinates in the FIRST QUADRANT
//   (0, 0) --> Bottom left
//   (1, 1) --> Top Right
// If the texture isn't a spritesheet, spriteRows == sprite Columns
const tableElement AssetLookupTable[] = {
  { 0, "DefaultObj"     , "src/Assets/Art/DefaultObject.png"              , Vector2D(0, 0), 1, 1, 1, 1 },
  { 1, "StartScreen"    , "src/Assets/Art/Emerald_StartScreen.png"        , Vector2D(0, 0), 1, 1, 1, 1 },
  { 2, "EndScreen"      , "src/Assets/Art/GameOverScreen.png"             , Vector2D(0, 0), 1, 1, 1, 1 },
  { 3, "Loading"        , "src/Assets/Art/Loading.png"                    , Vector2D(0, 0), 1, 1, 1, 1 },
  { 4, "GrassBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(0, 2), 3, 6, 1, 1 },
  { 5, "DirtBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(1, 2), 3, 6, 1, 1 },
  { 6, "StoneBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(2, 2), 3, 6, 1, 1 },
  { 7, "WaterBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(3, 2), 3, 6, 1, 1 },
  { 8, "SandBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(4, 2), 3, 6, 1, 1 },
  { 9, "TreeBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(5, 2), 3, 6, 1, 1 },
  {10, "LeafBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(0, 1), 3, 6, 1, 1 },
  {11, "TNTBlock"       , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(1, 1), 3, 6, 1, 1 },
  {12, "GlassBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(2, 1), 3, 6, 1, 1 },
  {13, "GoldBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(3, 1), 3, 6, 1, 1 },
  {14, "DiamondBlock"   , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(4, 1), 3, 6, 1, 1 },
  {15, "RedStoneBlock"  , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(5, 1), 3, 6, 1, 1 },
  {16, "WoodBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(0, 0), 3, 6, 1, 1 },
  {17, "CoalBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D(1, 0), 3, 6, 1, 1 },
  {18, "Hilda_D_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 3), 4, 4, 1, 1 },
  {19, "Hilda_D_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 3), 4, 4, 1, 1 },
  {20, "Hilda_D_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 3), 4, 4, 1, 1 },
  {21, "Hilda_D_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 3), 4, 4, 1, 1 },
  {22, "Hilda_L_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 2), 4, 4, 1, 1 },
  {23, "Hilda_L_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 2), 4, 4, 1, 1 },
  {24, "Hilda_L_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 2), 4, 4, 1, 1 },
  {25, "Hilda_L_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 2), 4, 4, 1, 1 },
  {26, "Hilda_R_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 1), 4, 4, 1, 1 },
  {27, "Hilda_R_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 1), 4, 4, 1, 1 },
  {28, "Hilda_R_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 1), 4, 4, 1, 1 },
  {29, "Hilda_R_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 1), 4, 4, 1, 1 },
  {30, "Hilda_U_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(0, 0), 4, 4, 1, 1 },
  {31, "Hilda_U_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(1, 0), 4, 4, 1, 1 },
  {32, "Hilda_U_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(2, 0), 4, 4, 1, 1 },
  {33, "Hilda_U_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D(3, 0), 4, 4, 1, 1 },
  {34, "Miku"           , "src/Assets/Art/Trainer_Miku.png"               , Vector2D(0, 0), 1, 1, 1, 1 },
  {35, "Trees"          , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(0, 0), 1, 1, 1, 1 },  // TODO: Enable sheet
  {36, "Tyranitar"      , "src/Assets/Art/Tyranitar.png"                  , Vector2D(0, 0), 1, 1, 1, 1 }
};


namespace AssetLT
{
  // Returns the asset's path and sheet index from assetName
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

  // Returns the asset's path and sheet index from ID #
  assetInfo findAsset(int _id)
  {
    // Prepare the return value
    assetInfo ret_val;

    // Get the size of the lookup table
    int num_elements = sizeof(AssetLookupTable) / sizeof(tableElement);

    // Check for a valid ID
    if (_id >= 0 && _id < num_elements)
    {
      // Index into the lookup table using the passed ID number
      ret_val.assetPath = AssetLookupTable[_id].assetPath;
      ret_val.sheetIndex = AssetLookupTable[_id].sheetIndex;
      ret_val.spriteRows = AssetLookupTable[_id].spriteRows;
      ret_val.spriteColumns = AssetLookupTable[_id].spriteColumns;
      ret_val.unitsHigh = AssetLookupTable[_id].unitsHigh;
      ret_val.unitsWide = AssetLookupTable[_id].unitsWide;
    }

    // Return the ret_val regardless if valid ID or not (invalid ID returns default ret_val)
    return ret_val;
  }
}