#include <iostream>
#include "Engine/Engine.h"


// Note:
// The game window doesn't respond to closing via X
// --> Need to handle that ourselves (cleanup, deconstructors, etc)
// The game window won't draw to a full screen
// --> It will only draw to a section of the full screen
// --> Need to make the adjustment to our viewport


int main()
{
  std::cout << "Hello World!" << std::endl;

  // Initialize our game engine
  Engine engine;
  engine.Initialize("Pokemon");

  // Game loop
  while (true)
  {
    engine.Update();
    engine.Render();
  }

  return 0;
}