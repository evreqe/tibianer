#pragma once

#include "common.h"

#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm/replace_if.hpp>
#include <boost/range/algorithm/remove_if.hpp>

#include "boost_base64.hpp"
#include "boost_zlib.hpp"

#include "pugixml.hpp"

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

    struct Properties_t
    {
        std::string Name;
        std::string Author;
        std::string Description;

        std::int32_t PlayerStartX = 0;
        std::int32_t PlayerStartY = 0;
        tb::ZAxis_t PlayerStartZ = tb::ZAxis::Default;

        tb::TimeOfDay TimeOfDay = tb::TimeOfDay::Day;
    };

    Properties_t* getProperties();

    bool load(const std::string& fileName);

    std::uint32_t getTileIndexByTileCoords(const sf::Vector2i& tileCoords);
    std::uint32_t getTileIndexByPixelCoords(const sf::Vector2f& pixelCoords);

    sf::Vector2f getPixelCoordsByTileCoords(const sf::Vector2i& tileCoords);
    sf::Vector2i getTileCoordsByPixelCoords(const sf::Vector2f& pixelCoords);

    sf::Vector2i getTileCoordsByTileIndex(std::uint32_t tileIndex);
    sf::Vector2f getPixelCoordsByTileIndex(std::uint32_t tileIndex);

    bool isTileIndexOutOfBounds(std::uint32_t tileIndex);
    bool isTileCoordsOutOfBounds(const sf::Vector2i& tileCoords);

    tb::Tile::Ptr getTile(const sf::Vector2i& tileCoords, tb::ZAxis_t z);
    tb::Tile::Ptr getTileOfThing(tb::Thing::Ptr thing);

    const std::string& getFileName();

    std::uint32_t getPixelWidth();
    std::uint32_t getPixelHeight();

    std::uint32_t getNumPixels();

    std::uint32_t getTileWidth();
    std::uint32_t getTileHeight();

    std::uint32_t getNumTiles();

    tb::TileMap::Ptr getTileMapOfTilesAtZ(tb::ZAxis_t z);
    tb::TileMap::Ptr getTileMapOfTileEdgesAtZ(tb::ZAxis_t z);

private:

    Properties_t m_properties;

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
