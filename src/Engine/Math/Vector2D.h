#ifndef VECTOR2D_H
#define VECTOR2D_H


// Serves as a data type to group 2 related values (i.e. 2D coordinates).
class Vector2D
{
  public:
    /**
      A constructor that initializes a default Vector2D where x and y are 0.
      \param None
      \return None
    **/
    Vector2D();

    /**
      A constructor that initializes a Vector2D's x and y values to _x.
      \param float _x --> Value to set x and y to.
      \return None
    **/
    Vector2D(float _x);

    /**
      A constructor that initializes a Vector2D's x value to _x and y value to _y.
      \param float _x --> Value to set x to.
      \param float _y --> Value to set y to.
      \return None
    **/
    Vector2D(float _x, float _y);

    /**
      A constructor that initializes a Vector2D's x and y values to that of another Vector2D object.
      \param Vector2D& other --> Reference of another Vector2D object.
      \return None
    **/
    Vector2D(const Vector2D& other);
    
    // Overloading Mathematical Operators
    Vector2D& operator=(const Vector2D& other);
    Vector2D operator+(const Vector2D& other);
    Vector2D operator-(const Vector2D& other);
    Vector2D operator*(const Vector2D& other);
    Vector2D operator*(float _x);
    Vector2D operator/(const Vector2D& other);
    Vector2D operator/(float _x);

    // Overloading Logical Operators
    bool operator==(const Vector2D& other);
    bool operator!=(const Vector2D& other);
    
    /**
      Computes the Dot Product between 2 Vector2D objects. Used for detecting collisions via the Separating Axis Theorem.
      \param Vector2D& a --> Reference to the first Vector2D object.
      \param Vector2D& b --> Reference to the second Vector2D object.
      \return Dot Product of a and b as a float.
    **/
    static float dot(const Vector2D& a, const Vector2D& b);

    /**
      Computes the Projection of Vector2D a onto Vector2D b. Used for detecting collisions via the Separating Axis Theorem.
      \param Vector2D& a --> Reference to the first Vector2D object.
      \param Vector2D& b --> Reference to the second Vector2D object.
      \return Projection of a onto b as a float.
    **/
    static Vector2D project(const Vector2D& a, const Vector2D& b);
    
    // Public since Vector2D is just a special data type
    float x;  // Vector2D's x value
    float y;  // Vector2D's y value
};


#endif
