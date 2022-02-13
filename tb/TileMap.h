#pragma once

#include <string>
#include <vector>
#include <iterator>
#include <memory>

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"
#include "tb/Tile.hpp"
#include "tb/Sprite.hpp"

namespace tb
{

class TileMap
{

public:

    void load(uint32_t width, uint32_t height, std::vector<tb::SpriteID_t> tiles, const std::string& name, tb::TileMapType type, tb::ZAxis_t z)
    {
        m_tiles.clear();

        m_tileList.clear();

        m_waterTileNumbers.clear();

        //m_tiles = tiles;
        //m_tiles = std::move(tiles);
        m_tiles.swap(tiles);

        m_name = name;

        m_type = type;

        m_z = z;

        m_waterOffset = 0;

        for (uint32_t i = 0; i < width; ++i)
        {
            for (uint32_t j = 0; j < height; ++j)
            {
                int tileNumber = i + j * width;

                int tileId = m_tiles.at(tileNumber);

                sf::Vector2u tilePosition
                (
                    i * tb::Constants::TileSize,
                    j * tb::Constants::TileSize
                );

                //tb::SpriteFlags_t tileFlags = tb::UMaps::spriteFlags[tileId];

                //if (tileFlags.test(tb::SpriteFlags::water) && m_type == tb::TileMapTypes::tiles && m_z == tb::ZAxis::ground)
                //{
                    //m_waterTileNumbers.push_back(tileNumber);
                //}

                //if (tileId == tb::TILE_NULL && m_type == tb::TileMapTypes::tiles)
                //{
                    //tileFlags.set(tb::SpriteFlags::null);
                //}

                tb::Tile::Ptr tile = std::make_shared<tb::Tile>();
                tile->setNumber(tileNumber);
                tile->setId(tileId);
                tile->setPosition(tilePosition);
                tile->setZ(z);
                tile->setFlags(tileFlags);
                m_tileList.push_back(tile);
            }
        }

        std::sort(m_tileList.begin(), m_tileList.end(), tb::Tile::sortByTileNumber_t());

        applyTilePatterns();
    }

    void updateTileId(int tileNumber, int tileId)
    {
        m_tiles.at(tileNumber) = tileId;

        m_tileList.at(tileNumber)->setId(tileId);
    }

    void updateTileFlags(int tileNumber, int tileId)
    {
        tb::SpriteFlags_t tileFlags = tb::UMaps::spriteFlags[tileId];

        m_tileList.at(tileNumber)->setFlags(tileFlags);
    }

    std::vector<int>* getTiles()
    {
        return &m_tiles;
    }

    tb::Tile::List* getTileList()
    {
        return &m_tileList;
    }

    std::vector<int>* getWaterTileNumbers()
    {
        return &m_waterTileNumbers;
    }

    void loadWaterTileNumbers()
    {
        m_waterTileNumbers.clear();

        for (auto& tile : m_tileList)
        {
            if (tile->getFlags().test(tb::SpriteFlags::water))
            {
                m_waterTileNumbers.push_back(tile->getNumber());
            }
        }
    }

    void doAnimatedWater()
    {
        for (auto tileNumber : m_waterTileNumbers)
        {
            int tileId = m_tiles.at(tileNumber);

            if (tileId >= tb::SpriteData::waterBegin && tileId <= tb::SpriteData::waterEnd)
            {
                if (tileId == tb::SpriteData::water[3])
                {
                    tileId = tb::SpriteData::water[0];
                }
                else if (tileId == tb::SpriteData::water[7])
                {
                    tileId = tb::SpriteData::water[4];
                }
                else
                {
                    tileId++;
                }

                updateTileId(tileNumber, tileId);
            }
        }
    }

    void doAnimatedWaterEx()
    {
        if (m_waterOffset > 3)
        {
            m_waterOffset = 0;
        }

        for (auto tileNumber : m_waterTileNumbers)
        {
            int tileId = m_tiles.at(tileNumber);

            if (tileId >= tb::SpriteData::waterBegin && tileId <= tb::SpriteData::waterEnd)
            {
                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int waterIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                waterIndex = tb::mapWidth - waterIndex;

                while (waterIndex > 3)
                {
                    waterIndex = waterIndex - 4;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    waterIndex += 4;
                }

                if (waterIndex < 4)
                {
                    waterIndex += m_waterOffset;

                    while (waterIndex > 3)
                    {
                        waterIndex = waterIndex - 4;
                    }
                }
                else
                {
                    waterIndex += m_waterOffset;

                    while (waterIndex > 7)
                    {
                        waterIndex = waterIndex - 4;
                    }
                }

                updateTileId(tileNumber, tb::SpriteData::water[waterIndex]);
            }
        }

        m_waterOffset++;
    }

