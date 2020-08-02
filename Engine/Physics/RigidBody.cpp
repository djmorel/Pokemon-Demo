#include "RigidBody.h"
#include "../Engine.h"


RigidBody::RigidBody()
{
  pos = nullptr;
  rot = nullptr;
  scale = nullptr;
  gravity = 0;
  friction = 1;  // Means no friction -> velocity.x *= friction
  velocity = 0;
}


void RigidBody::Initialize(Vector3D* _pos, float* _rot, Vector3D* _scale, Vector3D* _size, float _gravity, float _friction)
{
  pos = _pos;
  rot = _rot;
  scale = _scale;
  size = _size;
  gravity = _gravity;
  friction = _friction;
  velocity = 0;
}


// TODO: Modify so that Pokemon game doesn't worry about gravity or friction
void RigidBody::Update()
{
  velocity.x *= friction;
  velocity.y += gravity;

  *pos = *pos + (velocity * Engine::getDT());
}


void RigidBody::Render(Vector3D c)
{
  glLoadIdentity();
  glTranslatef(pos->x, pos->y, pos->z);
  glRotatef(*rot, 0, 0, 1);
  glScalef(scale->x, scale->y, scale->z);

  // Rendering
  glColor4f(c.x, c.y, c.z, 1);  // Set asset color to white in case some other code changed it
  glBegin(GL_LINES);            // Begin rendering as lines
  {
    // Note: Drawing lines come in pairs (NOT the same as drawing full sprites)

    // Draw line from bottom left to bottom right
    glVertex2f(0, 0);              // Bottom left
    glVertex2f(size->x, 0);        // Bottom right

    // Draw line from bottom right to top right
    glVertex2f(size->x, 0);        // Bottom right
    glVertex2f(size->x, size->y);  // Top right

    // Draw line from top right to top left
    glVertex2f(size->x, size->y);  // Top right
    glVertex2f(0, size->y);        // Top left

    // Draw line from top left to bottom left
    glVertex2f(0, size->y);        // Top left
    glVertex2f(0, 0);              // Bottom left

  }
  glEnd();  // End our drawing

}


void RigidBody::addForce(Vector3D force)
{
  velocity = velocity + force;
}