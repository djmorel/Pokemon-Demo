#ifndef TRANSITIONSTATE_H
#define TRANSITIONSTATE_H


#include "../Math/Vector3D.h"

class TransitionState
{
  public:
    TransitionState();
    TransitionState(Vector3D _color, bool _fadeIn, int _time);

  private:
    Vector3D color;   // RGB color for transition
    bool fadeIn;      // True means fadeIn effect & False means fadeOut effect
    int time;         // Specifies transition duration (seconds)
    bool isComplete;  // Specifies if state finished
};


#endif