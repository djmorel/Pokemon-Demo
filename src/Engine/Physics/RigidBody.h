#ifndef RIGIDBODY_H
#define RIGIDBODY_H


#include "../Math/Vector3D.h"
#include "../Math/Rect.h"


// Class that adds physics to a Sprite. Assign RigidBody data to match its associated Sprite.
class RigidBody
{
  public:
    /**
      A constructor that initializes a default RigidBody.
      \param None
      \return None
    **/
    RigidBody();

    /**
      Initializes a RigidBody to that of the passed parameters.
      \param Vector3D* _pos --> Pointer to the Sprite's position.
      \param float* _rot --> Pointer to the Sprite's rotation.
      \param Vector3D* _scale --> Pointer to the Sprite's scale.
      \param Vector3D* _size --> Pointer to the Sprite's size.
      \param float _gravity --> Gravity to act upon the RigidBody.
      \param float _friction --> Friction to act upon the RigidBody.
      \param Rect _boundingRect --> Definines the boundaries of the RigidBody (may not match Sprite's appeared dimensions).
      \return None
    **/
    void Initialize(Vector3D* _pos, float* _rot, Vector3D* _scale, Vector3D* _size, float _gravity, float _friction, Rect _boundingRect);

    /**
      Updates RigidBody based on the applied Physics and changes in the vertices' position.
      \param None
      \return None
    **/
    void Update();

    /**
      Renders the RigidBody's outlines as defined by its bounding Rect.
      \param Vector3D c --> RGB values for the bounding Rect's outlines.
      \return None
    **/
    void Render(Vector3D c);

    /**
      Gets the RigidBody's current velocity.
      \param None
      \return Vector3D value representing the velocity.
    **/
    Vector3D getVelocity();

    /**
      Gets the RigidBody's position.
      \param None
      \return Vector3D pointer to the RigidBody's position.
    **/
    Vector3D* getPos();

    /**
      Adds a force to the RigidBody's velocity.
      \param Vector3D force --> Force to add.
      \return None
    **/
    void addForce(Vector3D force);

    /**
      Sets the RigidBody's velocity to a set amount.
      \param Vector3D _velocity --> Velocity to set for the RigidBody.
      \return None
    **/
    void setVelocity(Vector3D _velocity);

    /**
      Determines if 2 RigidBodies collide via the Separating Axis Theorem. Static function so any class can call it.
      \param const RigidBody& rbA --> Reference to the first RigidBody.
      \param const RigidBody& rbB --> Reference to the second RigidBody.
      \return True if the RigidBodies are currently colliding, or False if not.
    **/
    static bool isColliding(const RigidBody& rbA, const RigidBody& rbB);


  private:
    Vector3D* pos;      // Pointer to the associated Sprite's position
    float* rot;         // Pointer to the associated Sprite's rotation
    float lastRot;      // Record of the last rotation
    Vector3D* scale;    // Pointer to the associated Sprite's scale
    Vector3D* size;     // Pointer to the associated Sprite's size
    float gravity;      // Gravity that acts upon this RigidBody
    float friction;     // Friction that acts upon this RigidBody
    Vector3D velocity;  // RigidBody's velocity
    Rect boundingRect;  // RigidBody's Rect object (defines its own vertices so it doesn't have to match that of the associated Sprite)
};


#endif