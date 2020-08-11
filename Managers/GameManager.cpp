#include "GameManager.h"


// TODO
// - Establish npc and objects as a vector (allows for proper updating and rendering)
// - Implement save file system


GameManager::GameManager()
{
  // Initialize the game engine
  mEngine = new Engine();
  mEngine->Initialize("Pokemon");

  // Initialize the start and end screens
  mStartSprite = Sprite("StartScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));
  mStartSprite.setScale(1.07f);
  mGameOverSprite = Sprite("EndScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0));

  // Set the player and world pointers to null for now (haven't loaded save file yet)
  mPlayer = nullptr;
  mTileManager = nullptr;

  // Set the state to START
  mState = State::START;
}


GameManager::~GameManager()
{
  // Delete our dynamically allocated members
  delete mEngine;
  delete mPlayer;
  delete mInputManager;
  delete mTileManager;
}


// Starts game states
// Returns 0 on success, -1 on LoadGame() error, or -2 on undefined state error
int GameManager::Start()
{
  // Optional stuff
  Sprite npcSprite = Sprite("Tyranitar", Vector3D((float)(Engine::SCREEN_WIDTH / 1.3), (float)(Engine::SCREEN_HEIGHT / 1.3), 0));
  npcSprite.setScale(0.5f);
  Character npc(npcSprite);
  ImmovableObject tree = ImmovableObject("Trees", Vector3D(100, 100, 0), 0, 2.0f);
  // End of optional stuff

  // Add a Loading Icon for state changes
  Sprite loadingIcon = Sprite("Loading", Vector3D((float)(Engine::SCREEN_WIDTH / 2), (float)(Engine::SCREEN_HEIGHT / 5), 0));
  loadingIcon.setScale(0.3f);

  // Game loop
  while (true)
  {
    // Exit the game if ESC key is pressed
    if (Keyboard::keyDown(GLFW_KEY_ESCAPE))
    {
      // TODO: Ask player if he/she wants to save game

      break;
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
        if (mTileManager == nullptr || mPlayer == nullptr)
        {
          // Game wasn't properly loaded so terminate the program
          std::cout << "ERROR: World not initialized" << std::endl;
          return -1;
        }

        mTileManager->Update();
        mPlayer->Update();
        npc.Update();
        tree.Update();
        mInputManager->Update();

        mEngine->BeginRender();
        mTileManager->Render();
        mPlayer->Render();
        npc.Render();
        tree.Render();
        mEngine->EndRender();

        bool collision = RigidBody::isColliding(mPlayer->getRB(), npc.getRB());
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
        mTileManager->Render();
        mPlayer->Render();
        npc.Render();
        tree.Render();
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
  // TODO: Clean up

  mState = state;

  if (mState == State::START)
  {
    // Clear the world's contents
    mTileManager->clearWorld();
    delete mTileManager;
    delete mPlayer;
  }
}


void GameManager::LoadGame()
{
  // TODO: Implement save file system


  // Load the player
  Sprite playerSprite = Sprite("Hilda_F_Stand", Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0));
  playerSprite.setScale(2.0f);
  mPlayer = new Character(playerSprite, Vector3D(1, 0.66f, 1), Vector3D(0, -16.0f, 0));  // Parameters ensure boundingRect matches the tiles

  // Enable player input
  mInputManager = new InputManager(mPlayer);

  // Load the world
  mTileManager = new WorldManager();
}