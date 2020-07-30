#ifndef SPRITE_H
#define SPRITE_H


#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include "Texture.h"


// Handles the actual sprite such as its position and rotation
class Sprite
{
  public:
    Sprite();
    Sprite(std::string imagePath);
    Sprite(std::string imagePath, float _xPos, float _yPos);

    void Update();
    void Render();

    void setPos(float x, float y);
    void setRotTo(float x);  // Set the rotation to an absolute value
    void setRotBy(float x);  // Set the rotation relative to x
    void setScale(float x);
    void setScale(float x, float y);

  private:
    Texture texture;
    float xPos;
    float yPos;
    float rot;
    float xScale;
    float yScale;

};


#endif