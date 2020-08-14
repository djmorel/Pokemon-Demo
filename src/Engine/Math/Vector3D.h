#ifndef VECTOR3D_H
#define VECTOR3D_H


class Vector3D
{
  public:
    // Constructors
    Vector3D();
    Vector3D(float _x);
    Vector3D(float _x, float _y, float _z);
    Vector3D(const Vector3D &other);

    // Overloading operators
    Vector3D& operator= (const Vector3D& other);
    Vector3D operator+(const Vector3D& other);
    Vector3D operator-(const Vector3D& other);
    Vector3D operator*(const Vector3D& other);
    Vector3D operator*(float _x);
    bool operator==(const Vector3D& other);
    bool operator!=(const Vector3D& other);

    // Functions for the Separating Axis Theorem
    static float dot(const Vector3D& a, const Vector3D& b);
    static Vector3D project(const Vector3D& a, const Vector3D& b);

    // Make members public for easier access
    float x;
    float y;
    float z;
};


#endif