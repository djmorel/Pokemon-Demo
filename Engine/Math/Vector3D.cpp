#include "Vector3D.h"


Vector3D::Vector3D()
{
  x = 0;
  y = 0;
  z = 0;
}


Vector3D::Vector3D(const Vector3D& other)
{
  x = other.x;
  y = other.y;
  z = other.z;
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

  ret.x *= _x;
  ret.y *= _x;
  ret.z *= _x;

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