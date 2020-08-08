#include "ImmovableObject.h"
#include "../Math/Rect.h"


Sprite* ImmovableObject::objSprite_ptr = nullptr;


void ImmovableObject::Initialize()
{
  objSprite_ptr = new Sprite("DirtBlock");
  objSprite_ptr->setScale(0.8f);
}


ImmovableObject::ImmovableObject()
{
  /*
  if (objSprite_ptr == nullptr)
  {
    std::cout << "Error: Trying to instantiate an ImmovableObject without calling Initialize()" << std::endl;
    return;
  }
  */
  objSprite = Sprite("Assets/Art/DefaultObj.png");
  //objSprite = Sprite(*objSprite_ptr);
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


Vector2D ImmovableObject::getDimensions()
{
  return Vector2D(objSprite.getSize()->x * objSprite.getScale()->x, objSprite.getSize()->x * objSprite.getScale()->y);
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