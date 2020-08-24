#include "WorldManager.h"
#include "../Engine/Engine.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cmath>



WorldManager::WorldManager(std::string mapPath, PlayerInfo* _playerInfo)
{
  // Set the PlayerInfo pointer so that buildWorld() can access the player coordinates later
  playerInfo = _playerInfo;

  // Read the map blueprints into the map vector
  if (readMap(mapPath) < 0)
  {
    std::cout << "ERROR: Unable to read map blueprints..." << std::endl;
  }
  else
  {
    // Create the tiles from the map vector
    if (buildWorld() < 0)
    {
      std::cout << "ERROR: map has no elements" << std::endl;
    }
  }
}



WorldManager::~WorldManager()
{
  // Free all tiles
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    delete tiles[i];
  }
  tiles.clear();

  // Clear the map
  map.clear();
}



void WorldManager::Update()
{
  // Don't need to do the following since keeping entire map & leaving offscreen tiles offscreen
  /*
  // Vector to hold offscreen tiles
  std::vector<int> tilesToDelete;

  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    tiles[i]->Update();

    // Check if tiles are offscreen
    if (tiles[i]->getPos().x < 0 || tiles[i]->getPos().x > Engine::SCREEN_WIDTH)
    {
      // Tile is out if the valid x range
      tilesToDelete.push_back(i);
    }
    else if (tiles[i]->getPos().y < 0 || tiles[i]->getPos().y > Engine::SCREEN_HEIGHT)
    {
      // Tile is out of the valid y range
      tilesToDelete.push_back(i);
    }
  }

  // Clean up unecessary tiles
  for (int i = tilesToDelete.size() - 1; i >= 0; i--)
  {
    // Go backwards to prevent element misalignment from smaller element erases
    delete tiles[tilesToDelete[i]];                 // Free the allocated memory
    tiles.erase(tiles.begin() + tilesToDelete[i]);  // Remove the entry
  }
  */
}



void WorldManager::Render()
{
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    tiles[i]->Render();
  }
}



int WorldManager::readMap(std::string mapPath)
{
  // Open the passed map file
  std::ifstream fd;
  fd.open(mapPath);

  // Error check the file descriptor
  if (!fd.is_open())
  {
    // Unable to open the file
    std::cout << "Failed to open file: " << mapPath <<std::endl;
    return -1;
  }

  // Variables for reading the map file
  char ch;                    // Holds the currently read character
  TileInfo _tile;             // Holds info on the currently read tile
  std::string _id = "";       // String to hold the tile's ID
  std::string _type = "";     // String to hold the tile's type
  std::vector<TileInfo> row;  // Vector to hold row entries
  bool readID = true;         // Flags if reading tile ID (True) or tile type (false)
  bool completedRow = false;  // Flags if a row is complete, and ready to check mapCols
  int colCount = 0;           // Holds a temporary column count for reference

  // Read the map file
  while ( fd.get(ch) )
  {
    // Check what character we have
    if (ch == ',')  // Finished reading a number
    {
      // Convert charNum to a string
      try
      {
        _tile.id = std::stoi(_id);      // Convert the tile ID string to an integer
        _tile.type = std::stoi(_type);  // Convert the tile type string to an integer
        row.push_back(_tile);           // Add the tile info to the row
      }
      catch (std::invalid_argument const &e)
      {
        // Unable to convert to an int, so corrupt/invalid map
        return -3;
      }
      catch (std::out_of_range const& e)
      {
        // Unable to convert to an int, so corrupt/invalid map
        return -3;
      }

      // Reset reading variables and flags
      _id = "";
      _type = "";
      readID = true;

      // Increment the temporary column count
      colCount++;
    }
    else if (ch == ':')
    {
      // About to read the tile type
      readID = false;
    }
    else if (ch == ';')  // Finished reading a number and a row
    {
      // Convert charNum to a string
      try
      {
        _tile.id = std::stoi(_id);      // Convert the tile ID string to an integer
        _tile.type = std::stoi(_type);  // Convert the tile type string to an integer
        row.push_back(_tile);           // Add the tile info to the row
        map.push_back(row);             // Add the completed row to the map
      }
      catch (std::invalid_argument const& e)
      {
        // Unable to convert to an int, so corrupt/invalid map
        return -3;
      }
      catch (std::out_of_range const& e)
      {
        // Unable to convert to an int, so corrupt/invalid map
        return -3;
      }

      // Reset reading variables and flags
      _id = "";
      _type = "";
      readID = true;

      // Reset the row
      row.clear();

      // Record that a column and row has been completed
      colCount++;
      mapRows++;

      // Check that the column count matches previous ones
      if (completedRow && (colCount != mapCols))
      {
        // The column count isn't consistent, so the map is invalid/corrupted
        return -3;
      }
      else
      {
        completedRow = true;
        mapCols = colCount;
      }

      // Reset the temporary column count
      colCount = 0;
    }
    else if (isdigit(ch) || ch == '-')  // Have a numerical character to add to a reading variable
    {
      if (readID)
      {
        _id.push_back(ch);
      }
      else
      {
        _type.push_back(ch);
      }
    }
    else if (ch != '\n' && ch != ' ')  // Have an invalid character in the map
    {
      // Return an error identifying a corrupt/invalid map
      return -3;
    }
  }  // Completed reading the map file

  // Close the file
  fd.close();
  if (fd.is_open())
  {
    // File not closed
    return -2;
  }

  // Successfully completed reading the map, and closed the file
  return 0;
}



