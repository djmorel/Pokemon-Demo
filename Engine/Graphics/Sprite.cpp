#include "Sprite.h"


Sprite::Sprite()
{
  xPos = 0;
  yPos = 0;
  texture = Texture();
}


Sprite::Sprite(std::string imagePath)
{
  texture = Texture(imagePath);
  xPos = 0;
  yPos = 0;
}


Sprite::Sprite(std::string imagePath, float _xPos, float _yPos)
{
  texture = Texture(imagePath);
  xPos = _xPos;
  yPos = _yPos;
}


void Sprite::Update()
{
  // Do nothing until we get I/O going
}


void Sprite::Render()
{
  // Render our texture via OpenGL code
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture.GetID());

  // Obey the following order for the math to work out
  // Load Idenity -> Translate -> Rotate -> Scale
  glLoadIdentity();
  glTranslatef(xPos, yPos, 0);  // In 2D so zPos = 0
  //glRotatef()
  //glScalef()

  // Rendering
  glColor4f(1, 1, 1, 1);   // Set asset color to white in case some other code changed it
  glBegin(GL_QUADS);       // Begin rendering with a mode (2D sprites means use quads)
  // Setup texture coordinates with our real scene coordinates (where our matrix moved to)
  // Use the following order to ensure the entire sprite gets rendered properly (must use one-hot coordinate positions)
  glTexCoord2f(0, 0);  glVertex2f(0, 0);                                     // Bottom left
  glTexCoord2f(1, 0);  glVertex2f(texture.GetWidth(), 0);                    // Bottom right
  glTexCoord2f(1, 1);  glVertex2f(texture.GetWidth(), texture.GetHeight());  // Up right
  glTexCoord2f(0, 1);  glVertex2f(0, texture.GetHeight());                   // Up left
  // Note:
  // glTexCoord2f() -> Percentage (0 to 1) of image to start drawing from (Horizontal, Vertical)
  // glVertex2f() -> Start drawing at a given position
  //
  // If we didn't translate, we would replace 0 with xPos and yPos like so:
  // glTexCoord2f(0, 0);  glVertex2f(xPos, yPos);
  // glTexCoord2f(1, 0);  glVertex2f(xPos + texture.GetWidth(), yPos);
  // glTexCoord2f(1, 1);  glVertex2f(xPos + texture.GetWidth(), yPos + texture.GetHeight());
  // glTexCoord2f(0, 1);  glVertex2f(xPos, yPos + texture.GetHeight());
  glEnd();  // End our drawing

  glDisable(GL_TEXTURE_2D);
}