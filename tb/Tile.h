#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteFlags.h"

#include "tb/TileBase.h"

#include "tb/Entity.h"
#include "tb/Object.h"
#include "tb/Creature.h"
#include "tb/Animation.h"

namespace tb
{

class Tile : public tb::TileBase
{

public:

    Tile();
    ~Tile();

    using Ptr = std::shared_ptr<tb::Tile>;
    using List = std::vector<tb::Tile::Ptr>;

    struct SortByTileIndex
    {
        bool operator()(tb::Tile::Ptr a, tb::Tile::Ptr b) const
        {
            return (a->getTileIndex() < b->getTileIndex());
        }
    };

    tb::SpriteID getSpriteID();
    void setSpriteID(tb::SpriteID spriteID);

    tb::SpriteFlags* getSpriteFlags();
    void setSpriteFlags(const tb::SpriteFlags& spriteFlags);

    std::uint8_t getHeight();
    void setHeight(std::uint8_t height);

    void addObject(tb::Object::Ptr object);
    void removeObject(tb::Object::Ptr object);

    void addTileEdgeObject(tb::Object::Ptr object);
    void removeTileEdgeObject(tb::Object::Ptr object);

    void addCreature(tb::Creature::Ptr creature);
    void removeCreature(tb::Creature::Ptr creature);

    void addAnimation(tb::Animation::Ptr animation);
    void removeAnimation(tb::Animation::Ptr animation);

    void addEntity(tb::Entity::Ptr entity);
    void removeEntity(tb::Entity::Ptr entity);

    tb::Thing::List createThingList();

    tb::Object::List* getObjectList();
    tb::Object::List* getTileEdgeObjectList();
    tb::Creature::List* getCreatureList();
    tb::Animation::List* getAnimationList();
    tb::Entity::List* getEntityList();

private:

    tb::SpriteID m_spriteID = tb::Constants::SpriteIDNull;

    tb::SpriteFlags m_spriteFlags;

    std::uint8_t m_height = 0; // number of objects stacked vertically on the tile

    tb::Object::List m_objectList;
    tb::Object::List m_tileEdgeObjectList;
    tb::Creature::List m_creatureList;
    tb::Animation::List m_animationList;
    tb::Entity::List m_entityList;

};

}
