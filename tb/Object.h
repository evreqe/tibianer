#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"
#include "tb/Thing.hpp"
#include "tb/Sprite.hpp"

namespace tb
{

class Object : public tb::Thing
{

public:

    typedef std::shared_ptr<tb::Object> Ptr;
    typedef std::vector<tb::Object::Ptr> List;

    struct SortBySpriteID_t
    {
        bool operator()(tb::Object::Ptr a, tb::Object::Ptr b) const
        {
            return a->getSpriteID() < b->getSpriteID();
        }
    };

    struct SortByCount_t
    {
        bool operator()(tb::Object::Ptr a, tb::Object::Ptr b) const
        {
            return a->getCount() > b->getCount();
        }
    };

    Object()
    {
        setIsObject(true);
    }

    Object(sf::Vector2u tileCoords, tb::ZAxis_t z, tb::SpriteID_t id)
    {
        setIsObject(true);

        setTileCoords(tileCoords.x, tileCoords.y);

        setZ(z);

        setSpriteID(id);

        //if (m_flags.test(tb::SpriteFlags::groupable))
        //{
            //setCountById();
        //}
    }

    void update()
    {
        updateTileCoords();
    }

/*
    void doAnimation()
    {
        for (auto& animatedObjects : tb::animatedObjectsList)
        {
            auto animatedObjectIt = std::find(animatedObjects.begin(), animatedObjects.end(), m_id);

            if (animatedObjectIt != animatedObjects.end())
            {
                animatedObjectIt++;

                if (animatedObjectIt == animatedObjects.end())
                {
                    animatedObjectIt = animatedObjects.begin();
                }

                setId(*animatedObjectIt);

                return;
            }
        }
    }
*/

/*
    void doDecay()
    {
        for (auto& decayObjects : tb::decayObjectsList)
        {
            auto decayObjectIt = std::find(decayObjects.begin(), decayObjects.end(), m_id);

            if (decayObjectIt != decayObjects.end())
            {
                decayObjectIt++;

                if (decayObjectIt == decayObjects.end())
                {
                    setIsReadyForErase(true);
                    return;
                }

                setId(*decayObjectIt);

                m_clockDecay.restart();

                return;
            }
        }
    }
*/

/*
    void doRegenerate()
    {
        if (m_id == tb::SpriteData::bushBlueBerryEmpty)
        {
            setId(tb::SpriteData::bushBlueBerry);
        }
        if (m_id == tb::SpriteData::snowBallMoundEmpty)
        {
            setId(tb::SpriteData::snowBallMound);
        }
        else if (m_id == tb::SpriteData::grassJungleCut)
        {
            setId(tb::SpriteData::grassJungle);
        }
        else if (m_id == tb::SpriteData::wheatCut)
        {
            setId(tb::SpriteData::wheatGreen);
        }
        else if (m_id == tb::SpriteData::wheatGreen)
        {
            setId(tb::SpriteData::wheatYellow);
        }
        else if (m_id == tb::SpriteData::digHole[1])
        {
            setId(tb::SpriteData::digHole[0]);
        }
        else if (m_id == tb::SpriteData::digHoleIce[1])
        {
            setId(tb::SpriteData::digHoleIce[0]);
        }

        m_clockRegenerate.restart();
    }
*/

    tb::SpriteID_t getSpriteID()
    {
        return m_spriteID;
    }

    void setSpriteID(tb::SpriteID_t id)
    {
        m_spriteID = id;

        m_sprite.setID(m_spriteID);

/*
        m_flags = tb::UMaps::spriteFlags[m_id];

        if (m_flags.test(tb::SpriteFlags::tileEdge))
        {
            setDrawIndex(tb::DRAW_INDEX_TILE_EDGE);
        }

        if (m_flags.test(tb::SpriteFlags::decal))
        {
            setDrawIndex(tb::DRAW_INDEX_DECAL);
        }

        if (m_flags.test(tb::SpriteFlags::drawLast))
        {
            setDrawIndex(tb::DRAW_INDEX_LAST);
        }

        if
        (
            m_flags.test(tb::SpriteFlags::tileEdge) == false &&
            m_flags.test(tb::SpriteFlags::decal)    == false &&
            m_flags.test(tb::SpriteFlags::drawLast) == false
        )
        {
            setDrawIndex(tb::DRAW_INDEX_DEFAULT);
        }

        if (m_flags.test(tb::SpriteFlags::transparent))
        {
            m_sprite[0].setColor(sf::Color::Transparent);
        }
        else
        {
            m_sprite[0].setColor(sf::Color::White);
        }

        if (m_flags.test(tb::SpriteFlags::offset))
        {
            m_sprite[0].setPosition
            (
                -tb::THING_DRAW_OFFSET,
                -tb::THING_DRAW_OFFSET
            );
        }
*/
    }

/*
    void setIdByCount()
    {
        for (auto groupableObjectsIt = tb::groupedObjectsList.begin(); groupableObjectsIt != tb::groupedObjectsList.end(); groupableObjectsIt++)
        {
            auto groupableObjectIt = std::find(groupableObjectsIt->begin(), groupableObjectsIt->end(), m_id);

            if (groupableObjectIt != groupableObjectsIt->end())
            {
                setId
                (
                    tb::groupedObjectsList
                        .at(std::distance(tb::groupedObjectsList.begin(), groupableObjectsIt))
                        .at(tb::Utility::getGroupableObjectIndexByCount(m_count, groupableObjectsIt->size()))
                );

                return;
            }
        }
    }

    void setCountByID()
    {
        for (auto& groupableObjects : tb::groupedObjectsList)
        {
            auto groupableObjectIt = std::find(groupableObjects.begin(), groupableObjects.end(), m_id);

            if (groupableObjectIt != groupableObjects.end())
            {
                m_count = tb::Utility::getCountByGroupableObjectIndex(groupableObjectIt - groupableObjects.begin(), groupableObjects.size());
                return;
            }
        }
    }
*/

    void setCount(int count)
    {
        m_count = count;
    }

    int getCount()
    {
        return m_count;
    }

    tb::ObjectType getType()
    {
        return m_type;
    }

    void setType(tb::ObjectType type)
    {
        m_type = type;
    }

    const tb::Sprite& getSprite() const
    {
        return m_sprite;
    }

    void setIsDecay(bool b)
    {
        m_isDecay = b;

        m_clockDecay.restart();
    }

    bool isDecay()
    {
        return m_isDecay;
    }

    sf::Clock* getClockDecay()
    {
        return &m_clockDecay;
    }

    sf::Clock* getClockRegenerate()
    {
        return &m_clockRegenerate;
    }

private:

    tb::SpriteID_t m_spriteID = tb::Constants::SpriteIDDefault;

    tb::ObjectType m_type = tb::ObjectType::Null;

    uint8_t m_count = 1;

    tb::Sprite m_sprite;

    bool m_isDecay = false;

    sf::Clock m_clockDecay;

    sf::Clock m_clockRegenerate;

};

}

