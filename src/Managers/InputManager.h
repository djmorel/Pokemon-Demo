#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include "../Engine/Engine.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"
#include "CharacterManager.h"
#include "WorldManager.h"


class InputManager
{
  public:
    /**
      A constructor that configures the InputManager.
      \param PlayerInfo* _playerInfo - Pointer to the GameManager's playerInfo object.
      \param CharacterManager* _cm - Pointer to the CharacterManager.
      \param WorldManager* _world - Pointer to the WorldManager.
      \return None
    **/
    InputManager(PlayerInfo* _playerInfo, CharacterManager* _cm, WorldManager* _world);

    /**
      Records player input, and handles responses.
      \param None
      \return None
    **/
    void Update();

    /**
      Checks if a predefined input was entered, and sets the isActive flag and direction accordingly.
      \param None
      \return None
    **/
    void handleInput();

    /**
      Updates the direction flags and variables based on the currently received direction.
      \param Sprite::dir direction - Requested direction to handle from player input.
      \return None
    **/
    void updateDirections(Sprite::dir direction);

    /**
      Processes player/world movement and Sprite animations.
      \param bool movePlayer - True if the player should move, or False if the world should instead.
      \param bool changeSprite - True if the player's Sprite frame should change, or False if not.
      \param Vector3D &displacement - Number of pixels to move the player/world by. Note: Pass by reference so the function can change it.
      \param float duration - How long should the movement take (milliseconds).
      \return 0 if success, or -1 if the currentDirection isn't one of the 4 valid directions.
    **/
    int processMovement(bool movePlayer, bool changeSprite, Vector3D &displacement, float duration);

    // Waits for the current input to finish
    /**
      Blocks new input from being received by setting InputManager::enableInput to false.
      \param None
      \return None
    **/
    void blockNewInput();

    /**
      Enables new input from being received by setting InputManager::enableInput to true.
      \param None
      \return None
    **/
    void enableNewInput();

    /**
      Gets the current value of the isActive flag.
      \param None
      \return bool value representing the current isActive state.
    **/
    bool getIsActive();


  private:
    PlayerInfo* playerInfo;         // Pointer to the GameManager's PlayerInfo object (tracks player coordinates on the map and screen)
    CharacterManager* cm;           // Pointer to the CharacterManager
    WorldManager* world;            // Pointer to the world
    int animationCount = 0;         // Counter for how many times an animation has to be called
    int walkCountQuota = 8;         // Amount of times the walk animation has to be called
    bool enableInput = true;        // Enables new input to be received
    bool isActive = false;          // Blocks incoming input from processing
    bool run = false;               // Makes the player "run" by halving the animation duration
    Sprite::dir currentDirection;   // Specifies the current animation direction
    Sprite::dir previousDirection;  // Specifies the previous animation direction
    bool newDirection;              // Flag for moving in a new direction
};

#endif