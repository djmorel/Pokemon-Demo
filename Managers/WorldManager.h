#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "../Engine/Actors/ImmovableObject.h"
#include <vector>


class WorldManager
{
  public:
    WorldManager();
    ~WorldManager();

    void buildWorld();  // Sets the environment to that of the save file
    void clearWorld();  // Clears the environment

    void Update();
    void Render();

  private:
    std::vector<ImmovableObject*> tiles;

};


#endif