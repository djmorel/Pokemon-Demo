#include "Entity.h"
#include "../Math/Rect.h"


Entity::Entity()
{
  sprite = Sprite("Assets/Art/DefaultObj.png");
}


Entity::Entity(std::string assetName)
{
  sprite = Sprite(assetName);
}


Entity::Entity(int _id)
{
  sprite = Sprite(_id);
}


Entity::Entity(std::string assetName, Vector3D _pos, float _rot, float _scale)
{
  sprite = Sprite(assetName, _pos, _rot, _scale);

  // Configure the Rect
  Rect rc = Rect();
  rc.setSize(Vector3D(sprite.getSize()->x * sprite.getScale()->x, sprite.getSize()->y * sprite.getScale()->y, 1));

  rb = RigidBody();
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 0, rc);
}


Entity::Entity(int _id, Vector3D _pos, float _rot, float _scale)
{
  sprite = Sprite(_id, _pos, _rot, _scale);

  // Configure the Rect
  Rect rc = Rect();
  rc.setSize(Vector3D(sprite.getSize()->x * sprite.getScale()->x, sprite.getSize()->y * sprite.getScale()->y, 1));

  rb = RigidBody();
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 0, rc);
}


Vector2D Entity::getDimensions()
{
  return Vector2D(sprite.getSize()->x * sprite.getScale()->x, sprite.getSize()->x * sprite.getScale()->y);
}


Vector3D Entity::getPos()
{
  return Vector3D(sprite.getPos()->x, sprite.getPos()->y, sprite.getPos()->z);
}


Sprite& Entity::getSprite()
{
  return sprite;
}


void Entity::Update()
{
  rb.Update();
}


void Entity::Render()
{
  sprite.Render();
  rb.Render(Vector3D(0.51f, 0.86f, 0.87f));  // Light-Blue rigid body
}