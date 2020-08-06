#ifndef ASSETLOOKUPTABLE_H
#define ASSETLOOKUPTABLE_H


#include <string>
#include "../Engine/Math/Vector2D.h"


struct tableElement
{
  std::string assetName;
  std::string assetPath;
  bool isSheet;
  Vector2D sheetIndex;
};
typedef struct tableElement tableElement;

struct assetInfo
{
  std::string assetPath;
  Vector2D sheetIndex;
};
typedef struct assetInfo assetInfo;


namespace AssetLT
{
  assetInfo findAsset(std::string assetName);  // Returns the asset's path and sheet index
}

#endif