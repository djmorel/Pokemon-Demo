#ifndef ENGINE_H
#define ENGINE_H


#include <iostream>
#include "GLFW/glfw3.h"
#pragma comment(lib, "opengl32.lib")


class Engine
{
  public:
    static const int SCREEN_WIDTH = 1024;
    static const int SCREEN_HEIGHT = 768;
    static float getDT();

    Engine();
    ~Engine();

    bool Initialize(const char* windowTitle);

    void Update();       // Update the current state
    void BeginRender();  // Render the new state (clear back buffer)
    void EndRender();    // Render the new state (swap buffers)


  private:
    static GLFWwindow* window;
    static float dt;  // Delta time used for movement (ensures speed is same for all machines)
    static float lastTime;

};


#endif