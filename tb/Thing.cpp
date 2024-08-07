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

Thing::ThingProperties_t* Thing::getThingProperties()
{
    return &m_thingProperties;
}

std::uint32_t Thing::getTileIndex()
{
    return m_tileIndex;
}

void Thing::setTileIndex(std::uint32_t tileIndex)
{
    m_tileIndex = tileIndex;
}

sf::Vector2i Thing::getTileCoords()
{
    return m_tileCoords;
}

void Thing::setTileCoords(const sf::Vector2i& tileCoords)
{
    m_tileCoords = tileCoords;

    m_pixelCoords.x = static_cast<float>(m_tileCoords.x * tb::Constants::TileSize);
    m_pixelCoords.y = static_cast<float>(m_tileCoords.y * tb::Constants::TileSize);
}

std::int32_t Thing::getTileX()
{
    return m_tileCoords.x;
}

void Thing::setTileX(std::int32_t tileX)
{
    m_tileCoords.x = tileX;

    m_pixelCoords.x = static_cast<float>(tileX * tb::Constants::TileSize);
}

std::int32_t Thing::getTileY()
{
    return m_tileCoords.y;
}

void Thing::setTileY(std::int32_t tileY)
{
    m_tileCoords.y = tileY;

    m_pixelCoords.y = static_cast<float>(tileY * tb::Constants::TileSize);
}

sf::Vector2f Thing::getPixelCoords()
{
    return m_pixelCoords;
}

void Thing::setPixelCoords(const sf::Vector2f& pixelCoords)
{
    m_pixelCoords = pixelCoords;

    if (pixelCoords.x < 0.0f)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = static_cast<int>(pixelCoords.x / tb::Constants::TileSizeAsFloat);
    }

    if (pixelCoords.y < 0.0f)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = static_cast<int>(pixelCoords.y / tb::Constants::TileSizeAsFloat);
    }
}

float Thing::getPixelX()
{
    return m_pixelCoords.x;
}

void Thing::setPixelX(float pixelX)
{
    m_pixelCoords.x = pixelX;

    if (pixelX < 0.0f)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = static_cast<int>(pixelX / tb::Constants::TileSizeAsFloat);
    }
}

float Thing::getPixelY()
{
    return m_pixelCoords.y;
}

void Thing::setPixelY(float pixelY)
{
    m_pixelCoords.y = pixelY;

    if (pixelY < 0.0f)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = static_cast<int>(pixelY / tb::Constants::TileSizeAsFloat);
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

std::uint8_t Thing::getDrawOffset()
{
    return m_drawOffset;
}

void Thing::setDrawOffset(std::uint8_t drawOffset)
{
    m_drawOffset = drawOffset;
}

}
