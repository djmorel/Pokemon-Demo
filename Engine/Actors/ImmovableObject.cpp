#include "ImmovableObject.h"
#include "../Math/Rect.h"


ImmovableObject::ImmovableObject()
{
  objSprite = Sprite("Assets/Art/DefaultObj.png");
}


ImmovableObject::ImmovableObject(std::string imagePath)
{
  objSprite = Sprite(imagePath);
}


ImmovableObject::ImmovableObject(std::string imagePath, Vector3D _pos, float rot, float scale)
{
  objSprite = Sprite(imagePath, _pos);
  objSprite.rotateTo(rot);
  objSprite.setScale(scale);

  // Configure the Rect
  Rect rc = Rect();
  rc.setSize(Vector3D(objSprite.getSize()->x * objSprite.getScale()->x, objSprite.getSize()->y * objSprite.getScale()->y, 1));

  rb = RigidBody();
  rb.Initialize(objSprite.getPos(), objSprite.getRot(), objSprite.getScale(), objSprite.getSize(), 0, 0, rc);
}


void ImmovableObject::Update()
{
  rb.Update();
}


void ImmovableObject::Render()
{
  objSprite.Render();
  rb.Render(Vector3D(0.51f, 0.86f, 0.87f));  // Light-Blue rigid body
}
