#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/IO/Mouse.h"
#include "Engine/IO/Keyboard.h"
#include "Engine/Actors/Character.h"


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
  //testSprite.setScale(0.25f);

  Character player(testSprite);

  // Game loop
  while (true)
  {
    engine.Update();
    //testSprite.Update()
    player.Update();

    // Enable mouse movement support
    //testSprite.setPos((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

    // Enable mouse button support
    if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
      // Left click means rotate counter clockwise
      player.getSprite().rotateBy(10);
    }
    if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
      // Right click means rotate clockwise once
      player.getSprite().rotateBy(-10);
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
      //player.getSprite().moveUp();  // Move directly
      player.getRB().addForce(Vector3D(0, 20, 0));  // Apply force
    }
    if (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT))
    {
      // "A" and "Left Arrow" keys set to move left
      //player.getSprite().moveLeft();  // Move directly
      player.getRB().addForce(Vector3D(-20, 0, 0));  // Apply force
    }
    if (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN))
    {
      // "S" and "Down Arrow" keys set to move down
      //player.getSprite().moveDown();  // Move directly
      player.getRB().addForce(Vector3D(0, -20, 0));  // Apply force
    }
    if (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT))
    {
      // "D" and "Right Arrow" keys set to move right
      //player.getSprite().moveRight();  // Move directly
      player.getRB().addForce(Vector3D(20, 0, 0));  // Apply force
    }

    engine.BeginRender();
    player.Render();
    engine.EndRender();
  }

  return 0;
}