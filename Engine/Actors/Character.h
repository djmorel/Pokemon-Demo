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
    ~Character();
    Character(Sprite _sprite);
    Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset);

    // Identifies sprite orientation
    enum class dir
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

    void Update();
    void Render();

    Sprite& getSprite();
    RigidBody& getRB();

    void setSprite(Sprite _sprite);
    void pushSpriteVector(dir _dir, Sprite* _sprite);
    void popSpriteVector(dir _dir);

    void updateIndex(dir _dir);

    void moveSprites(Vector3D v);

    void walkUp(bool move, bool changeSprite);
    void walkDown(bool move, bool changeSprite);
    void walkLeft(bool move, bool changeSprite);
    void walkRight(bool move, bool changeSprite);

  private:
    Sprite sprite;  // Current sprite
    RigidBody rb;
    Rect boundingRect;

    // ASSUME each vector contains sequential elements
    std::vector<Sprite*> upSprites;     // Vector of UP sprites (idle, walk1, walk2, walk3)
    int upIndex = 0;                    // Tracks current UP sprite animation
    std::vector<Sprite*> downSprites;   // Vector of DOWN sprites (idle, walk1, walk2, walk3)
    int downIndex = 0;                  // Tracks current DOWN sprite animation
    std::vector<Sprite*> leftSprites;   // Vector of LEFT sprites (idle, walk1, walk2, walk3)
    int leftIndex = 0;                  // Tracks current LEFT sprite animation
    std::vector<Sprite*> rightSprites;  // Vector of RIGHT sprites (idle, walk1, walk2, walk3)
    int rightIndex = 0;                 // Tracks current RIGHT sprite animation
};


#endif