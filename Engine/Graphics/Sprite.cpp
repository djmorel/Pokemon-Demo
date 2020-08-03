#include "Sprite.h"
#include "../Engine.h"


Sprite::Sprite()
{
  texture = Texture();
  pos = Vector3D(0);
  rot = 0;
  scale = Vector3D(1);
  size = Vector3D(0);
  speed = 100;
}


Sprite::Sprite(std::string imagePath)
{
  texture = Texture(imagePath);
  pos = Vector3D(0);
  rot = 0;
  scale = Vector3D(1);
  size = Vector3D((float)texture.getWidth(), (float)texture.getHeight(), 1);
  speed = 100;
}


Sprite::Sprite(std::string imagePath, Vector3D v)
{
  texture = Texture(imagePath);
  pos = v;
  rot = 0;
  scale = Vector3D(1);
  size = Vector3D((float)texture.getWidth(), (float)texture.getHeight(), 1);
  speed = 100;
}


void Sprite::Update()
{
  // Do nothing until we get I/O going
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
  glRotatef(rot, 0, 0, 1);      // Rotate about the z axis since 2D
  glScalef(scale.x, scale.y, 1);

  // Rendering
  glColor4f(1, 1, 1, 1);  // Set asset color to white in case some other code changed it
  glBegin(GL_QUADS);      // Begin rendering with a mode (2D sprites means use quads)
  {
    // Setup texture coordinates with our real scene coordinates (where our matrix moved to)
    // Use the following order to ensure the entire sprite gets rendered properly (must use one-hot coordinate positions)
    // Use the "/ 2" part to set anchor point at the center of the image
    glTexCoord2i(0, 0);  glVertex2i(-texture.getWidth() / 2, -texture.getHeight() / 2);  // Bottom left
    glTexCoord2i(1, 0);  glVertex2i( texture.getWidth() / 2, -texture.getHeight() / 2);  // Bottom right
    glTexCoord2i(1, 1);  glVertex2i( texture.getWidth() / 2,  texture.getHeight() / 2);  // Top right
    glTexCoord2i(0, 1);  glVertex2i(-texture.getWidth() / 2,  texture.getHeight() / 2);  // Top left
    // Note:
    // glTexCoord2f() -> Percentage (0 to 1) of image to start drawing from (Horizontal, Vertical)
    // glVertex2i() -> Start drawing at a given position
    //
    // If we didn't translate, we would replace 0 with xPos and yPos
  }
  glEnd();  // End our drawing

  glDisable(GL_TEXTURE_2D);
}


void Sprite::setSpeedTo(float x)
{
  speed = x;
}


void Sprite::moveTo(Vector3D v)
{
  pos = v;
}


void Sprite::moveBy(Vector3D v)
{
  pos = pos + (v * Engine::getDT());
}


void Sprite::moveLeft()
{
  pos = pos - Vector3D((speed * Engine::getDT()), 0, 0);
}


void Sprite::moveRight()
{
  pos = pos + Vector3D((speed * Engine::getDT()), 0, 0);
}


void Sprite::moveUp()
{
  pos = pos + Vector3D(0, (speed * Engine::getDT()), 0);
}


void Sprite::moveDown()
{
  pos = pos - Vector3D(0, (speed * Engine::getDT()), 0);
}


void Sprite::rotateTo(float x)
{
  rot = x;
}


void Sprite::rotateBy(float x)
{
  // Rotate by x degrees
  rot += x;
  // Rotation to match all machine performances
  //rot += x * Engine::getDT();
}


void Sprite::setScale(float x)
{
  scale = Vector3D(x, x, 0);
}


void Sprite::setScale(Vector3D v)
{
  scale = v;
}


Vector3D* Sprite::getPos()
{
  return &pos;
}


float* Sprite::getRot()
{
  return & rot;
}


Vector3D* Sprite::getScale()
{
  return &scale;
}


Vector3D* Sprite::getSize()
{
  return &size;
}
