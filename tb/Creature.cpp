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

Creature::Creature(const sf::Vector2i& tileCoords, tb::ZAxis_t z)
{
    setThingType(tb::ThingType::Creature);

    setTileCoords(tileCoords);
    setZ(z);

    m_dummySprite.setID(2182);
    m_dummySprite.setTileWidthAndHeightByID(2182);
}

Creature::Properties_t* Creature::getProperties()
{
    return &m_properties;
}

Creature::Skills_t* Creature::getSkills()
{
    return &m_skills;
}

void Creature::update()
{
    sf::Vector2f pixelCoords = getPixelCoords();

    m_dummySprite.setPosition(pixelCoords);
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

void Creature::setOutfitSprite(tb::OutfitIndex_t outfitIndex, const tb::Sprite& sprite)
{
    m_outfitSpriteList.at(outfitIndex) = sprite;
}

}
