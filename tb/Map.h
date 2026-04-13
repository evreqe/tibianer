#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteData.h"

#include "tb/TileMap.h"
#include "tb/Thing.h"
#include "tb/Entity.h"
#include "tb/Object.h"
#include "tb/Creature.h"

namespace tb
{

class Map
{

public:

    Map();
    ~Map();

    static Map& getInstance()
    {
        static Map instance;
        return instance;
    }

private:

    Map(const Map&) = delete;
    Map(Map&&) = delete;
    Map& operator=(const Map&) = delete;
    Map& operator=(Map&&) = delete;

public:

    struct Properties
    {
        std::string Name;
        std::string Author;
        std::string Description;

        tb::TileCoord PlayerStartX = 0;
        tb::TileCoord PlayerStartY = 0;
        tb::AxisZ PlayerStartZ = tb::Constants::AxisZDefault;

        tb::TimeOfDay TimeOfDay = tb::TimeOfDay::Day;
    };

    Properties* getProperties();

    bool load(const std::string& fileName);

    tb::TileIndex getTileIndexByTileCoords(const tb::TileCoords& tileCoords);
    tb::TileIndex getTileIndexByPixelCoords(const tb::PixelCoords& pixelCoords);

    tb::TileCoords getTileCoordsByPixelCoords(const tb::PixelCoords& pixelCoords);
    tb::PixelCoords getPixelCoordsByTileCoords(const tb::TileCoords& tileCoords);

    tb::TileCoords getTileCoordsByTileIndex(tb::TileIndex tileIndex);
    tb::PixelCoords getPixelCoordsByTileIndex(tb::TileIndex tileIndex);

    bool isTileIndexOutOfBounds(tb::TileIndex tileIndex);
    bool isTileCoordsOutOfBounds(const tb::TileCoords& tileCoords);

    tb::Tile::Ptr getTile(const tb::TileCoords& tileCoords, tb::AxisZ axisZ);
    tb::Tile::Ptr getTileAtThing(tb::Thing::Ptr thing);

    const std::string& getFileName();

    std::uint32_t getPixelWidth();
    std::uint32_t getPixelHeight();

    std::uint32_t getNumPixels();

    std::uint32_t getTileWidth();
    std::uint32_t getTileHeight();

    std::uint32_t getNumTiles();

    tb::TileMap::Ptr getTileMapOfTilesAtAxisZ(tb::AxisZ axisZ);
    tb::TileMap::Ptr getTileMapOfTileEdgesAtAxisZ(tb::AxisZ axisZ);

private:

    Properties m_properties;

    std::string m_fileName;

    std::uint32_t m_pixelWidth = 0;
    std::uint32_t m_pixelHeight = 0;

    std::uint32_t m_numPixels = 0; // = m_pixelWidth * m_pixelHeight

    std::uint32_t m_tileWidth = 0;
    std::uint32_t m_tileHeight = 0;

    std::uint32_t m_numTiles = 0; // = m_tileWidth * m_tileHeight

    tb::TileMap::List m_tileMapOfTilesList;
    tb::TileMap::List m_tileMapOfTileEdgesList;

};

}

namespace
{
    inline tb::Map& g_Map = tb::Map::getInstance();
}
