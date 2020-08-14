#ifndef ASSETLOOKUPTABLE_H
#define ASSETLOOKUPTABLE_H


#include <string>
#include "../Engine/Math/Vector2D.h"


struct tableElement
{
  int assetID;            // Numerical ID for the asset (indexable)
  std::string assetName;  // Name ID for the asset
  std::string assetPath;  // Path for the asset
  Vector2D sheetIndex;    // Index of the sprite on the sheet (first quadrant coordinates)
  int spriteRows;         // Number of sprite units per sheet row
  int spriteColumns;      // Number of sprite units per sheet column
  int unitsHigh;          // How many sprite units make up this sprite's height
  int unitsWide;          // How many sprite units make up this sprite's width
};
typedef struct tableElement tableElement;


// Struct initialized to invalid asset entry
struct assetInfo
{
  std::string assetPath = "";
  Vector2D sheetIndex   = Vector2D(-1, -1);
  int spriteRows        = -1;
  int spriteColumns     = -1;
  int unitsHigh         = -1;
  int unitsWide         = -1;
};
typedef struct assetInfo assetInfo;


namespace AssetLT
{
  assetInfo findAsset(std::string assetName);  // Returns the asset's path and sheet index from assetName
  assetInfo findAsset(int _id);                // Returns the asset's path and sheet index from ID #
}

#endif