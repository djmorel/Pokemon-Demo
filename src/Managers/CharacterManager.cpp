#include "CharacterManager.h"
#include "../Engine/Engine.h"
#include <iostream>
#include <stdio.h>
#include <string>



CharacterManager::CharacterManager(PlayerInfo* _playerInfo)
{
  // Initialize the playerInfo pointer
  playerInfo = _playerInfo;
}



CharacterManager::~CharacterManager()
{
  // Delete all characters
  for (unsigned int i = 0; i < characters.size(); i++)
  {
    delete characters[i];
  }
  characters.clear();
}



void CharacterManager::Update()
{
  // Update all characters on the map
  for (unsigned int i = 0; i < characters.size(); i++)
  {
    characters[i]->character.Update();
  }
}



void CharacterManager::Render()
{
  // Render all characters on the map
  for (unsigned int i = 0; i < characters.size(); i++)
  {
    characters[i]->character.Render();
  }
}



int CharacterManager::loadCharacter(std::string characterPath, bool isPlayer, Vector3D _pos, float _rot, Vector3D _scale)
{
  // Only proceed loadCharacter() if the player is loaded or is to be loaded as the characters vector's first element
  // Only one player can exist in the characters vector
  if ( (isPlayer && characters.size() != 0) || (!isPlayer && characters.size() == 0) )
  {
    // Invalidates our assumption that the player is the first element in the characters vector
    return -1;
  }

  // Variables
  std::ifstream fd;                                   // File descriptor/handler
  std::string line;                                   // Line read from the savefile
  int lineNum = 0;                                    // Tracks the current line number
  CharacterInfo* characterInfo = new CharacterInfo;   // Includes the character

  // Set the player status for the current character
  characterInfo->character.setPlayerStatus(isPlayer);

  // Open the CharacterInfo file
  fd.open(characterPath);

  // Ensure the file is open
  if (!fd.is_open())
  {
    // Unable to open CharacterInfo file, so return an error
    delete characterInfo;
    return -2;
  }

  // File is open, so let's read it line-by-line
  while (getline(fd, line))
  {
    if (lineNum == 0)  // Load the character name
    {
      characterInfo->name = line;
    }
    else if (lineNum == 1)  // Load the character's sprite path
    {
      characterInfo->spritePath = line;
    }
    else if (lineNum == 2)  // Load information about the Sprite frames
    {
      // Configure the Sprite and all of its directional frames
      if ( configSprite(characterInfo->character, line, _pos, _rot, _scale) < 0 )
      {
        // Failed to create the Sprite (likely intPull's fault), so return an error
        delete characterInfo;
        fd.close();
        return -4;
      }
      else
      {
        // Set up the character's rigid body
        if (isPlayer)
        {
          // TODO: Make general RB based on typical character model
          characterInfo->character.setRB(Vector3D(1, 0.66f, 1), Vector3D(0, -16.0f, 0));  // Ensures rigid body matches the tiles
        }
        else
        {
          characterInfo->character.setRB();
        }
      }
    }

    // TODO: Add more else if conditions when savefile has more information

    lineNum++;
  }

  // Close the CharacterInfo file
  fd.close();

  // Check that the CharacterInfo file was actually read
  if (lineNum < 2)
  {
    // Failed to read all the lines in the CharacterInfo file
    delete characterInfo;
    return -3;
  }

  // Add the characterInfo to the characters vector
  characters.push_back(characterInfo);

  // Successfully loaded the character
  return 0;
}



int CharacterManager::configSprite(Character &character, std::string &line, Vector3D _pos, float _rot, Vector3D _scale)
{
  int numSprites = 0;            // Holds the number of sprites per animation's direction
  int id = -1;                   // Holds an assetID
  std::vector<int> spriteCodes;  // Tracks the assetIDs for the animation sprites
  Sprite _sprite;                 // Pointer to a new Sprite
  Sprite::dir directions[] = { Sprite::dir::DOWN,
                               Sprite::dir::LEFT,
                               Sprite::dir::RIGHT,
                               Sprite::dir::UP };

  // Determine how many sprites are assigned to a direction's animation
  numSprites = InfoFiles::intPull(line, ':');

  // Error checking
  if (numSprites < 0)
  {
    // Error in gathering number of sprites, so corrupt/invalid CharacterInfo file
    return -1;
  }

  // Add the assetIDs to spriteCodes
  for (int i = 0; i < numSprites * 4; i++)
  {
    // Get the next assetID
    id = InfoFiles::intPull(line, ',');

    // Add the valid assetID to spriteCodes
    if (id < 0)
    {
      // assetID MUST be positive, so error in gathering ID (corrupt/invalid CharacterInfo file)
      std::cout << "ERROR: Corrupt CharacterInfo file" << std::endl;
      return -2;
    }
    else
    {
      // Record the assetID
      spriteCodes.push_back(id);
    }
  }

  // Add the sprite to the character
  _sprite = Sprite(spriteCodes[0], _pos, _rot, _scale);

  // Use the assetIDs in spriteCodes to create spriteAnimations
  for (unsigned int i = 1; i < spriteCodes.size(); i++)
  {
    // Add the sprite frames to the sprite object
    if (_sprite.pushSpriteInfo(spriteCodes[i]) < 0)
    {
      // Push failed since invalid assetID
      std::cout << "ERROR: Invalid assetID " << spriteCodes[i] << " when adding sprite frames" << std::endl;
      return -2;
    }
  }

  // Set the Sprite's spriteInfo tracker variables
  _sprite.setFramesPerDirection(numSprites);
  _sprite.setFrameIndex(0);

  // Set the configured sprite to the character
  character.setSprite(_sprite);

  // Successfully configured the character's sprite
  return 0;
}



Character* CharacterManager::getPlayer()
{
  return &characters[0]->character;
}



void CharacterManager::clearCharacters(bool savePlayer)
{
  int end;

  // Check if we clear the player character or not
  if (savePlayer)
  {
    end = 1;
  }
  else
  {
    end = 0;
  }

  // Delete the appropriate CharacterInfo instances
  // Go backwards in case we want to save the player character
  for (int i = characters.size() - 1; i >= end; i--)
  {
    delete characters[i];
    characters.pop_back();
  }
}



int CharacterManager::moveCharacter(unsigned int index, bool changeSprite, Vector3D displacement, Sprite::dir direction, float duration)
{
  // Check that the passed index is a valid number
  if (characters.size() <= index)
  {
    // Index exceeds the bounds of the characters vector
    return -1;
  }

  // Call on the player's walk animation to move it
  characters[index]->character.getSprite().walk(changeSprite, displacement, direction, duration);

  return 0;
}



void CharacterManager::moveAllNPCs(Vector3D displacement)
{
  // Move all NPCs by a certain displacement
  for (unsigned int i = 1; i < characters.size(); i++)
  {
    // Move the NPC sprites
    characters[i]->character.getSprite().moveBy(displacement);
  }
}