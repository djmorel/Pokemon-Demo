#include "InputManager.h"


InputManager::InputManager(Character* _player)
{
  player = _player;
  currentDirection = WalkAnimation::dir::DOWN;   // Player starts in the front-facing (DOWN) direction
  previousDirection = currentDirection;
  newDirection = false;
}


void InputManager::Update()
{
  // Enable mouse button support
  if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
  {
    // Left click means rotate counter clockwise
    player->getSprite().rotateBy(10);
  }
  if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT))
  {
    // Right click means rotate clockwise once
    player->getSprite().rotateBy(-10);
  }

  // Enable keyboard support (WASD movement)
  if ( !isActive && (Keyboard::key(GLFW_KEY_W) || Keyboard::key(GLFW_KEY_UP)) )
  {
    // "W" and "UP Arrow" keys set to move up
    isActive = true;
    currentDirection = WalkAnimation::dir::UP;

    // Check if going in a new direction
    if (previousDirection != currentDirection)
    {
      newDirection = true;
    }
    else
    {
      newDirection = false;
    }
    previousDirection = currentDirection;
  }
  if ( !isActive && (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT)) )
  {
    // "A" and "Left Arrow" keys set to move left
    isActive = true;
    currentDirection = WalkAnimation::dir::LEFT;

    // Check if going in a new direction
    if (previousDirection != currentDirection)
    {
      newDirection = true;
    }
    else
    {
      newDirection = false;
    }
    previousDirection = currentDirection;
  }
  if ( !isActive && (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN)) )
  {
    // "S" and "Down Arrow" keys set to move down
    isActive = true;
    currentDirection = WalkAnimation::dir::DOWN;

    // Check if going in a new direction
    if (previousDirection != currentDirection)
    {
      newDirection = true;
    }
    else
    {
      newDirection = false;
    }
    previousDirection = currentDirection;
  }
  if ( !isActive && (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT)) )
  {
    // "D" and "Right Arrow" keys set to move right
    isActive = true;
    currentDirection = WalkAnimation::dir::RIGHT;

    // Check if going in a new direction
    if (previousDirection != currentDirection)
    {
      newDirection = true;
    }
    else
    {
      newDirection = false;
    }
    previousDirection = currentDirection;
  }


  if (isActive)
  {
    // Flag for changing sprite
    bool changeSprite = (animationCount == 2) || (animationCount == 6);
    bool movePlayer = true;

    // Determine which animation to process
    switch (currentDirection)
    {
      case WalkAnimation::dir::UP:
      {
        player->walkAnimation.walkUp(movePlayer, changeSprite, newDirection);
        animationCount++;
        break;
      }
      case WalkAnimation::dir::DOWN:
      {
        player->walkAnimation.walkDown(movePlayer, changeSprite, newDirection);
        animationCount++;
        break;
      }
      case WalkAnimation::dir::LEFT:
      {
        player->walkAnimation.walkLeft(movePlayer, changeSprite, newDirection);
        animationCount++;
        break;
      }
      case WalkAnimation::dir::RIGHT:
      {
        player->walkAnimation.walkRight(movePlayer, changeSprite, newDirection);
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

    // Reset newDirection
    newDirection = false;

    // Check if we completed enough movement animations
    if (animationCount >= 8)
    {
      isActive = false;    // Remove the processing flag
      animationCount = 0;  // Reset the count
    }
  }
}