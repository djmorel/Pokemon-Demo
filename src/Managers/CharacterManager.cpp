#include "CharacterManager.h"
#include "../Engine/Engine.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>



CharacterManager::CharacterManager()
{
  // Do nothing
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



int CharacterManager::createPlayer()
{
  // Open the passed map file
  std::ifstream fd;
  fd.open(savefilePath);

  // Check if the file already exists
  if (fd.is_open())
  {
    char response = '\0';

    // Unable to open the file
    std::cout << "CAUTION: Savefile already exists. Starting a new game will overwrite the existing savefile." << std::endl;

    while (response != 'Y' && response != 'y' && response != 'N' && response != 'n')
    {
      std::cout << "Continue (Y/N)? ";
      std::cin >> response;
    }

    // Handle the user response
    if (response == 'N' || response == 'n')
    {
      // Close the file
      fd.close();

      // Cancel player creation
      return -1;
    }

    // Close the file
    fd.close();

    // Delete the file
    if (remove(savefilePath) != 0)
    {
      // Unable to delete the exisiting savefile
      return -2;
    }
  }  // File doesn't exist or has successfully been deleted

  // Create a new savefile

  // TODO: Request and add the player's name

  // TODO: Request and add the player's gender (Will most likely turn out to be select your character)

  // TODO: Note the player character's CharacterInfo path

  // TODO: Configure the player's screen coordinates based on game start

  // TODO: Configure the player's map coordinates based on game start

  // Successfully created a player savefile
  return 0;
}



int CharacterManager::loadPlayer()
{
  // Variables
  std::ifstream fd;  // File descriptor/handler
  std::string line;  // Line read from the savefile
  int lineNum = 0;   // Tracks the current line number

  // Open the save file
  fd.open(savefilePath);

  // Ensure the file is open
  if (!fd.is_open())
  {
    // Unable to open savefile, so return an error
    return -1;
  }

  // File is open, so let's read it line-by-line
  while (getline(fd, line))
  {
    if (lineNum == 0)
    {
      // Load the player name
      playerInfo.name = line;
    }
    else if (lineNum == 1)
    {
      // Load the player gender
      playerInfo.gender = (line == "M");
    }
    else if (lineNum == 2)
    {
      // Load the player characterInfo path
      playerInfo.charInfoPath = line;
    }
    else if (lineNum == 3)
    {
      playerInfo.mapPath = line;
    }
    else if (lineNum == 4)
    {
      // Load the player screen coordinates
      playerInfo.screenCoord = line2coord(line);

      // Check that line2coord didn't fail
      if (playerInfo.screenCoord.x == -1 || playerInfo.screenCoord.y == -1)
      {
        // A coordinate is -1, so the stoi conversion failed
        return -2;
      }
    }
    else if (lineNum == 5)
    {
      // Load the player map coordinates
      playerInfo.mapCoord = line2coord(line);

      // Check that line2coord didn't fail
      if (playerInfo.mapCoord.x == -1 || playerInfo.mapCoord.y == -1)
      {
        // A coordinate is -1, so the stoi conversion failed
        return -2;
      }
    }

    // TODO: Add more else if conditions when savefile has more information

    lineNum++;
  }

  // Check that all of the lines were properly read
  if (lineNum < 5)
  {
    return -3;
  }

  // Call loadCharacter to load the player sprite and animations
  // Need (3 * 32.0f) / 2 since haven't configured the rigid body yet (Hilda sprite is 64x96 when scaled to 2.0f)
  if ( loadCharacter(playerInfo.charInfoPath, true, Vector3D(playerInfo.screenCoord.x * 64.0f + 64.0f / 2, playerInfo.screenCoord.y * 64.0f + (3 * 32.0f) / 2, 0), 0, Vector3D(2.0f) ) < 0 )
  {
    return -4;
  }

  // Successfully loaded player information
  return 0;
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
    else if (lineNum == 2)  // Load information about the walk animation
    {
      // Configure the walkAnimation (it's assumes that ALL Character objects have a WalkAnimation)
      if ( configAnimation(characterInfo->character, line, _pos, _rot, _scale) < 0 )
      {
        // Failed to create the animation (likely intPull's fault), so return an error
        delete characterInfo;
        fd.close();
        return -4;
      }
      else
      {
        // Set up the character's sprite
        characterInfo->character.setSprite(characterInfo->character.getWalkAnimation().getDefaultSprite());

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



int CharacterManager::configAnimation(Character &character, std::string &line, Vector3D _pos, float _rot, Vector3D _scale)
{
  int numSprites = 0;            // Holds the number of sprites per animation's direction
  int id = -1;                   // Holds an assetID
  std::vector<int> spriteCodes;  // Tracks the assetIDs for the animation sprites
  Sprite* spriteAnimation;       // Pointer to a new Sprite
  WalkAnimation::dir directions[] = { WalkAnimation::dir::DOWN,
                                      WalkAnimation::dir::LEFT,
                                      WalkAnimation::dir::RIGHT,
                                      WalkAnimation::dir::UP };

  // Determine how many sprites are assigned to a direction's animation
  numSprites = intPull(line, ':');

  // Error checking
  if (numSprites < 0)
  {
    // Error in gathering number of sprites, so corrupt/invalid CharacterInfo file
    return -1;
  }

  // Add the assetIDs to spriteCodes
  for (unsigned int i = 0; i < numSprites * 4; i++)
  {
    // Get the next assetID
    id = intPull(line, ',');

    // Add the valid assetID to spriteCodes
    if (id < 0)
    {
      // Error in gathering ID, so corrupt/invalid CharacterInfo file
      std::cout << "ERROR: Corrupt CharacterInfo file" << std::endl;
      return -2;
    }
    else
    {
      // Record the assetID
      spriteCodes.push_back(id);
    }
  }

  // Use the assetIDs in spriteCodes to create spriteAnimations
  for (unsigned int i = 0; i < spriteCodes.size(); i++)
  {
    // Create the sprite animations
    spriteAnimation = new Sprite(spriteCodes[i], _pos, _rot, _scale);
    character.getWalkAnimation().pushSpriteVector(directions[i / numSprites], spriteAnimation);
  }

  // Successfully added the animation to the passed character
  return 0;
}



Vector2D CharacterManager::line2coord(std::string line)
{
  // Setup a default invalid return
  Vector2D ret_val = Vector2D(-1);

  // Setup reading variables
  std::string x = "";
  std::string y = "";
  bool isX = true;

  // Iterate through the passed string, line
  for (unsigned int i = 0; i < line.length(); i++)
  {
    if (isX)
    {
      if (line[i] == ',')
      {
        isX = false;
      }
      else
      {
        x.push_back(line[i]);
      }
    }
    else
    {
      y.push_back(line[i]);
    }
  }

  // Try converting the tokens into ints
  try
  {
    ret_val = Vector2D(std::stoi(x), std::stoi(y));
  }
  catch (std::invalid_argument const& e)
  {
    // Unable to convert to an int, so we'll return the default Vector2D
  }
  catch (std::out_of_range const& e)
  {
    // Unable to convert to an int, so we'll return the default Vector2D
  }

  return ret_val;
}



int CharacterManager::intPull(std::string &line, char delimiter)
{
  std::string intString = "";

  // Loop through the string until the delimiter is reached
  for (unsigned int i = 0; i < line.length(); i++)
  {
    if (line[i] == delimiter)
    {
      // Empty the contents of line up to and including the delimiter
      line.erase(0, i + 1);

      // Break from the loop
      break;
    }
    else
    {
      // Add the read character to our integer string
      intString.push_back(line[i]);
    }
  }

  // Attempt to convert intString to an actual int
  try
  {
    return std::stoi(intString);
  }
  catch (std::invalid_argument const& e)
  {
    // Unable to convert to an int
    return -1;
  }
  catch (std::out_of_range const& e)
  {
    // Unable to convert to an int
    return -1;
  }
}



Character* CharacterManager::getPlayer()
{
  return &characters[0]->character;
}



PlayerInfo& CharacterManager::getPlayerInfo()
{
  return playerInfo;
}



void CharacterManager::clearCharacters(bool savePlayer)
{
  unsigned int i;

  // Check if we clear the player character or not
  if (savePlayer)
  {
    i = 1;
  }
  else
  {
    i = 0;
  }

  // Delete tha appropriate CharacterInfo instances
  for (i; i < characters.size(); i++)
  {
    delete characters[i];
  }
  characters.clear();
}