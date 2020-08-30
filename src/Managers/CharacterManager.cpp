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
  std::vector<unsigned int> renderLater;  // Contains Character indices that should appear above the player

  // Determine the row and col values by accounting for 2 tiles offscreen (if possible)
  int min_X = (int)floor(playerInfo->mapCoord.x - playerInfo->screenCoord.x - 2);
  int max_X = (int)floor(playerInfo->mapCoord.x + (Engine::SCREEN_WIDTH / 64 - playerInfo->screenCoord.x)) + 1;
  int min_Y = (int)floor(playerInfo->mapCoord.y - playerInfo->screenCoord.y - 2);
  int max_Y = (int)floor(playerInfo->mapCoord.y + (Engine::SCREEN_HEIGHT / 64 - playerInfo->screenCoord.y)) + 1;

  // Render all NPCs on screen and some offscreen (by 1 tile)
  // Note: Here we assume that Characters on the top of the map appear first in the characters vector
  for (unsigned int i = 1; i < characters.size(); i++)
  {
    // Check that the character is between the min and max bounds
    if ( characters[i]->mapCoord.x > min_X && characters[i]->mapCoord.x < max_X &&
         characters[i]->mapCoord.y > min_Y && characters[i]->mapCoord.y < max_Y    )
    {
      // Check if the current NPC is below the player
      if (characters[i]->mapCoord.y < playerInfo->mapCoord.y)
      {
        // Record this NPC's index since we'll need to render them again after the player
        renderLater.push_back(i);
      }
      else
      {
        // Render the NPC now
        characters[i]->character.Render();
      }
    }
  }

  // Render the player (puts player on top of the NPCs)
  characters[0]->character.Render();

  // Render appropriate NPCs on top of the player
  for (unsigned int i = 0; i < renderLater.size(); i++)
  {
    characters[ renderLater[i] ]->character.Render();
  }
}



int CharacterManager::loadCharacter(std::string characterInfoPath, bool isPlayer, Vector3D _pos, float _rot, Vector3D _scale)
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
  fd.open(characterInfoPath);

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



CharacterInfo* CharacterManager::getCharacterInfo(unsigned int index)
{
  // Check for a valid index
  if (index >= characters.size())
  {
    return nullptr;
  }
  else
  {
    return characters[index];
  }
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



unsigned int CharacterManager::getCharactersSize()
{
  return characters.size();
}



bool CharacterManager::npcCollision(Sprite::dir direction)
{
  int offsetX = 0;
  int offsetY = 0;

  // Determine the projected x and y map coordinate offsets
  if (direction == Sprite::dir::DOWN)
  {
    offsetY = -1;
  }
  else if (direction == Sprite::dir::LEFT)
  {
    offsetX = -1;
  }
  else if (direction == Sprite::dir::RIGHT)
  {
    offsetX = 1;
  }
  else if (direction == Sprite::dir::UP)
  {
    offsetY = 1;
  }

  // Determine the player's map coordinates if the requested direction passes
  int col = (int)floor(playerInfo->mapCoord.x + offsetX);
  int row = (int)floor(playerInfo->mapCoord.y + offsetY);

  // Search through the NPCs for a collision
  for (unsigned int i = 1; i < characters.size(); i++)
  {
    if (characters[i]->mapCoord.x == col && characters[i]->mapCoord.y == row)
    {
      // Collision detected!
      return true;
    }
  }

  // No NPC collision detected
  return false;
}