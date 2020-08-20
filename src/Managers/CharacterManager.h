#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


#include "../Engine/Actors/Character.h"
#include "../Engine/Math/Vector2D.h"
#include <vector>


struct PlayerInfo
{
  std::string name;          // Player nickname
  bool gender;               // 0 for female & 1 for male
  std::string charInfoPath;  // Path to CharacterInfo
  std::string mapPath;       // Path of last visited map
  Vector2D screenCoord;      // (x, y) coordinates on screen
  Vector2D mapCoord;         // (x, y) coordinates on map
};
typedef struct PlayerInfo PlayerInfo;


struct CharacterInfo
{
  Character character;     // Character object, which contains a WalkAnimation
  std::string name;        // Name of the character
  std::string spritePath;  // Path to the character's spritesheet
};
typedef struct CharacterInfo CharacterInfo;


class CharacterManager
{
  public:
    /**
      A constructor that does nothing special.
      \param None
      \return None
    **/
    CharacterManager();
    
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
      Creates a new player savefile for the game and rewrites over old savefile if it exists. References CharacterManager's const character array, savefilePath.
      \param None
      \return 0 on success, -1 if cancel player creation, or -2 if unable to delete existing file.
    **/
    int createPlayer();
    
    /**
      Loads player information from the savefile into GameManager's playerInfo struct.
      \param None
      \return 0 on success, -1 if unable to open savefile, -2 if line2coord() failure, -3 if corrupt savefile, or -4 if loadCharacter() failure.
    **/
    int loadPlayer();
    
    /**
      Loads either the player or a character into the characters vector. Note that the player can ONLY be loaded when the characters vector is empty.
      \param std::string characterPath - String for the full CharacterInfo file path.
      \param bool isPlayer - 0 if the requested character is an NPC, or 1 if it's the player.
      \param Vector3D _pos - The screen position for each of the WalkAnimation Sprites.
      \param float _rot - The rotation for each of the WalkAnimation Sprites.
      \param Vector3D _scale - The scale for each of the WalkAnimation Sprites.
      \return 0 on success, -1 if call invalidates the player is first element assumption, -2 if unable to open CharacterInfo file, -3 if CharacterInfo file not fully read, or -4 if configAnimation() failure.
    **/
    int loadCharacter(std::string characterPath, bool isPlayer, Vector3D _pos, float _rot, Vector3D _scale);
    
    /**
      Configures a WalkAnimation object to the passed character.
      \param Character &character - The Character object that is getting its WalkAnimation configured.
      \param std::string &line - The line from the CharacterInfo file that specifies the assetIDs for the WalkAnimation Sprites. Assumes the listed assetIDs come in multiple of 4 to account for the directions (DOWN, LEFT, RIGHT, UP).
      \param Vector3D _pos - The screen position for each of the WalkAnimation Sprites.
      \param float _rot - The rotation for each of the WalkAnimation Sprites.
      \param Vector3D _scale - The scale for each of the WalkAnimation Sprites.
      \return 0 on success, -1 if invalid numSprites format in CharacterInfo file, or -2 if invalid assetID format in CharacterInfo file.
    **/
    int configAnimation(Character &character, std::string &line, Vector3D _pos, float _rot, Vector3D _scale);
    
    /**
      Converts a string to a Vector2D (x, y) coordinate.
      \param std::string line - String in the format of int_x,int_y.
      \return Vector2D(-1, -1) on failure, or Vector2D based on what was read.
    **/
    Vector2D line2coord(std::string line);
    
    /**
      Reads from a string up to a delimiter character, and converts what was read to a positive int.
      \param std::string &line - Address of a string to pull an integer from. Note characters (including delimiter) read from the string are erased.
      \param char delimiter - Character that indicates where to stop pulling the integer from the passed string.
      \return int >= 0 on success, or -1 on std::stoi() failure.
    **/
    int intPull(std::string &line, char delimiter);
    
    /**
      Retrieves CharacterManager's player, the first element of the characters vector.
      \param None
      \return Character pointer to the player's Character object.
    **/
    Character* getPlayer();
    
    /**
      Retrieves CharacterManager's player information.
      \param None
      \return Address of the player's PlayerInfo object.
    **/
    PlayerInfo& getPlayerInfo();
    
    /**
      Clears CharacterInfo objects in CharacterManager's characters vector.
      \param bool savePlayer - 0 clears the entirety of the characters vector, but 1 keeps the player's CharacterInfo in the vector.
      \return None
    **/
    void clearCharacters(bool savePlayer);  // Deletes the contents of the characters vector


    void movePlayer(bool move, bool changeSprite, bool newDirection, Vector3D displacement, WalkAnimation::dir direction, int duration);


    void moveNPCs(bool move, bool changeSprite, bool newDirection, Vector3D displacement, WalkAnimation::dir direction, int duration);


  private:
    const char savefilePath[22] = "src/Save/Savefile.txt";
    PlayerInfo playerInfo;
    std::vector<CharacterInfo*> characters;  // Vector of all characters on the current map
};


#endif