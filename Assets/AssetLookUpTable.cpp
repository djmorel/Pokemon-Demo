#include "AssetLookupTable.h"
#include <string.h>


const tableElement AssetLookupTable[] = {
  {"DefaultObj"     , "Assets/Art/DefaultObject.png"              , false, Vector2D(-1, -1) },
  {"GrassBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(0, 0)   },
  {"DirtBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(0, 1)   },
  {"StoneBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(0, 2)   },
  {"WaterBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(0, 3)   },
  {"SandBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(0, 4)   },
  {"TreeBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(0, 5)   },
  {"LeafBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(1, 0)   },
  {"TNTBlock"       , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(1, 1)   },
  {"GlassBlock"     , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(1, 2)   },
  {"GoldBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(1, 3)   },
  {"DiamondBlock"   , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(1, 4)   },
  {"RedStoneBlock"  , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(1, 5)   },
  {"WoodBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(2, 0)   },
  {"CoalBlock"      , "Assets/Art/MinecraftBlocks_Spritesheet.png", true , Vector2D(2, 1)   },
  {"Hilda_F_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(0, 0)   },
  {"Hilda_F_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(0, 1)   },
  {"Hilda_F_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(0, 2)   },
  {"Hilda_F_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(0, 3)   },
  {"Hilda_L_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(1, 0)   },
  {"Hilda_L_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(1, 1)   },
  {"Hilda_L_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(1, 2)   },
  {"Hilda_L_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(1, 3)   },
  {"Hilda_R_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(2, 0)   },
  {"Hilda_R_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(2, 1)   },
  {"Hilda_R_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(2, 2)   },
  {"Hilda_R_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(2, 3)   },
  {"Hilda_B_Stand"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(3, 0)   },
  {"Hilda_B_Walk1"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(3, 1)   },
  {"Hilda_B_Walk2"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(3, 2)   },
  {"Hilda_B_Walk3"  , "Assets/Art/Trainer_Hilda_Spritesheet.png"  , true , Vector2D(3, 3)   },
  {"Miku"           , "Assets/Art/Trainer_Miku.png"               , false, Vector2D(-1, -1) },
  {"Trees"          , "Assets/Art/Tree_Spritesheet.png"           , false, Vector2D(-1, -1) },  // TODO: Enable sheet
  {"Tyranitar"      , "Assets/Art/Tyranitar.png"                  , false, Vector2D(-1, -1) }
};


namespace AssetLT
{
  // Returns the asset's path and sheet index
  assetInfo findAsset(std::string assetName)
  {
    // Prepare the return value
    assetInfo ret_val;
    ret_val.assetPath = "";
    ret_val.sheetIndex = Vector2D(-1, -1);
  
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
      }
    }
  
    // Couldn't find the asset, so return the default ret_val
    return ret_val;
  }
}