    void applyTilePatterns()
    {
        for (auto& tile : m_tileList)
        {
            int tileId = tile->getId();

            // water
            if (tileId >= tb::SpriteData::waterBegin && tileId <= tb::SpriteData::waterEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 4;
                }

                updateTileId(tileNumber, tb::SpriteData::water[spriteIndex]);
            }

            // lava
            if (tileId >= tb::SpriteData::lavaBegin && tileId <= tb::SpriteData::lavaEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 4;
                }

                updateTileId(tileNumber, tb::SpriteData::lava[spriteIndex]);
            }

            // oil
            if (tileId >= tb::SpriteData::oilBegin && tileId <= tb::SpriteData::oilEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 4;
                }

                updateTileId(tileNumber, tb::SpriteData::oil[spriteIndex]);
            }

            // grey tiles
            if (tileId >= tb::SpriteData::greyTilesBegin && tileId <= tb::SpriteData::greyTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                int row = tb::mapHeight - tileCoords.y;

                row = tb::mapHeight - row;

                while (row > 3)
                {
                    row = row - 4;
                }

                if (row > 0)
                {
                    spriteIndex += 4 * row;
                }

                updateTileId(tileNumber, tb::SpriteData::greyTiles[spriteIndex]);
            }

            // brown tiles
            if (tileId >= tb::SpriteData::brownTilesBegin && tileId <= tb::SpriteData::brownTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 2)
                {
                    spriteIndex = spriteIndex - 3;
                }

                int row = tb::mapHeight - tileCoords.y;

                row = tb::mapHeight - row;

                while (row > 2)
                {
                    row = row - 3;
                }

                if (row > 0)
                {
                    spriteIndex += 3 * row;
                }

