#include "Vector3D.h"
#include <math.h>



Vector3D::Vector3D()
{
  x = 0;
  y = 0;
  z = 0;
}



Vector3D::Vector3D(float _x)
{
  x = _x;
  y = _x;
  z = _x;
}



Vector3D::Vector3D(float _x, float _y, float _z)
{
  x = _x;
  y = _y;
  z = _z;
}



Vector3D::Vector3D(const Vector3D& other)
{
  x = other.x;
  y = other.y;
  z = other.z;
}



Vector3D& Vector3D::operator=(const Vector3D& other)
{
  x = other.x;
  y = other.y;
  z = other.z;

  return *this;
}



Vector3D Vector3D::operator+(const Vector3D& other)
{
  Vector3D ret;

  ret.x = x + other.x;
  ret.y = y + other.y;
  ret.z = z + other.z;

  return ret;
}



Vector3D Vector3D::operator-(const Vector3D& other)
{
  Vector3D ret;

  ret.x = x - other.x;
  ret.y = y - other.y;
  ret.z = z - other.z;

  return ret;
}



Vector3D Vector3D::operator*(const Vector3D& other)
{
  Vector3D ret;

  ret.x = x * other.x;
  ret.y = y * other.y;
  ret.z = z * other.z;

  return ret;
}



Vector3D Vector3D::operator*(float _x)
{
  Vector3D ret;

  ret.x = x * _x;
  ret.y = y * _x;
  ret.z = z * _x;

  return ret;
}



Vector3D Vector3D::operator/(const Vector3D& other)
{
  Vector3D ret;

  ret.x = x / other.x;
  ret.y = y / other.y;
  ret.z = z / other.z;

  return ret;
}



Vector3D Vector3D::operator/(float _x)
{
  Vector3D ret;

  ret.x = x / _x;
  ret.y = y / _x;
  ret.z = z / _x;

  return ret;
}



bool Vector3D::operator==(const Vector3D& other)
{
  return (x == other.x && y == other.y && z == other.z);
}



bool Vector3D::operator!=(const Vector3D& other)
{
  return !operator==(other);
}



float Vector3D::dot(const Vector3D& a, const Vector3D& b)
{
  return (a.x * b.x + a.y * b.y);
}



Vector3D Vector3D::project(const Vector3D& a, const Vector3D& b)
{
  // Projects vector a onto vector b
  return Vector3D( (Vector3D::dot(a, b) / ( (float)pow(b.x, 2) + (float)pow(b.y, 2) )) * b.x,
                   (Vector3D::dot(a, b) / ( (float)pow(b.x, 2) + (float)pow(b.y, 2) )) * b.y,
                   0);
}