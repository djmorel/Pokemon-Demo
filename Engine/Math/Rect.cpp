#include "Rect.h"


Rect::Rect()
{
  pos = Vector3D(0);
  size = Vector3D(0);
  UpdateVertices();
}


Rect::Rect(Vector3D _size)
{
  pos = Vector3D(0);
  size = _size;
  UpdateVertices();
}


Rect::Rect(Vector3D _pos, Vector3D _size)
{
  pos = _pos;
  size = _size;
  UpdateVertices();
}


void Rect::moveBy(Vector3D by)
{
  pos = pos + by;
  UpdateVertices();
}


void Rect::moveTo(Vector3D to)
{
  pos = to;
  UpdateVertices();
}


void Rect::setSize(Vector3D _size)
{
  size = _size;
  UpdateVertices();
}


void Rect::UpdateVertices()
{
  upperLeftVertex  = Vector3D(pos.x - (size.x / 2), pos.y + (size.y / 2), 0);
  upperRightVertex = Vector3D(pos.x + (size.x / 2), pos.y + (size.y / 2), 0);
  lowerLeftVertex  = Vector3D(pos.x - (size.x / 2), pos.y - (size.y / 2), 0);
  lowerRightVertex = Vector3D(pos.x + (size.x / 2), pos.y - (size.y / 2), 0);
}