                updateTileId(tileNumber, tb::SpriteData::brownTiles[spriteIndex]);
            }

            // brown ladder tiles
            if (tileId >= tb::SpriteData::brownLadderTilesBegin && tileId <= tb::SpriteData::brownLadderTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 2)
                {
                    spriteIndex = spriteIndex - 3;
                }

                int row = tb::mapHeight - tileCoords.y;

                row = tb::mapHeight - row;

                while (row > 2)
                {
                    row = row - 3;
                }

                if (row > 0)
                {
                    spriteIndex += 3 * row;
                }

                updateTileId(tileNumber, tb::SpriteData::brownLadderTiles[spriteIndex]);
            }

            // orange black tiles
            if (tileId >= tb::SpriteData::orangeBlackTilesBegin && tileId <= tb::SpriteData::orangeBlackTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                int row = tb::mapHeight - tileCoords.y;

                row = tb::mapHeight - row;

                while (row > 3)
                {
                    row = row - 4;
                }

                if (row > 0)
                {
                    spriteIndex += 4 * row;
                }

                updateTileId(tileNumber, tb::SpriteData::orangeBlackTiles[spriteIndex]);
            }

            // stone tiles
            if (tileId == tb::SpriteData::stoneTilesBegin || tileId == tb::SpriteData::stoneTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 1)
                {
                    spriteIndex = spriteIndex - 2;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 2;
                }

                updateTileId(tileNumber, tb::SpriteData::stoneTiles[spriteIndex]);
            }

            // cobblestone tiles
            if (tileId >= tb::SpriteData::cobbleStoneTilesBegin && tileId <= tb::SpriteData::cobbleStoneTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 4;
                }

                updateTileId(tileNumber, tb::SpriteData::cobbleStoneTiles[spriteIndex]);
            }

            // yellow tiles
            if (tileId >= tb::SpriteData::yellowTilesBegin && tileId <= tb::SpriteData::yellowTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 1)
                {
                    spriteIndex = spriteIndex - 2;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 2;
                }

                updateTileId(tileNumber, tb::SpriteData::yellowTiles[spriteIndex]);
            }

            // cracked sand tiles
            if (tileId >= tb::SpriteData::crackedSandTilesBegin && tileId <= tb::SpriteData::crackedSandTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 1)
                {
                    spriteIndex = spriteIndex - 2;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 2;
                }

                updateTileId(tileNumber, tb::SpriteData::crackedSandTiles[spriteIndex]);
            }

            // brick tiles
            if (tileId >= tb::SpriteData::brickTilesBegin && tileId <= tb::SpriteData::brickTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 1)
                {
                    spriteIndex = spriteIndex - 2;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 2;
                }

                updateTileId(tileNumber, tb::SpriteData::brickTiles[spriteIndex]);
            }

            // mountain tiles
            if (tileId >= tb::SpriteData::mountainTilesBegin && tileId <= tb::SpriteData::mountainTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 1)
                {
                    spriteIndex = spriteIndex - 2;
                }

                // odd row
                if (tileCoords.y & 1)
                {
                    spriteIndex += 2;
                }

                updateTileId(tileNumber, tb::SpriteData::mountainTiles[spriteIndex]);
            }

            // sand tiles
            if (tileId >= tb::SpriteData::sandTilesBegin && tileId <= tb::SpriteData::sandTilesEnd)
            {
                int tileNumber = tile->getNumber();

                sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                int spriteIndex = tb::mapWidth - (tileNumber % tb::mapWidth);

                spriteIndex = tb::mapWidth - spriteIndex;

                while (spriteIndex > 3)
                {
                    spriteIndex = spriteIndex - 4;
                }

                int row = tb::mapHeight - tileCoords.y;

                row = tb::mapHeight - row;

                while (row > 3)
                {
                    row = row - 4;
                }

                if (row > 0)
                {
                    spriteIndex += 4 * row;
                }

                updateTileId(tileNumber, tb::SpriteData::sandTiles[spriteIndex]);
            }
        }
    }

    void applyTileObjectPatterns()
    {
        for (auto& tile : m_tileList)
        {
            tb::Object::List* objectList = tile->getObjectList();

            if (objectList->size() == 0)
            {
                continue;
            }

            for (auto& object : *objectList)
            {
                int objectId = object->getId();

                // horizontal stone wall
                if (objectId == 566 || objectId == 570)
                {
                    int tileNumber = tile->getNumber();

                    if (m_z & 1)
                    {
                        if (tileNumber & 1)
                        {
                            object->setId(566);
                        }
                        else
                        {
                            object->setId(570);
                        }
                    }
                    else
                    {
                        if (tileNumber & 1)
                        {
                            object->setId(570);
                        }
                        else
                        {
                            object->setId(566);
                        }
                    }
                }

                // vertical stone wall
                if (objectId == 584 || objectId == 588)
                {
                    int tileNumber = tile->getNumber();

                    sf::Vector2u tileCoords = getTileCoordsByTileNumber(tileNumber);

                    if (m_z & 1)
                    {
                        if (tileCoords.y & 1)
                        {
                            object->setId(584);
                        }
                        else
                        {
                            object->setId(588);
                        }
                    }
                    else
                    {
                        if (tileCoords.y & 1)
                        {
                            object->setId(588);
                        }
                        else
                        {
                            object->setId(584);
                        }
                    }
                }
            }
        }
    }

    sf::Vector2u getTileCoordsByTileNumber(uint32_t tileNumber)
    {
        return sf::Vector2u
        (
            tileNumber % tb::Variables::MapWidth,
            tileNumber / tb::Variables::MapHeight
        );
    }

    const std::string& getName() const
    {
        return m_name;
    }

    void setName(const std::string& name)
    {
        m_name = name;
    }

    tb::TileMapType getType()
    {
        return m_type;
    }

    void setType(tb::TileMapType type)
    {
        m_type = type;
    }

    tb::ZAxis_t getZ()
    {
        return m_z;
    }

    void setZ(tb::ZAxis_t z)
    {
        m_z = z;
    }

private:

    std::string m_name = std::string();

    tb::TileMapType m_type;

    tb::ZAxis_t m_z;

    std::vector<tb::SpriteID_t> m_tiles;

    tb::Tile::List m_tileList;

    std::vector<uint32_t> m_waterTileNumbers;

    uint32_t m_waterOffset;

};

}
