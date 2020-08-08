#include "InputManager.h"


InputManager::InputManager(Character* _character)
{
  character = _character;
}


void InputManager::Update()
{
  // Enable mouse button support
  if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
  {
    // Left click means rotate counter clockwise
    character->getSprite().rotateBy(10);
  }
  if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT))
  {
    // Right click means rotate clockwise once
    character->getSprite().rotateBy(-10);
  }

  // TODO: Decide if an elseif structure is best for trainer movement on grid
  // Enable keyboard support (WASD movement)
  if (Keyboard::keyDown(GLFW_KEY_W) || Keyboard::keyDown(GLFW_KEY_UP))
  {
    // "W" and "UP Arrow" keys set to move up
    character->getSprite().moveUp();  // Move directly
    //character->getRB().addForce(Vector3D(0, 20, 0));  // Apply force
  }
  if (Keyboard::keyDown(GLFW_KEY_A) || Keyboard::keyDown(GLFW_KEY_LEFT))
  {
    // "A" and "Left Arrow" keys set to move left
    character->getSprite().moveLeft();  // Move directly
    //character->getRB().addForce(Vector3D(-20, 0, 0));  // Apply force
  }
  if (Keyboard::keyDown(GLFW_KEY_S) || Keyboard::keyDown(GLFW_KEY_DOWN))
  {
    // "S" and "Down Arrow" keys set to move down
    character->getSprite().moveDown();  // Move directly
    //character->getRB().addForce(Vector3D(0, -20, 0));  // Apply force
  }
  if (Keyboard::keyDown(GLFW_KEY_D) || Keyboard::keyDown(GLFW_KEY_RIGHT))
  {
    // "D" and "Right Arrow" keys set to move right
    character->getSprite().moveRight();  // Move directly
    //character->getRB().addForce(Vector3D(20, 0, 0));  // Apply force
  }
}