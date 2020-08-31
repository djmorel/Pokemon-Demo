#ifndef ENTITY_H
#define ENTITY_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"
#include <string>


// Overworld objects (i.e. tiles, trees, buildings, fences, etc) that shouldn't move and have their RigidBody match the Sprite dimensions.
class Entity
{
  public:
    /**
      A constructor that sets the Entity's Sprite to a default Texture.
      \param None
      \return None
    **/
    Entity();

    /**
      A constructor that sets the Entity's Sprite to an asset from the AssetLookUpTable. Sets the Sprite object's values to default pos, rot, and scale values.
      \param std::string assetName --> Name of an asset to search for in the AssetLookupTable.
      \return None
    **/
    Entity(std::string assetName);

    /**
      A constructor that sets the Entity's Sprite to an asset from the AssetLookUpTable. Sets the Sprite object's values to default pos, rot, and scale values.
      \param int assetID --> ID used to index into the AssetLookupTable for an asset.
      \return None
    **/
    Entity(int _id);

    /**
      A constructor that sets the Entity's Sprite to an asset from the AssetLookUpTable, and configures the Sprite object's pos, rot, and scale values.
      \param std::string assetName --> Name of an asset to search for in the AssetLookupTable.
      \param Vector3D _pos --> Position to set the Sprite to.
      \param float _rot --> Rotation to set the Sprite to.
      \param Vector3D _scale --> Scale to set the Sprite to.
      \return None
    **/
    Entity(std::string assetName, Vector3D _pos, float _rot, float _scale);

    /**
      A constructor that sets the Entity's Sprite to an asset from the AssetLookUpTable, and configures the Sprite object's pos, rot, and scale values.
      \param int assetID --> ID used to index into the AssetLookupTable for an asset.
      \param Vector3D _pos --> Position to set the Sprite to.
      \param float _rot --> Rotation to set the Sprite to.
      \param Vector3D _scale --> Scale to set the Sprite to.
      \return None
    **/
    Entity(int _id, Vector3D _pos, float _rot, float _scale);

    /**
      Updates the Entity's Sprite and RigidBody.
      \param None
      \return None
    **/
    void Update();

    /**
      Renders the Entity's Sprite and RigidBody.
      \param None
      \return None
    **/
    void Render();

    /**
      Gets the Entity's dimensions as it appears on the screen. Units are in pixels.
      \param None
      \return Vector2D object containing the x and y dimensions.
    **/
    Vector2D getDimensions();

    /**
      Gets the Entity's Sprite. Useful for manipulating the Entity's Sprite object (i.e. displacements).
      \param None
      \return Address of the Entity's Sprite.
    **/
    Sprite& getSprite();

    /**
      Sets the Entity's dimensions to a specified value by adjusting the Sprite's scale. Automatically configs the RigidBody.
      \param Vector3D v --> Dimensions for the Entity. Units are in pixels.
      \return None
    **/
    void setDimensions(Vector3D v);

    /**
      Configures the Entity's RigidBody based on the current Sprite.
      \param None
      \return None
    **/
    void configRB();


  private:
    Sprite sprite;  // Entity's Sprite
    RigidBody rb;   // Entity's RigidBody (used for Physics)
};


#endif