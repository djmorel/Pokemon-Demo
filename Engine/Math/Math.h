#ifndef MATH_H
#define MATH_H


#include "Vector3D.h"
#include <vector>


#define PI 3.14159


namespace Math
{
  double deg2rad(double degrees);
  double rad2deg(double radians);
  Vector3D rotatePoint(Vector3D point, Vector3D pivot, float rot);
  float min(std::vector<float> x);
  float max(std::vector<float> x);
  float abs(float x);
}


#endif