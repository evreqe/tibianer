#pragma once

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Entity.hpp"
#include "tb/Object.hpp"
//#include "tb/Creature.hpp"
//#include "tb/Animation.hpp"

namespace tb
{

class Tile
{

public:

    typedef std::shared_ptr<tb::Tile> Ptr;
    typedef std::vector<tb::Tile::Ptr> List;

    struct sortByTileNumber_t
    {
        bool operator()(tb::Tile::Ptr a, tb::Tile::Ptr b) const
        {
            return (a->getNumber() < b->getNumber());
        }
    };

    uint32_t getNumber()
    {
        return m_number;
    }

    void setNumber(uint32_t number)
    {
        m_number = number;
    }

    tb::SpriteID_t getSpriteID()
    {
        return m_spriteID;
    }

    void setSpriteID(tb::SpriteID_t id)
    {
        m_spriteID = id;
    }

    sf::Vector2u getPosition()
    {
        return m_position;
    }

    tb::ZAxis_t getZ()
    {
        return m_z;
    }

    void setZ(tb::ZAxis_t z)
    {
        m_z = z;
    }

    uint8_t getHeight()
    {
        return m_height;
    }

    void setHeight(uint8_t height)
    {
        m_height = height;
    }

    tb::Entity::List* getEntityList()
    {
        return &m_entityList;
    }

    tb::Object::List* getObjectList()
    {
        return &m_objectList;
    }

    void addEntity(tb::Entity::Ptr entity)
    {
        m_entityList.push_back(entity);
    }

    void removeEntity(tb::Entity::Ptr entity)
    {
        auto it = std::find(m_entityList.begin(), m_entityList.end(), entity);

        if (it != m_entityList.end())
        {
            m_entityList.erase(it);
        }
    }

    void addObject(tb::Object::Ptr object)
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

    void removeObject(tb::Object::Ptr object)
    {
        auto it = std::find(m_objectList.begin(), m_objectList.end(), object);

        if (it != m_objectList.end())
        {
            m_objectList.erase(it);
        }
    }

/*
    void addCreature(tb::Creature::Ptr creature)
    {
        if (creature->isDead() == true)
        {
            m_creatureList.insert(m_creatureList.begin(), creature);
        }
        else
        {
            m_creatureList.push_back(creature);
        }
    }
*/


/*
    void addAnimation(tb::Animation::Ptr animation)
    {
        m_animationList.push_back(animation);
    }
*/

private:

    uint32_t m_number = 0; // index of the tile on the screen from left to right, top to bottom

    tb::SpriteID_t m_spriteID = 0;

    sf::Vector2u m_position;

    tb::ZAxis_t m_z = tb::ZAxis::Default;

    uint8_t m_height = 0; // number of objects stacked vertically on the tile

    tb::Entity::List m_entityList;
    tb::Object::List m_objectList;
    //tb::Creature::List m_creatureList;
    //tb::Animation::List m_animationList;

};

}
