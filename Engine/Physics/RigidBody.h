#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../Math/Vector3D.h"
#include "../Math/Rect.h"


// Class to separate physics from the sprite itself
// Assign RigidBody data to match that of a given sprite
class RigidBody
{
  public:
    RigidBody();

    void Initialize(Vector3D* _pos, float* _rot, Vector3D* _scale, Vector3D* _size, float _gravity, float _friction, Rect _boundingRect);

    void Update();
    void Render(Vector3D c);  // For debugging (accepts RGB color)

    void addForce(Vector3D f);
    Vector3D getVelocity();
    void setVelocity(Vector3D _velocity);

    static bool isColliding(const RigidBody& rbA, const RigidBody& rbB);


  private:
    // Pointers to track sprite data
    Vector3D* pos;
    float* rot;
    float lastRot;
    Vector3D* scale;
    Vector3D* size;

    float gravity;  // Note: could have global gravity for all objects
    float friction;
    Vector3D velocity;

    Rect boundingRect;

};


#endif