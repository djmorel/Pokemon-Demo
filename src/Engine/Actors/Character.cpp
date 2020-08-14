#include "Character.h"
#include "../Engine.h"


Character::Character()
{
  // Do nothing
  bool isPlayer = false;
}


Character::Character(Sprite _sprite)
{
  sprite = _sprite;
  isPlayer = false;

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale());
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction
}


Character::Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset)
{
  sprite = _sprite;
  isPlayer = false;

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale() * rectSizeOffset);  // Scale the boundingRect
  boundingRect.moveBy(rectPosOffset);                                             // Move the boundingRect
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction
}


Character::~Character()
{
  walkAnimation.~WalkAnimation();
}


void Character::Update()
{
  sprite.Update();
  rb.Update();
}


void Character::Render()
{
  sprite.Render();
  rb.Render(Vector3D(0, 0, 0));  // Black rigid body
  //rb.Render(Vector3D(0.51f, 0.86f, 0.87f));  // Light-Blue rigid body
}


Sprite& Character::getSprite()
{
  return sprite;
}


RigidBody& Character::getRB()
{
  return rb;
}


void Character::setSprite(Sprite _sprite)
{
  sprite = _sprite;
}


void Character::setAsPlayer(bool _isPlayer)
{
  isPlayer = _isPlayer;
}


// Note: MUST call setAsPlayer BEFORE enableWalkAnimation...
void Character::enableWalkAnimation()
{
  walkAnimation = WalkAnimation(&sprite, nullptr, isPlayer);
}