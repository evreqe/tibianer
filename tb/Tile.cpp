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

uint32_t Tile::getTileIndex()
{
    return m_tileIndex;
}

void Tile::setTileIndex(uint32_t tileIndex)
{
    m_tileIndex = tileIndex;
}

tb::SpriteID_t Tile::getSpriteID()
{
    return m_spriteID;
}

void Tile::setSpriteID(tb::SpriteID_t spriteID)
{
    m_spriteID = spriteID;
}

tb::SpriteFlags* Tile::getSpriteFlags()
{
    return &m_spriteFlags;
}

void Tile::setSpriteFlags(const tb::SpriteFlags& spriteFlags)
{
    m_spriteFlags = spriteFlags;
}

sf::Vector2f Tile::getPixelCoords()
{
    return m_pixelCoords;
}

void Tile::setPixelCoords(const sf::Vector2f& pixelCoords)
{
    m_pixelCoords = pixelCoords;

    if (pixelCoords.x < 0.0f)
    {
        m_tileCoords.x = 0;
    }
    else
    {
        m_tileCoords.x = static_cast<int>(pixelCoords.x / tb::Constants::TileSizeFloat);
    }

    if (pixelCoords.y < 0.0f)
    {
        m_tileCoords.y = 0;
    }
    else
    {
        m_tileCoords.y = static_cast<int>(pixelCoords.y / tb::Constants::TileSizeFloat);
    }
}

float Tile::getPixelX()
{
    return m_pixelCoords.x;
}

void Tile::setPixelX(float pixelX)
{
    m_pixelCoords.x = pixelX;

    m_tileCoords.x = static_cast<int>(pixelX / tb::Constants::TileSizeFloat);
}

float Tile::getPixelY()
{
    return m_pixelCoords.y;
}

void Tile::setPixelY(float pixelY)
{
    m_pixelCoords.y = pixelY;

    m_tileCoords.y = static_cast<int>(pixelY / tb::Constants::TileSizeFloat);
}

sf::Vector2i Tile::getTileCoords()
{
    return m_tileCoords;
}

void Tile::setTileCoords(const sf::Vector2i& tileCoords)
{
    m_tileCoords = tileCoords;

    m_pixelCoords.x = static_cast<float>(tileCoords.x * tb::Constants::TileSize);
    m_pixelCoords.y = static_cast<float>(tileCoords.y * tb::Constants::TileSize);
}

int Tile::getTileX()
{
    return m_tileCoords.x;
}

void Tile::setTileX(int tileX)
{
    m_tileCoords.x = tileX;

    m_pixelCoords.x = static_cast<float>(tileX * tb::Constants::TileSize);
}

int Tile::getTileY()
{
    return m_tileCoords.y;
}

void Tile::setTileY(int tileY)
{
    m_tileCoords.y = tileY;

    m_pixelCoords.y = static_cast<float>(tileY * tb::Constants::TileSize);
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

void Tile::addTileEdgeObject(tb::Object::Ptr object)
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

    m_tileEdgeObjectList.push_back(object);
}

void Tile::removeTileEdgeObject(tb::Object::Ptr object)
{
    //auto it = std::find(m_objectList.begin(), m_objectList.end(), object);
    //if (it != m_objectList.end())
    //{
        //m_objectList.erase(it);
    //}

    std::erase(m_tileEdgeObjectList, object);
}

void Tile::addCreature(tb::Creature::Ptr creature)
{
    m_creatureList.push_back(creature);
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

tb::Creature::List* Tile::getCreatureList()
{
    return &m_creatureList;
}

}
