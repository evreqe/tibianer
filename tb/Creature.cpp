#include "common.h"

#include "tb/Creature.h"

namespace tb
{

Creature::Creature() :
    m_dummySprite(tb::Resources::Textures::SpriteSheet)
{
    setThingType(tb::ThingType::Creature);
}

Creature::~Creature()
{
    //
}

Creature::Creature(const tb::TileCoords& tileCoords, tb::AxisZ axisZ) :
    m_dummySprite(tb::Resources::Textures::SpriteSheet)
{
    setThingType(tb::ThingType::Creature);

    setTileCoords(tileCoords);
    setAxisZ(axisZ);

    m_dummySprite.setID(2181);
    m_dummySprite.setTileWidthAndHeightByID(2181);
}

Creature::Properties* Creature::getProperties()
{
    return &m_properties;
}

Creature::Skills* Creature::getSkills()
{
    return &m_skills;
}

Creature::Outfit* Creature::getOutfit()
{
    return &m_outfit;
}

void Creature::update()
{
    tb::PixelCoords pixelCoords = getPixelCoords();

    m_dummySprite.setPosition(pixelCoords);

    if (m_properties.HasOutfit == true)
    {
        pixelCoords.x -= tb::Constants::TileCreatureOffset;
        pixelCoords.y -= tb::Constants::TileCreatureOffset;

        for (std::uint32_t i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
        {
            for (std::uint32_t j = 0; j < tb::Constants::NumOutfitSpriteDirections; j++)
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

    bool applyDirection = false;

    tb::Direction direction = tb::Direction::Down;

    switch (movementDirection)
    {
        case tb::MovementDirection::Up:
            direction = tb::Direction::Up;
            applyDirection = true;
            break;

        case tb::MovementDirection::Right:
            direction = tb::Direction::Right;
            applyDirection = true;
            break;

        case tb::MovementDirection::Down:
            direction = tb::Direction::Down;
            applyDirection = true;
            break;

        case tb::MovementDirection::Left:
            direction = tb::Direction::Left;
            applyDirection = true;
            break;
    }

    if (applyDirection == true)
    {
        setDirection(direction);
    }
}

std::uint8_t Creature::getTileOffset()
{
    //
}

void Creature::setTileOffset(std::uint8_t tileOffset)
{
    //
}

std::string* Creature::getName()
{
    return &m_name;
}

void Creature::setName(const std::string& name)
{
    m_name = name;
}

std::string* Creature::getDescription()
{
    return &m_description;
}

void Creature::setDescription(const std::string& description)
{
    m_description = description;
}

tb::Direction Creature::getDirection()
{
    return m_direction;
}

void Creature::setDirection(tb::Direction direction)
{
    m_direction = direction;
}

std::uint8_t Creature::getTeamIndex()
{
    return m_teamIndex;
}

void Creature::setTeamIndex(std::uint8_t teamIndex)
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

void Creature::setOutfitSprites(std::uint8_t head, std::uint8_t body, std::uint8_t legs, std::uint8_t feet)
{
    for (std::uint32_t i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
    {
        m_outfitSpriteIDArray.at(i).clear();
        m_outfitSpriteList.at(i).clear();
    }

    m_outfitSpriteIDArray.at(tb::Constants::OutfitIndexHead) = g_OutfitSpritesData.getDataList()->at(tb::Constants::OutfitIndexHead).SpriteIDList_List.at(head);
    m_outfitSpriteIDArray.at(tb::Constants::OutfitIndexBody) = g_OutfitSpritesData.getDataList()->at(tb::Constants::OutfitIndexBody).SpriteIDList_List.at(body);
    m_outfitSpriteIDArray.at(tb::Constants::OutfitIndexLegs) = g_OutfitSpritesData.getDataList()->at(tb::Constants::OutfitIndexLegs).SpriteIDList_List.at(legs);
    m_outfitSpriteIDArray.at(tb::Constants::OutfitIndexFeet) = g_OutfitSpritesData.getDataList()->at(tb::Constants::OutfitIndexFeet).SpriteIDList_List.at(feet);

    for (std::uint32_t i = 0; i < tb::Constants::NumOutfitSpriteIndex; i++)
    {
        for (std::uint32_t j = 0; j < tb::Constants::NumOutfitSpriteDirections; j++)
        {
            tb::SpriteID spriteID = m_outfitSpriteIDArray.at(i).at(j);

            tb::Sprite sprite(tb::Resources::Textures::SpriteSheet);
            sprite.setID(spriteID);

            m_outfitSpriteList.at(i).push_back(sprite);
        }
    }
}

void Creature::setOutfit(std::uint8_t head, std::uint8_t body, std::uint8_t legs, std::uint8_t feet)
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
        tb::Sprite* spriteHead = &m_outfitSpriteList.at(tb::Constants::OutfitIndexHead).at(magic_enum::enum_integer(m_direction));
        tb::Sprite* spriteBody = &m_outfitSpriteList.at(tb::Constants::OutfitIndexBody).at(magic_enum::enum_integer(m_direction));
        tb::Sprite* spriteLegs = &m_outfitSpriteList.at(tb::Constants::OutfitIndexLegs).at(magic_enum::enum_integer(m_direction));
        tb::Sprite* spriteFeet = &m_outfitSpriteList.at(tb::Constants::OutfitIndexFeet).at(magic_enum::enum_integer(m_direction));

        spriteList.push_back(spriteFeet);
        spriteList.push_back(spriteLegs);
        spriteList.push_back(spriteBody);
        spriteList.push_back(spriteHead);
    }

    return spriteList;
}

}
