#include "Mouse.h"


// Initialize static variables
double Mouse::x = 0;
double Mouse::y = 0;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };


void Mouse::mousePosCallback(GLFWwindow* window, double _x, double _y)
{
  // Note:
  // GLFWwindoes have (0, 0) at the top left of the screen
  // Our OpenGL Viewport has (0, 0) at the bottom left of the screen
  // Therefore we need to perform a conversion for the vertical coordinate!

  // Get the frame buffer size
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  x = _x;
  y = height - _y;
}


void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  if (button < 0)
  {
    // Invalid mouse button
    return;
  }

  // Update the state of buttonsDown[] & buttonsUp[] based on what just happened
  if (action != GLFW_RELEASE && buttons[button] == false)
  {
    // Haven't released button, and haven't pressed it yet
    buttonsDown[button] = true;
    buttonsUp[button] = false;
  }
  else if (action == GLFW_RELEASE && buttons[button] == true)
  {
    // Just released button, and it was pressed previously
    buttonsDown[button] = false;
    buttonsUp[button] = true;
  }

  // Update the buttons[] array (current state)
  buttons[button] = action != GLFW_RELEASE;
}


double Mouse::getMouseX()
{
  return x;
}


double Mouse::getMouseY()
{
  return y;
}


bool Mouse::buttonDown(int button)
{
  // Only record a button press once
  bool x = buttonsDown[button];
  buttonsDown[button] = false;
  return x;
}


bool Mouse::buttonUp(int button)
{
  // Only record a button release once
  bool x = buttonsUp[button];
  buttonsUp[button] = false;
  return x;
}


bool Mouse::button(int button)
{
  return buttons[button];
}