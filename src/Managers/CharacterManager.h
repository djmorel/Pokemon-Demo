#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


#include "../Engine/Actors/Character.h"
#include "../Engine/Math/Vector2D.h"
#include "../InfoFiles/InfoFiles.h"
#include <vector>


// Stuct containing information for a given Character object.
struct CharacterInfo
{
  Character character;     // Character object, which contains a WalkAnimation
  std::string name;        // Name of the character
  std::string spritePath;  // Path to the character's spritesheet
  Vector2D mapCoord;       // Character's map coordinates. Note: We only care about the NPC's mapCoordinates.
};
typedef struct CharacterInfo CharacterInfo;


// Manages Character objects (including the player) for the game.
class CharacterManager
{
  public:
    /**
      A constructor that initializes the playerInfo pointer from GameManager.
      \param PlayerInfo* _playerInfo --> Pointer to GameManager's playerInfo. Ensures the information is consistent between classes.
      \return None
    **/
    CharacterManager(PlayerInfo* _playerInfo);
    
    /**
      A deconstructor that deletes all instances of CharacterInfo objects, and clears the CharacterManager::characters vector.
      \param None
      \return None
    **/
    ~CharacterManager();
    
    /**
      Updates all Character objects in the CharacterManager::characters vector.
      \param None
      \return None
    **/
    void Update();
    
    /**
      Renders all Character objects in the CharacterManager::characters vector.
      \param None
      \return None
    **/
    void Render();
    
    /**
      Loads either the player or an NPC into CharacterManager::characters. Note that the player can ONLY be loaded when CharacterManager::characters is empty.
      \param std::string characterInfoPath --> String for the full CharacterInfo file path.
      \param bool isPlayer --> True if the requested character is the player, or False if an NPC.
      \param Vector3D _pos --> The screen position for the Character's Sprite.
      \param float _rot --> The rotation for each of the Character's Sprite.
      \param Vector3D _scale --> The scale for each of the Character's Sprite.
      \return 0 on success, -1 if call invalidates the first element assumption, -2 if unable to open CharacterInfo file, -3 if CharacterInfo file not fully read, or -4 if configAnimation() failure.
    **/
    int loadCharacter(std::string characterInfoPath, bool isPlayer, Vector3D _pos, float _rot, Vector3D _scale);
    
    /**
      Configures a Sprite for the passed character.
      \param Character& character --> The Character object that is getting its Sprite configured.
      \param std::string& line --> The line from the CharacterInfo file that specifies the assetIDs for the WalkAnimation Sprites. Assumes the listed assetIDs come in multiple of 4 to account for the directions (DOWN, LEFT, RIGHT, UP).
      \param Vector3D _pos --> The screen position for the Character's Sprite.
      \param float _rot --> The rotation for the Character's Sprite.
      \param Vector3D _scale --> The scale for the Character's Sprite.
      \return 0 on success, -1 if invalid numSprites format in CharacterInfo file, or -2 if invalid assetID format in CharacterInfo file.
    **/
    int configSprite(Character& character, std::string& line, Vector3D _pos, float _rot, Vector3D _scale);
    
    /**
      Retrieves CharacterManager's player, the first element of the CharacterManager::characters vector.
      \param None
      \return Character pointer to the player's Character object.
    **/
    Character* getPlayer();

    /**
      Indexes into CharacterManager::characters, and returns a pointer to the CharacterInfo of the specified element.
      \param unsigned int index --> Index to the CharacterManager::characters vector.
      \return CharacterInfo pointer to the characters element, or nullptr if invalid passed index.
    **/
    CharacterInfo* getCharacterInfo(unsigned int index);

    /**
      Clears CharacterInfo objects in CharacterManager::characters.
      \param bool savePlayer --> True keeps the player's CharacterInfo in the vector, and False removes it as well.
      \return None
    **/
    void clearCharacters(bool savePlayer);

    /**
      Moves a specified character. Recall that the player is the 1st element in CharacterManager::characters.
      \param unsigned int index --> Index specifying what character to move. Set to 0 to move the player.
      \param bool changeSprite --> True to change the character's current Sprite frame, or False to keep it.
      \param Vector3D displacement --> Position to move the character's Sprite by.
      \param Sprite::dir direction --> Specifies the direction to move the Sprite.
      \param float duration --> How long the movement shoult take (in milliseconds).
      \return 0 if success, or -1 if invalid index.
    **/
    int moveCharacter(unsigned int index, bool changeSprite, Vector3D displacement, Sprite::dir direction, float duration);

    /**
      Moves all NPCs (second element and onward in CharacterManager::characters).
      \param Vector3D displacement --> How much to move the NPC sprites by.
      \return None
    **/
    void moveAllNPCs(Vector3D displacement);

    /**
      Returns the size of the CharacterManager::characters vector.
      \param None
      \return Size of CharacterManager::characters as an unsigned int.
    **/
    unsigned int getCharactersSize();

    /**
      Checks if the player's movement in a particular direction would result in an NPC collision.
      \param Sprite::dir direction --> Direction of player's requested movement.
      \return True if the requested direction results in an NPC collision, or False if not.
    **/
    bool npcCollision(Sprite::dir direction);


    // TODO: Implement
    // Move the NPCs in a certain way as specified by their movement style (need to add that parameter!)
    void randomizeNPCs();


  private:
    PlayerInfo* playerInfo;                  // Pointer to the player's PlayerInfo object (gives player's coordinates)
    std::vector<CharacterInfo*> characters;  // Vector of all characters on the current map
};


#endif