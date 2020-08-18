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
  Character character;
  std::string name;
  std::string spritePath;  // TODO: Determine if this is necessary
  //bool hasWalkAnimation;
  //WalkAnimation walkAnimation;
};
typedef struct CharacterInfo CharacterInfo;


class CharacterManager
{
  public:
    CharacterManager();
    ~CharacterManager();

    void Update();  // Doesn't do anything
    void Render();

    int createPlayer();                     // Creates a new player save file (rewrites old one if it exists!)
    int loadPlayer();                       // Loads player save info
    int loadCharacter(std::string characterPath, bool isPlayer, Vector3D _pos, float _rot, Vector3D _scale);  // Loads a character from CharacterInfo directory

    int configAnimation(Character &character, std::string &line, Vector3D _pos, float _rot, Vector3D _scale);

    Vector2D line2coord(std::string line);  // Converts a string line to Vector2D coordinates
    int intPull(std::string &line, char delimiter);

    Character* getPlayer();
    PlayerInfo& getPlayerInfo();

    void clearCharacters(bool savePlayer);  // Deletes the contents of the characters vector


  private:
    const char savefilePath[22] = "src/Save/Savefile.txt";
    PlayerInfo playerInfo;
    std::vector<CharacterInfo*> characters;  // Vector of all characters on the current map
};


#endif