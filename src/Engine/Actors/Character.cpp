#include "Character.h"
#include "../Engine.h"


Character::Character()
{
  // Initialize walkAnimation
  walkAnimation = WalkAnimation(&sprite, isPlayer);
}


Character::Character(Sprite _sprite)
{
  sprite = _sprite;
  hasSprite = true;

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale());
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction
}


Character::Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset)
{
  sprite = _sprite;
  hasSprite = true;

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


WalkAnimation& Character::getWalkAnimation()
{
  return walkAnimation;
}


void Character::setSprite(Sprite _sprite)
{
  sprite = _sprite;
  hasSprite = true;
  //sprite.moveTo( *(_sprite.getPos()) );
}


int Character::setRB()
{
  // Check that the sprite was set
  if (!hasSprite)
  {
    return -1;
  }

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale());
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction

  return 0;
}


int Character::setRB(Vector3D rectSizeOffset, Vector3D rectPosOffset)
{
  // Check that the sprite was set
  if (!hasSprite)
  {
    return -1;
  }

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale() * rectSizeOffset);  // Scale the boundingRect
  boundingRect.moveBy(rectPosOffset);                                             // Move the boundingRect
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction

  return 0;
}


// Note: Call this function if the character is the player PRIOR to setting any animation
void Character::setPlayerStatus(bool _isPlayer)
{
  isPlayer = _isPlayer;
}