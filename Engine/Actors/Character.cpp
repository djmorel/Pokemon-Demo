#include "Character.h"


Character::Character()
{
  // Do nothing
}


Character::Character(Sprite _sprite)
{
  sprite = _sprite;
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), -10, 0.9f);
}


void Character::Update()
{
  sprite.Update();
  rb.Update();
}


void Character::Render()
{
  sprite.Render();
  rb.Render(Vector3D(0.51f, 0.86f, 0.87f));  // Light-Blue rigid body
}


Sprite& Character::getSprite()
{
  return sprite;
}


RigidBody& Character::getRB()
{
  return rb;
}