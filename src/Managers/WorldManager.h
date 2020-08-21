#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "../Engine/Actors/Entity.h"
#include "../Engine/Animations/WalkAnimation.h"
#include <vector>


class WorldManager
{
  public:
    WorldManager();
    WorldManager(std::string mapPath);
    ~WorldManager();

    int readMap(std::string mapPath);
    int buildWorld();                            // Sets the environment to that of the save file

    // Checks if there is enough offscreen tiles to move the world (info for InputManager)
    bool canMoveWorld(Vector2D playerScreenCoord, Vector2D playerMapCoord, WalkAnimation::dir direction);

    void moveWorld(Vector3D v);                  // Moves the environment (InputManager determines if it needs to move player or world)
    void clearWorld();                           // Clears the environment

    void Update();
    void Render();

  private:
    // Note: Assume the map text files have rows with equal column counts
    std::vector< std::vector<int> > map;  // RAM-like record of the world map
    int mapRows = 0;                      // Tracks the map's row count
    int mapCols = 0;                      // Tracks the map's column count
    std::vector<Entity*> tiles;

};


#endif