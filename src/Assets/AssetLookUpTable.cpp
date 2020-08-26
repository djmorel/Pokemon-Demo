#include "AssetLookupTable.h"
#include "../Engine/Engine.h"
#include <string.h>


// Note: Spritesheets are organized based on x & y coordinates in the FIRST QUADRANT
//   (0, 0) --> Bottom left
//   (1, 1) --> Top Right
// If the texture isn't a spritesheet, spriteRows == sprite Columns
const tableElement AssetLookupTable[] = {
// ID  assetName          assetPath                                         sheetIndex       rows cols
  { 0, "DefaultObj"     , "src/Assets/Art/DefaultObject.png"              , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 1, "StartScreen"    , "src/Assets/Art/Emerald_StartScreen.png"        , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT, 0)},
  { 2, "EndScreen"      , "src/Assets/Art/GameOverScreen.png"             , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT, 0)},
  { 3, "Loading"        , "src/Assets/Art/Loading.png"                    , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 4, "GrassBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 0,  2) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 5, "DirtBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 1,  2) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 6, "StoneBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 2,  2) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 7, "WaterBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 3,  2) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 8, "SandBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 4,  2) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  { 9, "TreeBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 5,  2) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {10, "LeafBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 0,  1) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {11, "TNTBlock"       , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 1,  1) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {12, "GlassBlock"     , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 2,  1) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {13, "GoldBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 3,  1) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {14, "DiamondBlock"   , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 4,  1) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {15, "RedStoneBlock"  , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 5,  1) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {16, "WoodBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 0,  0) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {17, "CoalBlock"      , "src/Assets/Art/MinecraftBlocks_Spritesheet.png", Vector2D( 1,  0) ,  6,  3,  1,  1 , Vector3D(64, 64, 0)                                     },
  {18, "Hilda_D_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 0,  3) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {19, "Hilda_D_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 1,  3) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {20, "Hilda_D_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 2,  3) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {21, "Hilda_D_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 3,  3) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {22, "Hilda_L_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 0,  2) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {23, "Hilda_L_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 1,  2) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {24, "Hilda_L_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 2,  2) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {25, "Hilda_L_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 3,  2) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {26, "Hilda_R_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 0,  1) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {27, "Hilda_R_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 1,  1) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {28, "Hilda_R_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 2,  1) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {29, "Hilda_R_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 3,  1) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {30, "Hilda_U_Stand"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 0,  0) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {31, "Hilda_U_Walk1"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 1,  0) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {32, "Hilda_U_Walk2"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 2,  0) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {33, "Hilda_U_Walk3"  , "src/Assets/Art/Trainer_Hilda_Spritesheet.png"  , Vector2D( 3,  0) ,  4,  4,  1,  1 , Vector3D(64, 96, 0)                                     },
  {34, "Miku"           , "src/Assets/Art/Trainer_Miku.png"               , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(128, 128, 0)                                   },
  {35, "Tyranitar"      , "src/Assets/Art/Tyranitar.png"                  , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(128, 128, 0)                                   },
  {36, "Trees"          , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D( 0,  0) ,  1,  1,  1,  1 , Vector3D(128, 128, 0)                                   },
  {37, "Trees_Top1st"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D( 0, 40) , 48, 54, 11, 14 , Vector3D(192, 192, 0)                                   },
  {38, "Trees_Top2nd"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(11, 40) , 48, 54, 12, 14 , Vector3D(192, 192, 0)                                   },
  {39, "Trees_Top3rd"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(23, 40) , 48, 54, 10, 14 , Vector3D(160, 192, 0)                                   },
  {40, "Trees_Cen1st"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D( 1, 23) , 48, 54,  9, 13 , Vector3D(160, 192, 0)                                   },
  {41, "Trees_Cen2nd"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(11, 22) , 48, 54,  8, 14 , Vector3D(128, 192, 0)                                   },
  {42, "Trees_Cen3rd"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(34, 18) , 48, 54, 10, 14 , Vector3D(160, 192, 0)                                   },
  {43, "Trees_Cen4th"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(44, 27) , 48, 54,  4, 10 , Vector3D(64, 128, 0)                                    },
  {44, "Trees_Bot1st"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D( 0,  5) , 48, 54, 11, 15 , Vector3D(176, 192, 0)                                   },
  {45, "Trees_Bot2nd"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(23,  4) , 48, 54, 10, 14 , Vector3D(176, 192, 0)                                   },
  {46, "Trees_Bot3rd"   , "src/Assets/Art/Tree_Spritesheet.png"           , Vector2D(34,  4) , 48, 54, 10, 14 , Vector3D(160, 192, 0)                                   } 
};


namespace AssetLT
{
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
        //ret_val.spriteRows = AssetLookupTable[i].sprite_Cols_Rows.y;
        //ret_val.spriteColumns = AssetLookupTable[i].sprite_Cols_Rows.x;
        //ret_val.unitsHigh = AssetLookupTable[i].units_Wide_High.y;
        //ret_val.unitsWide = AssetLookupTable[i].units_Wide_High.x;
        ret_val.spriteRows = AssetLookupTable[i].spriteRows;
        ret_val.spriteColumns = AssetLookupTable[i].spriteColumns;
        ret_val.unitsHigh = AssetLookupTable[i].unitsHigh;
        ret_val.unitsWide = AssetLookupTable[i].unitsWide;
      }
    }
  
    // Couldn't find the asset, so return the default ret_val
    return ret_val;
  }



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


  Vector3D getDefaultDimensions(int _id)
  {
    // Get the size of the lookup table
    int num_elements = sizeof(AssetLookupTable) / sizeof(tableElement);
    
    // Check for a valid ID
    if (_id >= 0 && _id < num_elements)
    {
      return AssetLookupTable[_id].suggestedDimensions;
    }
    else
    {
      // Invalid assetID, so return an error return value
      return Vector3D(0);
    }
  }
}
