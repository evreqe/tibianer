#include "tb/Object.h"

namespace tb
{

Object::Object()
{
    setThingType(tb::ThingType::Object);
}

Object::~Object()
{
    //
}

Object::Properties_t* Object::getProperties()
{
    return &m_properties;
}

Object::Object(const sf::Vector2i& tileCoords, tb::ZAxis_t z, tb::SpriteID_t spriteID)
{
    setThingType(tb::ThingType::Object);

    setTileCoords(tileCoords);
    setZ(z);

    setSpriteID(spriteID);

    update();

    //if (m_flags.test(tb::SpriteFlags::groupable))
    //{
        //setCountById();
    //}

    // TODO: get object type from sprite data
    //tb::ObjectType objectType = x;
    //setObjectType(objectType);
}

void Object::update()
{
    sf::Vector2f pixelCoords = getPixelCoords();

    m_sprite.setPosition(pixelCoords);
}

/*
    void Object::doAnimation()
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
    void Object::doDecay()
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
    void Object::doRegenerate()
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

tb::Sprite* Object::getSprite()
{
    return &m_sprite;
}

tb::SpriteID_t Object::getSpriteID()
{
    return m_sprite.getID();
}

void Object::setSpriteID(tb::SpriteID_t spriteID)
{
    m_sprite.setID(spriteID);

    m_sprite.setTileWidthAndHeightByID(spriteID);

    //tb::SpriteData::Data* data = &g_SpriteData.getDataList()->at(spriteID);

    //if (data == nullptr)
    //{
        //g_Log.write("data == nullptr\n");
        //return;
    //}

    //g_Log.write("spriteID: {}\n", spriteID);

    //g_Log.write("tileWidth: {}\n", data->TileWidth);
    //g_Log.write("tileHeight: {}\n", data->TileHeight);

    //m_sprite.setTileHeight(data->TileWidth);
    //m_sprite.setTileWidth(data->TileHeight);

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

tb::ObjectType Object::getObjectType()
{
    return m_objectType;
}

void Object::setObjectType(tb::ObjectType objectType)
{
    m_objectType = objectType;
}

void Object::setCount(uint32_t count)
{
    m_count = count;
}

uint32_t Object::getCount()
{
    return m_count;
}

sf::Clock* Object::getDecayClock()
{
    return &m_decayClock;
}

sf::Clock* Object::getRegenerateClock()
{
    return &m_regenerateClock;
}

}
