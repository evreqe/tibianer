#pragma once

#include "common.h"

#include "tb/Constants.h"

#include "tb/TileBase.h"

namespace tb
{

class Thing : public tb::TileBase
{

public:

    Thing();
    ~Thing();

    using Ptr = std::shared_ptr<tb::Thing>;
    using List = std::vector<tb::Thing::Ptr>;

    struct SortByTileIndex
    {
        bool operator()(tb::Thing::Ptr a, tb::Thing::Ptr b) const
        {
            return (a->getTileIndex() < b->getTileIndex());
        }
    };

    struct SortByTileCoords
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

    struct Properties
    {
        bool ShouldErase = false;
    };

    Properties* getProperties();

    std::uint64_t getUniqueID();
    void setUniqueID(std::uint64_t uniqueID);

    tb::ThingType getThingType();
    void setThingType(tb::ThingType thingType);

    tb::DrawOrderType getDrawOrderType();
    void setDrawOrderType(tb::DrawOrderType drawOrder);

    std::uint8_t getDrawOffset();
    void setDrawOffset(std::uint8_t drawOffset);

private:

    Properties m_properties;

    std::uint64_t m_uniqueID = 0;

    tb::ThingType m_thingType = tb::ThingType::Null;

    tb::DrawOrderType m_drawOrderType = tb::DrawOrderType::Default;

    std::uint8_t m_drawOffset = 0;

};

}
