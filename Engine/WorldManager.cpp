#include "WorldManager.h"
#include "Engine.h"


WorldManager::WorldManager()
{
  // TODO: Load the map blueprints

  // Create the tiles
  for (unsigned int j = 0; j < Engine::SCREEN_HEIGHT / 64; j++)
  {
    for (unsigned int i = 0; i < Engine::SCREEN_WIDTH / 64; i++)
    {
      // Create a new instance of the tile ImmovableObject
      if (j < 9)
      {
        tiles.push_back(new ImmovableObject("LeafBlock", Vector3D(i * 64 + 64 / 2, j * 64 + 64 / 2, 0), 0, 0.8f));
      }
      else
      {
        tiles.push_back(new ImmovableObject("WaterBlock", Vector3D(i * 64 + 64 / 2, j * 64 + 64 / 2, 0), 0, 0.8f));
      }
      // NOTE: Implement a better way to ensure the tiles are 64x64p (they are with the above config,
      //       but it may not be clearly visible)
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


unsigned int WorldManager::getSize()
{
  return tiles.size();
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