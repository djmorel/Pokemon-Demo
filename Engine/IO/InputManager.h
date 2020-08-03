#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include "../Actors/Character.h"
#include "../Engine.h"
#include "Mouse.h"
#include "Keyboard.h"


class InputManager
{
  public:
    InputManager(Character* _character);

    void Update();

  private:
    Character* character;

};

#endif