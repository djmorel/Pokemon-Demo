#ifndef RECT_H
#define RECT_H


#include "Vector3D.h"


// Tracks the vertices of a RigidBody.
class Rect
{
  public:
    /**
      A constructor that initializes a default Rect and updates its vertices.
      \param None
      \return None
    **/
    Rect();

    /**
      A constructor that initializes a Rect with a particular size, and updates its vertices.
      \param Vector3D _size --> Size for the Rect.
      \return None
    **/
    Rect(Vector3D _size);

    /**
      A constructor that initializes a Rect with a particular position and size, and updates its vertices.
      \param Vector3d _pos --> Position for the Rect.
      \param Vector3D _size --> Size for the Rect.
      \return None
    **/
    Rect(Vector3D _pos, Vector3D _size);

    /**
      Moves the Rect by a specified amount, and updates its vertices.
      \param Vector3d by --> Position to move by.
      \return None
    **/
    void moveBy(Vector3D by);

    /**
      Moves the Rect to a particular location, and updates its vertices.
      \param Vector3d to --> Position to move to.
      \return None
    **/
    void moveTo(Vector3D to);

    /**
      Sets the Rect's size to a specified amount, and updates its vertices.
      \param Vector3d _size --> Size for the Rect.
      \return None
    **/
    void setSize(Vector3D _size);

    /**
      Gets the Rect's upper left vertex position.
      \param None
      \return Position of the vertex.
    **/
    Vector3D getUpperLeftVertex();

    /**
      Gets the Rect's upper right vertex position.
      \param None
      \return Position of the vertex.
    **/
    Vector3D getUpperRightVertex();

    /**
      Gets the Rect's lower left vertex position.
      \param None
      \return Position of the vertex.
    **/
    Vector3D getLowerLeftVertex();

    /**
      Gets the Rect's lower right vertex position.
      \param None
      \return Position of the vertex.
    **/
    Vector3D getLowerRightVertex();

    /**
      Sets the Rect's upper left vertex to a specified position.
      \param Vector3D _pos --> Position to set the vertex to.
      \return None
    **/
    void setUpperLeftVertex(Vector3D _pos);

    /**
      Sets the Rect's upper right vertex to a specified position.
      \param Vector3D _pos --> Position to set the vertex to.
      \return None
    **/
    void setUpperRightVertex(Vector3D _pos);

    /**
      Sets the Rect's lower left vertex to a specified position.
      \param Vector3D _pos --> Position to set the vertex to.
      \return None
    **/
    void setLowerLeftVertex(Vector3D _pos);

    /**
      Sets the Rect's lower right vertex to a specified position.
      \param Vector3D _pos --> Position to set the vertex to.
      \return None
    **/
    void setLowerRightVertex(Vector3D _pos);


  private:
    Vector3D pos;               // Position of the Rect with respect to the GLFW window
    Vector3D size;              // Size of the Rect
    Vector3D upperLeftVertex;   // Position of the Rect's upper left vertex with respect to the GLFW window
    Vector3D upperRightVertex;  // Position of the Rect's upper right vertex with respect to the GLFW window
    Vector3D lowerLeftVertex;   // Position of the Rect's lower left vertex with respect to the GLFW window
    Vector3D lowerRightVertex;  // Position of the Rect's lower right vertex with respect to the GLFW window

    /**
      Updates the Rect's vertices according to its position and size.
      \param None
      \return None
    **/
    void UpdateVertices();
};


#endif