#include "Texture.h"



Texture::Texture()
{
  // Empty constructor for array/vector setup
  id = -1;  // Allows us to set up our texture before we draw it

  // Initialize height & width
  // Note that they will get proper values from GetTextureParams()
  height = 0;
  width = 0;
}



Texture::Texture(int _id)
{
  id = _id;

  if (!getTextureParams())
  {
    std::cout << "Error loading image with ID: " << id << std::endl;
  }
}



Texture::Texture(std::string path)
{
  // Load a texture from a path, and give it an ID
  id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);

  if (!getTextureParams())
  {
    std::cout << "Error loading image: " << path << std::endl;
  }
}



int Texture::getID()
{
  return id;
}



int Texture::getWidth()
{
  return width;
}



int Texture::getHeight()
{
  return height;
}



bool Texture::getTextureParams()
{
  // If a valid ID, set it up
  if (id > 0)
  {
    int mipLevel = 0;
    glBindTexture(GL_TEXTURE_2D, id);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &height);
    return true;
  }

  return false;
}