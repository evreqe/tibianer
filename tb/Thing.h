#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"

namespace tb
{

class Thing
{

public:

    typedef std::shared_ptr<tb::Thing> Ptr;
    typedef std::vector<tb::Thing::Ptr> List;

    struct SortByTileNumber_t
    {
        bool operator()(tb::Thing::Ptr a, tb::Thing::Ptr b) const
        {
            return (a->getTileNumber() < b->getTileNumber());
        }
    };

    struct SortByTileCoords_t
    {
        bool operator()(tb::Thing::Ptr a, tb::Thing::Ptr b) const
        {
            ////return (a->getTileX() == b->getTileX() ? a->getTileY() < b->getTileY() : a->getTileX() < b->getTileX());

            if (a->getTileX() == b->getTileX())
            {
                if (a->getTileY() == b->getTileY())
                {
                    return a->getDrawIndex() < b->getDrawIndex();
                }
                else
                {
                    return a->getTileY() < b->getTileY();
                }
            }

            return a->getTileX() < b->getTileX();
        }
    };

    Thing()
    {
        //
    }

    void updateTileNumber()
    {
        m_tileNumber = m_tileX + (m_tileY * tb::Variables::MapWidth);
    }

    void setCoords(uint32_t x, uint32_t y)
    {
        setX(x);
        setY(y);

        setTileX(x * tb::Constants::TileSize);
        setTileY(y * tb::Constants::TileSize);
    }

    void setTileCoords(uint32_t tileX, uint32_t tileY)
    {
        if (tileX == 0 || tileY == 0)
        {
            std::cout << "Error: divide by zero in Thing::setTileCoords()\n";
            return;
        }

        setX(tileX / tb::Constants::TileSize);
        setY(tileY / tb::Constants::TileSize);

        setTileX(tileX);
        setTileY(tileY);
    }

    void updateTileCoords()
    {
        m_tileX = m_x * tb::Constants::TileSize;
        m_tileY = m_y * tb::Constants::TileSize;

        updateTileNumber();
    }

    uint32_t getTileX()
    {
        return m_tileX;
    }

    void setTileX(uint32_t x)
    {
        m_tileX = x;
    }

    uint32_t getTileY()
    {
        return m_tileY;
    }

    void setTileY(uint32_t y)
    {
        m_tileY = y;
    }

    sf::Vector2u getTileCoords()
    {
        return sf::Vector2u(m_tileX, m_tileY);
    }

    uint32_t getTileNumber()
    {
        return m_tileNumber;
    }

    void setTileNumber(int tileNumber)
    {
        m_tileNumber = tileNumber;
    }

    uint32_t getX()
    {
        return m_x;
    }

    void setX(uint32_t x)
    {
        m_x = x;
    }

    uint32_t getY()
    {
        return m_y;
    }

    void setY(uint32_t y)
    {
        m_y = y;
    }

    tb::ZAxis_t getZ()
    {
        return m_z;
    }

    void setZ(tb::ZAxis_t z)
    {
        m_z = z;
    }

    sf::Vector2u getCoords()
    {
        return sf::Vector2u(m_x, m_y);
    }

    tb::DrawIndex getDrawIndex()
    {
        return m_drawIndex;
    }

    void setDrawIndex(tb::DrawIndex drawIndex)
    {
        m_drawIndex = drawIndex;
    }

    uint32_t getDrawOffset()
    {
        return m_drawOffset;
    }

    void setDrawOffset(int drawOffset)
    {
        m_drawOffset = drawOffset;
    }

    bool isReadyForErase()
    {
        return m_isReadyForErase;
    }

    void setIsReadyForErase(bool b)
    {
        m_isReadyForErase = b;
    }

    bool isEntity()
    {
        return m_isEntity;
    }

    void setIsEntity(bool b)
    {
        m_isEntity = b;
    }

    bool isObject()
    {
        return m_isObject;
    }

    void setIsObject(bool b)
    {
        m_isObject = b;
    }

    bool isCreature()
    {
        return m_isCreature;
    }

    void setIsCreature(bool b)
    {
        m_isCreature = b;
    }

private:

    uint32_t m_uniqueID = 0;

    uint32_t m_tileNumber = 0;

    uint32_t m_tileX = 0;
    uint32_t m_tileY = 0;

    uint32_t m_x = 0;
    uint32_t m_y = 0;
    tb::ZAxis_t m_z = 0;

    tb::DrawIndex m_drawIndex = tb::DrawIndex::Default;

    uint32_t m_drawOffset = 0;

    bool m_isReadyForErase = false;

    bool m_isEntity = false;
    bool m_isObject = false;
    bool m_isCreature = false;

};

}
