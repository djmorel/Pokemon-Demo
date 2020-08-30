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



class GameManager
{
  public:
    GameManager();
    ~GameManager();

    // TODO: Modify based on the StateStack in the Pokemon Lua video
    enum class State
    {
      START,
      GAMEPLAY,
      SAVE,
      GAMEOVER
    };

    int Start();
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
    Sprite mStartSprite;
    Sprite mGameOverSprite;
    State mState;
    void setState(State state);  // Private since GameManager will handle its own state
};


#endif