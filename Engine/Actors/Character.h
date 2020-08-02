#ifndef CHARACTER_H
#define CHARACTER_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"


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

};


#endif