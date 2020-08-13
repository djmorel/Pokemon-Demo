#include "ImmovableObject.h"
#include "../Math/Rect.h"


ImmovableObject::ImmovableObject()
{
  objSprite = Sprite("Assets/Art/DefaultObj.png");
}


ImmovableObject::ImmovableObject(std::string assetName)
{
  objSprite = Sprite(assetName);
}


ImmovableObject::ImmovableObject(int _id)
{
  objSprite = Sprite(_id);
}


ImmovableObject::ImmovableObject(std::string assetName, Vector3D _pos, float _rot, float _scale)
{
  objSprite = Sprite(assetName, _pos, _rot, _scale);

  // Configure the Rect
  Rect rc = Rect();
  rc.setSize(Vector3D(objSprite.getSize()->x * objSprite.getScale()->x, objSprite.getSize()->y * objSprite.getScale()->y, 1));

  rb = RigidBody();
  rb.Initialize(objSprite.getPos(), objSprite.getRot(), objSprite.getScale(), objSprite.getSize(), 0, 0, rc);
}


ImmovableObject::ImmovableObject(int _id, Vector3D _pos, float _rot, float _scale)
{
  objSprite = Sprite(_id, _pos, _rot, _scale);

  // Configure the Rect
  Rect rc = Rect();
  rc.setSize(Vector3D(objSprite.getSize()->x * objSprite.getScale()->x, objSprite.getSize()->y * objSprite.getScale()->y, 1));

  rb = RigidBody();
  rb.Initialize(objSprite.getPos(), objSprite.getRot(), objSprite.getScale(), objSprite.getSize(), 0, 0, rc);
}


Vector2D ImmovableObject::getDimensions()
{
  return Vector2D(objSprite.getSize()->x * objSprite.getScale()->x, objSprite.getSize()->x * objSprite.getScale()->y);
}


Vector3D ImmovableObject::getPos()
{
  return Vector3D(objSprite.getPos()->x, objSprite.getPos()->y, objSprite.getPos()->z);
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