#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "tb/Log.h"

namespace tb
{

class Thing
{

public:

    Thing();
    virtual ~Thing();

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
            ////return (a->getTileX() == b->getTileX() ? a->getTileY() < b->getTileY() : a->getTileX() < b->getTileX());

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

    uint32_t getTileIndex();
    void setTileIndex(uint32_t tileIndex);

    sf::Vector2u getTileCoords();
    void setTileCoords(const sf::Vector2u& tileCoords);

    uint32_t getTileX();
    void setTileX(uint32_t tileX);

    uint32_t getTileY();
    void setTileY(uint32_t tileY);

    sf::Vector2u getPixelCoords();
    void setPixelCoords(const sf::Vector2u& pixelCoords);

    uint32_t getPixelX();
    void setPixelX(uint32_t pixelX);

    uint32_t getPixelY();
    void setPixelY(uint32_t pixelY);

    tb::ZAxis_t getZ();
    void setZ(tb::ZAxis_t z);

    tb::ThingType getThingType();
    void setThingType(tb::ThingType thingType);

    tb::DrawOrderType getDrawOrderType();
    void setDrawOrderType(tb::DrawOrderType drawOrder);

    uint8_t getDrawOffset();
    void setDrawOffset(uint8_t drawOffset);

    bool getIsReadyForErase();
    void setIsReadyForErase(bool b);

private:

    uint32_t m_uniqueID = 0;

    uint32_t m_tileIndex = 0;

    sf::Vector2u m_tileCoords;
    sf::Vector2u m_pixelCoords;

    tb::ZAxis_t m_z = 0;

    tb::ThingType m_thingType = tb::ThingType::Null;

    tb::DrawOrderType m_drawOrderType = tb::DrawOrderType::Default;

    uint8_t m_drawOffset = 0;

    bool m_isReadyForErase = false;
};

}
