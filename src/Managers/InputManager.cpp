#include "InputManager.h"


InputManager::InputManager(CharacterManager* _cm, WorldManager* _world)
{
  cm = _cm;
  world = _world;
  currentDirection = Sprite::dir::DOWN;   // Player starts in the front-facing (DOWN) direction
  previousDirection = currentDirection;
  newDirection = false;

  pScreenCoord = &_cm->getPlayerInfo().screenCoord;
  pMapCoord = &_cm->getPlayerInfo().mapCoord;
}


void InputManager::Update()
{
  handleInput();

  // Only process changes when the isActive flag is raised
  if (isActive)
  {
    // Flag for changing sprite
    bool changeSprite = (animationCount == 2) || (animationCount == 6);
    bool movePlayer = shouldMovePlayer();
    Vector3D displacement;
    int duration;  // Duration of the animation in milliseconds

    // Set displacement and duration
    if (newDirection)
    {
      // Set the displacement to 0
      displacement = Vector3D(0);
      duration = 80;
    }
    else if (movePlayer)
    {
      // If the player is to move, make sure the player stays in the bounds of the screen
      if ( ((currentDirection == Sprite::dir::UP   ) && (pScreenCoord->y >= Engine::SCREEN_HEIGHT / 64.0f - 1)) || 
           ((currentDirection == Sprite::dir::DOWN ) && (pScreenCoord->y <= 0                                )) ||
           ((currentDirection == Sprite::dir::LEFT ) && (pScreenCoord->x <= 0                                )) ||
           ((currentDirection == Sprite::dir::RIGHT) && (pScreenCoord->x >= Engine::SCREEN_WIDTH / 64.0f  - 1)) )
      {
        // Player is at the edge of the screen, so prevent movement!
        displacement = Vector3D(0);

        // TODO: Play a bumping sound effect
        std::cout << "Hey! You're not allowed to jump off the map!" << std::endl;
      }
      else  // Player isn't at the edge of the screen
      {
        displacement = Vector3D(8);
      }
      duration = 40;
    }
    else
    {
      // Attempted movement doesn't send the player off the edge of the map, so grant the walk movement
      displacement = Vector3D(8);
      duration = 40;
    }

    // Animate the world!
    processMovement(movePlayer, changeSprite, displacement, duration);

    // Adjust isActive and animationCount if necessary
    if (newDirection)
    {
      // Reset the flags and count
      newDirection = false;
      isActive = false;
      animationCount = 0;
    }
    else
    {
      // Check if we completed enough movement animations
      if (animationCount >= walkCountQuota)
      {
        isActive = false;    // Remove the processing flag
        animationCount = 0;  // Reset the count

        // Update player coordinates
        cm->updatePlayerMapCoord(Vector2D(displacement.x / walkCountQuota, displacement.y / walkCountQuota));
        if (movePlayer)
        {
          // Update the player's screen coordinates if the player moved relative to the screen
          cm->updatePlayerScreenCoord(Vector2D(displacement.x / walkCountQuota, displacement.y / walkCountQuota));
        }
      }
    }
  }
}


void InputManager::handleInput()
{
  // Enable mouse button support
  if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT))
  {
    // Left click means rotate counter clockwise
    cm->getPlayer()->getSprite().rotateBy(10);
  }
  if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT))
  {
    // Right click means rotate clockwise once
    cm->getPlayer()->getSprite().rotateBy(-10);
  }

  // Enable keyboard support (WASD movement)
  if (!isActive && (Keyboard::key(GLFW_KEY_W) || Keyboard::key(GLFW_KEY_UP)))
  {
    // "W" and "UP Arrow" keys set to move up
    isActive = true;
    updateDirections(Sprite::dir::UP);
  }
  if (!isActive && (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT)))
  {
    // "A" and "Left Arrow" keys set to move left
    isActive = true;
    updateDirections(Sprite::dir::LEFT);
  }
  if (!isActive && (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN)))
  {
    // "S" and "Down Arrow" keys set to move down
    isActive = true;
    updateDirections(Sprite::dir::DOWN);
  }
  if (!isActive && (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT)))
  {
    // "D" and "Right Arrow" keys set to move right
    isActive = true;
    updateDirections(Sprite::dir::RIGHT);
  }
}


void InputManager::updateDirections(Sprite::dir direction)
{
  currentDirection = direction;

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


bool InputManager::shouldMovePlayer()
{
  // Calculate if the player or the world should move
  if (world->canMoveWorld(currentDirection, *pScreenCoord, *pMapCoord))
  {
    // Check if the player is in the correct part of the screen to move the world
    if (pScreenCoord->x <= 7 && currentDirection == Sprite::dir::LEFT)
    {
      return false;
    }
    else if (pScreenCoord->x >= 8 && currentDirection == Sprite::dir::RIGHT)
    {
      return false;
    }
    else if (pScreenCoord->y <= 5 && currentDirection == Sprite::dir::DOWN)
    {
      return false;
    }
    else if (pScreenCoord->y >= 6 && currentDirection == Sprite::dir::UP)
    {
      return false;
    }
    else
    {
      // We aren't in the correct regions to move the world, so move the player instead
      return true;
    }
  }
  else
  {
    // Can't move the map (no valid offscreen tiles), so we must move the player
    return true;
  }
}


int InputManager::processMovement(bool movePlayer, bool changeSprite, Vector3D &displacement, int duration)
{
  // Multiply the displacement by the directional identity Vector3D
  if (currentDirection == Sprite::dir::DOWN)
  {
    displacement = displacement * Vector3D(0, -1, 0);
  }
  else if (currentDirection == Sprite::dir::LEFT)
  {
    displacement = displacement * Vector3D(-1, 0, 0);
  }
  else if (currentDirection == Sprite::dir::RIGHT)
  {
    displacement = displacement * Vector3D(1, 0, 0);
  }
  else if (currentDirection == Sprite::dir::UP)
  {
    displacement = displacement * Vector3D(0, 1, 0);
  }
  else
  {
    // Reached an error state, so return an error and break out of the animation
    isActive = false;    // Remove the processing flag
    animationCount = 0;  // Reset count
    return -1;
  }
  
  // Move the player or the world
  cm->moveCharacter(0, movePlayer, changeSprite, newDirection, displacement, currentDirection, duration);
  if (!movePlayer)
  {
    world->moveWorld(displacement * Vector3D(-1));   // World moves opposite of the character's direction
  }
  
  // Update the animationCount
  animationCount++;

  // Return success
  return 0;
}