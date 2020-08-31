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
  configRB();
}



Entity::Entity(int _id, Vector3D _pos, float _rot, float _scale)
{
  sprite = Sprite(_id, _pos, _rot, _scale);
  configRB();
}



void Entity::Update()
{
  sprite.Update();
  rb.Update();
}



void Entity::Render()
{
  sprite.Render();
  rb.Render(Vector3D(0.51f, 0.86f, 0.87f));  // Light-Blue rigid body
}



Vector2D Entity::getDimensions()
{
  return Vector2D(sprite.getSize()->x * sprite.getScale()->x, sprite.getSize()->x * sprite.getScale()->y);
}



Sprite& Entity::getSprite()
{
  return sprite;
}



void Entity::setDimensions(Vector3D v)
{
  // Set the sprite dimensions, then update the rigid body
  sprite.setDimensions(v);
  configRB();
}



void Entity::configRB()
{
  // Configure the Rect
  Rect rc = Rect();
  rc.setSize(*sprite.getSize() * *sprite.getScale());

  rb = RigidBody();
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, rc);
}