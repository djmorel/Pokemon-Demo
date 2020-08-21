#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#//include "../Engine/Actors/Character.h"
#include "../Engine/Engine.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"
#include "CharacterManager.h"
#include "WorldManager.h"


class InputManager
{
  public:
    InputManager(CharacterManager* _cm, WorldManager* _world);

    void Update();

  private:
    CharacterManager* cm;                  // Pointer to the CharacterManager
    Vector2D* pScreenCoord;                // Tracks the player coordinates on the screen (x: 0-15 & y: 0-11)
    Vector2D* pMapCoord;                   // Tracks the player coordinates on the map (x & y ranges depend on map)
    WorldManager* world;                   // Pointer to the world
    int animationCount = 0;                // Counter for how many times an animation has to be called
    int walkCountQuota = 8;                // Amount of times the walk animation has to be called
    bool isActive = false;                 // Blocks incoming input from processing
    WalkAnimation::dir currentDirection;   // Specifies the current animation direction
    WalkAnimation::dir previousDirection;  // Specifies the previous animation direction
    bool newDirection;                     // Flag for moving in a new direction
};

#endif