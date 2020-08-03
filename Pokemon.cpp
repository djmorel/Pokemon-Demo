#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/Actors/Character.h"
#include "Engine/IO/InputManager.h"


// Note:
// The game window doesn't respond to closing via X
// --> Need to handle that ourselves (cleanup, deconstructors, etc)
// The game window won't draw to a full screen
// --> It will only draw to a section of the full screen
// --> Need to make the adjustment to our viewport


int main()
{
  std::cout << "The time has come...\nAschente!" << std::endl;

  // Initialize our game engine
  Engine engine;
  engine.Initialize("Pokemon");

  Sprite testSprite = Sprite("Assets/Art/Tyranitar.png", Vector3D(engine.SCREEN_WIDTH/2, engine.SCREEN_HEIGHT/2, 0));
  testSprite.setScale(0.5f);

  Character player(testSprite);
  InputManager im(&player);

  // Game loop
  while (true)
  {
    engine.Update();
    //testSprite.Update()
    player.Update();
    im.Update();

    // Enable mouse movement support
    //testSprite.setPos((float)Mouse::getMouseX(), (float)Mouse::getMouseY());



    engine.BeginRender();
    player.Render();
    engine.EndRender();
  }

  return 0;
}