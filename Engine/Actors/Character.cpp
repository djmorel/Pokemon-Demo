#include "Character.h"
#include "../Engine.h"
#include <thread>
#include <chrono>


Character::Character()
{
  // Do nothing
}


Character::~Character()
{
  // Clean the animation sprite vectors
  for (int i = 0; i < upSprites.size(); i++)
  {
    delete upSprites[i];
  }
  for (int i = 0; i < downSprites.size(); i++)
  {
    delete downSprites[i];
  }
  for (int i = 0; i < leftSprites.size(); i++)
  {
    delete leftSprites[i];
  }
  for (int i = 0; i < rightSprites.size(); i++)
  {
    delete rightSprites[i];
  }
}


Character::Character(Sprite _sprite)
{
  sprite = _sprite;

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale());
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction
}


Character::Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset)
{
  sprite = _sprite;

  Rect boundingRect = Rect();
  boundingRect.setSize(*sprite.getSize() * *sprite.getScale() * rectSizeOffset);  // Scale the boundingRect
  boundingRect.moveBy(rectPosOffset);                                             // Move the boundingRect
  rb.Initialize(sprite.getPos(), sprite.getRot(), sprite.getScale(), sprite.getSize(), 0, 1, boundingRect);  // No gravity or friction
}


void Character::Update()
{
  sprite.Update();
  rb.Update();
}


void Character::Render()
{
  sprite.Render();
  rb.Render(Vector3D(0, 0, 0));  // Black rigid body
  //rb.Render(Vector3D(0.51f, 0.86f, 0.87f));  // Light-Blue rigid body
}


Sprite& Character::getSprite()
{
  return sprite;
}


RigidBody& Character::getRB()
{
  return rb;
}


void Character::setSprite(Sprite _sprite)
{
  sprite = _sprite;
}


void Character::pushSpriteVector(dir _dir, Sprite* _sprite)
{
  if (_dir == dir::UP)
  {
    upSprites.push_back(_sprite);
  }
  else if (_dir == dir::DOWN)
  {
    downSprites.push_back(_sprite);
  }
  else if (_dir == dir::LEFT)
  {
    leftSprites.push_back(_sprite);
  }
  else if (_dir == dir::RIGHT)
  {
    rightSprites.push_back(_sprite);
  }
}


void Character::popSpriteVector(dir _dir)
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


void Character::updateIndex(dir _dir)
{
  switch (_dir)
  {
    case dir::UP:
    {
      if ( upIndex < ((int)upSprites.size() - 1) )
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
      if ( downIndex < ((int)downSprites.size() - 1) )
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
      if ( leftIndex < ((int)leftSprites.size() - 1) )
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
      if ( rightIndex < ((int)rightSprites.size() - 1) )
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


void Character::moveSprites(Vector3D v)
{
  // Update each of the sprite positions by v
  for (int i = 0; i < upSprites.size(); i++)
  {
    upSprites[i]->moveBy(v);
  }
  for (int i = 0; i < downSprites.size(); i++)
  {
    downSprites[i]->moveBy(v);
  }
  for (int i = 0; i < leftSprites.size(); i++)
  {
    leftSprites[i]->moveBy(v);
  }
  for (int i = 0; i < rightSprites.size(); i++)
  {
    rightSprites[i]->moveBy(v);
  }
}


void Character::walkUp()
{
  // Reset the animations for the other directions
  downIndex = 0;
  leftIndex = 0;
  rightIndex = 0;

  // Check the animation index
  sprite.moveBy(Vector3D(0, 16, 0));
  moveSprites(Vector3D(0, 16, 0));

  updateIndex(dir::UP);
  sprite = *(upSprites.at(upIndex));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add delay
}


void Character::walkDown()
{
  // Reset the animations for the other directions
  upIndex = 0;
  leftIndex = 0;
  rightIndex = 0;

  // Check the animation index
  sprite.moveBy(Vector3D(0, -16, 0));
  moveSprites(Vector3D(0, -16, 0));

  updateIndex(dir::DOWN);
  sprite = *(downSprites.at(downIndex));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add delay
}


void Character::walkLeft()
{
  // Reset the animations for the other directions
  upIndex = 0;
  downIndex = 0;
  rightIndex = 0;

  // Check the animation index
  sprite.moveBy(Vector3D(-16, 0, 0));
  moveSprites(Vector3D(-16, 0, 0));

  updateIndex(dir::LEFT);
  sprite = *(leftSprites.at(leftIndex));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add delay
}


void Character::walkRight()
{
  // Reset the animations for the other directions
  upIndex = 0;
  downIndex = 0;
  leftIndex = 0;

  // Check the animation index
  sprite.moveBy(Vector3D(16, 0, 0));
  moveSprites(Vector3D(16, 0, 0));

  updateIndex(dir::RIGHT);
  sprite = *(rightSprites.at(rightIndex));
  std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Add delay
}