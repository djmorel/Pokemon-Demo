#ifndef INFOFILES_H
#define INFOFILES_H

#include "../Engine/Math/Vector2D.h"
#include <iostream>
#include <fstream>
#include <string>


// Tile type constants
#define DEFAULT   0  // Default tile that player steps on
#define IMMOVABLE 1  // Tile the player can't step on
#define ENCOUNTER 2  // Tile that grants a wild Pokemon encounter
#define BATTLE    3  // Tile that grants a Pokemon battle
#define LOADMAP   4  // Tile that may load a new map if the right direction is entered on the tile


// Structure containing tile information
struct TileInfo
{
  int id;             // assetID for the tile
  int type;           // Type of the tile
  int layeredItemID;  // assetID for the layered item on this tile (-1 means no layered item)
};
typedef struct TileInfo TileInfo;


// Structure containing player information
struct PlayerInfo
{
  std::string name;          // Player nickname
  bool gender;               // 0 for female & 1 for male
  std::string charInfoPath;  // Path to CharacterInfo
  std::string mapPath;       // Path of last visited map
  Vector2D screenCoord;      // (x, y) coordinates on screen
  Vector2D mapCoord;         // (x, y) coordinates on map
};
typedef struct PlayerInfo PlayerInfo;


namespace InfoFiles
{
  /**
    Converts a string to a Vector2D (x, y) coordinate.
    \param std::string line - String in the format of int_x,int_y.
    \return Vector2D(-1, -1) on failure, or Vector2D based on what was read.
  **/
  Vector2D line2coord(std::string line);

  /**
    Reads from a string up to a delimiter character, and converts what was read to a positive int.
    \param std::string &line - Address of a string to pull an integer from. Note characters (including delimiter) read from the string are erased.
    \param char delimiter - Character that indicates where to stop pulling the integer from the passed string.
    \return int >= 0 on success, or -1 on std::stoi() failure.
  **/
  int intPull(std::string& line, char delimiter);

  /**
    Converts 3 strings into ints, and puts them into a TileInfo object.
    \param std::string _id - String representation of the tile ID.
    \param std::string _type - String representation of the tile type.
    \param std::string _layeredItemID - String representation of the layered item ID.
    \return TileInfo object containing the string to int conversions. If TileInfo.id is -42, the stoi conversion failed and the object is invalid.
  **/
  TileInfo str2TileInfo(std::string _id, std::string _type, std::string _layeredItemID);
}


#endif
