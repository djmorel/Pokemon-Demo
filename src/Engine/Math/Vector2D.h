#ifndef VECTOR2D_H
#define VECTOR2D_H


class Vector2D
{
public:
  // Constructors
  Vector2D();
  Vector2D(float _x);
  Vector2D(float _x, float _y);
  Vector2D(const Vector2D& other);

  // Overloading operators
  Vector2D& operator=(const Vector2D& other);
  Vector2D operator+(const Vector2D& other);
  Vector2D operator-(const Vector2D& other);
  Vector2D operator*(const Vector2D& other);
  Vector2D operator*(float _x);
  bool operator==(const Vector2D& other);
  bool operator!=(const Vector2D& other);

  // Functions for the Separating Axis Theorem
  static float dot(const Vector2D& a, const Vector2D& b);
  static Vector2D project(const Vector2D& a, const Vector2D& b);

  // Make members public for easier access
  float x;
  float y;
};


#endif
