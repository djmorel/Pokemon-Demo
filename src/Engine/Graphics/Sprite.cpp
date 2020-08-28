#include "Sprite.h"
#include "../Engine.h"
#include "../Math/Math.h"



Sprite::Sprite()
{
  // Create a placeholder assetInfo
  assetInfo _spriteInfo;
  _spriteInfo.assetPath = "";
  _spriteInfo.sheetIndex = Vector2D(-1, -1);
  _spriteInfo.spriteRows = -1;
  _spriteInfo.spriteColumns = -1;
  _spriteInfo.unitsHigh = -1;
  _spriteInfo.unitsWide = -1;

  // Add the placeholder to the Sprite's spriteInfo vector
  spriteInfo.push_back(_spriteInfo);

  // Config the spriteInfo tracker variables to mark the placeholder
  framesPerDirection = -1;
  frameIndex = 0;

  // Set the remaining Sprite members as default placeholders
  texture = Texture();
  pos = Vector3D(0);
  rot = 0;
  scale = Vector3D(1);
  size = Vector3D(0);
  speed = 0;
}



Sprite::Sprite(std::string assetName)
{
  // Check if the assetInfo was successfully added to the Sprite spriteInfo vector
  if (pushSpriteInfo(assetName) < 0)
  {
    std::cout << "ERROR Invalid asset name: " << assetName << std::endl;
    return;
  }

  // Config the spriteInfo tracker variables
  framesPerDirection = 1;
  frameIndex = 0;

  // Set the remaining Sprite members according to the retrieved assetInfo
  texture = Texture(spriteInfo[frameIndex].assetPath);
  pos = Vector3D(0);
  rot = 0;

  // Set the size based on the texture dimensions
  if (spriteInfo[frameIndex].spriteRows == 1 && spriteInfo[frameIndex].spriteColumns == 1)
  {
    size = Vector3D((float)texture.getWidth(), (float)texture.getHeight(), 1);
  }
  else
  {
    // Caclulate the sprite unit height and width
    float unitHeight = (float)texture.getHeight() / (float)spriteInfo[frameIndex].spriteRows;
    float unitWidth = (float)texture.getWidth() / (float)spriteInfo[frameIndex].spriteColumns;
    float spriteHeight = spriteInfo[frameIndex].unitsHigh * unitHeight;
    float spriteWidth = spriteInfo[frameIndex].unitsWide * unitWidth;

    size = Vector3D(spriteWidth, spriteHeight, 1);
  }
  scale = Vector3D(1);
  speed = 0;
}



Sprite::Sprite(int assetID)
{
  // Check if the assetInfo was successfully added to the Sprite spriteInfo vector
  if (pushSpriteInfo(assetID) < 0)
  {
    std::cout << "ERROR Invalid asset ID: " << assetID << std::endl;
    return;
  }

  // Config the spriteInfo tracker variables
  framesPerDirection = 1;
  frameIndex = 0;

  // Set the remaining Sprite members according to the retrieved assetInfo
  texture = Texture(spriteInfo[frameIndex].assetPath);
  pos = Vector3D(0);
  rot = 0;

  // Set the size based on the texture dimensions
  if (spriteInfo[frameIndex].spriteRows == 1 && spriteInfo[frameIndex].spriteColumns == 1)
  {
    size = Vector3D((float)texture.getWidth(), (float)texture.getHeight(), 1);
  }
  else
  {
    // Caclulate the sprite unit height and width
    float unitHeight = (float)texture.getHeight() / (float)spriteInfo[frameIndex].spriteRows;
    float unitWidth = (float)texture.getWidth() / (float)spriteInfo[frameIndex].spriteColumns;
    float spriteHeight = spriteInfo[frameIndex].unitsHigh * unitHeight;
    float spriteWidth = spriteInfo[frameIndex].unitsWide * unitWidth;

    size = Vector3D(spriteWidth, spriteHeight, 1);
  }
  scale = Vector3D(1);
  speed = 0;
}



