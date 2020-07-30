#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "GLFW/glfw3.h"
#pragma comment(lib, "opengl32.lib")

class Engine
{
  public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    Engine();
    ~Engine();

    bool Initialize(const char* windowTitle);

    void Update();       // Update the current state
    void BeginRender();  // Render the new state (clear back buffer)
    void EndRender();    // Render the new state (swap buffers)


  private:
    static GLFWwindow* window;

};

#endif
