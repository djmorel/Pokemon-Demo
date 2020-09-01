#ifndef VECTOR3D_H
#define VECTOR3D_H


// Serves as a data type to group 3 related values (i.e. 3D coordinates).
class Vector3D
{
  public:
    /**
      A constructor that initializes a default Vector3D where x, y and z are 0.
      \param None
      \return None
    **/
    Vector3D();

    /**
      A constructor that initializes a Vector3D's x, y, and z values to _x.
      \param float _x --> Value to set x, y, and z to.
      \return None
    **/
    Vector3D(float _x);

    /**
      A constructor that initializes a Vector3D's x value to _x, y value to _y, and z value to _z.
      \param float _x --> Value to set x to.
      \param float _y --> Value to set y to.
      \param float _z --> Value to set z to.
      \return None
    **/
    Vector3D(float _x, float _y, float _z);

    /**
      A constructor that initializes a Vector3D's x, y, and z values to that of another Vector3D object.
      \param Vector3D& other --> Reference of another Vector2D object.
      \return None
    **/
    Vector3D(const Vector3D& other);

    // Overloading Mathematical Operators
    Vector3D& operator=(const Vector3D& other);
    Vector3D operator+(const Vector3D& other);
    Vector3D operator-(const Vector3D& other);
    Vector3D operator*(const Vector3D& other);
    Vector3D operator*(float _x);
    Vector3D operator/(const Vector3D& other);
    Vector3D operator/(float _x);

    // Overloading Logical Operators
    bool operator==(const Vector3D& other);
    bool operator!=(const Vector3D& other);

    /**
      Computes the Dot Product between 2 Vector3D objects. Used for detecting collisions via the Separating Axis Theorem.
      \param Vector3D& a --> Reference to the first Vector3D object.
      \param Vector3D& b --> Reference to the second Vector3D object.
      \return Dot Product of a and b as a float.
    **/
    static float dot(const Vector3D& a, const Vector3D& b);

    /**
      Computes the Projection of Vector3D a onto Vector3D b. Used for detecting collisions via the Separating Axis Theorem.
      \param Vector3D& a --> Reference to the first Vector3D object.
      \param Vector3D& b --> Reference to the second Vector3D object.
      \return Projection of a onto b as a float.
    **/
    static Vector3D project(const Vector3D& a, const Vector3D& b);

    // Public since Vector2D is just a special data type
    float x;  // Vector3D's x value
    float y;  // Vector3D's y value
    float z;  // Vector3D's z value
};


#endif