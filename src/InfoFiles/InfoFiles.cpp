#include "InfoFiles.h"


namespace InfoFiles
{
  Vector2D InfoFiles::line2coord(std::string line)
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
      ret_val = Vector2D((float)std::stoi(x), (float)std::stoi(y));
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



  int InfoFiles::intPull(std::string& line, char delimiter)
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


  std::string InfoFiles::strPull(std::string& line, char delimiter)
  {
    std::string ret_string = "";

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
        ret_string.push_back(line[i]);
      }
    }

    return ret_string;
  }


  TileInfo InfoFiles::str2TileInfo(std::string _id, std::string _type, std::string _layeredItemID)
  {
    // Create a default, invalid TileInfo object
    TileInfo ret_val;
    ret_val.id = -42;
    ret_val.type = -1;
    ret_val.layeredItemID = -1;

    // Try to convert the input strings to ints
    try
    {
      // Convert the tile ID string to an integer
      ret_val.id = std::stoi(_id);

      // Check if the tile is of the default type
      if (_type == "")
      {
        ret_val.type = 0;
      }
      else
      {
        // Convert the tile type string to an integer
        ret_val.type = std::stoi(_type);
      }

      // Check if there is a layered item to record
      if (_layeredItemID == "")
      {
        ret_val.layeredItemID = -1;
      }
      else
      {
        // Convert the layered item ID string to an integer
        ret_val.layeredItemID = std::stoi(_layeredItemID);
      }
    }
    catch (std::invalid_argument const& e)
    {
      // Unable to convert to an int, so corrupt/invalid map
      // Make sure the tile ID is set as -1 to mark a failed conversion
      ret_val.id = -42;
    }
    catch (std::out_of_range const& e)
    {
      // Unable to convert to an int, so corrupt/invalid map
      // Make sure the tile ID is set as -1 to mark a failed conversion
      ret_val.id = -42;
    }

    // Return the current ret_val (failed or success version)
    return ret_val;
  }

}  // End of namespace InfoFiles functions