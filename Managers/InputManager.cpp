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
  if ( !isActive && (Keyboard::key(GLFW_KEY_W) || Keyboard::key(GLFW_KEY_UP)) )
  {
    // "W" and "UP Arrow" keys set to move up
    //character->walkUp();
    isActive = true;
    animationDir = Character::dir::UP;
  }
  if ( !isActive && (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT)) )
  {
    // "A" and "Left Arrow" keys set to move left
    //character->walkLeft();
    isActive = true;
    animationDir = Character::dir::LEFT;
  }
  if ( !isActive && (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN)) )
  {
    // "S" and "Down Arrow" keys set to move down
    //character->walkDown();
    isActive = true;
    animationDir = Character::dir::DOWN;
  }
  if ( !isActive && (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT)) )
  {
    // "D" and "Right Arrow" keys set to move right
    //character->walkRight();
    isActive = true;
    animationDir = Character::dir::RIGHT;
  }


  if (isActive)
  {
    // Determine which animation to process
    switch (animationDir)
    {
      case Character::dir::UP:
      {
        character->walkUp();
        animationCount++;
        break;
      }
      case Character::dir::DOWN:
      {
        character->walkDown();
        animationCount++;
        break;
      }
      case Character::dir::LEFT:
      {
        character->walkLeft();
        animationCount++;
        break;
      }
      case Character::dir::RIGHT:
      {
        character->walkRight();
        animationCount++;
        break;
      }
      default:
      {
        // Reached an error state
        isActive = false;    // Remove the processing flag
        animationCount = 0;  // Reset count
        break;
      }
    }

    // Check if we completed enough movement animations
    if (animationCount >= 4)
    {
      isActive = false;    // Remove the processing flag
      animationCount = 0;  // Reset the count
    }
  }
}