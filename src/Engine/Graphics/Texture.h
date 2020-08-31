#ifndef TEXTURE_H
#define TEXTURE_H


#include <iostream>
#include <string>
#include "GLFW/glfw3.h"  // In the nupengl package
#include "soil.h"        // In the soil.1.16.0 package


// The image itself. Only handles an OpenGL texture and its data.
class Texture
{
  public:
    /**
      A constructor that configures a placeholder Texture.
      \param None
      \return None
    **/
    Texture();

    /**
      A constructor that configures a Texture based on an OpenGL texture ID.
      \param int _id --> ID representing an OpenGL texture to load.
      \return None
    **/
    Texture(int _id);

    /**
      A constructor that configures a Texture based on image's file path.
      \param std::string path --> Path of the image to load.
      \return None
    **/
    Texture(std::string path);

    /**
      Gets the Texture's id.
      \param None
      \return The Texture's id as an int.
    **/
    int getID();

    /**
      Gets the Texture's width.
      \param None
      \return The Texture's width (in pixels) as an int.
    **/
    int getWidth();

    /**
      Gets the Texture's height.
      \param None
      \return The Texture's height (in pixels) as an int.
    **/
    int getHeight();

  private:
    int id;                   // OpenGL texture load id
    int width;                // Size of Texture's width (in pixels)
    int height;               // Size of Texture's height (in pixels)

    /**
      Binds a Texture from its current id, and saves its parameters into Texture::width and Texture::height.
      \param None
      \return True if successfully configured the parameters, or False if not.
    **/
    bool getTextureParams();
};


#endif