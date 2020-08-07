#ifndef SPRITE_H
#define SPRITE_H


#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include "Texture.h"
#include "../Math/Vector3D.h"
#include "../Math/Vector2D.h"
#include "../../Assets/AssetLookupTable.h"
#include <vector>


// The actual game sprite
// Takes the image (texture) and manipulates its position, rotation, etc
class Sprite
{
  public:
    Sprite();
    Sprite(std::string assetName);
    Sprite(std::string assetName, Vector3D _pos);

    void Update();
    void Render();

    void setSpeedTo(float x);   // Set the speed to an absolute value
    void moveTo(Vector3D v);    // Set the position to an absolute value
    void moveBy(Vector3D v);    // Set the position relative by x
    void moveLeft();            // Move left by one unit
    void moveRight();           // Move right by one unit
    void moveUp();              // Move up by one unit
    void moveDown();            // Move down by one unit
    void rotateTo(float x);     // Set the rotation to an absolute value
    void rotateBy(float x);     // Set the rotation relative by x
    void setScale(float x);     // Set the scale to x by x
    void setScale(Vector3D v);  // Set the scale to x by y

    Vector3D* getPos();
    float* getRot();
    Vector3D* getScale();
    Vector3D* getSize();

  private:
    assetInfo spriteInfo;
    Texture texture;
    float speed;
    Vector3D pos;
    float rot;
    Vector3D scale;
    Vector3D size;
};


#endif