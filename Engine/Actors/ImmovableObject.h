#ifndef IMMOVABLEOBJECT_H
#define IMMOVABLEOBJECT_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"


// Static overworld objects (i.e. trees, buildings, fences, etc) that lack animations
class ImmovableObject
{
  public:
    ImmovableObject();
    ImmovableObject(std::string assetName);
    ImmovableObject(int _id);
    ImmovableObject(std::string assetName, Vector3D _pos, float rot, float scale);
    ImmovableObject(int _id, Vector3D _pos, float rot, float scale);

    Vector2D getDimensions();
    Vector3D getPos();

    void Update();
    void Render();

  private:
    Sprite objSprite;
    RigidBody rb;

};


#endif