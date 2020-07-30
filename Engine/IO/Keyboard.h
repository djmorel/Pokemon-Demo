#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "GLFW/glfw3.h"


class Keyboard
{
  public:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static bool keyDown(int key);  // Was key just down?
    static bool keyUp(int key);    // Was key just released?
    static bool key(int key);      // What is the current state of key?

  private:
    static bool keys[];      // Are keys currently held down? (Ongoing choice)
    static bool keysDown[];  // Were keys just pressed?
    static bool keysUp[];    // Were keys just released?

};


#endif