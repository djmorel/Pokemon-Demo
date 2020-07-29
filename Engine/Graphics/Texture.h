#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include "soil.h"

class Texture
{
  public:
    // 3 Overloaded Constructors
    Texture();
    Texture(int _id);
    Texture(std::string path);

    int GetID();
    int GetWidth();
    int GetHeight();

  private:
    int id;
    int width;
    int height;

    bool GetTextureParams();

};


#endif
