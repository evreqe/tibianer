#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/Entity.h"
#include "tb/Object.h"
#include "tb/Creature.h"
//#include "tb/Animation.h"

namespace tb
{

class Tile
{

public:

    Tile();
    ~Tile();

    using Ptr = std::shared_ptr<tb::Tile>;
    using List = std::vector<tb::Tile::Ptr>;

    struct sortByTileIndex_t
    {
        bool operator()(tb::Tile::Ptr a, tb::Tile::Ptr b) const
        {
            return (a->getTileIndex() < b->getTileIndex());
        }
    };

    uint32_t getTileIndex();
    void setTileIndex(uint32_t tileIndex);

    tb::SpriteID_t getSpriteID();
    void setSpriteID(tb::SpriteID_t spriteID);

    tb::SpriteFlags_t getSpriteFlags();
    void setSpriteFlags(const tb::SpriteFlags_t& spriteFlags);

    sf::Vector2u getPixelCoords();
    void setPixelCoords(const sf::Vector2u& pixelCoords);

    sf::Vector2u getTileCoords();
    void setTileCoords(const sf::Vector2u& tileCoords);

    uint32_t getTileX();
    void setTileX(uint32_t tileX);

    uint32_t getTileY();
    void setTileY(uint32_t tileY);

    tb::ZAxis_t getZ();
    void setZ(tb::ZAxis_t z);

    uint8_t getHeight();
    void setHeight(uint8_t height);

    void addEntity(tb::Entity::Ptr entity);
    void removeEntity(tb::Entity::Ptr entity);

    void addObject(tb::Object::Ptr object);
    void removeObject(tb::Object::Ptr object);

    void addCreature(tb::Creature::Ptr creature);


/*
    void addAnimation(tb::Animation::Ptr animation);
*/

    tb::Entity::List* getEntityList();
    tb::Object::List* getObjectList();
    tb::Object::List* getTileEdgeObjectList();
    tb::Creature::List* getCreatureList();

private:

    uint32_t m_tileIndex = 0; // index of the tile on the screen from left to right, top to bottom

    tb::SpriteID_t m_spriteID = 0;

    tb::SpriteFlags_t m_spriteFlags;

    sf::Vector2u m_tileCoords;
    sf::Vector2u m_pixelCoords;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    uint8_t m_height = 0; // number of objects stacked vertically on the tile

    tb::Entity::List m_entityList;
    tb::Object::List m_objectList;
    tb::Object::List m_tileEdgeObjectList;
    tb::Creature::List m_creatureList;
    //tb::Animation::List m_animationList;

};

}
