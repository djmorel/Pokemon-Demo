#ifndef SPRITE_H
#define SPRITE_H


#include "Texture.h"
#include "../Math/Vector3D.h"
#include "../Math/Vector2D.h"
#include "../../Assets/AssetLookupTable.h"
#include <iostream>
#include <string>
#include <vector>


// The actual game sprite
// Takes the image (texture) and manipulates its position, rotation, etc
class Sprite
{
  public:
    /**
      A constructor that configures a placeholder sprite.
      \param None
      \return None
    **/
    Sprite();

    /**
      A constructor that configures a Sprite according to an asset name.
      \param std::string assetName - Name of an asset to search for in the AssetLookupTable.
      \return None
    **/
    Sprite(std::string assetName);

    /**
      A constructor that configures a Sprite according to an asset ID.
      \param int assetID - An ID used to index into the AssetLookupTable for an asset.
      \return None
    **/
    Sprite(int assetID);

    /**
      A constructor that configures a Sprite according to an asset name and a set of properties.
      \param std::string assetName - Name of an asset to search for in the AssetLookupTable.
      \param Vector3D _pos - Position to set the Sprite to.
      \param float _rot - Rotation to set the Sprite to.
      \param Vector3D _scale - Scale to set the Sprite to.
      \return None
    **/
    Sprite(std::string assetName, Vector3D _pos, float _rot, Vector3D _scale);

    /**
      A constructor that configures a Sprite according to an asset ID and a set of properties.
      \param int assetID - An ID used to index into the AssetLookupTable for an asset.
      \param Vector3D _pos - Position to set the Sprite to.
      \param float _rot - Rotation to set the Sprite to.
      \param Vector3D _scale - Scale to set the Sprite to.
      \return None
    **/
    Sprite(int assetID, Vector3D _pos, float _rot, Vector3D _scale);

    // Defines the 4 possible directions for a Sprite's frame orientation
    // Follows the order of directions in the Sprite's spriteInfo vector, and CharacterInfo files
    enum class dir
    {
      DOWN,
      LEFT,
      RIGHT,
      UP
    };

    /**
      Currently does nothing for the Sprite.
      \param None
      \return None
    **/
    void Update();

    /**
      Renders the Sprite according to its currently indexed spriteInfo element, following OpenGL's matrix rules.
      \param None
      \return None
    **/
    void Render();

    /**
      Sets the Sprite's speed to an absolute value.
      \param float _speed - Speed to set the Sprite to.
      \return None
    **/
    void setSpeedTo(float _speed);

    /**
      Sets the Sprite's position to a fixed value.
      \param Vector3D _pos - Position to set the Sprite to.
      \return None
    **/
    void moveTo(Vector3D _pos);

    /**
      Sets the Sprite's position by a relative value.
      \param Vector3D v - Position to move the Sprite by.
      \return None
    **/
    void moveBy(Vector3D v);

    /**
      Moves the Sprite's position to the left based on its current speed.
      \param None
      \return None
    **/
    void moveLeft();

    /**
      Moves the Sprite's position to the right based on its current speed.
      \param None
      \return None
    **/
    void moveRight();

    /**
      Moves the Sprite's position upwards based on its current speed.
      \param None
      \return None
    **/
    void moveUp();

    /**
      Moves the Sprite's position downwards based on its current speed.
      \param None
      \return None
    **/
    void moveDown();

    /**
      Sets the Sprite's rotation to a fixed value in degrees.
      \param float _rot - Rotation (degrees) to set the Sprite to.
      \return None
    **/
    void rotateTo(float _rot);

    /**
      Sets the Sprite's rotation by a relative value in degrees.
      \param float x - Rotation (degrees) to rotate the Sprite by.
      \return None
    **/
    void rotateBy(float x);

    /**
      Sets the Sprite's scale to a fixed value (x by x by 0).
      \param float x - Scale to set the Sprite to.
      \return None
    **/
    void setScale(float x);

    /**
      Sets the Sprite's scale to a fixed Vector3D value.
      \param Vector3D _scale - Scale to set the Sprite to.
      \return None
    **/
    void setScale(Vector3D _scale);

    /**
      Sets the Sprite's dimensions on the screen to a fixed pixel count (x by x by 0). Calculates the appropriate scale.
      \param float x - Screen size to set the Sprite to (only affects x and y).
      \return None
    **/
    void setDimensions(float x);

