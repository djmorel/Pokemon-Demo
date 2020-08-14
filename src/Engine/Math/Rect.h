#ifndef RECT_H
#define RECT_H


#include "Vector3D.h"


// Tracks the vertices of a rigid body
class Rect
{
  public:
    Rect();
    Rect(Vector3D _size);
    Rect(Vector3D _pos, Vector3D _size);

    void moveBy(Vector3D by);
    void moveTo(Vector3D to);
    void setSize(Vector3D _size);

    Vector3D upperLeftVertex;
    Vector3D upperRightVertex;
    Vector3D lowerLeftVertex;
    Vector3D lowerRightVertex;

  private:
    Vector3D pos;
    Vector3D size;

    void UpdateVertices();
};


#endif