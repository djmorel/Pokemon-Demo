#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "GLFW/glfw3.h"


// Checks the states of incoming keyboard input using GLFW.
class Keyboard
{
  public:
    /**
      Updates the status of each key array.
      \param GLFWwindow* window --> The GLFW window receiving input.
      \param int key --> Current key in question.
      \param int scancode --> Ignore [Not used in current function implementation].
      \param int action --> Current key's action (i.e. GLFW_RELEASE, GLFW_PRESS, etc).
      \param int mods --> Ignore [Not used in current function implementation].
      \return None
    **/
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
      Checks the current state of a key.
      \param int key --> Current key in question.
      \return True if the key is currently pressed, or False if not.
    **/
    static bool key(int key);

    /**
      Checks if a key was just down. Uses the key to index into keysDown, and sets the element to false.
      \param int key --> Current key in question.
      \return True if the key was just down, or False if not.
    **/
    static bool keyDown(int key);

    /**
      Checks if a key was just released. Uses the key to index into keysUp, and sets the element to false.
      \param int key --> Current key in question.
      \return True if the key was just released, or False if not.
    **/
    static bool keyUp(int key);    // Was key just released?


  private:
    static bool keys[];      // Array that answers: Are keys currently held down? (Ongoing choice)
    static bool keysDown[];  // Array that answers: Were keys just pressed?
    static bool keysUp[];    // Array that answers: Were keys just released?
};


#endif