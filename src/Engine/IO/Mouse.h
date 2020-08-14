#ifndef MOUSE_H
#define MOUSE_H


#include "GLFW/glfw3.h"


// Use static to only instantiate ONE mouse
class Mouse
{
  public:
    static void mousePosCallback(GLFWwindow* window, double _x, double _y);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    static double getMouseX();
    static double getMouseY();

    static bool buttonDown(int button);  // Was button just down?
    static bool buttonUp(int button);    // Was button just released?
    static bool button(int button);      // What is the current state of button?

  private:
    static double x;
    static double y;

    static bool buttons[];      // Are mouse buttons currently held down? (Ongoing choice)
    static bool buttonsDown[];  // Were mouse buttons just pressed?
    static bool buttonsUp[];    // Were mouse buttons just released?

};


#endif