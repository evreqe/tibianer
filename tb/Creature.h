#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"

#include "tb/OutfitSpritesData.h"

#include "tb/Thing.h"
#include "tb/Sprite.h"
//#include "tb/Container.h"

namespace tb
{

class Creature : public tb::Thing
{

public:

    Creature();
    ~Creature();
    Creature(const sf::Vector2i& tileCoords, tb::ZAxis_t z);

    using Ptr = std::shared_ptr<tb::Creature>;
    using List = std::vector<tb::Creature::Ptr>;

    using OutfitSpriteIDArray = std::array<tb::SpriteIDList, tb::Constants::NumOutfitSpriteIndex>;
    using OutfitSpriteList = std::array<tb::Sprite::List, tb::Constants::NumOutfitSpriteIndex>;

    struct Properties_t
    {
        bool IsPlayer = false;
        bool IsDead = false;
        bool IsSleeping = false;
        bool HasCustomName = false;
        bool HasOutfit = false;
    };

    struct Skills_t
    {
        std::uint32_t FistFighting        = tb::Constants::SkillLevelDefault;
        std::uint32_t ClubFighting        = tb::Constants::SkillLevelDefault;
        std::uint32_t SwordFighting       = tb::Constants::SkillLevelDefault;
        std::uint32_t AxeFighting         = tb::Constants::SkillLevelDefault;
        std::uint32_t DistanceFighting    = tb::Constants::SkillLevelDefault;
        std::uint32_t Shielding           = tb::Constants::SkillLevelDefault;
        std::uint32_t Fishing             = tb::Constants::SkillLevelDefault;
    };

    struct Outfit_t
    {
        std::uint8_t Head = 0;
        std::uint8_t Body = 0;
        std::uint8_t Legs = 0;
        std::uint8_t Feet = 0;
    };

    Properties_t* getProperties();
    Skills_t* getSkills();
    Outfit_t* getOutfit();

    void update();

    void setDirectionByMovementDirection(tb::MovementDirection movementDirection);

    std::uint8_t getTileOffset();
    void setTileOffset(std::uint8_t tileOffset);

    std::string getName();
    void setName(const std::string& name);

    std::string getDescription();
    void setDescription(const std::string& description);

    tb::Direction getDirection();
    void setDirection(tb::Direction direction);

    std::uint8_t getTeamIndex();
    void setTeamIndex(std::uint8_t teamIndex);

    tb::Vocation getVocation();
    void setVocation(tb::Vocation vocation);

    tb::BloodType getBloodType();
    void setBloodType(tb::BloodType bloodType);

    float getMovementSpeed();
    void setMovementSpeed(float movementSpeed);

    sf::Clock* getMovementClock();

    tb::Sprite* getDummySprite();

    OutfitSpriteIDArray* getOutfitSpriteIDArray();
    OutfitSpriteList* getOutfitSpriteList();

    void setOutfitSprites(std::uint8_t head, std::uint8_t body, std::uint8_t legs, std::uint8_t feet);
    void setOutfit(std::uint8_t head, std::uint8_t body, std::uint8_t legs, std::uint8_t feet);

    std::vector<tb::Sprite*> getSpriteList();

private:

    Properties_t m_properties;
    Skills_t m_skills;
    Outfit_t m_outfit;

    std::uint8_t m_tileOffset = 0;
    std::uint8_t m_tileWidth = 1;
    std::uint8_t m_tileHeight = 1;

    std::string m_name;
    std::string m_description;

    tb::Direction m_direction = tb::Direction::Down;

    std::uint8_t m_teamIndex = 0;

    tb::Vocation m_vocation = tb::Vocation::None;

    tb::BloodType m_bloodType = tb::BloodType::None;

    std::uint32_t m_healthPoints = 10;
    std::uint32_t m_healthPointsMax = 10;

    std::uint32_t m_manaPoints = 0;
    std::uint32_t m_manaPointsMax = 0;

    std::uint32_t m_bankGold = 0;
    std::uint32_t m_bankPlatinum = 0;

    std::uint32_t m_experiencePoints = 0;
    std::uint32_t m_magicExperiencePoints = 0;

    std::uint32_t m_level = 1;
    std::uint32_t m_magicLevel = 0;

    std::uint32_t m_capacity = 0; // encumbrance

    float m_movementSpeed = 0.5f;
    sf::Clock m_movementClock;

    tb::Sprite m_dummySprite;

    // head, body, legs, feet
    tb::Creature::OutfitSpriteIDArray m_outfitSpriteIDArray;

    tb::Creature::OutfitSpriteList m_outfitSpriteList;

/*
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        if (m_isDead == true)
        {
            target.draw(m_spriteCorpse[0], states);

            if (m_corpseSize == tb::CreatureCorpseSizes::medium)
            {
                target.draw(m_spriteCorpse[1], states);
            }
            else if (m_corpseSize == tb::CreatureCorpseSizes::large)
            {
                target.draw(m_spriteCorpse[1], states);
                target.draw(m_spriteCorpse[2], states);
                target.draw(m_spriteCorpse[3], states);
            }

            return;
        }

        if (m_isSleeping == true)
        {
            return;
        }

        if (m_hasOutfit == false)
        {
            target.draw(m_sprite[0], states);

            if (m_size == tb::CreatureSizes::medium)
            {
                target.draw(m_sprite[1], states);
            }
            else if (m_size == tb::CreatureSizes::large)
            {
                target.draw(m_sprite[1], states);
                target.draw(m_sprite[2], states);
                target.draw(m_sprite[3], states);
            }
        }
        else
        {
            // draw in reverse: feet, legs, body, head
            target.draw(m_spriteOutfit[3], states);
            target.draw(m_spriteOutfit[2], states);
            target.draw(m_spriteOutfit[1], states);
            target.draw(m_spriteOutfit[0], states);
        }
    }
*/

};

}
