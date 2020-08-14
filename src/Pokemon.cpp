#include <iostream>
#include "Managers/GameManager.h"
/*
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/Actors/Character.h"
#include "Engine/Actors/Entity.h"
#include "Managers/InputManager.h"
#include "Managers/WorldManager.h"
*/


// Note:
// The game window doesn't respond to closing via X
// --> Need to handle that ourselves (cleanup, deconstructors, etc)
// The game window won't draw to a full screen
// --> It will only draw to a section of the full screen
// --> Need to make the adjustment to our viewport

// TODO
// For the real game, remove any uneccessary rotation/movement stuff
// --> Likely won't need the Separating Axis Theorem for collisons, and just check bounding areas


int main()
{
  std::cout << "The time has come...\nAschente!" << std::endl;

  GameManager gameManager;
  int ret_val = gameManager.Start();

  // Error handling for the Game Manager
  if (ret_val < 0)
  {
    std::cout << "Uh oh, there was a problem with GameManager::Start()..." << std::endl;
  }

  return 0;
}