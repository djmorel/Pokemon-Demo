#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H


#include "../Engine/Actors/Entity.h"
#include "../InfoFiles/InfoFiles.h"
#include "../Engine/Math/Vector2D.h"
#include <vector>


// Structure for containing tile contents
struct WorldElements
{
  Entity* tile;         // Pointer to the tile Entity
  Entity* layeredItem;  // Pointer to the layered item Entity
};
typedef struct WorldElements WorldElements;


// Manages map layouts (tiles and layered item entities) for the game.
class WorldManager
{
  public:
    /**
      A constructor that configures a World from a map and player information. Note: Use this constructor rather than a default constructor (not defined).
      \param std::string mapPath --> Path of the WorldMap file to read and build.
      \param PlayerInfo* _playerInfo --> Pointer to the player information structure.
      \return None
    **/
    WorldManager(PlayerInfo* _playerInfo, std::string mapPath);

    /**
      A deconstructor that frees all tiles associated with the current world, and clears the tile & map vectors.
      \param None
      \return None
    **/
    ~WorldManager();

    /**
      Was intended to clean offscreen tiles, but currently does nothing.
      \param None
      \return None
    **/
    void Update();

    /**
      Renders all tiles on the map.
      \param None
      \return None
    **/
    void RenderTiles();

    /**
      Renders all layered items on the map.
      \param None
      \return None
    **/
    void RenderLayeredItems();

    /**
      Reads a WorldMap file, and records the information in the map vector for later RAM-like access.
      \param std::string mapPath --> Path of the WorldMap file to read.
      \return 0 on success, -1 if unable to open the WorldMap file, -2 if unable to close the WorldMap file, or -3 if WorldMap file is corrupt/invalid.
    **/
    int readMap(std::string mapPath);

    /**
      Builds a world based on information recorded in the map vector.
      \param None
      \return 0 on success, or -1 if the map vector has no elements.
    **/
    int buildWorld();

    /**
      Calls subfunctions to check if the world can move relative to the player.
      \param Sprite::dir direction --> Direction of requested player movement (opposite of actual world movement).
      \param int screenX --> x coordinate of the player's current position on the screen.
      \param int screenY --> y coordinate of the player's current position on the screen.
      \param int mapX --> x coordinate of the player's current position on the map.
      \param int mapY --> y coordinate of the player's current position on the map.
      \return True if the World can move relative to the player, or False if it can't.
    **/
    bool canMoveWorld(Sprite::dir direction, int screenX, int screenY, int mapX, int mapY);

    /**
      Checks if there are enough offscreen tiles to move the world relative to the player.
      \param Sprite::dir direction --> Direction of requested player movement (opposite of actual world movement).
      \param int screenX --> x coordinate of the player's current position on the screen.
      \param int screenY --> y coordinate of the player's current position on the screen.
      \param int mapX --> x coordinate of the player's current position on the map.
      \param int mapY --> y coordinate of the player's current position on the map.
      \return True if the World has offscreen tiles in the passed direction, or False if not.
    **/
    bool hasOffscreenTiles(Sprite::dir direction, int screenX, int screenY, int mapX, int mapY);

    /**
      Checks if all immediate offscreen tiles in the requested direction have a valid tile ID (ID >= 0) to appear on the map.
      \param Sprite::dir direction --> Direction of requested player movement (opposite of actual world movement).
      \param int screenX --> x coordinate of the player's current position on the screen.
      \param int screenY --> y coordinate of the player's current position on the screen.
      \param int mapX --> x coordinate of the player's current position on the map.
      \param int mapY --> y coordinate of the player's current position on the map.
      \return True if the passed direction's immediate offscreen tiles are valid, or False if not.
    **/
    bool validOffscreenTiles(Sprite::dir direction, int screenX, int screenY, int mapX, int mapY);

    /**
      Checks what type of tile the player would step on if the specified direction is granted.
      \param Sprite::dir direction --> Direction of requested player movement.
      \param int mapX --> x coordinate of the player's current position on the map.
      \param int mapY --> y coordinate of the player's current position on the map.
      \return int >= 0 specifying the next tile's type (as per the tile type constants), or -1 if the next tile exceeds the map's bounds.
    **/
    int nextTile(Sprite::dir direction, int mapX, int mapY);

    /**
      Moves all world elements by the passed argument.
      \param Vector3D v --> Number of pixels to move by.
      \return None
    **/
    void moveWorld(Vector3D v);

    /**
      Determines if the player Sprite should move relative to the screen.
      \param Sprite::dir direction --> Direction of requested player movement.
      \param Vector2D playerScreenCoord --> Player's current x and y screen coordinates.
      \param Vector2D playerMapCoord --> Player's current x and y map coordinates.
      \return 0 if the world should move, 1 if the player should move, or -1 if the player shouldn't move because the next tile is immovable.
    **/
    int shouldMovePlayer(Sprite::dir direction, Vector2D playerScreenCoord, Vector2D playerMapCoord);

    /**
      Deletes all world elements by clearing the map and tiles vectors.
      \param None
      \return None
    **/
    void clearWorld();


  private:
    PlayerInfo* playerInfo;  // Pointer to the GameManager's playerInfo. Ensures classes reference the same value.

    // Note: WorldMap files MUST have ALL rows contain the same column count
    std::vector< std::vector<TileInfo> > map;            // RAM-like record of the WorldMap
    int mapRows = 0;                                     // Tracks the map's row count
    int mapCols = 0;                                     // Tracks the map's column count
    std::vector< std::vector<WorldElements> > elements;  // Holds references to each tile and layered item
};


#endif