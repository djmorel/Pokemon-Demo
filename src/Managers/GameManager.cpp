#include "GameManager.h"
#include <iostream>
#include <fstream>



GameManager::GameManager()
{
  // Set the savefile path to the default location
  savefilePath = "src/Save/Savefile.txt";

  // Initialize the game engine
  mEngine = new Engine();
  mEngine->Initialize("Pokemon");

  // Initialize the start and end screens
  mStartSprite = Sprite("StartScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1.07f));
  mGameOverSprite = Sprite("EndScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1));

  // Initialize the character manager
  mCharacterManager = new CharacterManager(getPlayerInfo());

  // Set the world pointer to null for now (haven't loaded save file yet)
  mWorldManager = nullptr;

  // Set the state to START
  mState = State::START;

  // Set player spawning based on the savefile coordinates
  newMap_StartSpawn = false;
  newMap_EndSpawn = false;
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
// Returns 0 on success, -1 on loadGame() error, or -2 on undefined state error
int GameManager::Start()
{
  // Add a Loading Icon for state changes
  Sprite loadingIcon = Sprite("Loading", Vector3D((float)(Engine::SCREEN_WIDTH / 2), (float)(Engine::SCREEN_HEIGHT / 5), 0), 0, Vector3D(0.3f));

  // Add a Save Game Icon for saving the game
  Sprite saveGameIcon = Sprite(79, Vector3D((float)Engine::SCREEN_WIDTH / 1.1f, (float)Engine::SCREEN_HEIGHT / 9, 0), 0, Vector3D(0.75f));

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
          if (loadGame() < 0)
          {
            std::cout << "ERROR: Unable to load the game" << std::endl;
            return -1;
          }
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
        mInputManager->Update();

        mEngine->BeginRender();
        mWorldManager->RenderTiles();
        mCharacterManager->Render();
        mWorldManager->RenderLayeredItems();
        mEngine->EndRender();

        // K key results in a game over
        if (Keyboard::keyDown(GLFW_KEY_K))
        {
          setState(State::GAMEOVER);
          std::cout << "Thanks for playing!" << std::endl;
        }

        // P key saves the game
        if (Keyboard::keyDown(GLFW_KEY_P))
        {
          setState(State::SAVE);
        }

        break;
      }
      case State::SAVE:
      {
        mWorldManager->Update();
        mCharacterManager->Update();
        mInputManager->Update();

        mEngine->BeginRender();
        mWorldManager->RenderTiles();
        mCharacterManager->Render();
        mWorldManager->RenderLayeredItems();
        saveGameIcon.Render();
        mEngine->EndRender();

        if (saveGame() == 0)
        {
          // Game successfully saved, so exit the SAVE state
          setState(State::GAMEPLAY);
        }

        break;
      }
      case State::GAMEOVER:
      {
        mEngine->BeginRender();
        mWorldManager->RenderTiles();
        mCharacterManager->Render();
        mWorldManager->RenderLayeredItems();
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


int GameManager::loadGame()
{
  // TODO: Implement save file system
  std::cout << "Preparing to load game..." << std::endl;

  // Load the player from the savefile
  int success = loadPlayer();
  if (success == -1)
  {
    std::cout << "ERROR: Unable to open savefile" << std::endl;
    return -1;
  }
  else if (success == -2)
  {
    std::cout << "ERROR: line2coord() failure" << std::endl;
    return -2;
  }
  else if (success == -3)
  {
    std::cout << "ERROR: Corrupt savefile" << std::endl;
    return -3;
  }
  else if (success == -4)
  {
    std::cout << "ERROR: loadCharacter() failure" << std::endl;
    return -4;
  }
  else if (success == 0)
  {
    std::cout << "Successfully loaded game!" << std::endl;
    std::cout << "Player Name        : " << playerInfo.name << std::endl;
    std::cout << "Player Gender      : " << playerInfo.gender << std::endl;
    std::cout << "Character Info Path: " << playerInfo.charInfoPath << std::endl;
    std::cout << "MapInfo Path       : " << playerInfo.mapInfoPath << std::endl;
    std::cout << "Screen Coordinates : " << playerInfo.screenCoord.x << ", " << playerInfo.screenCoord.y << std::endl;
    std::cout << "Map Coordinates    : " << playerInfo.mapCoord.x << ", " << playerInfo.mapCoord.y << std::endl;
  }
  else
  {
    std::cout << "ERROR: Don't know what happened... Reached an invalid loadPlayer() return value..." << std::endl;
    return -5;
  }

  // Load the MapInfo file to get the mapPath and create NPCs
  if (loadMapInfo(playerInfo.mapInfoPath) < 0)
  {
    std::cout << "ERROR: Unable to load MapInfo file..." << std::endl;
    return -6;
  }

  // Load the world
  delete mWorldManager;  // Call delete if a previous world existed
  mWorldManager = new WorldManager(getPlayerInfo(), mapPath);

  // Enable player input
  delete mInputManager;  // Call delete if a previous InputManager was already configured
  mInputManager = new InputManager(getPlayerInfo(), mCharacterManager, mWorldManager);

  // Successfully loaded game
  return 0;
}



int GameManager::createPlayer()
{
  // Open the passed map file
  std::ifstream fd;
  fd.open(savefilePath);

  // Check if the file already exists
  if (fd.is_open())
  {
    char response = '\0';

    // Unable to open the file
    std::cout << "CAUTION: Savefile already exists. Starting a new game will overwrite the existing savefile." << std::endl;

    while (response != 'Y' && response != 'y' && response != 'N' && response != 'n')
    {
      std::cout << "Continue (Y/N)? ";
      std::cin >> response;
    }

    // Handle the user response
    if (response == 'N' || response == 'n')
    {
      // Close the file
      fd.close();

      // Cancel player creation
      return -1;
    }

    // Close the file
    fd.close();

    // Delete the file
    if (remove(savefilePath.c_str()) != 0)
    {
      // Unable to delete the exisiting savefile
      return -2;
    }
  }  // File doesn't exist or has successfully been deleted

  // Create a new savefile

  // TODO: Request and add the player's name

  // TODO: Request and add the player's gender (Will most likely turn out to be select your character)

  // TODO: Note the player character's CharacterInfo path

  // TODO: Configure the player's screen coordinates based on game start

  // TODO: Configure the player's map coordinates based on game start

  // Successfully created a player savefile
  return 0;
}



int GameManager::loadPlayer()
{
  // Variables
  std::ifstream fd;  // File descriptor/handler
  std::string line;  // Line read from the savefile
  int lineNum = 0;   // Tracks the current line number

  // Open the save file
  fd.open(savefilePath);

  // Ensure the file is open
  if (!fd.is_open())
  {
    // Unable to open savefile, so return an error
    return -1;
  }

  // File is open, so let's read it line-by-line
  while (getline(fd, line))
  {
    if (lineNum == 0)
    {
      // Load the player name
      playerInfo.name = line;
    }
    else if (lineNum == 1)
    {
      // Load the player gender
      playerInfo.gender = (line == "M");
    }
    else if (lineNum == 2)
    {
      // Load the player characterInfo path
      playerInfo.charInfoPath = line;
    }
    else if (lineNum == 3)
    {
      playerInfo.mapInfoPath = line;
    }
    else if (lineNum == 4)
    {
      // Load the player screen coordinates
      playerInfo.screenCoord = InfoFiles::line2coord(line);

      // Check that line2coord didn't fail
      if (playerInfo.screenCoord.x == -1 || playerInfo.screenCoord.y == -1)
      {
        // A coordinate is -1, so the stoi conversion failed
        return -2;
      }
    }
    else if (lineNum == 5)
    {
      // Load the player map coordinates
      playerInfo.mapCoord = InfoFiles::line2coord(line);

      // Check that line2coord didn't fail
      if (playerInfo.mapCoord.x == -1 || playerInfo.mapCoord.y == -1)
      {
        // A coordinate is -1, so the stoi conversion failed
        return -2;
      }
    }

    // Record that a line was just read
    lineNum++;
  }

  // Check that all of the lines were properly read
  if (lineNum < 5)
  {
    return -3;
  }

  // Call loadCharacter to load the player sprite and animations
  // Need (3 * 32.0f) / 2 since haven't configured the rigid body yet (Hilda sprite is 64x96 when scaled to 2.0f)
  Vector3D _pos = Vector3D(playerInfo.screenCoord.x * 64.0f + 64.0f / 2, playerInfo.screenCoord.y * 64.0f + (3 * 32.0f) / 2, 0);
  if (mCharacterManager->loadCharacter(playerInfo.charInfoPath, true, _pos, 0, Vector3D(2.0f)) < 0)
  {
    return -4;
  }

  // Successfully loaded player information
  return 0;
}



int GameManager::loadMapInfo(std::string mapInfoPath)
{
  // Variables
  std::ifstream fd;       // File descriptor
  std::string line = "";  // Tracks the contents of the file's line
  int lineNum = 0;        // Tracks the number of lines read

  // Open the MapInfo file
  fd.open(mapInfoPath);

  // Error check the file descriptor
  if (!fd.is_open())
  {
    // Unable to open the file
    std::cout << "Failed to open file: " << mapInfoPath << std::endl;
    return -1;
  }

  // File is open, so let's read line-by-line
  while (getline(fd, line))
  {
    if (lineNum == 0)
    {
      // Record the path to the WorldMap
      mapPath = line;
    }
    else if (lineNum == 1 && newMap_StartSpawn)
    {
      // Record the map's start spawn screen coordinates for the player
      playerInfo.screenCoord.x = (float)InfoFiles::intPull(line, ',');
      playerInfo.screenCoord.y = (float)InfoFiles::intPull(line, ',');

      // Record the map's start spawn map coordinates for the player
      playerInfo.mapCoord.x = (float)InfoFiles::intPull(line, ',');
      playerInfo.mapCoord.y = (float)InfoFiles::intPull(line, ',');

      // Check that the intPull calls were successful
      if (playerInfo.screenCoord.x < 0 || playerInfo.screenCoord.y < 0 || playerInfo.mapCoord.x < 0 || playerInfo.mapCoord.y < 0)
      {
        // intPull failed, so the MapInfo file must be corrupted/invalid
        fd.close();
        return -2;
      }

      // Move the player Character to the start spawn
      Vector3D _pos = Vector3D(playerInfo.screenCoord.x * 64.0f + 64.0f / 2, playerInfo.screenCoord.y * 64.0f + (3 * 32.0f) / 2, 0);
      mCharacterManager->getPlayer()->getSprite().moveTo(_pos);
    }
    else if (lineNum == 2 && newMap_EndSpawn)
    {
      // Record the map's end spawn screen coordinates for the player
      playerInfo.screenCoord.x = (float)InfoFiles::intPull(line, ',');
      playerInfo.screenCoord.y = (float)InfoFiles::intPull(line, ',');

      // Record the map's end spawn map coordinates for the player
      playerInfo.mapCoord.x = (float)InfoFiles::intPull(line, ',');
      playerInfo.mapCoord.y = (float)InfoFiles::intPull(line, ',');

      // Check that the intPull calls were successful
      if (playerInfo.screenCoord.x < 0 || playerInfo.screenCoord.y < 0 || playerInfo.mapCoord.x < 0 || playerInfo.mapCoord.y < 0)
      {
        // intPull failed, so the MapInfo file must be corrupted/invalid
        fd.close();
        return -2;
      }

      // Move the player Character to the end spawn
      Vector3D _pos = Vector3D(playerInfo.screenCoord.x * 64.0f + 64.0f / 2, playerInfo.screenCoord.y * 64.0f + (3 * 32.0f) / 2, 0);
      mCharacterManager->getPlayer()->getSprite().moveTo(_pos);
    }
    else if (lineNum >= 3)
    {
      // Pull the CharacterInfo path
      std::string characterInfoPath = InfoFiles::strPull(line, ':');

      // Pull the NPC's default facing direction
      int direction = InfoFiles::intPull(line, ':');

      // Pull the NPC's map coordinates
      int col = InfoFiles::intPull(line, ',');
      int row = InfoFiles::intPull(line, ',');

      // Check that the line pulls were successful
      if (characterInfoPath == "" || col < 0 || row < 0)
      {
        fd.close();
        return -3;
      }

      // Calculate the difference between the player's map and screen tile coordinates
      int offset_x = (int)floor((playerInfo.screenCoord.x - playerInfo.mapCoord.x) * 64 + 32);
      int offset_y = (int)floor((playerInfo.screenCoord.y - playerInfo.mapCoord.y) * 64 + (3 * 32) / 2);

      // Calculate the NPC position based on the NPC's map coordinates and the offset
      Vector3D npcPos = Vector3D(col * 64.0f + offset_x, row * 64.0f + offset_y, 0);

      if (mCharacterManager->loadCharacter(characterInfoPath, false, npcPos, 0, Vector3D(2.0f)) < 0)
      {
        // loadCharacter() call failed
        fd.close();
        return -3;
      }

      // Record the NPC's map coordinates
      mCharacterManager->getCharacterInfo(mCharacterManager->getCharactersSize() - 1)->mapCoord = Vector2D(col, row);

      // Set the NPC's default facing direction
      Sprite::dir dir;
      if (direction == 1)
      {
        dir = Sprite::dir::LEFT;
      }
      else if (direction == 2)
      {
        dir = Sprite::dir::RIGHT;
      }
      else if (direction == 3)
      {
        dir = Sprite::dir::UP;
      }
      else
      {
        // Default to DOWN
        dir = Sprite::dir::DOWN;
      }
      mCharacterManager->getCharacterInfo(mCharacterManager->getCharactersSize() - 1)->character.getSprite().setFacing(dir);

      std::cout << "Success! We added an NPC to the world with map coordinates: " << col << ", " << row << std::endl;
    }

    // Record that a line was just read
    lineNum++;
  }

  // Close the MapInfo file
  fd.close();

  // Check that the MapInfo file was actually read
  if (lineNum < 3)
  {
    return -4;
  }

  // Successfully read the MapInfo file
  return 0;
}



int GameManager::saveGame()
{
  // DEBUG
  std::cout << "Preparing to save game..." << std::endl;

  // Block the InputManager from handling new input
  mInputManager->blockNewInput();

  // Wait for the InputManager to finish processing its last input (if necessary)
  if (mInputManager->getIsActive())
  {
    // DEBUG
    std::cout << "We need to wait for the input to finish processing..." << std::endl;

    // Wait for the InputManager to finish processing its last input
    // The game will save the game at a later time in the game loop
    return -1;
  }
  else
  {
    // Open the savefile and prepare to write over it
    std::ofstream fd(savefilePath);

    if (!fd.is_open())
    {
      // Unable to open the savefile, so return an error
      return -2;
    }

    // Write the player's name to the savefile
    fd << playerInfo.name << std::endl;

    // Write the player's gender to the savefile
    if (playerInfo.gender)
    {
      fd << "M" << std::endl;
    }
    else
    {
      fd << "F" << std::endl;
    }

    // Write the player's CharacterInfo file path to the savefile
    fd << playerInfo.charInfoPath << std::endl;

    // Write the current map's MapInfo file path to the savefile
    fd << playerInfo.mapInfoPath << std::endl;

    // Write the player's current screen coordinates to the savefile
    fd << (int)floor(playerInfo.screenCoord.x) << "," << (int)floor(playerInfo.screenCoord.y) << std::endl;

    // Write the player's current map coordinates to the savefile
    fd << (int)floor(playerInfo.mapCoord.x) << "," << (int)floor(playerInfo.mapCoord.y) << std::endl;

    // Close the file
    fd.close();

    // Add a delay of 2 seconds
    while (((float)glfwGetTime() - Engine::getLastTime()) < 2)
    {
      // Stall in the while loop until the timer reaches the target duration of 2 seconds
      // This stalling method ensures that the player sees the save icon
      // Note: glfwGetTime records time in seconds since the GLFW window was created
    }

    // Enable input again
    mInputManager->enableNewInput();

    // DEBUG
    std::cout << "Game saved!" << std::endl;

    // Successfully saved game
    return 0;
  }
}



PlayerInfo* GameManager::getPlayerInfo()
{
  return &playerInfo;
}