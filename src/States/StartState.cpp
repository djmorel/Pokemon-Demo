#include "StartState.h"
#include "../Engine/Engine.h"


StartState::StartState()
{
  // Create the start screen
  startScreen = Sprite("StartScreen", Vector3D((float)Engine::SCREEN_WIDTH / 2, (float)Engine::SCREEN_HEIGHT / 2, 0), 0, Vector3D(1.07f));
}

// Note: GameManager should first push StartState()
// When player pressed continue, GameManager then pushes FadeInState(), PlayState(), DialogueState(), and FadeOutState()