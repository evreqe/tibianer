#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

#include "tb/SpriteFlags.h"

#include "tb/Entity.h"
#include "tb/Object.h"
#include "tb/Creature.h"
#include "tb/Animation.h"

namespace tb
{

class Tile
{

public:

    Tile();
    ~Tile();

    using Ptr = std::shared_ptr<tb::Tile>;
    using List = std::vector<tb::Tile::Ptr>;

    struct SortByTileIndex_t
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

    tb::SpriteFlags* getSpriteFlags();
    void setSpriteFlags(const tb::SpriteFlags& spriteFlags);

    sf::Vector2f getPixelCoords();
    void setPixelCoords(const sf::Vector2f& pixelCoords);

    float getPixelX();
    void setPixelX(float pixelX);

    float getPixelY();
    void setPixelY(float pixelY);

    sf::Vector2i getTileCoords();
    void setTileCoords(const sf::Vector2i& tileCoords);

    int getTileX();
    void setTileX(int tileX);

    int getTileY();
    void setTileY(int tileY);

    tb::ZAxis_t getZ();
    void setZ(tb::ZAxis_t z);

    uint8_t getHeight();
    void setHeight(uint8_t height);

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

    tb::Object::List* getObjectList();
    tb::Object::List* getTileEdgeObjectList();
    tb::Creature::List* getCreatureList();
    tb::Animation::List* getAnimationList();
    tb::Entity::List* getEntityList();

private:

    uint32_t m_tileIndex = 0; // index of the tile on the screen from left to right, top to bottom

    tb::SpriteID_t m_spriteID = 0;

    tb::SpriteFlags m_spriteFlags;

    sf::Vector2i m_tileCoords;
    sf::Vector2f m_pixelCoords;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    uint8_t m_height = 0; // number of objects stacked vertically on the tile

    tb::Object::List m_objectList;
    tb::Object::List m_tileEdgeObjectList;
    tb::Creature::List m_creatureList;
    tb::Animation::List m_animationList;
    tb::Entity::List m_entityList;

};

}
