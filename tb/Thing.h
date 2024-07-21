#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class Thing
{

public:

    Thing();
    ~Thing();

    using Ptr = std::shared_ptr<tb::Thing>;
    using List = std::vector<tb::Thing::Ptr>;

    struct SortByTileIndex_t
    {
        bool operator()(tb::Thing::Ptr a, tb::Thing::Ptr b) const
        {
            return (a->getTileIndex() < b->getTileIndex());
        }
    };

    struct SortByTileCoords_t
    {
        bool operator()(tb::Thing::Ptr a, tb::Thing::Ptr b) const
        {
            if (a->getTileX() == b->getTileX())
            {
                if (a->getTileY() == b->getTileY())
                {
                    return a->getDrawOrderType() < b->getDrawOrderType();
                }
                else
                {
                    return a->getTileY() < b->getTileY();
                }
            }

            return a->getTileX() < b->getTileX();
        }
    };

    struct ThingProperties_t
    {
        bool Erase = false;
    };

    ThingProperties_t* getThingProperties();

    std::uint32_t getTileIndex();
    void setTileIndex(std::uint32_t tileIndex);

    sf::Vector2i getTileCoords();
    void setTileCoords(const sf::Vector2i& tileCoords);

    std::int32_t getTileX();
    void setTileX(std::int32_t tileX);

    std::int32_t getTileY();
    void setTileY(std::int32_t tileY);

    sf::Vector2f getPixelCoords();
    void setPixelCoords(const sf::Vector2f& pixelCoords);

    float getPixelX();
    void setPixelX(float pixelX);

    float getPixelY();
    void setPixelY(float pixelY);

    tb::ZAxis_t getZ();
    void setZ(tb::ZAxis_t z);

    tb::ThingType getThingType();
    void setThingType(tb::ThingType thingType);

    tb::DrawOrderType getDrawOrderType();
    void setDrawOrderType(tb::DrawOrderType drawOrder);

    std::uint8_t getDrawOffset();
    void setDrawOffset(std::uint8_t drawOffset);

private:

    ThingProperties_t m_thingProperties;

    std::uint32_t m_uniqueID = 0;

    std::uint32_t m_tileIndex = 0;

    sf::Vector2i m_tileCoords;
    sf::Vector2f m_pixelCoords;

    tb::ZAxis_t m_z = 0;

    tb::ThingType m_thingType = tb::ThingType::Null;

    tb::DrawOrderType m_drawOrderType = tb::DrawOrderType::Default;

    std::uint8_t m_drawOffset = 0;

};

}