int WorldManager::buildWorld()
{
  // Map blueprints should be already loaded in the map vector
  if (map.size() <= 0)
  {
    // WorldManager::map wasn't initialized by readMap()
    return -1;
  }

  // Load the player's map and screen position from the PlayerInfo pointer (retrieved from GameManager's access to CharacterManager)
  int screenX = (int)floor(playerInfo->screenCoord.x);
  int screenY = (int)floor(playerInfo->screenCoord.y);
  int mapX    = (int)floor(playerInfo->mapCoord.x);
  int mapY    = (int)floor(playerInfo->mapCoord.y);

  // Calculate the difference between map and screen tile coordinates
  // Used to get the tile offset multiple
  int offset_x = (screenX - mapX) * 64 + 32;
  int offset_y = (screenY - mapY) * 64 + 32;

  // Draw the tiles relative to the game window
  for (int row = 0; row < mapRows; row++)
  {
    for (int col = 0; col < mapCols; col++)
    {
      if (map[row][col].id >= 0)
      {
        // Create a new instance of the tile Entity
        tiles.push_back(new Entity(map[row][col].id, Vector3D(col * 64.0f + offset_x, row * 64.0f + offset_y, 0), 0, 0.8f));
      }
    }
  }  // End of tile for loop

  // Successfully built the world
  return 0;
}


bool WorldManager::canMoveWorld(Sprite::dir direction, int screenX, int screenY, int mapX, int mapY)
//bool WorldManager::canMoveWorld(Sprite::dir direction, Vector2D playerScreenCoord, Vector2D playerMapCoord)
{
  /*
  // Convert the player's screen coordinates to ints
  int screenX = (int)floor(playerScreenCoord.x);
  int screenY = (int)floor(playerScreenCoord.y);

  // Conver the player's map coordinates to ints
  int mapX = (int)floor(playerMapCoord.x);
  int mapY = (int)floor(playerMapCoord.y);
  */

  // TODO: Check if the immediate movement would make the player step on an immovable tile
  // TODO: Work with InputManager to handle this (perhaps use ints for more return values)

  // Check 1: Check if there are any offscreen tiles in the requested direction
  if (!hasOffscreenTiles(direction, screenX, screenY, mapX, mapY))
  {
    // There aren't any offscreen tiles in the requested direction, so can't move the world
    return false;
  }

  // Check 2: Determine if any of the offscreen tiles contain invalid tile codes (id < 0)
  if (!validOffscreenTiles(direction, screenX, screenY, mapX, mapY))
  {
    // There is at least one invalid offscreen tile in the requested direction, so can't move the world
    return false;
  }

  // All checks passed, so the world can safely be moved in the requested direction
  return true;
}



bool WorldManager::hasOffscreenTiles(Sprite::dir direction, int screenX, int screenY, int mapX, int mapY)
{
  // Compare the player's map coordinates and map row/col count to see if movement would exceed the map's bounds
  if ((direction == Sprite::dir::LEFT) && ((mapX - screenX) < 1))
  {
    return false;
  }
  else if ((direction == Sprite::dir::RIGHT) && ((mapX + (Engine::SCREEN_WIDTH / 64 - screenX)) >= mapCols))
  {
    return false;
  }
  else if ((direction == Sprite::dir::UP) && ((mapY + (Engine::SCREEN_HEIGHT / 64 - screenY)) >= mapRows))
  {
    return false;
  }
  else if ((direction == Sprite::dir::DOWN) && ((mapY - screenY) < 1))
  {
    return false;
  }

  // There exist offscreen tiles in the requested direction
  return true;
}



