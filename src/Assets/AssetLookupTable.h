#ifndef ASSETLOOKUPTABLE_H
#define ASSETLOOKUPTABLE_H


#include <string>
#include "../Engine/Math/Vector2D.h"
#include "../Engine/Math/Vector3D.h"


struct tableElement
{
  int assetID;                   // Numerical ID for the asset (indexable)
  std::string assetName;         // Name ID for the asset
  std::string assetPath;         // Path for the asset
  Vector2D sheetIndex;           // Index of the sprite on the sheet (first quadrant coordinates)
  int spriteColumns;             // Number of sprite units per sheet column
  int spriteRows;                // Number of sprite units per sheet row
  int unitsWide;                 // How many sprite units make up this sprite's width
  int unitsHigh;                 // How many sprite units make up this sprite's height
  Vector3D suggestedDimensions;  // Suggested default dimension for the Sprite (in pixels) [TODO: Remove this when art is custom designed]
};
typedef struct tableElement tableElement;


// Struct initialized to invalid asset entry
struct assetInfo
{
  std::string assetPath = "";                // Path for the asset
  Vector2D sheetIndex   = Vector2D(-1, -1);  // Sprite's index on the spritesheet - (0, 0) at bottom left of the image
  int spriteRows        = -1;                // Number of rows (based on sprite units) on the spritesheet
  int spriteColumns     = -1;                // Number of columns (based on sprite units) on the spritesheet
  int unitsHigh         = -1;                // Number of sprite units in the y direction this sprite encompasses
  int unitsWide         = -1;                // Number of sprite units in the x direction this sprite encompasses
};
typedef struct assetInfo assetInfo;


namespace AssetLT
{
  /**
    Finds the asset's information from the AssetLookupTable.
    \param std::string assetName - Name shortcut for the asset.
    \return assetInfo object from the asset's entry.
  **/
  assetInfo findAsset(std::string assetName);

  /**
    Finds the asset's information from the AssetLookupTable.
    \param int _id - assetID that indexes to the AssetLookupTable.
    \return assetInfo object from the asset's entry.
  **/
  assetInfo findAsset(int _id);

  /**
    Finds the asset's suggested dimensions from the AssetLookupTable.
    \param int _id - assetID that indexes to the AssetLookupTable.
    \return Vector3D containing the asset's suggested default dimensions. If invalid assetID, returns Vector3D(0).
  **/
  Vector3D getDefaultDimensions(int _id);
}

#endif