#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"

#include "tb/OutfitData.h"

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
        uint32_t FistFighting        = tb::Constants::SkillLevelDefault;
        uint32_t ClubFighting        = tb::Constants::SkillLevelDefault;
        uint32_t SwordFighting       = tb::Constants::SkillLevelDefault;
        uint32_t AxeFighting         = tb::Constants::SkillLevelDefault;
        uint32_t DistanceFighting    = tb::Constants::SkillLevelDefault;
        uint32_t Shielding           = tb::Constants::SkillLevelDefault;
        uint32_t Fishing             = tb::Constants::SkillLevelDefault;
    };

    Properties_t* getProperties();
    Skills_t* getSkills();

    void update();

    uint8_t getTileOffset();
    void setTileOffset(uint8_t tileOffset);

    std::string getName();
    void setName(const std::string& name);

    tb::Direction getDirection();
    void setDirection(tb::Direction direction);

    uint8_t getTeamIndex();
    void setTeamIndex(uint8_t teamIndex);

    tb::Vocation getVocation();
    void setVocation(tb::Vocation vocation);

    tb::BloodType getBloodType();
    void setBloodType(tb::BloodType bloodType);

    tb::Sprite* getDummySprite();

    tb::SpriteID_t getOutfitSpriteID(tb::OutfitIndex_t outfitIndex);
    void setOutfitSpriteID(tb::OutfitIndex_t outfitIndex, tb::SpriteID_t spriteID);

    tb::Sprite* getOutfitSprite(tb::OutfitIndex_t outfitIndex);
    void setOutfitSprite(tb::OutfitIndex_t outfitIndex, const tb::Sprite& sprite);

private:

    Properties_t m_properties;

    Skills_t m_skills;

    uint8_t m_tileOffset;
    uint8_t m_tileWidth;
    uint8_t m_tileHeight;

    std::string m_name;

    tb::Direction m_direction;

    tb::BloodType m_bloodType;

    uint8_t m_teamIndex;

    tb::Vocation m_vocation;

    uint32_t m_healthPoints;
    uint32_t m_healthPointsMax;

    uint32_t m_manaPoints;
    uint32_t m_manaPointsMax;

    uint32_t m_bankGold;
    uint32_t m_bankPlatinum;

    uint32_t m_experiencePoints;
    uint32_t m_magicExperiencePoints;

    uint32_t m_level;
    uint32_t m_magicLevel;

    uint32_t m_capacity; // encumbrance

    tb::Sprite m_dummySprite;

    //std::vector<int> m_spritesList;
    //std::vector<int> m_spritesCorpseList;

    //tb::Sprite m_sprite[tb::NUM_CREATURE_SPRITES];
    //tb::Sprite m_spriteCorpse[tb::NUM_CREATURE_SPRITES];

    // head, body, legs, feet
    std::array<tb::SpriteID_t, tb::Constants::NumOutfitSpriteIndex> m_outfitSpriteIDList;

    // up, right, down, left
    std::array<tb::Sprite, tb::Constants::NumOutfitSpriteDirections> m_outfitSpriteList;

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
