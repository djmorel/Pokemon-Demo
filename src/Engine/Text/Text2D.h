#ifndef TEXT2D_H
#define TEXT2D_H


#include "../Engine.h"
#include "../Graphics/Texture.h"
//#include "../Graphics/FancyTexture.h"
#include <string>


class Text2D
{
  public:
    Text2D();
    ~Text2D();

    void Update();
    void Render();

    void initText2D(const char* texturePath);                    // const char* texturePath);
    void printText2D(std::string text, int x, int y, int size);  // const char* text, int x, int y, int size);
    void cleanupText2D();

  private:
    //Texture texture;
    unsigned int TextureID;
    unsigned int VertexBufferID;
    unsigned int UVBufferID;
};

#endif