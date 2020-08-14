#ifndef STARTSTATE_H
#define STARTSTATE_H


#include "../Graphics/Sprite.h"


class StartState
{
  public:
    StartState();

    void Update();
    void Render();

  private:
    Sprite startScreen;
};

#endif