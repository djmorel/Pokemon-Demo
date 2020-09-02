#ifndef ENGINE_H
#define ENGINE_H


#include <iostream>
#include <GLFW/glfw3.h>


// Note: If pragma isn't supported, will get a Linker Error. Should use a CMake approach instead to link OpenGL.
#pragma comment(lib, "opengl32.lib")


// Handles GLFW window creation and I/O initialization.
class Engine
{
  public:
    static const int SCREEN_WIDTH = 1024;  // Defines the size of the game window's width
    static const int SCREEN_HEIGHT = 768;  // Defines the size of the game window's height

    /**
      A constructor that initializes a default Engine. Requires a call to Engine::Initialize() afterwards for configuration.
      \param None
      \return None
    **/
    Engine();

    /**
      A deconstructor that doesn't do anything extra special.
      \param None
      \return None
    **/
    ~Engine();

    /**
      Initializes GLFW (window application interface), initializes keyboard & mouse support, enables transparent PNGs, and updates lastTime.
      \param const char* windowTitle --> Game's name to be displayed as the window's title.
      \return True if successfully initialized the Engine, or False if not.
    **/
    bool Initialize(const char* windowTitle);

    /**
      Updates the time the window has been created, and allows I/O events to be processed.
      \param None
      \return None
    **/
    void Update();

    /**
      Clears the window's current back buffer. To display a screen, Render Sprites after this call, and then call Engine::EndRender().
      \param None
      \return None
    **/
    void BeginRender();

    /**
      Swaps the window's buffer with its current back buffer to render on-screen Sprites. Note: Any Sprite::Render() calls after this call will NOT be displayed on the window.
      \param None
      \return None
    **/
    void EndRender();

    /**
      Gets the Engine's delta time (dt) value. Useful for handling object movement to be consistent for all machines regardless of hardware performance.
      \param None
      \return dt value as a float.
    **/
    static float getDT();

    /**
      Gets the last time Engine::Update() was called.
      \param None
      \return lastTime value as a float.
    **/
    static float getLastTime();


  private:
    static GLFWwindow* window;  // Pointer to the GLFW window
    static float dt;            // Tracks the difference between Engine::Update() calls.
    static float lastTime;      // Tracks the last time Engine::Update() was called.
};


#endif