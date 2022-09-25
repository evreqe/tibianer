#include "tb/Creature.h"

namespace tb
{

Creature::Creature()
{
    setThingType(tb::ThingType::Creature);
}

Creature::~Creature()
{
    //
}

Creature::Creature(const sf::Vector2u& tileCoords, tb::ZAxis_t z)
{
    setThingType(tb::ThingType::Creature);

    setTileCoords(tileCoords);
    setZ(z);

    m_dummySprite.setID(2182);
}

void Creature::update()
{
    m_dummySprite.setPosition(getPixelX(), getPixelY());
}

Creature::Properties_t* Creature::getProperties()
{
    return &m_properties;
}

Creature::Skills_t* Creature::getSkills()
{
    return &m_skills;
}

std::string Creature::getName()
{
    return m_name;
}

void Creature::setName(const std::string& name)
{
    m_name = name;
}

tb::Sprite* Creature::getDummySprite()
{
    return &m_dummySprite;
}

tb::SpriteID_t Creature::getOutfitSpriteID(tb::OutfitIndex_t outfitIndex)
{
    return m_outfitSpriteIDList.at(outfitIndex);
}

void Creature::setOutfitSpriteID(tb::OutfitIndex_t outfitIndex, tb::SpriteID_t spriteID)
{
    m_outfitSpriteIDList.at(outfitIndex) = spriteID;
}

tb::Sprite* Creature::getOutfitSprite(tb::OutfitIndex_t outfitIndex)
{
    return &m_outfitSpriteList.at(outfitIndex);
}

void Creature::setOutfitSprite(tb::OutfitIndex_t outfitIndex, tb::Sprite sprite)
{
    m_outfitSpriteList.at(outfitIndex) = sprite;
}

}
