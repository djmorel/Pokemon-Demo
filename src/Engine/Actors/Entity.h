#ifndef ENTITY_H
#define ENTITY_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"


// Overworld objects (i.e. trees, buildings, fences, etc) that lack animations
class Entity
{
  public:
    Entity();
    Entity(std::string assetName);
    Entity(int _id);
    Entity(std::string assetName, Vector3D _pos, float _rot, float _scale);
    Entity(int _id, Vector3D _pos, float _rot, float _scale);

    Vector2D getDimensions();
    Vector3D getPos();
    Sprite& getSprite();

    void Update();
    void Render();

  private:
    Sprite sprite;
    RigidBody rb;
};


#endif