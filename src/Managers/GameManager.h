#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include "../Engine/Engine.h"
#include "../Engine/Actors/Character.h"  // Already contains sprite
#include "InputManager.h"
#include "WorldManager.h"


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
    int LoadGame();

  private:
    Engine* mEngine;
    Character* mPlayer;
    InputManager* mInputManager;
    WorldManager* mWorldManager;
    Sprite mStartSprite;
    Sprite mGameOverSprite;
    State mState;

    void setState(State state);  // Private since GameManager will handle its own state

};


#endif