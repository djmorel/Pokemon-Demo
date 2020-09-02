#include "Engine.h"
#include "IO/Mouse.h"
#include "IO/Keyboard.h"



// Declare our static variables
GLFWwindow* Engine::window = NULL;
float Engine::dt = 0;
float Engine::lastTime = 0;



Engine::Engine()
{
  // Do nothing so we initialize our constructor in the Initialize() function
}



Engine::~Engine()
{
  // Do nothing so we initialize our destructor in the Initialize() function
}



bool::Engine::Initialize(const char* windowTitle)
{
  // Initialize GLFW, our window application interface
  if (!glfwInit())
  {
    std::cout << "Error initializing GLFW" << std::endl;
    return false;
  }

  // Create the game window
  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);

  // Check if our window was made
  if (window == NULL)
  {
    std::cout << "Error creating window" << std::endl;
    return false;
  }

  /*
  // Initialize GLEW (needed if using glDrawArrays()
  glewExperimental = true;
  if (!glewInit())
  {
    std::cout << "Error initializing GLEW" << std::endl;
    return false;
  }
  */

  // GLFW Setup
  glfwMakeContextCurrent(window);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glfwSwapInterval(1);  // How often we swap between buffers (current screen & next drawn screen)

  // Get mouse data
  glfwSetCursorPosCallback(window, Mouse::mousePosCallback);
  glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);

  // Get keyboard data
  glfwSetKeyCallback(window, Keyboard::keyCallback);

  // Get the context of our actual monitor
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  // Configure our window to be in the center of the user's monitor
  int xPos = (mode->width - SCREEN_WIDTH) / 2;
  int yPos = (mode->height - SCREEN_HEIGHT) / 2;
  glfwSetWindowPos(window, xPos, yPos);

  // GL Setup (Viewport)
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);  // How our viewport is handled (look into more options)
  glLoadIdentity();  // Start our identity matrix
  glOrtho(0, width, 0, height, -10, 10);  // Camera setup
  glDepthRange(-10, 10);
  glMatrixMode(GL_MODELVIEW);

  // Alpha Blending (allows PNG backgrounds to be transparent)
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Update lastTime
  lastTime = (float)glfwGetTime();

  return true;
}



void Engine::Update()
{
  // Update the times
  float now = (float)glfwGetTime();
  dt = (now - lastTime);
  lastTime = now;

  // Allow I/O events to be processed
  glfwPollEvents();  // Handles commands in the queue
}



void Engine::BeginRender()
{
  glClearColor(0.0f/255.0f, 128.0f/255.0f, 64.0f/255.0f, 1);  // Clear back buffer to a color (R, G, B, alpha). Needs floats so divide values by 255.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear the depth
}



void Engine::EndRender()
{
  // Render to the back buffer (next screen)

  // Swap the buffer
  glfwSwapBuffers(window);

  // Note: NOTHING after here will be presented to the screen
  // Already swapped buffer and BeginRender() begins with a clear
}



float Engine::getDT()
{
  return dt;
}



float Engine::getLastTime()
{
  return lastTime;
}