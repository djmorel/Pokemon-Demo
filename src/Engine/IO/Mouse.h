#ifndef MOUSE_H
#define MOUSE_H


#include "GLFW/glfw3.h"


// Checks the states of incoming mouse input using GLFW. Use static to only instantiate ONE mouse.
class Mouse
{
  public:
    /**
      Updates the status of the mouse's position.
      \param GLFWwindow* window --> The GLFW window receiving input.
      \param double _x --> x coordinate position of the mouse.
      \param double _y --> y coordinate position of the mouse.
      \return None
    **/
    static void mousePosCallback(GLFWwindow* window, double _x, double _y);

    /**
      Updates the status of the mouse's buttons.
      \param GLFWwindow* window --> The GLFW window receiving input.
      \param int button --> Current button in question.
      \param int action --> Current button's action (i.e. GLFW_RELEASE, GLFW_PRESS, etc).
      \param int mods --> Ignore [Not used in current function implementation].
      \return None
    **/
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    /**
      Gets the mouse's current x coordinate position.
      \param None
      \return x coordinate position as a double.
    **/
    static double getMouseX();

    /**
      Gets the mouse's current y coordinate position.
      \param None
      \return y coordinate position as a double.
    **/
    static double getMouseY();

    /**
      Checks the current state of a mouse button.
      \param int button --> Current button in question.
      \return True if the button is currently pressed, or False if not.
    **/
    static bool button(int button);

    /**
      Checks if a mouse button was just down. Uses the button to index into buttonsDown, and sets the element to false.
      \param int button --> Current button in question.
      \return True if the button was just down, or False if not.
    **/
    static bool buttonDown(int button);

    /**
      Checks if a mouse button was just released. Uses the button to index into buttonsUp, and sets the element to false.
      \param int button --> Current button in question.
      \return True if the button was just released, or False if not.
    **/
    static bool buttonUp(int button);


  private:
    static double x;            // Mouse's current x coordinate position with respect to the GLFW window
    static double y;            // Mouse's current y coordinate position with respect to the GLFW window
    static bool buttons[];      // Array that answers: Are mouse buttons currently held down? (Ongoing choice)
    static bool buttonsDown[];  // Array that answers: Were mouse buttons just pressed?
    static bool buttonsUp[];    // Array that answers: Were mouse buttons just released?
};


#endif