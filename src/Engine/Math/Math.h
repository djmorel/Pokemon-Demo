#ifndef MATH_H
#define MATH_H


#include "Vector3D.h"
#include <vector>


#define PI 3.14159


// Provides various mathematical functions.
namespace Math
{
  /**
    Converts an angle in degrees to radians.
    \param double degrees --> Angle in degrees.
    \return An angle in radians as a double.
  **/
  double deg2rad(double degrees);

  /**
    Converts an angle in radians to degrees.
    \param double radians --> Angle in radians.
    \return An angle in degrees as a double.
  **/
  double rad2deg(double radians);

  /**
    Determines a point's position (vertex) after a rotation about a pivot. Assumes rotation about the z-axis. Replaces OpenGL's glRotate() for boundingRects.
    \param Vector3D point --> A point/vertex to be rotated.
    \param Vector3D pivot --> Location of the pivot point.
    \param float rot --> How much is the pivot point rotated.
    \return The new position of the point/vertex after rotating about the pivot.
  **/
  Vector3D rotatePoint(Vector3D point, Vector3D pivot, float rot);

  /**
    Searches a float vector for the minimum element.
    \param std::vector<float> x --> Vector to search.
    \return Min float value from the vector.
  **/
  float min(std::vector<float> x);

  /**
    Searches a float vector for the maximum element.
    \param std::vector<float> x --> Vector to search.
    \return Max float value from the vector.
  **/
  float max(std::vector<float> x);

  /**
    Calculates the absolute value of the passed value.
    \param float x --> Value to calculate the absolute value for.
    \return Absolute value of x as a float.
  **/
  float abs(float x);
}


#endif