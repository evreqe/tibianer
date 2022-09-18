#include "tb/Tile.h"

namespace tb
{

Tile::Tile()
{
    //
}

Tile::~Tile()
{
    //
}

uint32_t Tile::getTileNumber()
{
    return m_tileNumber;
}

void Tile::setTileNumber(uint32_t tileNumber)
{
    m_tileNumber = tileNumber;
}

tb::SpriteID_t Tile::getSpriteID()
{
    return m_spriteID;
}

void Tile::setSpriteID(tb::SpriteID_t spriteID)
{
    m_spriteID = spriteID;
}

tb::SpriteFlags_t Tile::getSpriteFlags()
{
    return m_spriteFlags;
}

void Tile::setSpriteFlags(const tb::SpriteFlags_t& spriteFlags)
{
    m_spriteFlags = spriteFlags;
}

sf::Vector2u Tile::getPixelCoords()
{
    return Tile::m_pixelCoords;
}

void Tile::setPixelCoords(const sf::Vector2u& pixelCoords)
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

sf::Vector2u Tile::getTileCoords()
{
    return m_tileCoords;
}

void Tile::setTileCoords(const sf::Vector2u& tileCoords)
{
    m_tileCoords = tileCoords;

    m_pixelCoords.x = tileCoords.x * tb::Constants::TileSize;
    m_pixelCoords.y = tileCoords.y * tb::Constants::TileSize;
}

uint32_t Tile::getTileX()
{
    return m_tileCoords.x;
}

void Tile::setTileX(uint32_t tileX)
{
    m_tileCoords.x = tileX;

    m_pixelCoords.x = tileX * tb::Constants::TileSize;
}

uint32_t Tile::getTileY()
{
    return m_tileCoords.y;
}

void Tile::setTileY(uint32_t tileY)
{
    m_tileCoords.y = tileY;

    m_pixelCoords.y = tileY * tb::Constants::TileSize;
}

tb::ZAxis_t Tile::getZ()
{
    return m_z;
}

void Tile::setZ(tb::ZAxis_t z)
{
    m_z = z;
}

uint8_t Tile::getHeight()
{
    return m_height;
}

void Tile::setHeight(uint8_t height)
{
    m_height = height;
}

void Tile::addEntity(tb::Entity::Ptr entity)
{
    m_entityList.push_back(entity);
}

void Tile::removeEntity(tb::Entity::Ptr entity)
{
    //auto it = std::find(m_entityList.begin(), m_entityList.end(), entity);
    //if (it != m_entityList.end())
    //{
        //m_entityList.erase(it);
    //}

    std::erase(m_entityList, entity);
}

void Tile::addObject(tb::Object::Ptr object)
{
    /*
            if (object->getFlags().test(tb::SpriteFlags::decal))
            {
                m_objectList.insert(m_objectList.begin(), object);
            }
            else
            {
                m_objectList.push_back(object);
            }
    */

    m_objectList.push_back(object);
}

void Tile::removeObject(tb::Object::Ptr object)
{
    //auto it = std::find(m_objectList.begin(), m_objectList.end(), object);
    //if (it != m_objectList.end())
    //{
        //m_objectList.erase(it);
    //}

    std::erase(m_objectList, object);
}

tb::Entity::List* Tile::getEntityList()
{
    return &m_entityList;
}

tb::Object::List* Tile::getObjectList()
{
    return &m_objectList;
}

tb::Object::List* Tile::getTileEdgeObjectList()
{
    return &m_tileEdgeObjectList;
}

}
