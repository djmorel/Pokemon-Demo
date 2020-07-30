#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/IO/Mouse.h"


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

    testSprite.setPos((float)Mouse::getMouseX(), (float)Mouse::getMouseY());
    //testSprite.setScale(0.25f);

    if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
      // Left click means rotate counter clockwise
      testSprite.setRotBy(10);
    }
    if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
      // Right click means rotate clockwise once
      testSprite.setRotBy(-10);
    }
    /*
    // More mouse movements
    if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_RIGHT))
    {
      // Right click release rotates clockwise once
      testSprite.setRotBy(-10);
    }
    if (Mouse::button(GLFW_MOUSE_BUTTON_MIDDLE))
    {
      // Sprite continuously rotates clockwise as long as the middle button is pressed
      testSprite.setRotBy(10);
    }
    */

    engine.BeginRender();
    testSprite.Render();
    engine.EndRender();
  }

  return 0;
}