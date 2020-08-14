#ifndef WALKANIMATION_H
#define WALKANIMATION_H


#include "../Graphics/Sprite.h"
#include "../Actors/ImmovableObject.h"
#include <vector>


class WalkAnimation
{
  public:
    WalkAnimation();
    WalkAnimation(Sprite* _sprite_ptr, std::vector<ImmovableObject*>* _tiles_ptr, bool _isPlayer);
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
    void setTilesPtr(std::vector<ImmovableObject*>* _tiles_ptr);

    void pushSpriteVector(dir _dir, Sprite* _sprite_ptr);
    void popSpriteVector(dir _dir);

    void updateIndex(dir _dir);

    void moveSprites(Vector3D v);  // Moves actor sprite
    void moveWorld(Vector3D v);    // Moves world tiles and entities

    // Movement functions with respect
    void walkUp(bool move, bool changeSprite, bool newDirection);
    void walkDown(bool move, bool changeSprite, bool newDirection);
    void walkLeft(bool move, bool changeSprite, bool newDirection);
    void walkRight(bool move, bool changeSprite, bool newDirection);


  private:
    Sprite* sprite_ptr;                        // Pointer to the actor sprite (i.e. player or NPC)
    std::vector<ImmovableObject*>* tiles_ptr;  // Pointer to the world tiles
    bool isPlayer;                             // Flag if the actor is the player

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