Sprite::Sprite(std::string assetName, Vector3D _pos, float _rot, Vector3D _scale)
{
  // Check if the assetInfo was successfully added to the Sprite spriteInfo vector
  if (pushSpriteInfo(assetName) < 0)
  {
    std::cout << "ERROR Invalid asset name: " << assetName << std::endl;
    return;
  }

  // Config the spriteInfo tracker variables
  framesPerDirection = 1;
  frameIndex = 0;

  // Set the remaining Sprite members according to the retrieved assetInfo and input arguments
  texture = Texture(spriteInfo[frameIndex].assetPath);
  pos = _pos;
  rot = _rot;

  // Set the size based on the texture dimensions
  if (spriteInfo[frameIndex].spriteRows == 1 && spriteInfo[frameIndex].spriteColumns == 1)
  {
    size = Vector3D((float)texture.getWidth(), (float)texture.getHeight(), 1);
  }
  else
  {
    // Caclulate the sprite unit height and width
    float unitHeight = (float)texture.getHeight() / (float)spriteInfo[frameIndex].spriteRows;
    float unitWidth = (float)texture.getWidth() / (float)spriteInfo[frameIndex].spriteColumns;
    float spriteHeight = spriteInfo[frameIndex].unitsHigh * unitHeight;
    float spriteWidth = spriteInfo[frameIndex].unitsWide * unitWidth;

    size = Vector3D(spriteWidth, spriteHeight, 1);
  }
  scale = _scale;
  speed = 100;
}



Sprite::Sprite(int assetID, Vector3D _pos, float _rot, Vector3D _scale)
{
  // Check if the assetInfo was successfully added to the Sprite spriteInfo vector
  if (pushSpriteInfo(assetID) < 0)
  {
    std::cout << "ERROR Invalid asset ID: " << assetID << std::endl;
    return;
  }

  // Config the spriteInfo tracker variables
  framesPerDirection = 1;
  frameIndex = 0;

  // Set the remaining Sprite members according to the retrieved assetInfo and input arguments
  texture = Texture(spriteInfo[frameIndex].assetPath);
  pos = _pos;
  rot = _rot;

  // Set the size based on the texture dimensions
  if (spriteInfo[frameIndex].spriteRows == 1 && spriteInfo[frameIndex].spriteColumns == 1)
  {
    size = Vector3D((float)texture.getWidth(), (float)texture.getHeight(), 1);
  }
  else
  {
    // Caclulate the sprite unit height and width
    float unitHeight = (float)texture.getHeight() / (float)spriteInfo[frameIndex].spriteRows;
    float unitWidth = (float)texture.getWidth() / (float)spriteInfo[frameIndex].spriteColumns;
    float spriteHeight = spriteInfo[frameIndex].unitsHigh * unitHeight;
    float spriteWidth = spriteInfo[frameIndex].unitsWide * unitWidth;

    size = Vector3D(spriteWidth, spriteHeight, 1);
  }
  scale = _scale;
  speed = 100;
}



void Sprite::Update()
{
  // Do nothing (keep as a placeholder for future functionality)
}



