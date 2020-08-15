#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include "../Engine/Actors/Character.h"
#include "../Engine/Engine.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"
#include "WorldManager.h"


class InputManager
{
  public:
    InputManager(Character* _player, WorldManager* _world);

    void Update();

  private:
    Character* player;                     // Pointer to the player character
    WorldManager* world;                   // Pointer to the world
    int animationCount = 0;                // Counter for how many times an animation has to be called
    bool isActive = false;                 // Blocks incoming input from processing
    WalkAnimation::dir currentDirection;   // Specifies the current animation direction
    WalkAnimation::dir previousDirection;  // Specifies the previous animation direction
    bool newDirection;                     // Flag for moving in a new direction
};

#endif