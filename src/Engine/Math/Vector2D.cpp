#include "Vector2D.h"
#include <math.h>



Vector2D::Vector2D()
{
  x = 0;
  y = 0;
}



Vector2D::Vector2D(float _x)
{
  x = _x;
  y = _x;
}



Vector2D::Vector2D(float _x, float _y)
{
  x = _x;
  y = _y;
}



Vector2D::Vector2D(const Vector2D& other)
{
  x = other.x;
  y = other.y;
}



Vector2D& Vector2D::operator=(const Vector2D& other)
{
  x = other.x;
  y = other.y;

  return *this;
}



Vector2D Vector2D::operator+(const Vector2D& other)
{
  Vector2D ret;

  ret.x = x + other.x;
  ret.y = y + other.y;

  return ret;
}



Vector2D Vector2D::operator-(const Vector2D& other)
{
  Vector2D ret;

  ret.x = x - other.x;
  ret.y = y - other.y;

  return ret;
}



Vector2D Vector2D::operator*(const Vector2D& other)
{
  Vector2D ret;

  ret.x = x * other.x;
  ret.y = y * other.y;

  return ret;
}



Vector2D Vector2D::operator*(float _x)
{
  Vector2D ret;

  ret.x = x * _x;
  ret.y = y * _x;

  return ret;
}



Vector2D Vector2D::operator/(const Vector2D& other)
{
  Vector2D ret;

  ret.x = x / other.x;
  ret.y = y / other.y;

  return ret;
}



Vector2D Vector2D::operator/(float _x)
{
  Vector2D ret;

  ret.x = x / _x;
  ret.y = y / _x;

  return ret;
}



bool Vector2D::operator==(const Vector2D& other)
{
  return (x == other.x && y == other.y);
}



bool Vector2D::operator!=(const Vector2D& other)
{
  return !operator==(other);
}



float Vector2D::dot(const Vector2D& a, const Vector2D& b)
{
  return (a.x * b.x + a.y * b.y);
}



Vector2D Vector2D::project(const Vector2D& a, const Vector2D& b)
{
  // Projects vector a onto vector b
  return Vector2D( (Vector2D::dot(a, b) / ((float)pow(b.x, 2) + (float)pow(b.y, 2))) * b.x,
                   (Vector2D::dot(a, b) / ((float)pow(b.x, 2) + (float)pow(b.y, 2))) * b.y);
}