void Sprite::Render()
{
  // Render our texture via OpenGL code
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture.getID());

  // Obey the following order for the math to work out
  // Load Idenity -> Translate -> Rotate -> Scale
  glLoadIdentity();
  glTranslatef(pos.x, pos.y, 0);  // In 2D so zPos = 0
  glRotatef(rot, 0, 0, 1);        // Rotate about the z axis since 2D
  glScalef(scale.x, scale.y, 1);

  // Rendering
  glColor4f(1, 1, 1, 1);  // Set asset color to white in case some other code changed it
  glBegin(GL_QUADS);      // Begin rendering with a mode (2D sprites means use quads)
  {
    // Pull information about the spritesheet
    float x = (float)spriteInfo[frameIndex].sheetIndex.x;
    float y = (float)spriteInfo[frameIndex].sheetIndex.y;
    float xRatio = 1.0f / (float)spriteInfo[frameIndex].spriteColumns;
    float yRatio = 1.0f / (float)spriteInfo[frameIndex].spriteRows;

    // Setup texture coordinates with our real scene coordinates (where our matrix moved to) (first quadrant coordinates)
    // Use the following order to ensure the entire sprite gets rendered properly (must use one-hot coordinate positions)
    // Use the "/ 2" part to set anchor point at the center of the image

    // Top left vertex
    glTexCoord2f( (0 + x) * xRatio, (0 + y) * yRatio);
    glVertex2f(-texture.getWidth() * xRatio * spriteInfo[frameIndex].unitsWide / 2, -texture.getHeight() * yRatio * spriteInfo[frameIndex].unitsHigh / 2);

    // Bottom left vertex
    glTexCoord2f( (spriteInfo[frameIndex].unitsWide + x) * xRatio, (0 + y) * yRatio);
    glVertex2f( texture.getWidth() * xRatio * spriteInfo[frameIndex].unitsWide / 2, -texture.getHeight() * yRatio * spriteInfo[frameIndex].unitsHigh / 2);

    // Bottom right vertex
    glTexCoord2f( (spriteInfo[frameIndex].unitsWide + x) * xRatio, (spriteInfo[frameIndex].unitsHigh + y) * yRatio);
    glVertex2f( texture.getWidth() * xRatio * spriteInfo[frameIndex].unitsWide / 2,  texture.getHeight() * yRatio * spriteInfo[frameIndex].unitsHigh / 2);

    // Top right vertex
    glTexCoord2f( (0 + x) * xRatio, (spriteInfo[frameIndex].unitsHigh + y) * yRatio);
    glVertex2f(-texture.getWidth() * xRatio * spriteInfo[frameIndex].unitsWide / 2,  texture.getHeight() * yRatio * spriteInfo[frameIndex].unitsHigh / 2);

    // Note:
    // glTexCoord2f() -> Percentage (0 to 1) of image to start drawing from (Horizontal, Vertical)
    // glVertex2i() -> Start drawing at a given position
    // First Quadrant: (0, 0) is the bottom left & (1, 1) is the top right
    // If we didn't translate, we would replace 0 with xPos and yPos (in glVertex2i() function)
  }
  glEnd();  // End our drawing

  glDisable(GL_TEXTURE_2D);
}


void Sprite::setSpeedTo(float _speed)
{
  // Make sure speed is set an absolute value
  speed = Math::abs(_speed);
}


void Sprite::moveTo(Vector3D _pos)
{
  pos = _pos;
}



void Sprite::moveBy(Vector3D v)
{
  pos = pos + v;

  // Use getDT() if looking to move according to the processor's time
  // pos = pos + (v * Engine::getDT());
}



void Sprite::moveLeft()
{
  pos = pos - Vector3D(speed, 0, 0);

  // Use getDT() if looking to move according to the processor's time
  // pos = pos - Vector3D((speed * Engine::getDT()), 0, 0);
}



void Sprite::moveRight()
{
  pos = pos + Vector3D(speed, 0, 0);

  // Use getDT() if looking to move according to the processor's time
  // pos = pos + Vector3D((speed * Engine::getDT()), 0, 0);
}



void Sprite::moveUp()
{
  pos = pos + Vector3D(0, speed, 0);

  // Use getDT() if looking to move according to the processor's time
  // pos = pos + Vector3D(0, (speed * Engine::getDT()), 0);
}



void Sprite::moveDown()
{
  pos = pos - Vector3D(0, speed, 0);

  // Use getDT() if looking to move according to the processor's time
  // pos = pos - Vector3D(0, (speed * Engine::getDT()), 0);
}



void Sprite::rotateTo(float _rot)
{
  rot = _rot;
}



void Sprite::rotateBy(float x)
{
  rot += x;
}



void Sprite::setScale(float x)
{
  scale = Vector3D(x, x, 0);
}



void Sprite::setScale(Vector3D _scale)
{
  scale = _scale;
}



void Sprite::setDimensions(float x)
{
  scale = Vector3D(x, x, 0) / size;
}



void Sprite::setDimensions(Vector3D v)
{
  scale = v / size;
}



