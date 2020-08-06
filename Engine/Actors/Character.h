#ifndef CHARACTER_H
#define CHARACTER_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Math/Rect.h"


// Characters in the overworld (i.e. NPCs and Pokemon) that have animations & movement
class Character
{
  public:
    Character();
    Character(Sprite _sprite);

    void Update();
    void Render();

    Sprite& getSprite();
    RigidBody& getRB();

  private:
    Sprite sprite;
    RigidBody rb;
    Rect boundingRect;

};


#endif