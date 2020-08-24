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
    Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset);
    ~Character();

    void Update();
    void Render();

    Sprite& getSprite();  // Need for displacements
    RigidBody& getRB();

    void setSprite(Sprite _sprite);
    int setRB();
    int setRB(Vector3D rectSizeOffset, Vector3D rectPosOffset);  // Note: Requires setting sprite beforehand!
    void setPlayerStatus(bool _isPlayer);

  private:
    Sprite sprite;
    bool hasSprite = false;
    RigidBody rb;
    Rect boundingRect;
    bool isPlayer = false;
};


#endif