bool WorldManager::validOffscreenTiles(Sprite::dir direction, int screenX, int screenY, int mapX, int mapY)
{
  // Calculate the max and min index range for the tiles offscreen the map
  int max_X = mapX + (Engine::SCREEN_WIDTH / 64 - screenX);
  int max_Y = mapY + (Engine::SCREEN_HEIGHT / 64 - screenY);
  int min_X = mapX - screenX - 1;
  int min_Y = mapY - screenY - 1;

  // Check that the calculated index for the requested index doesn't exceed the map's bounds
  // If so, set the index to the corresponding edge
  if (min_X < 0)
  {
    min_X = 0;
  }
  if (max_X >= mapCols)
  {
    max_X = mapCols - 1;
  }
  if (min_Y < 0)
  {
    min_Y = 0;
  }
  if (max_Y >= mapRows)
  {
    max_Y = mapRows - 1;
  }

  // Iterate through the appropriate immediate offscreen tiles to see if any of them contain invalid tile codes
  if (direction == Sprite::dir::LEFT && min_X >= 0)
  {
    // Look at min_X (left offscreen tiles)
    for (int i = min_Y + 1; i < max_Y; i++)
    {
      if (map[i][min_X].id < 0)
      {
        return false;
      }
    }
  }
  else if (direction == Sprite::dir::RIGHT)
  {
    // Look at min_Y
    for (int i = min_Y + 1; i < max_Y; i++)
    {
      if (map[i][max_X].id < 0)
      {
        return false;
      }
    }
  }
  else if (direction == Sprite::dir::UP)
  {
    // Look at min_Y
    for (int i = min_X + 1; i < max_X; i++)
    {
      if (map[max_Y][i].id < 0)
      {
        return false;
      }
    }
  }
  else if (direction == Sprite::dir::DOWN)
  {
    // Look at min_Y
    for (int i = min_X + 1; i < max_X; i++)
    {
      if (map[min_Y][i].id < 0)
      {
        return false;
      }
    }
  }

  // There aren't any invalid offscreen tiles in the requested direction
  return true;
}



int WorldManager::nextTile(Sprite::dir direction, int mapX, int mapY)
{
  // Variables for tracking the next tile's coordinates
  int nextX = mapX;
  int nextY = mapY;

  // Determine the coordinates the player would move on
  if (direction == Sprite::dir::DOWN)
  {
    nextY--;
  }
  else if (direction == Sprite::dir::LEFT)
  {
    nextX--;
  }
  else if (direction == Sprite::dir::RIGHT)
  {
    nextX++;
  }
  else if (direction == Sprite::dir::UP)
  {
    nextY++;
  }

  // Check that the coordinates are still within the bounds of the map
  if ((0 <= nextX && nextX < mapCols) && (0 <= nextY && nextY < mapRows))
  {
    // Return the next tile's type
    return map[nextY][nextX].type;
  }
  else
  {
    // Invalid map coordinates
    return -1;
  }
}



void WorldManager::moveWorld(Vector3D v)
{
  // Move the world's tiles
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    // tiles_ptr gives a pointer to the tiles vector
    tiles[i]->getSprite().moveBy(v);
  }

  // TODO: Move world elements found in NPC & object vectors
}



int WorldManager::shouldMovePlayer(Sprite::dir direction, Vector2D playerScreenCoord, Vector2D playerMapCoord)
{
  // Convert the player's screen coordinates to ints
  int screenX = (int)floor(playerScreenCoord.x);
  int screenY = (int)floor(playerScreenCoord.y);

  // Conver the player's map coordinates to ints
  int mapX = (int)floor(playerMapCoord.x);
  int mapY = (int)floor(playerMapCoord.y);


  // Check if the next tile is immovable or not
  int nextTileType = nextTile(direction, mapX, mapY);
  if (nextTileType == IMMOVABLE)
  {
    // Can't let the player step on an IMMOVABLE tile, so return a warning
    return -1;
  }

  // Calculate if the player or the world should move
  if ( canMoveWorld(direction, screenX, screenY, mapX, mapY) )
  {
    // Check if the player is in the correct part of the screen to move the world
    if ( (screenX <= 7 && direction == Sprite::dir::LEFT ) ||
         (screenX >= 8 && direction == Sprite::dir::RIGHT) ||
         (screenY <= 5 && direction == Sprite::dir::DOWN ) ||
         (screenY >= 6 && direction == Sprite::dir::UP)       )
    {
      return 0;
    }
    else
    {
      // We aren't in the correct regions to move the world, so move the player instead
      return 1;
    }
  }
  else
  {
    // Can't move the map (no valid offscreen tiles), so we must move the player
    return 1;
  }
}



void WorldManager::clearWorld()
{
  // Delete tiles
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    delete tiles[i];  // Delete the pointers
  }
  tiles.clear();  // Clear the vector entries

  // Clear the map
  map.clear();
}