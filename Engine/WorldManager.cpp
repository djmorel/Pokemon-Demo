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
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    tiles[i]->Update();
  }
}


void WorldManager::Render()
{
  for (unsigned int i = 0; i < tiles.size(); i++)
  {
    tiles[i]->Render();
  }
}