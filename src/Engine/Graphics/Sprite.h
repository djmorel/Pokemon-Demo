#ifndef SPRITE_H
#define SPRITE_H


#include <iostream>
#include <string>
//#include "GLFW/glfw3.h"
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
    Sprite(int assetID);
    Sprite(std::string assetName, Vector3D _pos, float _rot, Vector3D _scale);
    Sprite(int assetID, Vector3D _pos, float _rot, Vector3D _scale);

    // Identifies sprite orientation
    enum class dir
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

    void Update();
    void Render();

    void setSpeedTo(float x);        // Set the speed to an absolute value
    void moveTo(Vector3D v);         // Set the position to an absolute value
    void moveBy(Vector3D v);         // Set the position relative by x
    void moveLeft();                 // Move left by one unit
    void moveRight();                // Move right by one unit
    void moveUp();                   // Move up by one unit
    void moveDown();                 // Move down by one unit
    void rotateTo(float x);          // Set the rotation to an absolute value
    void rotateBy(float x);          // Set the rotation relative by x
    void setScale(float x);          // Set the scale to x by x
    void setScale(Vector3D v);       // Set the scale to x by y
    void setDimensions(float x);     // Set the dimension of the sprite to a certain pixel count (only x & y)
    void setDimensions(Vector3D v);  // Set the dimension of the sprite to a certain pixel count

    Vector3D* getPos();
    float* getRot();
    Vector3D* getScale();
    Vector3D* getSize();

    int pushSpriteInfo(std::string assetName);
    int pushSpriteInfo(int assetID);
    void popSpriteInfo();

    void setFramesPerDirection(int _framesPerDirection);
    void setFrameIndex(int _frameIndex);
    int* getFramesPerDirection();
    int* getFrameIndex();

    int updateFrameIndex(dir direction);
    // Animates the sprite to walk in a specified direction
    void walk(bool move, bool changeFrame, bool newDirection, Vector3D displacement, dir direction, int duration);


  private:
    std::vector<assetInfo> spriteInfo;  // Holds spriteInfo for different frames (direction order is DOWN, LEFT, RIGHT, UP)
    Texture texture;
    float speed;
    Vector3D pos;
    float rot;
    Vector3D size;  // Size of the texture
    Vector3D scale;

    // For animations
    int framesPerDirection;  // Holds number of frames per direction (DOWN, LEFT, RIGHT, UP) for the sprite 
    int frameIndex;          // Tracks current Sprite frame
};


#endif