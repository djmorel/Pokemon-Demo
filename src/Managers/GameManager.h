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


    // TODO
    // Reads a MapInfo file, and tells WorldManager and CharacterManager to build the world and NPCs respectively
    int loadMapInfo(std::string mapInfoPath);

    // TODO
    // Takes the updated PlayerInfo object, and saves its contents into the savefile
    int saveGame();


    /**
      Retrieves CharacterManager's player information.
      \param None
      \return The player's PlayerInfo pointer.
    **/
    PlayerInfo* getPlayerInfo();


  private:
    std::string savefilePath;                // Location of the game's savefile
    PlayerInfo playerInfo;                   // Structure containing player information
    Engine* mEngine;
    CharacterManager* mCharacterManager;
    InputManager* mInputManager;
    WorldManager* mWorldManager;
    Sprite mStartSprite;
    Sprite mGameOverSprite;
    State mState;
    void setState(State state);  // Private since GameManager will handle its own state
};


#endif