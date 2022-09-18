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

#include "tb/Entity.h"
#include "tb/Object.h"

namespace tb
{

class Map
{

public:

    Map();
    ~Map();
    Map(const Map&) = delete;
    Map(Map&&) = delete;
    Map& operator=(const Map&) = delete;
    Map& operator=(Map&&) = delete;

    static Map& getInstance()
    {
        static Map map;
        return map;
    }

    struct Properties_t
    {
        std::string Name;
        std::string Author;
        std::string Description;

        uint32_t PlayerStartX = 0;
        uint32_t PlayerStartY = 0;
        tb::ZAxis_t PlayerStartZ = tb::ZAxis::Default;

        tb::TimeOfDay TimeOfDay = tb::TimeOfDay::Day;
    };

    template <class T>
    uint32_t getTileNumberByPixelCoords(T pixelCoords)
    {
        uint32_t tileX = 0;
        uint32_t tileY = 0;

        if (pixelCoords.x != 0)
        {
            tileX = pixelCoords.x / tb::Constants::TileSize;
        }

        if (pixelCoords.y != 0)
        {
            tileY = pixelCoords.y / tb::Constants::TileSize;
        }

        return tileX + (tileY * m_tileWidth);
    }

    template <class T>
    sf::Vector2u getTileCoordsByPixelCoords(T pixelCoords)
    {
        uint32_t tileX = 0;
        uint32_t tileY = 0;

        if (pixelCoords.x != 0)
        {
            tileX = pixelCoords.x / tb::Constants::TileSize;
        }

        if (pixelCoords.y != 0)
        {
            tileY = pixelCoords.y / tb::Constants::TileSize;
        }

        return sf::Vector2u(tileX, tileY);
    }

    bool load(const std::string& fileName);

    bool isTileNumberOutOfBounds(uint32_t tileNumber);
    bool isTileCoordsOutOfBounds(const sf::Vector2u& tileCoords);

    const std::string& getFileName();

    uint32_t getPixelWidth();
    uint32_t getPixelHeight();

    uint32_t getNumPixels();

    uint32_t getTileWidth();
    uint32_t getTileHeight();

    uint32_t getNumTiles();

    Properties_t* getProperties();

    tb::TileMap* getTileMapTiles(tb::ZAxis_t z);
    tb::TileMap* getTileMapTileEdges(tb::ZAxis_t z);

private:

    std::string m_fileName = std::string();

    uint32_t m_pixelWidth = 0;
    uint32_t m_pixelHeight = 0;

    uint32_t m_numPixels = 0; // = m_width * m_height

    uint32_t m_tileWidth = 0;
    uint32_t m_tileHeight = 0;

    uint32_t m_numTiles = 0; // m_tileWidth * m_tileHeight

    Properties_t m_properties;

    tb::TileMap::Array m_tileMapTiles;
    tb::TileMap::Array m_tileMapTileEdges;

};

}

namespace
{
    tb::Map& g_Map = tb::Map::getInstance();
}
