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

Creature::Outfit_t* Creature::getOutfit()
{
    return &m_outfit;
}

void Creature::update()
{
    sf::Vector2f pixelCoords = getPixelCoords();

    m_dummySprite.setPosition(pixelCoords);

    if (m_properties.HasOutfit == true)
    {
        pixelCoords.x -= tb::Constants::TileCreatureOffset;
        pixelCoords.y -= tb::Constants::TileCreatureOffset;

        for (unsigned int i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
        {
            for (unsigned int j = 0; j < tb::Constants::NumOutfitSpriteDirections; j++)
            {
                m_outfitSpriteList.at(i).at(j).setPosition(pixelCoords);
            }
        }
    }
}

void Creature::setDirectionByMovementDirection(tb::MovementDirection movementDirection)
{
    if (movementDirection == tb::MovementDirection::Null)
    {
        return;
    }

    tb::Direction direction = tb::Direction::Down;

    switch (movementDirection)
    {
        case tb::MovementDirection::Up:
            direction = tb::Direction::Up;
            break;

        case tb::MovementDirection::Right:
            direction = tb::Direction::Right;
            break;

        case tb::MovementDirection::Down:
            direction = tb::Direction::Down;
            break;

        case tb::MovementDirection::Left:
            direction = tb::Direction::Left;
            break;
    }

    setDirection(direction);
}

std::string Creature::getName()
{
    return m_name;
}

void Creature::setName(const std::string& name)
{
    m_name = name;
}

tb::Direction Creature::getDirection()
{
    return m_direction;
}

void Creature::setDirection(tb::Direction direction)
{
    m_direction = direction;
}

uint8_t Creature::getTeamIndex()
{
    return m_teamIndex;
}

void Creature::setTeamIndex(uint8_t teamIndex)
{
    m_teamIndex = teamIndex;
}

tb::Vocation Creature::getVocation()
{
    return m_vocation;
}

void Creature::setVocation(tb::Vocation vocation)
{
    m_vocation = vocation;
}

tb::BloodType Creature::getBloodType()
{
    return m_bloodType;
}

void Creature::setBloodType(tb::BloodType bloodType)
{
    m_bloodType = bloodType;
}

float Creature::getMovementSpeed()
{
    return m_movementSpeed;
}

void Creature::setMovementSpeed(float movementSpeed)
{
    m_movementSpeed = movementSpeed;
}

sf::Clock* Creature::getMovementClock()
{
    return &m_movementClock;
}

tb::Sprite* Creature::getDummySprite()
{
    return &m_dummySprite;
}

tb::Creature::OutfitSpriteIDArray* Creature::getOutfitSpriteIDArray()
{
    return &m_outfitSpriteIDArray;
}

tb::Creature::OutfitSpriteList* Creature::getOutfitSpriteList()
{
    return &m_outfitSpriteList;
}

void Creature::setOutfitSprites(uint8_t head, uint8_t body, uint8_t legs, uint8_t feet)
{
    for (unsigned int i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
    {
        m_outfitSpriteIDArray.at(i).clear();
        m_outfitSpriteList.at(i).clear();
    }

    m_outfitSpriteIDArray.at(tb::OutfitIndex::Head) = g_OutfitData.getDataList()->at(tb::OutfitIndex::Head).SpriteIDList_List.at(head);
    m_outfitSpriteIDArray.at(tb::OutfitIndex::Body) = g_OutfitData.getDataList()->at(tb::OutfitIndex::Body).SpriteIDList_List.at(body);
    m_outfitSpriteIDArray.at(tb::OutfitIndex::Legs) = g_OutfitData.getDataList()->at(tb::OutfitIndex::Legs).SpriteIDList_List.at(legs);
    m_outfitSpriteIDArray.at(tb::OutfitIndex::Feet) = g_OutfitData.getDataList()->at(tb::OutfitIndex::Feet).SpriteIDList_List.at(feet);

    for (unsigned int i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
    {
        for (unsigned int j = 0; j < tb::Constants::NumOutfitSpriteDirections; j++)
        {
            tb::SpriteID_t spriteID = m_outfitSpriteIDArray.at(i).at(j);

            tb::Sprite sprite;
            sprite.setID(spriteID);

            m_outfitSpriteList.at(i).push_back(sprite);
        }
    }
}

void Creature::setOutfit(uint8_t head, uint8_t body, uint8_t legs, uint8_t feet)
{
    if (head > tb::Constants::NumOutfitSpriteIDListHead - 1)
    {
        head = 0;
    }

    if (body > tb::Constants::NumOutfitSpriteIDListBody - 1)
    {
        body = 0;
    }

    if (legs > tb::Constants::NumOutfitSpriteIDListLegs - 1)
    {
        legs = 0;
    }

    if (feet > tb::Constants::NumOutfitSpriteIDListFeet - 1)
    {
        feet = 0;
    }

    m_outfit.Head = head;
    m_outfit.Body = body;
    m_outfit.Legs = legs;
    m_outfit.Feet = feet;

    setOutfitSprites(head, body, legs, feet);
}

std::vector<tb::Sprite*> Creature::getSpriteList()
{
    std::vector<tb::Sprite*> spriteList;

    if (m_properties.HasOutfit == true)
    {
        tb::Sprite* spriteHead = &m_outfitSpriteList.at(tb::OutfitIndex::Head).at(magic_enum::enum_integer(m_direction));
        tb::Sprite* spriteBody = &m_outfitSpriteList.at(tb::OutfitIndex::Body).at(magic_enum::enum_integer(m_direction));
        tb::Sprite* spriteLegs = &m_outfitSpriteList.at(tb::OutfitIndex::Legs).at(magic_enum::enum_integer(m_direction));
        tb::Sprite* spriteFeet = &m_outfitSpriteList.at(tb::OutfitIndex::Feet).at(magic_enum::enum_integer(m_direction));

        spriteList.push_back(spriteFeet);
        spriteList.push_back(spriteLegs);
        spriteList.push_back(spriteBody);
        spriteList.push_back(spriteHead);
    }

    return spriteList;
}

}
