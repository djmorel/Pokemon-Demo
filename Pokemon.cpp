#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/IO/Mouse.h"
#include "Engine/IO/Keyboard.h"


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

  Sprite testSprite = Sprite("Assets/Art/Tyranitar.png", Vector3D(100, 100, 0));

  // Game loop
  while (true)
  {
    engine.Update();
    testSprite.Update();

    // Enable mouse movement support
    //testSprite.setPos((float)Mouse::getMouseX(), (float)Mouse::getMouseY());
    //testSprite.setScale(0.25f);

    // Enable mouse button support
    if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
      // Left click means rotate counter clockwise
      testSprite.rotateBy(10);
    }
    if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
      // Right click means rotate clockwise once
      testSprite.rotateBy(-10);
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

    // Enable keyboard support (WASD movement)
    if (Keyboard::key(GLFW_KEY_W) || Keyboard::key(GLFW_KEY_UP))
    {
      // "W" and "UP Arrow" keys set to move up
      testSprite.moveUp();
    }
    if (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT))
    {
      // "A" and "Left Arrow" keys set to move left
      testSprite.moveLeft();
    }
    if (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN))
    {
      // "S" and "Down Arrow" keys set to move down
      testSprite.moveDown();
    }
    if (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT))
    {
      // "D" and "Right Arrow" keys set to move right
      testSprite.moveRight();
    }

    engine.BeginRender();
    testSprite.Render();
    engine.EndRender();
  }

  return 0;
}