#ifndef CHARACTER_H
#define CHARACTER_H


#include "../Graphics/Sprite.h"
#include "../Physics/RigidBody.h"
#include "../Math/Rect.h"


// Characters in the overworld (i.e. NPCs and Pokemon) that have animations & movement.
class Character
{
  public:
    /**
      Default constructor that just serves as a placeholder Character.
      \param None
      \return None
    **/
    Character();

    /**
      A constructor initializes a Character with a specific Sprite.
      \param Sprite _sprite --> Sprite to assign to the Character.
      \return None
    **/
    Character(Sprite _sprite);

    /**
      A constructor initializes a Character with a specific Sprite and a Rect that doesn't necessarily match the Sprite's dimensions.
      \param Sprite _sprite --> Sprite to assign to the Character.
      \param Vector3D rectSizeOffset --> Size offset for the Character's Rect (size sets the bounds of the RigidBody).
      \param Vector3D rectPosOffset --> Position offset for the Character's Rect (moves the bounds of the RigidBody).
      \return None
    **/
    Character(Sprite _sprite, Vector3D rectSizeOffset, Vector3D rectPosOffset);

    /**
      Default deconstructor that doesn't do anything extra special.
      \param None
      \return None
    **/
    ~Character();

    /**
      Updates the Character's Sprite and RigidBody.
      \param None
      \return None
    **/
    void Update();

    /**
      Renders the Character's Sprite and RigidBody (black outlines).
      \param None
      \return None
    **/
    void Render();

    /**
      Gets the Character's Sprite. Useful for manipulating the Character's Sprite object (i.e. displacements).
      \param None
      \return Address of the Character's Sprite.
    **/
    Sprite& getSprite();

    /**
      Gets the Character's RigidBody.
      \param None
      \return Address of the Character's RigidBody.
    **/
    RigidBody& getRB();

    /**
      Sets the Character's Sprite to the passed Sprite object. Useful for configuring default/placeholder Character objects.
      \param Sprite _sprite --> Sprite to assign to the Character.
      \return None
    **/
    void setSprite(Sprite _sprite);

    /**
      Sets the Character's RigidBody according to its current Sprite object. Useful when reassigning the Character's Sprite object.
      \param None
      \return 0 on success, or -1 if a Sprite hasn't been configured yet.
    **/
    int setRB();

    /**
      Sets the Character's RigidBody according to the passed parameters with respect to the current Sprite object. Useful when reassigning the Character's Sprite object.
      \param Vector3D rectSizeOffset --> Size offset for the Character's Rect (size sets the bounds of the RigidBody).
      \param Vector3D rectPosOffset --> Position offset for the Character's Rect (moves the bounds of the RigidBody).
      \return 0 on success, or -1 if a Sprite hasn't been configured yet.
    **/
    int setRB(Vector3D rectSizeOffset, Vector3D rectPosOffset);

    /**
      Sets the Character's player status.
      \param bool _isPlayer --> True if the Character if the player, or False if not.
      \return None
    **/
    void setPlayerStatus(bool _isPlayer);


  private:
    Sprite sprite;           // Character's Sprite
    RigidBody rb;            // Character's RigidBody (used for Physics)
    Rect boundingRect;       // Character's Rect (used for the RigidBody's boundaries)
    bool hasSprite = false;  // Flags if Character has a Sprite or not
    bool isPlayer = false;   // Flags if Character is the player Characters
};


#endif