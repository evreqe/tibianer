#include "common.h"

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

tb::SpriteID Tile::getSpriteID()
{
    return m_spriteID;
}

void Tile::setSpriteID(tb::SpriteID spriteID)
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

std::uint8_t Tile::getHeight()
{
    return m_height;
}

void Tile::setHeight(std::uint8_t height)
{
    m_height = height;
}

void Tile::addObject(tb::Object::Ptr object)
{
    m_objectList.push_back(object);
}

void Tile::removeObject(tb::Object::Ptr object)
{
    std::erase(m_objectList, object);
}

void Tile::addTileEdgeObject(tb::Object::Ptr object)
{
    m_tileEdgeObjectList.push_back(object);
}

void Tile::removeTileEdgeObject(tb::Object::Ptr object)
{
    std::erase(m_tileEdgeObjectList, object);
}

void Tile::addCreature(tb::Creature::Ptr creature)
{
    m_creatureList.push_back(creature);
}

void Tile::removeCreature(tb::Creature::Ptr creature)
{
    std::erase(m_creatureList, creature);
}

void Tile::addAnimation(tb::Animation::Ptr animation)
{
    m_animationList.push_back(animation);
}

void Tile::removeAnimation(tb::Animation::Ptr animation)
{
    std::erase(m_animationList, animation);
}

void Tile::addEntity(tb::Entity::Ptr entity)
{
    m_entityList.push_back(entity);
}

void Tile::removeEntity(tb::Entity::Ptr entity)
{
    std::erase(m_entityList, entity);
}

tb::Thing::List Tile::createThingList()
{
    tb::Thing::List thingList;

    tb::Object::List* objectList = getObjectList();
    tb::Creature::List* creatureList = getCreatureList();
    tb::Animation::List* animationList = getAnimationList();

    std::size_t thingListReserveSize = 
        objectList->size()           +
        creatureList->size()         +
        animationList->size();

    thingList.reserve(thingListReserveSize);

    thingList.insert(thingList.end(), objectList->begin(), objectList->end());
    thingList.insert(thingList.end(), creatureList->begin(), creatureList->end());
    thingList.insert(thingList.end(), animationList->begin(), animationList->end());

    std::stable_sort(std::execution::par, thingList.begin(), thingList.end(), tb::Thing::SortByTileCoords());

    return thingList;
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

tb::Animation::List* Tile::getAnimationList()
{
    return &m_animationList;
}

tb::Entity::List* Tile::getEntityList()
{
    return &m_entityList;
}

}
