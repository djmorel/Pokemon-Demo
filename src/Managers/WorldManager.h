#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "../Engine/Actors/Entity.h"
#include <vector>


class WorldManager
{
  public:
    WorldManager();
    WorldManager(std::string mapPath);
    ~WorldManager();

    int readMap(std::string mapPath);
    int buildWorld();   // Sets the environment to that of the save file
    void clearWorld();  // Clears the environment

    void Update();
    void Render();

  private:
    // Note: Assume the map text files have rows with equal column counts
    std::vector<int> map;  // RAM-like record of the world map (acts as a pseudo 2D vector)
    int mapRows = 0;       // Tracks the map's row count
    int mapCols = 0;       // Tracks the map's column count
    int originTileIndex;   // Indexes into map to find tile belonging at the bottom left-hand corner of game window
    std::vector<Entity*> tiles;

};


#endif