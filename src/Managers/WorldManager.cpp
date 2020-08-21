#include "WorldManager.h"
#include "../Engine/Engine.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cmath>


WorldManager::WorldManager()
{
  // Read the map blueprints into the map vector
  // Default map is Map_World.txt
  if (readMap("Assets/World_Maps/Map_World.txt") < 0)
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


WorldManager::WorldManager(std::string mapPath)
{
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
}


// Reads a map file into the WorldManager's local map
// Returns 0 on success, -1 if unable to open the file, -2 if unable to close the file, or -3 if map file is corrupted/invalid
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
  std::string charNum = "";   // String to hold numerical characters
  std::vector<int> row;       // Vector to hold row entries
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
        int num = std::stoi(charNum);
        row.push_back(num);  // Add the ID to the row
      }
      catch (std::invalid_argument const &e)
      {
        // Unable to convert to an int, so corrupted map
        return -3;
      }
      catch (std::out_of_range const& e)
      {
        // Unable to convert to an int, so corrupted map
        return -3;
      }

      // Reset charNum
      charNum = "";

      // Increment the temporary column count
      colCount++;
    }
    else if (ch == ';')  // Finished reading a number and a row
    {
      // Convert charNum to a string
      try
      {
        int num = std::stoi(charNum);
        row.push_back(num);  // Add the ID to the row
        map.push_back(row);  // Add the completed row to the map
      }
      catch (std::invalid_argument const& e)
      {
        // Unable to convert to an int, so corrupted map
        return -3;
      }
      catch (std::out_of_range const& e)
      {
        // Unable to convert to an int, so corrupted map
        return -3;
      }

      // Reset charNum
      charNum = "";

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
    else if (isdigit(ch) || ch == '-')  // Have a numerical character to add to charNum
    {
      charNum.push_back(ch);
    }
    else if (ch != '\n' && ch != ' ')  // Have an invalid character in the map
    {
      // Return an error identifying a corrupted map
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


/**
  Builds game world based on tiles in the map vector.
  \param None
  \return 0 on success, or -1 if map has no elements
**/
int WorldManager::buildWorld()
{
  // Map blueprints should be already loaded in the map vector
  if (map.size() <= 0)
  {
    // WorldManager::map wasn't initialized by readMap()
    return -1;
  }

  // TODO: Load from save file
  // Load the player's map and screen position from the save file
  int screenX = 8;
  int screenY = 5;
  int mapX = 12;
  int mapY = 7;

  // Calculate the difference between map and screen tile coordinates
  //   Used to get the tile offset multiple
  //   +1 to ensure complete overlap doesn't remove the base tile offset of 32 pixels (accounts for central anchor point)
  int diff_x = screenX - mapX;
  int diff_y = screenY - mapY;

  // Draw the tiles relative to the game window
  for (int row = 0; row < mapRows; row++)
  {
    for (int col = 0; col < mapCols; col++)
    {
      if (map[row][col] != -1)
      {
        // Create a new instance of the tile Entity
        tiles.push_back(new Entity(map[row][col], Vector3D(col * 64.0f + diff_x * 64.0f + 64.0f / 2, row * 64.0f + diff_y * 64.0f  + 64.0f / 2, 0), 0, 0.8f));
      }
    }
  }  // End of tile for loop

  // Successfully built the world
  return 0;
}


bool WorldManager::canMoveWorld(Vector2D playerScreenCoord, Vector2D playerMapCoord, WalkAnimation::dir direction)
{
  // Convert the player's screen coordinates to ints
  int screenX = floor(playerScreenCoord.x);
  int screenY = floor(playerScreenCoord.y);

  // Conver the player's map coordinates to ints
  int mapX = floor(playerMapCoord.x);
  int mapY = floor(playerMapCoord.y);

  // Compare the player's screen and map coordinates to see if movement would exceed the map's bounds
  if ( (direction == WalkAnimation::dir::LEFT) && ((mapX - screenX) < 1) )
  {
    return false;
  }
  else if ( (direction == WalkAnimation::dir::RIGHT) && ((mapX - screenX) >= (mapCols - Engine::SCREEN_WIDTH / 64)) )
  {
    return false;
  }
  else if ( (direction == WalkAnimation::dir::UP) && ((mapY - screenY) >= (mapRows - Engine::SCREEN_HEIGHT / 64)) )
  {
    return false;
  }
  else if ((direction == WalkAnimation::dir::DOWN) && ((mapY - screenY) < 1) )
  {
    return false;
  }
  // There exist offscreen tiles, so we may be able to move the world

  // TODO: Check if any of the offscreen tiles are invalid
  // Need to find the difference between the screen and map +-1 and index into the map to find invalid tile codes (id < 0)


  // All checks passed, so the world can safely be moved
  return true;
}


// Moves world tiles and entities
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


void WorldManager::clearWorld()
{
  // Delete tiles
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    delete tiles[i];  // Delete the pointers
  }
  tiles.clear();  // Clear the vector entries
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