void Sprite::setFramesPerDirection(int _framesPerDirection)
{
  framesPerDirection = _framesPerDirection;
}



void Sprite::setFrameIndex(int _frameIndex)
{
  frameIndex = _frameIndex;
}



Vector3D* Sprite::getPos()
{
  return &pos;
}



float* Sprite::getRot()
{
  return &rot;
}



Vector3D* Sprite::getSize()
{
  return &size;
}



Vector3D* Sprite::getScale()
{
  return &scale;
}



int* Sprite::getFramesPerDirection()
{
  return &framesPerDirection;
}



int* Sprite::getFrameIndex()
{
  return &frameIndex;
}



int Sprite::pushSpriteInfo(std::string assetName)
{
  // Retrieve spriteInfo from the AssetLookupTable
  assetInfo _spriteInfo = AssetLT::findAsset(assetName);

  // Check if valid asset name passed
  if (_spriteInfo.assetPath == "")
  {
    // Invalid passed assetName, so return an error
    return -1;
  }

  // Add the assetInfo object to Sprite's spriteInfo vector
  spriteInfo.push_back(_spriteInfo);

  // Return success
  return 0;
}



int Sprite::pushSpriteInfo(int assetID)
{
  // Retrieve spriteInfo from the AssetLookupTable
  assetInfo _spriteInfo = AssetLT::findAsset(assetID);

  // Check if valid asset name passed
  if (_spriteInfo.assetPath == "")
  {
    // Invalid passed assetName, so return an error
    return -1;
  }

  // Add the assetInfo object to Sprite's spriteInfo vector
  spriteInfo.push_back(_spriteInfo);

  // Return success
  return 0;
}



void Sprite::popSpriteInfo()
{
  // Only pop if spriteInfo actually contains something
  if (spriteInfo.size() > 0)
  {
    spriteInfo.pop_back();
  }

  // If no more elements, record invalid values for the spriteInfo tracker variables
  if (spriteInfo.size() == 0)
  {
    framesPerDirection = -1;
    frameIndex = -1;
  }
}



int Sprite::updateFrameIndex(Sprite::dir direction)
{
  // Check that framesPerDirection and the size of the spriteInfo vector match
  if (spriteInfo.size() != framesPerDirection * 4)
  {
    return -1;
  }

  // Assign the direction offset based on the direction
  int dirOffset;
  if (direction == dir::DOWN)
  {
    dirOffset = 0;
  }
  else if (direction == dir::LEFT)
  {
    dirOffset = 1;
  }
  else if (direction == dir::RIGHT)
  {
    dirOffset = 2;
  }
  else if (direction == dir::UP)
  {
    dirOffset = 3;
  }
  else
  {
    // Invalid direction, so report an error
    return -2;
  }

  // Calculate the start and end frame ranges
  int startFrame = framesPerDirection * dirOffset;
  int endFrame = startFrame + framesPerDirection - 1;

  // Assign the frameIndex based on its current value
  if ( (frameIndex >= startFrame) && (frameIndex < endFrame) )
  {
    frameIndex++;
  }
  else
  {
    frameIndex = startFrame;
  }

  // Return success
  return 0;
}



void Sprite::walk(bool changeFrame, Vector3D displacement, Sprite::dir direction, float duration)
{
  // Check if the sprite's frame Index should change
  if (changeFrame)
  {
    // Adjust the sprite's frameIndex
    if (updateFrameIndex(direction) < 0)
    {
      // Unable to update the frame index, so report an error
      std::cout << "ERROR: Invalid direction or Sprite's framesPerDirection not configured properly!" << std::endl;
    }
  }

  // Move the Sprite according to its displacement
  moveBy(displacement);

  // Add delay to the walk
  while ( ((float)glfwGetTime() - Engine::getLastTime()) < duration / 1000)
  {
    // Stall in the while loop until the timer reaches the target duration
    // This stalling method ensures that worlds with lots of Sprite rendering don't add extra delay to the walk stall
    // Note: glfwGetTime records time in seconds since the GLFW window was created
  }
}