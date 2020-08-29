#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


#include "../Engine/Actors/Character.h"
#include "../Engine/Math/Vector2D.h"
#include "../InfoFiles/InfoFiles.h"
#include <vector>


struct CharacterInfo
{
  Character character;     // Character object, which contains a WalkAnimation
  std::string name;        // Name of the character
  std::string spritePath;  // Path to the character's spritesheet
  Vector2D mapCoord;       // Character's map coordinates. Note: We only care about the NPC's mapCoordinates.
};
typedef struct CharacterInfo CharacterInfo;


class CharacterManager
{
  public:
    /**
      A constructor that initializes the playerInfo pointer from GameManager.
      \param None
      \return None
    **/
    CharacterManager(PlayerInfo* _playerInfo);
    
    /**
      A deconstructor that deletes all instances of CharacterInfo, and clears the characters vector.
      \param None
      \return None
    **/
    ~CharacterManager();
    
    /**
      Updates all Character objects in CharacterManager's characters vector.
      \param None
      \return None
    **/
    void Update();
    
    /**
      Renders all Character objects in CharacterManager's characters vector.
      \param None
      \return None
    **/
    void Render();
    
    /**
      Loads either the player or a character into the characters vector. Note that the player can ONLY be loaded when the characters vector is empty.
      \param std::string characterInfoPath - String for the full CharacterInfo file path.
      \param bool isPlayer - True if the requested character is the player, or False if an NPC.
      \param Vector3D _pos - The screen position for the Character's Sprite.
      \param float _rot - The rotation for each of the Character's Sprite.
      \param Vector3D _scale - The scale for each of the Character's Sprite.
      \return 0 on success, -1 if call invalidates the player is first element assumption, -2 if unable to open CharacterInfo file, -3 if CharacterInfo file not fully read, or -4 if configAnimation() failure.
    **/
    int loadCharacter(std::string characterInfoPath, bool isPlayer, Vector3D _pos, float _rot, Vector3D _scale);
    
    /**
      Configures a Sprite for the passed character.
      \param Character &character - The Character object that is getting its Sprite configured.
      \param std::string &line - The line from the CharacterInfo file that specifies the assetIDs for the WalkAnimation Sprites. Assumes the listed assetIDs come in multiple of 4 to account for the directions (DOWN, LEFT, RIGHT, UP).
      \param Vector3D _pos - The screen position for the Character's Sprite.
      \param float _rot - The rotation for the Character's Sprite.
      \param Vector3D _scale - The scale for the Character's Sprite.
      \return 0 on success, -1 if invalid numSprites format in CharacterInfo file, or -2 if invalid assetID format in CharacterInfo file.
    **/
    int configSprite(Character& character, std::string& line, Vector3D _pos, float _rot, Vector3D _scale);
    
    /**
      Retrieves CharacterManager's player, the first element of the characters vector.
      \param None
      \return Character pointer to the player's Character object.
    **/
    Character* getPlayer();

    /**
      Clears CharacterInfo objects in CharacterManager's characters vector.
      \param bool savePlayer - False clears the entire characters vector, but True keeps the player's CharacterInfo in the vector.
      \return None
    **/
    void clearCharacters(bool savePlayer);

    /**
      Moves a specified character. Recall that the player is the 1st element in the CharacterManager::characters vector.
      \param unsigned int index - Index specifying what character to move. Set to 0 to move the player.
      \param bool changeSprite - True to change the character's current Sprite frame, or False to keep it.
      \param Vector3D displacement - Position to move the character's Sprite by.
      \param Sprite::dir direction - Specifies the direction to move the Sprite.
      \param float duration - How long the movement shoult take (in milliseconds).
      \return 0 if success, or -1 if invalid index.
    **/
    int moveCharacter(unsigned int index, bool changeSprite, Vector3D displacement, Sprite::dir direction, float duration);

    /**
      Moves all NPCs (second element and onward in the CharacterManager::characters vector).
      \param Vector3D displacement - Where to move the NPC sprites by.
      \return None
    **/
    void moveAllNPCs(Vector3D displacement);

    /**
      Gets the map coordinates of a specified Character.
      \param unsigned int index - Index to the CharacterManager::characters vector.
      \return Vector2D mapCoord of the indexed Character, or Vector2D(-1) if the passed index exceeds the size of CharacterManager::characters.
    **/
    Vector2D getMapCoord(unsigned int index);

    /**
      Sets the map coordinates of a specified Character to a specified amount.
      \param unsigned int index - Index to the CharacterManager::characters vector.
      \param Vector2D _mapCoord - New map coordinates for the Character.
      \return 0 on success, or -1 if the passed index exceeds the size of CharacterManager::characters.
    **/
    int setMapCoord(unsigned int index, Vector2D _mapCoord);

    /**
      Sets the map coordinates of a specified Character by a specified amount.
      \param unsigned int index - Index to the CharacterManager::characters vector.
      \param Vector2D _mapCoord - Map coordinates to add to the Character's existing mapCoord.
      \return 0 on success, or -1 if the passed index exceeds the size of CharacterManager::characters.
    **/
    int setMapCoordBy(unsigned int index, Vector2D _mapCoord);

    /**
      Returns the size of the CharacterManager::characters vector.
      \param None
      \return Size of the CharacterManager::characters vector as an unsigned int.
    **/
    unsigned int getCharactersSize();


    // TODO
    // Move the NPCs in a certain way as specified by their movement style (need to add that parameter!)
    void randomizeNPCs();


  private:
    PlayerInfo* playerInfo;                  // Pointer to the player's PlayerInfo object (gives player's coordinates)
    std::vector<CharacterInfo*> characters;  // Vector of all characters on the current map
};


#endif