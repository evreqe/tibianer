#include "tb/Thing.h"

namespace tb
{

Thing::Thing()
{
    //
}

Thing::~Thing()
{
    //
}

uint32_t Thing::getTileIndex()
{
    return m_tileIndex;
}

void Thing::setTileIndex(uint32_t tileIndex)
{
    m_tileIndex = tileIndex;
}

sf::Vector2u Thing::getTileCoords()
{
    return m_tileCoords;
}

void Thing::setTileCoords(const sf::Vector2u& tileCoords)
{
    m_tileCoords = tileCoords;

    m_pixelCoords.x = m_tileCoords.x * tb::Constants::TileSize;
    m_pixelCoords.y = m_tileCoords.y * tb::Constants::TileSize;
}

uint32_t Thing::getTileX()
{
    return m_tileCoords.x;
}

void Thing::setTileX(uint32_t tileX)
{
    m_tileCoords.x = tileX;

    m_pixelCoords.x = tileX * tb::Constants::TileSize;
}

uint32_t Thing::getTileY()
{
    return m_tileCoords.y;
}

void Thing::setTileY(uint32_t tileY)
{
    m_tileCoords.y = tileY;

    m_pixelCoords.y = tileY * tb::Constants::TileSize;
}

sf::Vector2u Thing::getPixelCoords()
{
    return m_pixelCoords;
}

void Thing::setPixelCoords(const sf::Vector2u& pixelCoords)
{
    m_pixelCoords = pixelCoords;

    if (pixelCoords.x == 0)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = pixelCoords.x / tb::Constants::TileSize;
    }

    if (pixelCoords.y == 0)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = pixelCoords.y / tb::Constants::TileSize;
    }
}

uint32_t Thing::getPixelX()
{
    return m_pixelCoords.x;
}

void Thing::setPixelX(uint32_t pixelX)
{
    m_pixelCoords.x = pixelX;

    if (pixelX == 0)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = pixelX / tb::Constants::TileSize;
    }
}

uint32_t Thing::getPixelY()
{
    return m_pixelCoords.y;
}

void Thing::setPixelY(uint32_t pixelY)
{
    m_pixelCoords.y = pixelY;

    if (pixelY == 0)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = pixelY / tb::Constants::TileSize;
    }
}

tb::ZAxis_t Thing::getZ()
{
    return m_z;
}

void Thing::setZ(tb::ZAxis_t z)
{
    m_z = z;
}

tb::ThingType Thing::getThingType()
{
    return m_thingType;
}

void Thing::setThingType(tb::ThingType thingType)
{
    m_thingType = thingType;
}

tb::DrawOrderType Thing::getDrawOrderType()
{
    return m_drawOrderType;
}

void Thing::setDrawOrderType(tb::DrawOrderType drawOrderType)
{
    m_drawOrderType = drawOrderType;
}

uint8_t Thing::getDrawOffset()
{
    return m_drawOffset;
}

void Thing::setDrawOffset(uint8_t drawOffset)
{
    m_drawOffset = drawOffset;
}

bool Thing::getIsReadyForErase()
{
    return m_isReadyForErase;
}

void Thing::setIsReadyForErase(bool b)
{
    m_isReadyForErase = b;
}

}
