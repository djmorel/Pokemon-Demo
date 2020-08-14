#ifndef CHARACTER_H
#define CHARACTER_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Math/Rect.h"
#include "../Animations/WalkAnimation.h"


// Characters in the overworld (i.e. NPCs and Pokemon) that have animations & movement
class Character
{
  public:
    Character();
    Character(Sprite _sprite);
    Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset);
    ~Character();

    void Update();
    void Render();

    Sprite& getSprite();
    RigidBody& getRB();

    void setSprite(Sprite _sprite);
    void setAsPlayer(bool _isPlayer);

    void enableWalkAnimation();

    WalkAnimation walkAnimation;  // Public so others can add to its animation sprite vector

  private:
    Sprite sprite;
    RigidBody rb;
    Rect boundingRect;
    bool isPlayer;
};


#endif