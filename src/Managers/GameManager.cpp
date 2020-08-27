#include "GameManager.h"
#include <iostream>
//#include <fstream>
//#include <stdio.h>


// TODO
// - Establish npc and objects as a vector (allows for proper updating and rendering)
// - Implement save file system


GameManager::GameManager()
{
  // Initialize the game engine
  mEngine = new Engine();
  mEngine->Initialize("Pokemon");

  // Initialize the start and end screens
  mStartSprite = Sprite("StartScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1.07f));
  mGameOverSprite = Sprite("EndScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1));

  // Initialize the character manager
  mCharacterManager = new CharacterManager();

  // Set the world pointer to null for now (haven't loaded save file yet)
  mWorldManager = nullptr;

  // Set the state to START
  mState = State::START;
}


GameManager::~GameManager()
{
  // Delete our dynamically allocated members
  // Recall that "delete" calls the object's destructors
  delete mEngine;
  delete mCharacterManager;
  delete mInputManager;
  delete mWorldManager;
}


// Starts game states
// Returns 0 on success, -1 on LoadGame() error, or -2 on undefined state error
int GameManager::Start()
{
  // Optional stuff
  Sprite npcSprite = Sprite("Tyranitar", Vector3D((float)(Engine::SCREEN_WIDTH / 1.3), (float)(Engine::SCREEN_HEIGHT / 1.3), 0), 0, Vector3D(0.5f));
  npcSprite.setDimensions(128.0f);
  Character npc(npcSprite);
  // End of optional stuff

  // Add a Loading Icon for state changes
  Sprite loadingIcon = Sprite("Loading", Vector3D((float)(Engine::SCREEN_WIDTH / 2), (float)(Engine::SCREEN_HEIGHT / 5), 0), 0, Vector3D(0.3f));

  // Game loop
  while (true)
  {
    // Exit the game if ESC key is pressed
    if (Keyboard::keyDown(GLFW_KEY_ESCAPE))
    {
      // TODO: Ask player if he/she wants to save game

      return 0;
    }

    // Always update the Engine, regardless of the state
    mEngine->Update();

    switch (mState)
    {
      case State::START:
      {
        mEngine->BeginRender();
        mStartSprite.Render();
        mEngine->EndRender();

        // Spacebar and Enter key start gameplay
        if (Keyboard::keyDown(GLFW_KEY_SPACE) || Keyboard::keyDown(GLFW_KEY_ENTER))
        {
          setState(State::GAMEPLAY);

          // Display the loading icon
          mStartSprite.Render();
          mStartSprite.Render();
          loadingIcon.Render();
          mEngine->EndRender();

          // Load the save file
          LoadGame();
        }

        break;
      }
      case State::GAMEPLAY:
      {
        // Error checking to ensure LoadGame() was called
        if (mWorldManager == nullptr)
        {
          // Game wasn't properly loaded so terminate the program
          std::cout << "ERROR: World not initialized" << std::endl;
          return -1;
        }

        mWorldManager->Update();
        mCharacterManager->Update();
        npc.Update();
        mInputManager->Update();

        mEngine->BeginRender();
        mWorldManager->RenderTiles();
        mCharacterManager->Render();
        mWorldManager->RenderLayeredItems();
        npc.Render();
        mEngine->EndRender();

        bool collision = RigidBody::isColliding(mCharacterManager->getPlayer()->getRB(), npc.getRB());
        if (collision)
        {
          setState(State::GAMEOVER);
          std::cout << "Oh no! You touched the scary Tyranitar!\nGame Over :(" << std::endl;
        }

        break;
      }
      case State::GAMEOVER:
      {
        mEngine->BeginRender();
        mWorldManager->RenderTiles();
        mCharacterManager->Render();
        mWorldManager->RenderLayeredItems();
        npc.Render();
        mGameOverSprite.Render();
        mEngine->EndRender();

        // Spacebar and Enter key return game state to START
        if (Keyboard::keyDown(GLFW_KEY_SPACE) || Keyboard::keyDown(GLFW_KEY_ENTER))
        {
          setState(State::START);
        }

        break;
      }
      default:
      {
        std::cout << "ERROR: Unhandled game state " << static_cast<int>(mState) << std::endl;
        return -2;
      }
    }
  }

  // Finished game with no errors
  return 0;
}


// Provides set up and clean up between states
void GameManager::setState(State state)
{
  mState = state;

  // State clean up
  if (mState == State::START)
  {
    // Clear all of the world's characters
    mCharacterManager->clearCharacters(false);  // Delete the player as well

    // Don't call delete on these pointers in case ~WorldManager() is called after GAMEOVER switches to START state
    //   delete mWorldManager;
    //   delete mCharacterManager;
    // Doing so causes their deconstructors twice, which poses problems
    // Rely on LoadGame() to handle the check for us
  }
}


int GameManager::LoadGame()
{
  // TODO: Implement save file system
  std::cout << "Preparing to load game..." << std::endl;

  // Load the player from the savefile
  int success = mCharacterManager->loadPlayer();
  if (success == -1)
  {
    std::cout << "ERROR: Unable to open savefile" << std::endl;
  }
  else if (success == -2)
  {
    std::cout << "ERROR: line2coord() failure" << std::endl;
  }
  else if (success == -3)
  {
    std::cout << "ERROR: Corrupt savefile" << std::endl;
  }
  else if (success == -4)
  {
    std::cout << "ERROR: loadCharacter() failure" << std::endl;
  }
  else if (success == 0)
  {
    std::cout << "Successfully loaded game!" << std::endl;
    std::cout << "Player Name        : " << mCharacterManager->getPlayerInfo()->name << std::endl;
    std::cout << "Player Gender      : " << mCharacterManager->getPlayerInfo()->gender << std::endl;
    std::cout << "Character Info Path: " << mCharacterManager->getPlayerInfo()->charInfoPath << std::endl;
    std::cout << "Map Path           : " << mCharacterManager->getPlayerInfo()->mapPath << std::endl;
    std::cout << "Screen Coordinates : " << mCharacterManager->getPlayerInfo()->screenCoord.x << ", " << mCharacterManager->getPlayerInfo()->screenCoord.y << std::endl;
    std::cout << "Map Coordinates    : " << mCharacterManager->getPlayerInfo()->mapCoord.x << ", " << mCharacterManager->getPlayerInfo()->mapCoord.y << std::endl;
  }
  else
  {
    std::cout << "ERROR: Don't know what happened... Reached an invalid loadPlayer() return value..." << std::endl;
  }

  // Load the world
  delete mWorldManager;  // Call delete if a previous world existed
  mWorldManager = new WorldManager(mCharacterManager->getPlayerInfo());

  // Enable player input
  delete mInputManager;  // Call delete if a previous InputManager was already configured
  mInputManager = new InputManager(mCharacterManager, mWorldManager);

  // Successfully loaded game
  return 0;
}