    /**
      Sets the Sprite's dimensions on the screen to a fixed Vector3D pixel count. Calculates the appropriate scale.
      \param float x - Screen size to set the Sprite to (only affects x and y).
      \return None
    **/
    void setDimensions(Vector3D v);

    /**
      Sets the Sprite's framesPerDirection to a fixed value.
      \param int _framesPerDirection - Number of frames for per direction. Each direction has the same number of frames.
      \return None
    **/
    void setFramesPerDirection(int _framesPerDirection);

    /**
      Sets the Sprite's frameIndex to a fixed value.
      \param int _frameIndex - Number to index into the spriteInfo vector. Should be between 0 and spriteInfo.size()-1 inclusively.
      \return None
    **/
    void setFrameIndex(int _frameIndex);

    /**
      Returns a pointer to the Sprite's position for reference.
      \param None
      \return Vector3D pointer to the Sprite's pos.
    **/
    Vector3D* getPos();

    /**
      Returns a pointer to the Sprite's rotation for reference.
      \param None
      \return float pointer to the Sprite's rot.
    **/
    float* getRot();

    /**
      Returns a pointer to the Sprite's size for reference.
      \param None
      \return Vector3D pointer to the Sprite's size.
    **/
    Vector3D* getSize();

    /**
      Returns a pointer to the Sprite's scale for reference.
      \param None
      \return Vector3D pointer to the Sprite's scale.
    **/
    Vector3D* getScale();

    /**
      Returns a pointer to the Sprite's frames per direction for reference.
      \param None
      \return int pointer to the Sprite's framesPerDirection.
    **/
    int* getFramesPerDirection();

    /**
      Returns a pointer to the Sprite's frame index for reference.
      \param None
      \return int pointer to the Sprite's frameIndex.
    **/
    int* getFrameIndex();

    /**
      Adds an assetInfo element to the Sprite's spriteInfo vector.
      \param std::string assetName - Name of the asset to add.
      \return 0 on success, or -1 if couldn't find the assetName in the AssetLookupTable.
    **/
    int pushSpriteInfo(std::string assetName);

    /**
      Adds an assetInfo element to the Sprite's spriteInfo vector.
      \param int assetID - ID of the asset to add.
      \return 0 on success, or -1 if invalid AssetLookupTable index.
    **/
    int pushSpriteInfo(int assetID);

    /**
      Removes the last assetInfo element from the Sprite's spriteInfo vector.
      \param None
      \return None
    **/
    void popSpriteInfo();

    /**
      Sets the frame index to point to the next frame for the passed direction.
      \param Sprite::dir direction - Direction for the next frame (DOWN, LEFT, RIGHT, or UP).
      \return 0 on success, -1 if framesPerDirection doesn't match spriteInfo's size, or -2 if invalid direction.
    **/
    int updateFrameIndex(Sprite::dir direction);


    // 
    /**
      Animates the Sprite to "walk" in a specified direction.
      \param bool changeFrame - True if the Sprite should update its frame, and False if not.
      \param Vector3D displacement - Position to move the Sprite by.
      \param Sprite::dir direction - Direction of the "walk" relative to the Sprite on the screen.
      \param float duration - How long the "walk" should take (milliseconds).
      \return 0 on success, -1 if framesPerDirection doesn't match spriteInfo's size, or -2 if invalid direction.
    **/
    void walk(bool changeFrame, Vector3D displacement, Sprite::dir direction, float duration);


  private:
    std::vector<assetInfo> spriteInfo;  // Holds spriteInfo for different frames (direction order is DOWN, LEFT, RIGHT, UP)
    Texture texture;                    // The image (Texture) the Sprite corresponds to
    float speed;                        // Sprite's speed (absolute value) [Note: not used in current game]
    Vector3D pos;                       // Location of Sprite relative to the screen
    float rot;                          // Rotation of Sprite relative to the screen
    Vector3D size;                      // Size of the Sprite's image region of the Texture
    Vector3D scale;                     // Scales the Sprite from the base Texture size
    int framesPerDirection;             // Sprite's number of frames per direction (DOWN, LEFT, RIGHT, UP)
    int frameIndex;                     // Tracks the current Sprite frame (indexes into spriteInfo vector)
};


#endif