#include "InputManager.h"



InputManager::InputManager(PlayerInfo* _playerInfo, CharacterManager* _cm, WorldManager* _world)
{
  playerInfo = _playerInfo;
  cm = _cm;
  world = _world;
  currentDirection = Sprite::dir::DOWN;  // Player starts in the front-facing (DOWN) direction
  previousDirection = currentDirection;
  newDirection = false;

  // Enable new input
  enableInput = true;
  isActive = false;
}



void InputManager::Update()
{
  handleInput();

  // Only process changes when the isActive flag is raised
  if (isActive)
  {
    // Local Variables
    int movePlayer;  // 1 = move the player, 0 = move the world, -1 = next tile is immovable, -2 = next tile has an NPC
    bool changeSprite = newDirection || (animationCount == 2) || (animationCount == 6);  // Flag for changing Sprite frame
    Vector3D displacement;                                                               // How much to move by
    float duration;                                                                      // Duration of the animation in milliseconds

    // Check if the player would hit an NPC
    if (cm->npcCollision(currentDirection))
    {
      movePlayer = -2;
    }
    else
    {
      // Have the WorldManager determine if the player should move
      movePlayer = world->shouldMovePlayer(currentDirection, playerInfo->screenCoord, playerInfo->mapCoord);
    }

    // Set displacement and duration
    if (newDirection)
    {
      // Set the displacement to 0
      displacement = Vector3D(0);
      duration = 80;
    }
    else if (movePlayer < 0)
    {
      // Next movement would hit an IMMOVABLE tile or an NPC
      displacement = Vector3D(0);
      duration = 50;

      // TODO: Play a bumping sound effect
      std::cout << "Hey, you can't move onto that tile!" << std::endl;
    }
    else if (movePlayer == 1)
    {
      // If the player is to move, make sure the player stays in the bounds of the screen
      if ( ((currentDirection == Sprite::dir::UP   ) && (playerInfo->screenCoord.y >= Engine::SCREEN_HEIGHT / 64.0f - 1)) || 
           ((currentDirection == Sprite::dir::DOWN ) && (playerInfo->screenCoord.y <= 0                                )) ||
           ((currentDirection == Sprite::dir::LEFT ) && (playerInfo->screenCoord.x <= 0                                )) ||
           ((currentDirection == Sprite::dir::RIGHT) && (playerInfo->screenCoord.x >= Engine::SCREEN_WIDTH / 64.0f  - 1))    )
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

      // Check if the player should run
      if (run)
      {
        duration = 20;
      }
      else
      {
        duration = 50;
      }
    }
    else
    {
      // Attempted movement doesn't send the player to an unwanted tile, so grant the walk movement
      displacement = Vector3D(8);

      // Check if the player should run
      if (run)
      {
        duration = 20;
      }
      else
      {
        duration = 50;
      }
    }

    // Animate the world!
    processMovement(movePlayer, changeSprite, displacement, duration);

    // Adjust isActive and animationCount if necessary
    if (newDirection)
    {
      // Reset the flags and count
      newDirection = false;
      isActive = false;
      run = false;
      animationCount = 0;
    }
    else
    {
      // Check if we completed enough movement animations
      if (animationCount >= walkCountQuota)
      {
        isActive = false;    // Remove the processing flag
        animationCount = 0;  // Reset the count
        run = false;         // Reset the run flag

        // Update player coordinates
        playerInfo->mapCoord = playerInfo->mapCoord + Vector2D(displacement.x / walkCountQuota, displacement.y / walkCountQuota);
        if (movePlayer)
        {
          // Update the player's screen coordinates if the player moved relative to the screen
          playerInfo->screenCoord = playerInfo->screenCoord + Vector2D(displacement.x / walkCountQuota, displacement.y / walkCountQuota);
        }

        // DEBUG
        std::cout << "Player screen coordinates: " << playerInfo->screenCoord.x << ", " << playerInfo->screenCoord.y << std::endl;
        std::cout << "Player map coordinates   : " << playerInfo->mapCoord.x << ", " << playerInfo->mapCoord.y << std::endl;
      }
    }
  }
}



void InputManager::handleInput()
{
  /*
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
  */

  // Enable running
  if (enableInput && !isActive && (Keyboard::key(GLFW_KEY_SPACE)))
  {
    run = true;
  }

  // Enable keyboard support (WASD movement)
  if (enableInput && !isActive && (Keyboard::key(GLFW_KEY_W) || Keyboard::key(GLFW_KEY_UP)))
  {
    // "W" and "UP Arrow" keys set to move up
    isActive = true;
    updateDirections(Sprite::dir::UP);
  }
  if (enableInput && !isActive && (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT)))
  {
    // "A" and "Left Arrow" keys set to move left
    isActive = true;
    updateDirections(Sprite::dir::LEFT);
  }
  if (enableInput && !isActive && (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN)))
  {
    // "S" and "Down Arrow" keys set to move down
    isActive = true;
    updateDirections(Sprite::dir::DOWN);
  }
  if (enableInput && !isActive && (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT)))
  {
    // "D" and "Right Arrow" keys set to move right
    isActive = true;
    updateDirections(Sprite::dir::RIGHT);
  }
}



void InputManager::updateDirections(Sprite::dir direction)
{
  previousDirection = cm->getPlayer()->getSprite().getFacing();
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
}



int InputManager::processMovement(bool movePlayer, bool changeSprite, Vector3D &displacement, float duration)
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
  if (movePlayer)
  {
    // Move the player relative to the screen
    cm->moveCharacter(0, (changeSprite || newDirection), displacement, currentDirection, duration);
  }
  else
  {
    // Move the world relative to the player (world moves opposite of the character's intended direction)
    // Note: ALWAYS move the world BEFORE calling the character walk to ensure proper duration stalls
    Vector3D worldDisplacement = displacement * Vector3D(-1);
    world->moveWorld(worldDisplacement);
    cm->moveAllNPCs(worldDisplacement);
    cm->moveCharacter(0, (changeSprite || newDirection), Vector3D(0), currentDirection, duration);
  }
  
  // Update the animationCount
  animationCount++;

  // Return success
  return 0;
}



void InputManager::blockNewInput()
{
  enableInput = false;
}



void InputManager::enableNewInput()
{
  enableInput = true;
}



bool InputManager::getIsActive()
{
  return isActive;
}