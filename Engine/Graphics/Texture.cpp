#include "Texture.h"


Texture::Texture()
{
  // Empty constructor for array/vector setup
  id = -1;  // Allows us to set up our texture before we draw it
}


Texture::Texture(int _id)
{
  id = _id;

  if (!GetTextureParams())
  {
    std::cout << "Error loading image with ID: " << id << std::endl;
  }
}


Texture::Texture(std::string path)
{
  // Load a texture from a path, and give it an ID
  id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA);

  if (!GetTextureParams())
  {
    std::cout << "Error loading image: " << path << std::endl;
  }
}


int Texture::GetID()
{
  return id;
}


int Texture::GetWidth()
{
  return width;
}


int Texture::GetHeight()
{
  return height;
}


bool Texture::GetTextureParams()
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