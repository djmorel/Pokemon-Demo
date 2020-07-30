#ifndef TEXTURE_H
#define TEXTURE_H


#include <iostream>
#include <string>
#include "GLFW/glfw3.h"
#include "soil.h"


// Only handles OpenGL texture and its data
class Texture
{
  public:
    // 3 Overloaded Constructors
    Texture();
    Texture(int _id);
    Texture(std::string path);

    int getID();
    int getWidth();
    int getHeight();

  private:
    int id;
    int width;
    int height;

    bool getTextureParams();

};


#endif