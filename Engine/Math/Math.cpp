#include "Math.h"
#include <math.h>


namespace Math
{
  double deg2rad(double degrees)
  {
    return (degrees * PI) / 180;
  }

  double rad2deg(double radians)
  {
    return (radians * 180) / PI;
  }

  Vector3D rotatePoint(Vector3D point, Vector3D pivot, float rot)
  {
    // Find sin and cos at the rotation theta
    double radRot = deg2rad(rot);
    double s = sin(radRot);
    double c = cos(radRot);

    // Get the points at the pivot
    point = point - pivot;

    // Get the new x and y values
    float newX = (float)(point.x * c - point.y * s);
    float newY = (float)(point.x * s + point.y * c);

    // Add back the pivot to the new x and y values
    point.x = newX + pivot.x;
    point.y = newY + pivot.y;

    return point;
  }


  // Finds the minimum value of the passed vector
  float min(std::vector<float> x)
  {
    // Set the first element as the minimum
    float min = x[0];

    // Iterate through the vector to find the true minimum
    for (unsigned int i = 1; i < x.size(); i++)
    {
      if (x[i] < min)
        min = x[i];
    }

    return min;
  }


  // Finds the maximum value of the passed vector
  float max(std::vector<float> x)
  {
    // Set the first element as the maximum
    float max = x[0];

    // Iterate through the vector to find the true minimum
    for (unsigned int i = 1; i < x.size(); i++)
    {
      if (x[i] > max)
        max = x[i];
    }

    return max;
  }


  float abs(float x)
  {
    if (x > 0)
    {
      return x;
    }
    return -x;
  }

}