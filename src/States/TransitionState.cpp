#include "TransitionState.h"


TransitionState::TransitionState()
{
  color = Vector3D(0, 0, 0);  // Default color is black
  fadeIn = false;             // Default is fade out
  time = 1;                   // Default duration is 1 second
  isComplete = false;         // Transition isn't finished
}


TransitionState::TransitionState(Vector3D _color, bool _fadeIn, int _time)
{
  color = _color;
  fadeIn = _fadeIn;
  time = _time;
  isComplete = false;
}