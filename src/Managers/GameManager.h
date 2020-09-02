#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include "../Engine/Engine.h"
#include "../Engine/Actors/Character.h"  // Already contains sprite
#include "InputManager.h"
#include "CharacterManager.h"
#include "WorldManager.h"
#include "../InfoFiles/InfoFiles.h"
#include "../Engine/Text/Text2D.h"
#include <string>


// Handles the game's states, and calls upon the other Managers for their respective handling.
class GameManager
{
  public:
    /**
      A constructor that initializes a GameManager by configuring the game engine, managers, and sets the game to the START state.
      \param None
      \return None
    **/
    GameManager();

    /**
      A deconstructor that deletes the dynamically allocated managers.
      \param None
      \return None
    **/
    ~GameManager();

    // TODO: Modify based on the future StateStack design
    enum class State
    {
      START,
      GAMEPLAY,
      SAVE,
      GAMEOVER
    };

    /**
      Starts the game loop to handle game states.
      \param None
      \return 0 on success, -1 on loadGame() error, or -2 on undefined state error.
    **/
    int Start();

    /**
      Loads the game from the savefile by first loading the player and then the MapInfo. Configures the GameManager's CharacterManager, WorldManager, and InputManager appropriately.
      \param None
      \return 0 on success, -1 on loadPlayer() failure, or -2 on loadMapInfo() failure.
    **/
    int loadGame();

    /**
      Creates a new player savefile for the game and rewrites over old savefile if it exists. References CharacterManager's savefilePath.
      \param None
      \return 0 on success, -1 if cancel player creation, or -2 if unable to delete existing file.
    **/
    int createPlayer();

    /**
      Loads player information from the savefile into GameManager's playerInfo struct.
      \param None
      \return 0 on success, -1 if unable to open savefile, -2 if line2coord() failure, -3 if corrupt savefile, or -4 if loadCharacter() failure.
    **/
    int loadPlayer();

    /**
      Loads a MapInfo file, and tells WorldManager and CharacterManager to load the world and NPCs respectively.
      \param std::string mapInfoPath - Path of the MapInfo file to load.
      \return 0 on success, -1 if unable to open the MapInfo file, -2 if detecting player spawn points failed, -3 if loading a NPC failed, or -4 if failed to read the minimum line count.
    **/
    int loadMapInfo(std::string mapInfoPath);

    /**
      Takes the updated PlayerInfo object, and saves its contents into the savefile.
      \param None
      \return 0 on success, -1 if waiting for the InputManager to handle player input, or -2 if unable to open the savefile.
    **/
    int saveGame();

    /**
      Retrieves CharacterManager's player information.
      \param None
      \return The player's PlayerInfo pointer.
    **/
    PlayerInfo* getPlayerInfo();


  private:
    std::string savefilePath;             // Location of the game's savefile
    std::string mapPath;                  // Location of the WorldMap file to build
    bool newMap_StartSpawn;               // Flags if player reached a new map or not (true means player should spawn at the start location)
    bool newMap_EndSpawn;                 // Flags if player reached a new map or not (true means player should spawn at the end location)
    PlayerInfo playerInfo;                // Structure containing player information
    Engine* mEngine;                      // Pointer to the game's Engine
    CharacterManager* mCharacterManager;  // Pointer to the game's CharacterManager
    WorldManager* mWorldManager;          // Pointer to the game's WorldManager
    InputManager* mInputManager;          // Pointer to the game's InputManager
    Sprite mStartSprite;                  // Sprite to display on the screen at the beginning of the game (game menu)
    Sprite mGameOverSprite;               // Sprite to display on the screen for a Game Over
    State mState;                         // Current state the game is in

    /**
      Handles switching between states by providing the setup and clean up. Private since GameManager will handle its own state.
      \param None
      \return None
    **/
    void setState(State state);
};


#endif