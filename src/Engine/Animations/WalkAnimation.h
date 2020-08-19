#ifndef WALKANIMATION_H
#define WALKANIMATION_H


#include "../Graphics/Sprite.h"
#include "../Actors/Entity.h"
#include <vector>


class WalkAnimation
{
  public:
    WalkAnimation();
    WalkAnimation(Sprite* _sprite_ptr, bool &_isPlayer);
    ~WalkAnimation();

    // Identifies sprite orientation
    enum class dir
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

    void setSpritePtr(Sprite* _sprite_ptr);
    Sprite& getDefaultSprite();

    void pushSpriteVector(dir _dir, Sprite* _sprite_ptr);
    void popSpriteVector(dir _dir);

    void updateIndex(dir _dir);

    void moveSprites(Vector3D v);  // Moves character's WalkAnimation sprites

    // Animates the character to walk in a specified direction
    void walk(bool move, bool changeSprite, bool newDirection, Vector3D displacement, dir direction, int duration);


  private:
    Sprite* sprite_ptr;                 // Pointer to the actor sprite (i.e. player or NPC)
    bool isPlayer;                      // Flag if the character is the player

    // ASSUME each vector's elements are in sequential frame order
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