#include "common.h"

#include "tb/TileBase.h"

namespace tb
{

TileBase::TileBase()
{
    //
}

TileBase::~TileBase()
{
    //
}

tb::TileIndex TileBase::getTileIndex()
{
    return m_tileIndex;
}

void TileBase::setTileIndex(tb::TileIndex tileIndex)
{
    m_tileIndex = tileIndex;
}

tb::TileCoords TileBase::getTileCoords()
{
    return m_tileCoords;
}

void TileBase::setTileCoords(const tb::TileCoords& tileCoords)
{
    m_tileCoords = tileCoords;

    m_pixelCoords.x = static_cast<tb::PixelCoord>(m_tileCoords.x * tb::Constants::TileSize);
    m_pixelCoords.y = static_cast<tb::PixelCoord>(m_tileCoords.y * tb::Constants::TileSize);
}

tb::TileCoord TileBase::getTileX()
{
    return m_tileCoords.x;
}

void TileBase::setTileX(tb::TileCoord tileX)
{
    m_tileCoords.x = tileX;

    m_pixelCoords.x = static_cast<tb::PixelCoord>(tileX * tb::Constants::TileSize);
}

tb::TileCoord TileBase::getTileY()
{
    return m_tileCoords.y;
}

void TileBase::setTileY(tb::TileCoord tileY)
{
    m_tileCoords.y = tileY;

    m_pixelCoords.y = static_cast<tb::PixelCoord>(tileY * tb::Constants::TileSize);
}

tb::PixelCoords TileBase::getPixelCoords()
{
    return m_pixelCoords;
}

void TileBase::setPixelCoords(const tb::PixelCoords& pixelCoords)
{
    m_pixelCoords = pixelCoords;

    if (pixelCoords.x <= 0.0f)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = static_cast<tb::TileCoord>(pixelCoords.x / tb::Constants::TileSizeAsFloat);
    }

    if (pixelCoords.y <= 0.0f)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = static_cast<tb::TileCoord>(pixelCoords.y / tb::Constants::TileSizeAsFloat);
    }
}

tb::PixelCoord TileBase::getPixelX()
{
    return m_pixelCoords.x;
}

void TileBase::setPixelX(tb::PixelCoord pixelX)
{
    m_pixelCoords.x = pixelX;

    if (pixelX <= 0.0f)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = static_cast<tb::TileCoord>(pixelX / tb::Constants::TileSizeAsFloat);
    }
}

tb::PixelCoord TileBase::getPixelY()
{
    return m_pixelCoords.y;
}

void TileBase::setPixelY(tb::PixelCoord pixelY)
{
    m_pixelCoords.y = pixelY;

    if (pixelY <= 0.0f)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = static_cast<tb::TileCoord>(pixelY / tb::Constants::TileSizeAsFloat);
    }
}

tb::AxisZ TileBase::getAxisZ()
{
    return m_axisZ;
}

void TileBase::setAxisZ(tb::AxisZ axisZ)
{
    m_axisZ = axisZ;
}

}
