#ifndef IMMOVABLEOBJECT_H
#define IMMOVABLEOBJECT_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"


// Static overworld objects (i.e. trees, buildings, fences, etc) that lack animations
class ImmovableObject
{
  public:
    // Consider adding these if I want to have a base tile to render multiple times...
    static Sprite* objSprite_ptr;
    static void Initialize();

    ImmovableObject();
    ImmovableObject(std::string imagePath);
    ImmovableObject(std::string imagePath, Vector3D _pos, float rot, float scale);

    Vector2D getDimensions();

    void Update();
    void Render();

  private:
    Sprite objSprite;
    RigidBody rb;

};


#endif