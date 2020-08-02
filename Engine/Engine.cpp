#include "Engine.h"
#include "IO/Mouse.h"
#include "IO/Keyboard.h"


// Declare our static variables from Engine.h
int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
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

  // GL Setup
  // Viewport
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);  // How our viewport is handled (look into more options)
  glLoadIdentity();  // Start our identity matrix
  glOrtho(0, width, 0, height, -10, 10);  // Camera setup
  glDepthRange(-10, 10);
  glMatrixMode(GL_MODELVIEW);

  // Alpha Blending (allows PNG backgrounds to be transparent)
  // Look into wiki for more info
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
  glClearColor((float)0.56, (float)0.4, (float)0.32, 1);  // Clear back buffer to brown (R, G, B, alpha) <- Floats (Divide RGB values by 255)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the depth
}

void Engine::EndRender()
{
  // Render to the back buffer (next screen)


  // Swap the buffer
  glfwSwapBuffers(window);

  // Note: NOTHING after here will be presented to the screen
  // Already swapped buffer and Render() begins with a clear
}


float Engine::getDT()
{
  return dt;
}
