#include "WalkAnimation.h"
#include <thread>
#include <chrono>


WalkAnimation::WalkAnimation()
{
  sprite_ptr = nullptr;
  tiles_ptr = nullptr;
  isPlayer = false;
}


WalkAnimation::WalkAnimation(Sprite* _sprite_ptr, std::vector<Entity*>* _tiles_ptr, bool _isPlayer)
{
  sprite_ptr = _sprite_ptr;
  tiles_ptr = _tiles_ptr;
  isPlayer = _isPlayer;
}


WalkAnimation::~WalkAnimation()
{
  // Free the sprites attributed to the actor
  for (unsigned int i = 0; i < upSprites.size(); i++)
  {
    delete upSprites[i];
  }
  for (unsigned int i = 0; i < downSprites.size(); i++)
  {
    delete downSprites[i];
  }
  for (unsigned int i = 0; i < leftSprites.size(); i++)
  {
    delete leftSprites[i];
  }
  for (unsigned int i = 0; i < rightSprites.size(); i++)
  {
    delete rightSprites[i];
  }
}


void WalkAnimation::setSpritePtr(Sprite* _sprite_ptr)
{
  sprite_ptr = _sprite_ptr;
}


void WalkAnimation::setTilesPtr(std::vector<Entity*>* _tiles_ptr)
{
  tiles_ptr = _tiles_ptr;
}


void WalkAnimation::pushSpriteVector(dir _dir, Sprite* _sprite_ptr)
{
  if (_dir == dir::UP)
  {
    upSprites.push_back(_sprite_ptr);
  }
  else if (_dir == dir::DOWN)
  {
    downSprites.push_back(_sprite_ptr);
  }
  else if (_dir == dir::LEFT)
  {
    leftSprites.push_back(_sprite_ptr);
  }
  else if (_dir == dir::RIGHT)
  {
    rightSprites.push_back(_sprite_ptr);
  }
}


void WalkAnimation::popSpriteVector(dir _dir)
{
  if (_dir == dir::UP)
  {
    upSprites.pop_back();
  }
  else if (_dir == dir::DOWN)
  {
    downSprites.pop_back();
  }
  else if (_dir == dir::LEFT)
  {
    leftSprites.pop_back();
  }
  else if (_dir == dir::RIGHT)
  {
    rightSprites.pop_back();
  }
}


void WalkAnimation::updateIndex(dir _dir)
{
  switch (_dir)
  {
    case dir::UP:
    {
      if (upIndex < ((int)upSprites.size() - 1))
      {
        upIndex++;
      }
      else
      {
        upIndex = 0;
      }
      break;
    }
    case dir::DOWN:
    {
      if (downIndex < ((int)downSprites.size() - 1))
      {
        downIndex++;
      }
      else
      {
        downIndex = 0;
      }
      break;
    }
    case dir::LEFT:
    {
      if (leftIndex < ((int)leftSprites.size() - 1))
      {
        leftIndex++;
      }
      else
      {
        leftIndex = 0;
      }
      break;
    }
    case dir::RIGHT:
    {
      if (rightIndex < ((int)rightSprites.size() - 1))
      {
        rightIndex++;
      }
      else
      {
        rightIndex = 0;
      }
      break;
    }
    default:
    {
      std::cout << "ERROR: Unidentified direction " << static_cast<int>(_dir) << std::endl;
      break;
    }
  }
}


void WalkAnimation::moveSprites(Vector3D v)
{
  // Update each of the sprite positions by v
  for (unsigned int i = 0; i < upSprites.size(); i++)
  {
    upSprites[i]->moveBy(v);
  }
  for (unsigned int i = 0; i < downSprites.size(); i++)
  {
    downSprites[i]->moveBy(v);
  }
  for (unsigned int i = 0; i < leftSprites.size(); i++)
  {
    leftSprites[i]->moveBy(v);
  }
  for (unsigned int i = 0; i < rightSprites.size(); i++)
  {
    rightSprites[i]->moveBy(v);
  }
}


// TODO: Figure out how I want to call tiles (may need to redefine Entity)
void WalkAnimation::moveWorld(Vector3D v)
{
  /*
  // Move world elements found in tiles
  for (unsigned int i = 0; i < tiles->size(); i++)
  {
    tiles->at(i).moveBy(v);
  }
  */


  // TODO: Move world elements found in NPC & object vectors
}


void WalkAnimation::walkUp(bool move, bool changeSprite, bool newDirection)
{
  // Reset the animations for the other directions
  downIndex = 0;
  leftIndex = 0;
  rightIndex = 0;

  // Check if this animation is for a new direction
  if (newDirection)
  {
    upIndex = 0;
    *(sprite_ptr) = *(upSprites[upIndex]);
  }

  // Check if the character sprite should move
  if (move)
  {
    sprite_ptr->moveBy(Vector3D(0, 8, 0));
    moveSprites(Vector3D(0, 8, 0));
  }

  // Check if the character sprite should change
  if (changeSprite)
  {
    // Adjust the animation index
    updateIndex(dir::UP);
    *(sprite_ptr) = *(upSprites[upIndex]);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(40));  // Add delay
}


void WalkAnimation::walkDown(bool move, bool changeSprite, bool newDirection)
{
  // Reset the animations for the other directions
  upIndex = 0;
  leftIndex = 0;
  rightIndex = 0;

  // Check if this animation is for a new direction
  if (newDirection)
  {
    downIndex = 0;
    *(sprite_ptr) = *(downSprites[downIndex]);
  }

  // Check if the character sprite should move
  if (move)
  {
    sprite_ptr->moveBy(Vector3D(0, -8, 0));
    moveSprites(Vector3D(0, -8, 0));
  }

  // Check if the character sprite should change
  if (changeSprite)
  {
    // Adjust the animation index
    updateIndex(dir::DOWN);
    *(sprite_ptr) = *(downSprites[downIndex]);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(40));  // Add delay
}


void WalkAnimation::walkLeft(bool move, bool changeSprite, bool newDirection)
{
  // Reset the animations for the other directions
  upIndex = 0;
  downIndex = 0;
  rightIndex = 0;

  // Check if this animation is for a new direction
  if (newDirection)
  {
    leftIndex = 0;
    *(sprite_ptr) = *(leftSprites[leftIndex]);
  }

  // Check if the character sprite should move
  if (move)
  {
    sprite_ptr->moveBy(Vector3D(-8, 0, 0));
    moveSprites(Vector3D(-8, 0, 0));
  }

  // Check if the character sprite should change
  if (changeSprite)
  {
    // Adjust the animation index
    updateIndex(dir::LEFT);
    *(sprite_ptr) = *(leftSprites[leftIndex]);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(40));  // Add delay
}


void WalkAnimation::walkRight(bool move, bool changeSprite, bool newDirection)
{
  // Reset the animations for the other directions
  upIndex = 0;
  downIndex = 0;
  leftIndex = 0;

  // Check if this animation is for a new direction
  if (newDirection)
  {
    rightIndex = 0;
    *(sprite_ptr) = *(rightSprites[rightIndex]);
  }

  // Check if the character sprite should move
  if (move)
  {
    sprite_ptr->moveBy(Vector3D(8, 0, 0));
    moveSprites(Vector3D(8, 0, 0));
  }

  // Check if the character sprite should change
  if (changeSprite)
  {
    // Adjust the animation index
    updateIndex(dir::RIGHT);
    *(sprite_ptr) = *(rightSprites[rightIndex]);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(40));  // Add delay
}




