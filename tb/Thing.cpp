#include "common.h"

#include "tb/Thing.h"

namespace tb
{

Thing::Thing()
{
    //
}

Thing::~Thing()
{
    //
}

Thing::Properties* Thing::getProperties()
{
    return &m_properties;
}

std::uint64_t Thing::getUniqueID()
{
    return m_uniqueID;
}

void Thing::setUniqueID(std::uint64_t uniqueID)
{
    m_uniqueID = uniqueID;
}

tb::ThingType Thing::getThingType()
{
    return m_thingType;
}

void Thing::setThingType(tb::ThingType thingType)
{
    m_thingType = thingType;
}

tb::DrawOrderType Thing::getDrawOrderType()
{
    return m_drawOrderType;
}

void Thing::setDrawOrderType(tb::DrawOrderType drawOrderType)
{
    m_drawOrderType = drawOrderType;
}

std::uint8_t Thing::getDrawOffset()
{
    return m_drawOffset;
}

void Thing::setDrawOffset(std::uint8_t drawOffset)
{
    m_drawOffset = drawOffset;
}

}
