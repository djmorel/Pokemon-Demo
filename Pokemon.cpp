#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphics/Sprite.h"
#include "Engine/Actors/Character.h"
#include "Engine/IO/InputManager.h"


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

  // Initialize our game engine
  Engine engine;
  engine.Initialize("Pokemon");

  Sprite testSprite = Sprite("Assets/Art/Tyranitar.png", Vector3D((float)engine.SCREEN_WIDTH/2, (float)engine.SCREEN_HEIGHT/2, 0));
  testSprite.setScale(0.5f);

  Sprite testSprite2 = Sprite("Assets/Art/Tyranitar.png", Vector3D((float)(engine.SCREEN_WIDTH / 1.3), (float)(engine.SCREEN_HEIGHT / 1.3), 0));
  testSprite2.setScale(0.5f);
  //testSprite2.moveBy(Vector3D(50, 50, 0));  // Won't do much with current implementation

  Character player(testSprite);
  Character npc(testSprite2);

  InputManager im(&player);

  // Game loop
  while (true)
  {
    engine.Update();
    //testSprite.Update()
    player.Update();
    npc.Update();
    bool collision = RigidBody::isColliding(player.getRB(), npc.getRB());
    std::cout << (collision ? "Colliding!" : "...") << std::endl;
    im.Update();

    // Enable mouse movement support
    //testSprite.setPos((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

    engine.BeginRender();
    player.Render();
    npc.Render();
    engine.EndRender();
  }

  return 0;
}