#include "WorldManager.h"
#include "../Engine/Engine.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>


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
        map.push_back(num);
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
        map.push_back(num);
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
    else if (isdigit(ch))  // Have a numerical character to add to charNum
    {
      charNum.push_back(ch);
    }
    else if (ch != '\n')  // Have an invalid character in the map
    {
      // Return an error identifying a corrupted map
      return -2;
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


// Builds game world based on tiles in the map vector
// Returns 0 on success, or -1 if map has no elements
int WorldManager::buildWorld()
{
  // Map blueprints should be already loaded in the map vector
  if (map.size() <= 0)
  {
    // WorldManager::map wasn't initialized by readMap()
    return -1;
  }

  // TODO: Implement tile location detection/math (use relative position of character?)
  // Determine which map tile belongs at the origin
  originTileIndex = 0;  // Assume origin tile is map's first element

  // Option A:
  // --> Draw the entire world from the map (some tiles may be offscreen)
  // --> Would just need to move all tiles as player "moves"
  // --> Longer processing time (depending on map)?
  // Option B:
  // --> Only draw tiles that would be shown on screen
  // --> Requires IM to do math to adjust what sprites are displayed
  // --> More complicated

  // Draw the tiles relative to the game window
  for (unsigned int row = 0; row < Engine::SCREEN_HEIGHT / 64; row++)
  {
    for (unsigned int col = 0; col < Engine::SCREEN_WIDTH / 64; col++)
    {
      // TODO: Adjust if go for the offscreen tile route
      // Get the current map index
      int index = (mapCols * row) + col;

      // Create a new instance of the tile ImmovableObject
      tiles.push_back(new ImmovableObject(map[index], Vector3D(col * 64.0f + 64.0f / 2, row * 64.0f + 64.0f / 2, 0), 0, 0.8f));
    }
  }  // End of tile for loop

  // Successfully built the world
  return 0;
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
}


void WorldManager::Render()
{
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    tiles[i]->Render();
  }
}