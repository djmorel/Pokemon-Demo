#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include "../Engine/Actors/Character.h"
#include "../Engine/Engine.h"
#include "../Engine/IO/Mouse.h"
#include "../Engine/IO/Keyboard.h"


class InputManager
{
  public:
    InputManager(Character* _character);

    void Update();

  private:
    Character* character;
    int animationCount = 0;       // Counter for how many times an animation has to be called
    bool isActive = false;        // Blocks incoming input from processing
    Character::dir animationDir;  // Specifies the animation's direction
};

#endif