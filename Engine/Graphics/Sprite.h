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

    void setSpeedTo(float x);         // Set the speed to an absolute value
    void moveTo(float x, float y);    // Set the position to an absolute value
    void moveBy(float x, float y);    // Set the position relative by x
    void moveLeft();                  // Move left by one unit
    void moveRight();                 // Move right by one unit
    void moveUp();                    // Move up by one unit
    void moveDown();                  // Move down by one unit
    void rotateTo(float x);           // Set the rotation to an absolute value
    void rotateBy(float x);           // Set the rotation relative by x
    void setScale(float x);           // Set the scale to x by x
    void setScale(float x, float y);  // Set the scale to x by y

  private:
    Texture texture;
    float speed;
    float xPos;
    float yPos;
    float rot;
    float xScale;
    float yScale;

};


#endif