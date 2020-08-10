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

};

#endif