#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "Actors/ImmovableObject.h"
#include <vector>


class WorldManager
{
  public:
    WorldManager();
    ~WorldManager();

    unsigned int getSize();

    void Update();
    void Render();

  private:
    std::vector<ImmovableObject*> tiles;

};


#endif