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



Vector3D Rect::getUpperLeftVertex()
{
  return upperLeftVertex;
}



Vector3D Rect::getUpperRightVertex()
{
  return upperRightVertex;
}



Vector3D Rect::getLowerLeftVertex()
{
  return lowerLeftVertex;
}



Vector3D Rect::getLowerRightVertex()
{
  return lowerRightVertex;
}



void Rect::setUpperLeftVertex(Vector3D _pos)
{
  upperLeftVertex = _pos;
}



void Rect::setUpperRightVertex(Vector3D _pos)
{
  upperRightVertex = _pos;
}



void Rect::setLowerLeftVertex(Vector3D _pos)
{
  lowerLeftVertex = _pos;
}



void Rect::setLowerRightVertex(Vector3D _pos)
{
  lowerRightVertex = _pos;
}



void Rect::UpdateVertices()
{
  upperLeftVertex  = Vector3D(pos.x - (size.x / 2), pos.y + (size.y / 2), 0);
  upperRightVertex = Vector3D(pos.x + (size.x / 2), pos.y + (size.y / 2), 0);
  lowerLeftVertex  = Vector3D(pos.x - (size.x / 2), pos.y - (size.y / 2), 0);
  lowerRightVertex = Vector3D(pos.x + (size.x / 2), pos.y - (size.y / 2), 0);
}