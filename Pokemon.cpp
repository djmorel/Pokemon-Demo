#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"


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

  Sprite testSprite = Sprite("Assets/Art/Tyranitar.png", 100, 100);

  // Game loop
  while (true)
  {
    engine.Update();
    testSprite.Update();

    engine.BeginRender();
    testSprite.Render();
    engine.EndRender();
  }

  return 0;
}