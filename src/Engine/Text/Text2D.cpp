#include "Text2D.h"
#include "../Math/Vector2D.h"
//#include <GL/glew.h>
//#include "FancyTexture.h"
#include <vector>


// Constructor that initializes a particular texture font
Text2D::Text2D()
{
  // Initialize the default font
  //initText2D("src/Engine/Text/SampleFont.png");
}


Text2D::~Text2D()
{
  // Destructor stuff
}


void Text2D::Update()
{
  // Do stuff
}


void Text2D::Render()
{
  // Do stuff
}


void Text2D::initText2D(const char* texturePath)
{

  /*
  // Set the texture
  unsigned int TextureID = loadDDS(texturePath);

  // Initialize VBO
  glGenBuffers(1, &VertexBufferID);  // We get an unauthorized access here... GLEW is initialized, but we still face problems...
  glGenBuffers(1, &UVBufferID);
  */
}


void Text2D::printText2D(std::string text, int x, int y, int size)
{

  /*
  std::vector<Vector2D> vertices;
  std::vector<Vector2D> UVs;

  // I already know the number of rows and columns
  int rows = 16;  // In the y direction
  int cols = 16;  // In the x direction

  // Compute the coordinates of the 4 vertices that will define our quad
  for (unsigned int i = 0; i < text.size(); i++)
  {
    Vector2D vertex_up_left    = Vector2D(x + i * size       , y + size);
    Vector2D vertex_up_right   = Vector2D(x + i * size + size, y + size);
    Vector2D vertex_down_right = Vector2D(x + i * size + size, y       );
    Vector2D vertex_down_left  = Vector2D(x + i * size       , y + size);

    // Add the vertices to the vertices vector in groups of 3 (shapes here are triangles)
    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );

    vertices.push_back(vertex_down_right);
    vertices.push_back(vertex_up_right  );
    vertices.push_back(vertex_down_left );

    // Get the character we are trying to print
    char character = text[i];
    float uv_x = (character % cols) / (float)cols;
    float uv_y = (character / rows) / (float)rows;

    // Compute the UVs
    Vector2D uv_up_left    = Vector2D(uv_x              , 1.0f - uv_y              );
    Vector2D uv_up_right   = Vector2D(uv_x + 1.0f / cols, 1.0f - uv_y              );
    Vector2D uv_down_right = Vector2D(uv_x + 1.0f / cols, 1.0f - uv_y + 1.0f / rows);
    Vector2D uv_down_left  = Vector2D(uv_x              , 1.0f - uv_y + 1.0f / rows);

    // Add the UVs to the UVs vector (in the triangle formation again)
    UVs.push_back(uv_up_left   );
    UVs.push_back(uv_down_left );
    UVs.push_back(uv_up_right  );

    UVs.push_back(uv_down_right);
    UVs.push_back(uv_up_right  );
    UVs.push_back(uv_down_left );
  }

  // Bind and fill the buffers
  glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector2D), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, UVBufferID);
  glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(Vector2D), &UVs[0], GL_STATIC_DRAW);

  // Bind the texture
  glActiveTexture(GL_TEXTURE0);  // How necessary is this?
  glBindTexture(GL_TEXTURE_2D, TextureID);

  // Enable, bind, & configure the vertex attributes (vertices)
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Enable, bind, & configure the vertex attributes (UVs)
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, UVBufferID);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Draw call
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  // Disable calls
  glDisable(GL_BLEND);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  */
}


void Text2D::cleanupText2D()
{

  /*
  // Delete the buffers
  glDeleteBuffers(1, &VertexBufferID);
  glDeleteBuffers(1, &UVBufferID);
  */
}