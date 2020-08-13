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
  mStartSprite = Sprite("StartScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1.07f));
  //mStartSprite.setScale(1.07f);
  mGameOverSprite = Sprite("EndScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1));

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
  Sprite npcSprite = Sprite("Tyranitar", Vector3D((float)(Engine::SCREEN_WIDTH / 1.3), (float)(Engine::SCREEN_HEIGHT / 1.3), 0), 0, Vector3D(0.5f));
  //npcSprite.setScale(0.5f);
  Character npc(npcSprite);
  ImmovableObject tree = ImmovableObject("Trees", Vector3D(100, 100, 0), 0, 2.0f);
  // End of optional stuff

  // Add a Loading Icon for state changes
  Sprite loadingIcon = Sprite("Loading", Vector3D((float)(Engine::SCREEN_WIDTH / 2), (float)(Engine::SCREEN_HEIGHT / 5), 0), 0, Vector3D(0.3f));
  //loadingIcon.setScale(0.3f);

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

    // Don't delete these pointers in case ~WorldManager() is called after GAMEOVER switches to START state
    //   delete mTileManager;
    //   delete mPlayer;
    // Rely on LoadGame() to handle the check for us
  }
}


int GameManager::LoadGame()
{
  // TODO: Implement save file system

  // Load the world
  if (mTileManager != nullptr)
  {
    // Free the memory
    delete mTileManager;
  }
  mTileManager = new WorldManager("Assets/WorldMaps/Map_World.txt");

  // TODO: Load the player from the save file

  // Load the player default sprite
  // "Hilda_D_Stand" is assetID 18
  Sprite playerSprite = Sprite(18, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  if (mPlayer != nullptr)
  {
    // Free the memory
    delete mPlayer;
  }
  mPlayer = new Character(playerSprite, Vector3D(1, 0.66f, 1), Vector3D(0, -16.0f, 0));  // Parameters ensure boundingRect matches the tiles

  // Set the mPlayer as the player
  mPlayer->setAsPlayer(true);

  // Give mPlayer a walking animation
  mPlayer->enableWalkAnimation();

  Sprite* spriteAnimation;

  // Load the player DOWN animation sprites
  // Hilda_D sprites have assetID's 18, 19, 20, and 21
  spriteAnimation = new Sprite(18, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::DOWN, spriteAnimation);
  spriteAnimation = new Sprite(19, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::DOWN, spriteAnimation);
  spriteAnimation = new Sprite(20, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::DOWN, spriteAnimation);
  spriteAnimation = new Sprite(21, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::DOWN, spriteAnimation);

  // Load the player UP animation sprites
  // Hilda_U sprites have assetID's 30, 31, 32, and 33
  spriteAnimation = new Sprite(30, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::UP, spriteAnimation);
  spriteAnimation = new Sprite(31, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::UP, spriteAnimation);
  spriteAnimation = new Sprite(32, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::UP, spriteAnimation);
  spriteAnimation = new Sprite(33, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::UP, spriteAnimation);

  // Load the player LEFT animation sprites
  // Hilda_U sprites have assetID's 22, 23, 24, and 25
  spriteAnimation = new Sprite(22, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::LEFT, spriteAnimation);
  spriteAnimation = new Sprite(23, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::LEFT, spriteAnimation);
  spriteAnimation = new Sprite(24, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::LEFT, spriteAnimation);
  spriteAnimation = new Sprite(25, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::LEFT, spriteAnimation);

  // Load the player RIGHT animation sprites
  // Hilda_U sprites have assetID's 26, 27, 28, and 29
  spriteAnimation = new Sprite(26, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::RIGHT, spriteAnimation);
  spriteAnimation = new Sprite(27, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::RIGHT, spriteAnimation);
  spriteAnimation = new Sprite(28, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::RIGHT, spriteAnimation);
  spriteAnimation = new Sprite(29, Vector3D((float)Engine::SCREEN_WIDTH / 2 + 32.0f, (float)Engine::SCREEN_HEIGHT / 2 - 16.0f, 0), 0, Vector3D(2.0f));
  mPlayer->walkAnimation.pushSpriteVector(WalkAnimation::dir::RIGHT, spriteAnimation);

  // Enable player input
  if (mInputManager != nullptr)
  {
    // Free the memory
    delete mInputManager;
  }
  mInputManager = new InputManager(mPlayer);

  // Successfully loaded game
  return 0;
}