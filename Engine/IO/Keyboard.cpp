#include "Keyboard.h"


// Initialize static variables
bool Keyboard::keys[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysDown[GLFW_KEY_LAST] = { 0 };
bool Keyboard::keysUp[GLFW_KEY_LAST] = { 0 };


void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key < 0)
  {
    // Invalid key
    return;
  }

  // Update the state of keysDown[] & keysUp[] based on what just happened
  if (action != GLFW_RELEASE && keys[key] == false)
  {
    // Haven't released key, and haven't pressed it yet
    keysDown[key] = true;
    keysUp[key] = false;
  }
  else if (action == GLFW_RELEASE && keys[key] == true)
  {
    // Just released key, and it was pressed previously
    keysDown[key] = false;
    keysUp[key] = true;
  }

  // Update the keys[] array (current state)
  keys[key] = action != GLFW_RELEASE;
}