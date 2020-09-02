#include "RigidBody.h"
#include "../Engine.h"
#include "../Math/Math.h"
#include <vector>



RigidBody::RigidBody()
{
  pos = nullptr;
  rot = nullptr;
  scale = nullptr;
  gravity = 0;
  friction = 1;  // Means no friction -> velocity.x *= friction
  velocity = 0;
}



void RigidBody::Initialize(Vector3D* _pos, float* _rot, Vector3D* _scale, Vector3D* _size, float _gravity, float _friction, Rect _boundingRect)
{
  pos = _pos;
  rot = _rot;
  lastRot = *rot;
  scale = _scale;
  size = _size;
  gravity = _gravity;
  friction = _friction;
  velocity = 0;
  boundingRect = _boundingRect;
}



void RigidBody::Update()
{
  velocity.x *= friction;
  velocity.y += gravity;

  *pos = *pos + (velocity * Engine::getDT());

  if (lastRot != *rot)
  {
    // Replaces OpenGL's glRotate() function
    boundingRect.setLowerLeftVertex( Math::rotatePoint( boundingRect.getLowerLeftVertex(), Vector3D(0), *rot - lastRot) );
    boundingRect.setLowerRightVertex(Math::rotatePoint(boundingRect.getLowerRightVertex(), Vector3D(0), *rot - lastRot) );
    boundingRect.setUpperLeftVertex( Math::rotatePoint( boundingRect.getUpperLeftVertex(), Vector3D(0), *rot - lastRot) );
    boundingRect.setUpperRightVertex(Math::rotatePoint(boundingRect.getUpperRightVertex(), Vector3D(0), *rot - lastRot) );
    lastRot = *rot;
  }
}



void RigidBody::Render(Vector3D c)
{
  glLoadIdentity();
  glTranslatef(pos->x, pos->y, pos->z);
  //glRotatef(*rot, 0, 0, 1);  // Uneeded since we manually did that
  //glScalef(scale->x, scale->y, scale->z);

  // Rendering
  glColor4f(c.x, c.y, c.z, 1);  // Set asset color to white in case some other code changed it (set to 0 for no visibility)
  glBegin(GL_LINES);            // Begin rendering as lines
  {
    // Note: Drawing lines come in pairs (NOT the same as drawing full sprites)

    // Draw line from bottom left to bottom right
    glVertex2f(boundingRect.getLowerLeftVertex().x, boundingRect.getLowerLeftVertex().y);
    glVertex2f(boundingRect.getLowerRightVertex().x, boundingRect.getLowerRightVertex().y);

    // Draw line from bottom right to top right
    glVertex2f(boundingRect.getLowerRightVertex().x, boundingRect.getLowerRightVertex().y);
    glVertex2f(boundingRect.getUpperRightVertex().x, boundingRect.getUpperRightVertex().y);

    // Draw line from top right to top left
    glVertex2f(boundingRect.getUpperRightVertex().x, boundingRect.getUpperRightVertex().y);
    glVertex2f(boundingRect.getUpperLeftVertex().x, boundingRect.getUpperLeftVertex().y);

    // Draw line from top left to bottom left
    glVertex2f(boundingRect.getUpperLeftVertex().x, boundingRect.getUpperLeftVertex().y);
    glVertex2f(boundingRect.getLowerLeftVertex().x, boundingRect.getLowerLeftVertex().y);
  }
  glEnd();  // End our drawing
}



Vector3D RigidBody::getVelocity()
{
  return velocity;
}



Vector3D* RigidBody::getPos()
{
  return pos;
}



void RigidBody::addForce(Vector3D force)
{
  velocity = velocity + force;
}



void RigidBody::setVelocity(Vector3D _velocity)
{
  velocity = _velocity;
}



bool RigidBody::isColliding(const RigidBody& rbA, const RigidBody& rbB)
{
  // Get the boundingRects
  Rect rcA = rbA.boundingRect;
  Rect rcB = rbB.boundingRect;

  // Get the vertices
  Vector3D aUR = rcA.getUpperRightVertex() + *rbA.pos;
  Vector3D aUL = rcA.getUpperLeftVertex() + *rbA.pos;
  Vector3D aLR = rcA.getLowerRightVertex() + *rbA.pos;
  Vector3D aLL = rcA.getLowerLeftVertex() + *rbA.pos;
  Vector3D bUR = rcB.getUpperRightVertex() + *rbB.pos;
  Vector3D bUL = rcB.getUpperLeftVertex() + *rbB.pos;
  Vector3D bLR = rcB.getLowerRightVertex() + *rbB.pos;
  Vector3D bLL = rcB.getLowerLeftVertex() + *rbB.pos;

  // Variables to hold the max and min values of the RigidBody scalars
  float aMax = 0;
  float aMin = 0;
  float bMax = 0;
  float bMin = 0;

  // Get the axes perpendicular to the vertices
  Vector3D axis1 = aUR - aUL;
  Vector3D axis2 = aUR - aLR;
  Vector3D axis3 = bUL - bLL;
  Vector3D axis4 = bUL - bUR;

  // Store the axes in a vector for easier manipulation
  std::vector<Vector3D> axes;
  axes.push_back(axis1);
  axes.push_back(axis2);
  axes.push_back(axis3);
  axes.push_back(axis4);

  // Iterate through the axes until we find one that doesn't collide
  for (unsigned int i = 0; i < axes.size(); i++)
  {
    // Project each Rect vertex onto the axis
    Vector3D aURproj = Vector3D::project(aUR, axes[i]);
    Vector3D aULproj = Vector3D::project(aUL, axes[i]);
    Vector3D aLRproj = Vector3D::project(aLR, axes[i]);
    Vector3D aLLproj = Vector3D::project(aLL, axes[i]);
    Vector3D bURproj = Vector3D::project(bUR, axes[i]);
    Vector3D bULproj = Vector3D::project(bUL, axes[i]);
    Vector3D bLRproj = Vector3D::project(bLR, axes[i]);
    Vector3D bLLproj = Vector3D::project(bLL, axes[i]);

    // Get the scalars of a and b
    float aURscalar = Vector3D::dot(aURproj, axes[i]);
    float aULscalar = Vector3D::dot(aULproj, axes[i]);
    float aLRscalar = Vector3D::dot(aLRproj, axes[i]);
    float aLLscalar = Vector3D::dot(aLLproj, axes[i]);
    float bURscalar = Vector3D::dot(bURproj, axes[i]);
    float bULscalar = Vector3D::dot(bULproj, axes[i]);
    float bLRscalar = Vector3D::dot(bLRproj, axes[i]);
    float bLLscalar = Vector3D::dot(bLLproj, axes[i]);

    // Find the min and max of a's scalars
    std::vector<float> aScalars;
    aScalars.push_back(aURscalar);
    aScalars.push_back(aULscalar);
    aScalars.push_back(aLRscalar);
    aScalars.push_back(aLLscalar);
    aMin = Math::min(aScalars);
    aMax = Math::max(aScalars);

    // Find the min and max of b's scalars
    std::vector<float> bScalars;
    bScalars.push_back(bURscalar);
    bScalars.push_back(bULscalar);
    bScalars.push_back(bLRscalar);
    bScalars.push_back(bLLscalar);
    bMin = Math::min(bScalars);
    bMax = Math::max(bScalars);

    // Check if the bounds of a and b overlap
    if ( !(bMin <= aMax && bMax >= aMin) )
    {
      // There's a gap, so no collision
      return false;
    }
  }

  // Never found a gap, so collision
  return true;
}