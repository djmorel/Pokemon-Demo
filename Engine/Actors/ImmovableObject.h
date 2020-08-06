#ifndef IMMOVABLEOBJECT_H
#define IMMOVABLEOBJECT_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"


// Static overworld objects (i.e. trees, buildings, fences, etc) that lack animations
class ImmovableObject
{
  public:
    // Unneeded since not creating multiple copies of the same thing
    //static Sprite* objSprite_ptr;
    //static void Initialize();

    ImmovableObject();
    ImmovableObject(std::string imagePath);
    ImmovableObject(std::string imagePath, Vector3D _pos, float rot, float scale);

    void Update();
    void Render();

  private:
    Sprite objSprite;
    RigidBody rb;

};


#endif