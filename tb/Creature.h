#pragma once

#include <cstdlib>
#include <ctime>

#include <string>

#include <SFML/Graphics.hpp>

#include "utility.hpp"

#include "tb/Constants.hpp"
#include "tb/Sprite.hpp"
#include "tb/Thing.hpp"
#include "tb/Container.hpp"

namespace tb
{

class Creature : public tb::Thing
{

public:

    typedef std::shared_ptr<tb::Creature> Ptr;
    typedef std::vector<tb::Creature::Ptr> List;

    struct Skills_t
    {
        uint8_t FistFighting        = tb::Constants::SkillLevelDefault;
        uint8_t ClubFighting        = tb::Constants::SkillLevelDefault;
        uint8_t SwordFighting       = tb::Constants::SkillLevelDefault;
        uint8_t AxeFighting         = tb::Constants::SkillLevelDefault;
        uint8_t DistanceFighting    = tb::Constants::SkillLevelDefault;
        uint8_t Shielding           = tb::Constants::SkillLevelDefault;
        uint8_t Fishing             = tb::Constants::SkillLevelDefault;
    };

    Skills_t Skills;

    struct StatusEffect_t
    {
        int type;
        int damage;
        unsigned int ticks;

        sf::Time timePerTick;
        sf::Clock clock;

        std::string name;
    };

    typedef std::vector<tb::Creature::StatusEffect_t> StatusEffectList;

    Creature::Creature(int tileX, int tileY, int z)
    {
        setIsCreature(true);

        setTileCoords(tileX, tileY);
        setPosition(sf::Vector2f(tileX, tileY));

        setZ(z);

        m_tileOffset = tb::THING_DRAW_OFFSET;

        m_isPlayer      = false;
        m_hasCustomName = false;
        m_isDead        = false;
        m_isSleeping    = false;
        m_hasOutfit     = true;

        m_name = tb::CREATURE_NAME_DEFAULT;

        m_direction = tb::Directions::down;

        m_team = tb::Teams::good;

        m_vocation = tb::Vocations::none;

        m_type = tb::CreatureTypes::human;

        m_size = tb::CreatureSizes::small;

        m_corpseSize = tb::CreatureCorpseSizes::small;

        m_bloodType = tb::CreatureBloodTypes::red;

        m_movementSpeed = tb::MovementSpeeds::default;

        m_numAnimations = 1;

        m_currentAnimation = 0;

        m_spritesList = tb::CreatureSprites::human;

        m_spritesCorpseList = tb::CreatureCorpseSprites::human;

        m_outfit[0] = tb::Outfits::default[0];
        m_outfit[1] = tb::Outfits::default[1];
        m_outfit[2] = tb::Outfits::default[2];
        m_outfit[3] = tb::Outfits::default[3];

        m_level      = 1;
        m_magicLevel = 1;

        m_exp = 0;

        m_cap = tb::INVENTORY_OBJECTS_MAX;

        m_hp    = 100;
        m_hpMax = 100;

        m_mp    = 200;
        m_mpMax = 200;

        setPropertiesByType();
    }

    void setPropertiesByType()
    {
        if (m_hasCustomName == false)
        {
            m_name = tb::UMaps::creatureNames[m_type];
        }

        if (m_type != tb::CreatureTypes::human)
        {
            m_hasOutfit = false;
        }

        m_size = tb::UMaps::creatureSizes[m_type];

        if (m_size == tb::CreatureSizes::large)
        {
            m_tileOffset = 0;
        }
        else
        {
            m_tileOffset = tb::THING_DRAW_OFFSET;
        }

        m_numAnimations = tb::UMaps::creatureNumAnimations[m_type];

        m_corpseSize = tb::UMaps::creatureCorpseSizes[m_type];

        m_spritesList = tb::UMaps::creatureSprites[m_type];

        m_spritesCorpseList = tb::UMaps::creatureCorpseSprites[m_type];

        m_spriteCorpse[0].setId(m_spritesCorpseList[0]);

        if (m_corpseSize == tb::CreatureCorpseSizes::medium)
        {
            // move corpse so it doesn't overlap creatures
            m_spriteCorpse[0].move
            (
                sf::Vector2f
                (
                    tb::TILE_SIZE,
                    0
                )
            );

            m_spriteCorpse[1].setId(m_spritesCorpseList[1]);

            m_spriteCorpse[1].setPosition
            (
                sf::Vector2f
                (
                    m_spriteCorpse[0].getPosition().x - tb::TILE_SIZE,
                    m_spriteCorpse[0].getPosition().y
                )
            );
        }
        else if (m_corpseSize == tb::CreatureCorpseSizes::large)
        {
            // move corpse so it doesn't overlap creatures
            m_spriteCorpse[0].move
            (
                sf::Vector2f
                (
                    tb::TILE_SIZE,
                    tb::TILE_SIZE
                )
            );

            m_spriteCorpse[1].setId(m_spritesCorpseList[1]);
            m_spriteCorpse[2].setId(m_spritesCorpseList[2]);
            m_spriteCorpse[3].setId(m_spritesCorpseList[3]);

            m_spriteCorpse[1].setPosition
            (
                sf::Vector2f
                (
                    m_spriteCorpse[0].getPosition().x - tb::TILE_SIZE,
                    m_spriteCorpse[0].getPosition().y
                )
            );

            m_spriteCorpse[2].setPosition
            (
                sf::Vector2f
                (
                    m_spriteCorpse[0].getPosition().x,
                    m_spriteCorpse[0].getPosition().y - tb::TILE_SIZE
                )
            );

            m_spriteCorpse[3].setPosition
            (
                sf::Vector2f
                (
                    m_spriteCorpse[0].getPosition().x - tb::TILE_SIZE,
                    m_spriteCorpse[0].getPosition().y - tb::TILE_SIZE
                )
            );
        }

        m_bloodType = tb::UMaps::creatureBloodTypes[m_type];
    }

    void updateSprite()
    {
        if (m_spritesList.size() == 0)
        {
            return;
        }

        if (m_size == tb::CreatureSizes::small)
        {
            m_sprite[0].setId(m_spritesList[m_direction + (4 * m_currentAnimation)]);
        }
        else if (m_size == tb::CreatureSizes::medium)
        {
            m_sprite[0].setId(m_spritesList[m_direction +     (8 * m_currentAnimation)]);
            m_sprite[1].setId(m_spritesList[m_direction + 4 + (8 * m_currentAnimation)]);

            sf::Vector2f spriteOffset(0, 0);

            switch (m_direction)
            {
                case tb::Directions::up:
                case tb::Directions::down:
                    spriteOffset.y -= tb::TILE_SIZE;
                    break;

                case tb::Directions::right:
                case tb::Directions::left:
                    spriteOffset.x -= tb::TILE_SIZE;
                    break;
            }

            m_sprite[1].setPosition
            (
                sf::Vector2f
                (
                    m_sprite[0].getPosition().x + spriteOffset.x,
                    m_sprite[0].getPosition().y + spriteOffset.y
                )
            );
        }
        else if (m_size == tb::CreatureSizes::large)
        {
            m_sprite[0].setId(m_spritesList[m_direction      + (16 * m_currentAnimation)]);
            m_sprite[1].setId(m_spritesList[m_direction + 4  + (16 * m_currentAnimation)]);
            m_sprite[2].setId(m_spritesList[m_direction + 8  + (16 * m_currentAnimation)]);
            m_sprite[3].setId(m_spritesList[m_direction + 12 + (16 * m_currentAnimation)]);

            m_sprite[1].setPosition
            (
                sf::Vector2f
                (
                    m_sprite[0].getPosition().x - tb::TILE_SIZE,
                    m_sprite[0].getPosition().y
                )
            );

            m_sprite[2].setPosition
            (
                sf::Vector2f
                (
                    m_sprite[0].getPosition().x,
                    m_sprite[0].getPosition().y - tb::TILE_SIZE
                )
            );

            m_sprite[3].setPosition
            (
                sf::Vector2f
                (
                    m_sprite[0].getPosition().x - tb::TILE_SIZE,
                    m_sprite[0].getPosition().y - tb::TILE_SIZE
                )
            );
        }
    }

    void setOutfit(int head, int body, int legs, int feet)
    {
        m_outfit[0] = head;
        m_outfit[1] = body;
        m_outfit[2] = legs;
        m_outfit[3] = feet;

        updateOutfit();
    }

    void setOutfitRandom()
    {
        m_outfit[0] = utility::getRandomNumber((unsigned int)0, (tb::Outfits::head.size() / 4) - 1);
        m_outfit[1] = utility::getRandomNumber((unsigned int)0, (tb::Outfits::body.size() / 4) - 1);
        m_outfit[2] = utility::getRandomNumber((unsigned int)0, (tb::Outfits::legs.size() / 4) - 1);
        m_outfit[3] = utility::getRandomNumber((unsigned int)0, (tb::Outfits::feet.size() / 4) - 1);

        updateOutfit();
    }

    void updateOutfit()
    {
        m_spriteOutfit[0].setId(tb::Outfits::head[(m_outfit[0] * 4) + m_direction]);
        m_spriteOutfit[1].setId(tb::Outfits::body[(m_outfit[1] * 4) + m_direction]);
        m_spriteOutfit[2].setId(tb::Outfits::legs[(m_outfit[2] * 4) + m_direction]);
        m_spriteOutfit[3].setId(tb::Outfits::feet[(m_outfit[3] * 4) + m_direction]);
    }

    void updateAnimation()
    {
        m_timeAnimation = m_clockAnimation.getElapsedTime();

        if (m_timeAnimation.asSeconds() >= tb::CreatureData::animationFrameTime)
        {
            m_currentAnimation++;

            if (m_currentAnimation > m_numAnimations - 1)
            {
                m_currentAnimation = 0;
            }

            m_clockAnimation.restart();
        }
    }

    void updateCorpse()
    {
        int corpseId = m_spriteCorpse[0].getId();

        for (std::size_t i = 0; i < m_spritesCorpseList.size(); i++)
        {
            int spriteId = m_spritesCorpseList.at(i);

            if (corpseId == spriteId)
            {
                if (m_corpseSize == tb::CreatureCorpseSizes::medium)
                {
                    i = i + 2;
                }
                else if (m_corpseSize == tb::CreatureCorpseSizes::large)
                {
                    i = i + 4;
                }
                else
                {
                    i++;
                }

                if (i > m_spritesCorpseList.size() - 1)
                {
                    setIsReadyForErase(true);
                    return;
                }

                m_spriteCorpse[0].setId(m_spritesCorpseList.at(i));

                if (m_corpseSize == tb::CreatureCorpseSizes::medium)
                {
                    m_spriteCorpse[1].setId(m_spritesCorpseList.at(i + 1));
                }
                else if (m_corpseSize == tb::CreatureCorpseSizes::large)
                {
                    m_spriteCorpse[1].setId(m_spritesCorpseList.at(i + 1));
                    m_spriteCorpse[2].setId(m_spritesCorpseList.at(i + 2));
                    m_spriteCorpse[3].setId(m_spritesCorpseList.at(i + 3));
                }

                break;
            }
        }

        m_clockCorpse.restart();
    }

    void update()
    {
        updateTileCoords();

        int drawOffset = getDrawOffset() * tb::THING_DRAW_OFFSET;

        if (m_isDead == false)
        {
            drawOffset += m_tileOffset;
        }

        setPosition(getTileX() - drawOffset, getTileY() - drawOffset);

        updateSprite();
        updateOutfit();
        updateAnimation();
    }

    void doTurn(int direction)
    {
        if (direction == tb::Directions::null)
        {
            return;
        }

        int dir = direction;

        if (dir > tb::Directions::left)
        {
            int random = utility::getRandomNumber(1, 2);

            switch (dir)
            {
                case tb::Directions::upLeft:
                    if (random == 1)
                    {
                        dir = tb::Directions::up;
                    }
                    else
                    {
                        dir = tb::Directions::left;
                    }
                    break;

                case tb::Directions::upRight:
                    dir = utility::getRandomNumber(tb::Directions::up, tb::Directions::right);
                    break;

                case tb::Directions::downRight:
                    dir = utility::getRandomNumber(tb::Directions::right, tb::Directions::down);
                    break;

                case tb::Directions::downLeft:
                    dir = utility::getRandomNumber(tb::Directions::down, tb::Directions::left);
                    break;
            }
        }

        setDirection(dir);
    }

    void modifyHp(int hpChange)
    {
        m_hp = m_hp + hpChange;

        if (m_hp > m_hpMax)
        {
            m_hp = m_hpMax;
        }

        if (m_hp < 0)
        {
            m_hp = 0;

            setIsDead(true);
        }
    }

    void modifyMp(int mpChange)
    {
        m_mp = m_mp + mpChange;

        if (m_mp > m_mpMax)
        {
            m_mp = m_mpMax;
        }

        if (m_mp < 0)
        {
            m_mp = 0;
        }
    }

    void setLastAttacker(tb::Creature::Ptr creature)
    {
        m_lastAttacker = creature;
    }

    tb::Creature::Ptr getLastAttacker()
    {
        return m_lastAttacker;
    }

    tb::Creature::StatusEffectList::iterator findStatusEffect(int type)
    {
        return std::find_if
        (
            m_statusEffectList.begin(),
            m_statusEffectList.end(),
            [&type](tb::Creature::StatusEffect_t const& statusEffect)
            { 
                return statusEffect.type == type;
            }
        );
    }

    bool hasStatusEffect(int type)
    {
        auto findStatusEffectIt = findStatusEffect(type);

        return findStatusEffectIt != m_statusEffectList.end();
    }

    void addStatusEffect(int type, int damage, unsigned int ticks, sf::Time timePerTick)
    {
        auto findStatusEffectIt = findStatusEffect(type);

        if (findStatusEffectIt != m_statusEffectList.end())
        {
            findStatusEffectIt->ticks = ticks;
            findStatusEffectIt->clock.restart();
            return;
        }

        tb::Creature::StatusEffect_t statusEffect;
        statusEffect.type        = type;
        statusEffect.damage      = damage;
        statusEffect.ticks       = ticks;
        statusEffect.timePerTick = timePerTick;

        statusEffect.name = tb::UMaps::creatureStatusEffectsNames[type];

        statusEffect.clock.restart();

        m_statusEffectList.push_back(statusEffect);
    }

    int getHealthState()
    {
        if (m_hp <= 0 || m_hpMax <= 0)
        {
            return tb::HealthStates::dead;
        }

        float hpPercent = ((float)m_hp / (float)m_hpMax) * 100.0;

        //std::cout << "name:      " << m_name << std::endl;
        //std::cout << "hp:        " << m_hp << std::endl;
        //std::cout << "hpMax:     " << m_hpMax << std::endl;
        //std::cout << "hpPercent: " << hpPercent << std::endl;
        //std::cout << std::endl;

        if (hpPercent >= 91)
        {
            return tb::HealthStates::healthy;
        }
        else if (hpPercent >= 76 && hpPercent <= 90)
        {
            return tb::HealthStates::barelyWounded;
        }
        else if (hpPercent >= 51 && hpPercent <= 75)
        {
            return tb::HealthStates::lightlyWounded;
        }
        else if (hpPercent >= 26 && hpPercent <= 50)
        {
            return tb::HealthStates::heavilyWounded;
        }
        else if (hpPercent >= 11 && hpPercent <= 25)
        {
            return tb::HealthStates::critical;
        }
        else if (hpPercent >= 1 && hpPercent <= 10)
        {
            return tb::HealthStates::nearlyDead;
        }
        else if (hpPercent <= 0)
        {
            return tb::HealthStates::dead;
        }

        return tb::HealthStates::unknown;
    }

    bool isDead()
    {
        return m_isDead;
    }

    void setIsDead(bool b)
    {
        m_isDead = b;

        if (m_isDead == true)
        {
            m_clockCorpse.restart();

            m_clockDead.restart();
        }
    }

    int getTileOffset()
    {
        return m_tileOffset;
    }

    void setTileOffset(int offset)
    {
        m_tileOffset = offset;
    }

    bool isPlayer()
    {
        return m_isPlayer;
    }

    void setIsPlayer(bool b)
    {
        m_isPlayer = b;
    }

    bool isSleeping()
    {
        return m_isSleeping;
    }

    void setIsSleeping(bool b)
    {
        m_isSleeping = b;
    }

    std::string getName()
    {
        return m_name;
    }

    void setName(std::string name)
    {
        m_name = name;
    }

    bool hasCustomName()
    {
        return m_hasCustomName;
    }

    void setHasCustomName(bool b)
    {
        m_hasCustomName = b;
    }

    int getType()
    {
        return m_type;
    }

    void setType(int type)
    {
        m_type = type;

        setPropertiesByType();
    }

    int getSize()
    {
        return m_size;
    }

    void setSize(int size)
    {
        m_size = size;
    }

    int getCorpseSize()
    {
        return m_corpseSize;
    }

    int getDirection()
    {
        return m_direction;
    }

    void setDirection(int direction)
    {
        m_direction = direction;
    }

    bool getIsMovementReady()
    {
        return m_isMovementReady;
    }

    void setIsMovementReady(bool b)
    {
        m_isMovementReady = b;
    }

    bool getIsLogicReady()
    {
        return m_isLogicReady;
    }

    void setIsLogicReady(bool b)
    {
        m_isLogicReady = b;
    }

    bool getIsSpeechReady()
    {
        return m_isSpeechReady;
    }

    void setIsSpeechReady(bool b)
    {
        m_isSpeechReady = b;
    }

    float getMovementSpeed()
    {
        return m_movementSpeed;
    }

    void setMovementSpeed(float movementSpeed)
    {
        m_movementSpeed = movementSpeed;
    }

    int getTeam()
    {
        return m_team;
    }

    void setTeam(int team)
    {
        m_team = team;
    }

    int getVocation()
    {
        return m_vocation;
    }

    void setVocation(int vocation)
    {
        m_vocation = vocation;
    }

    int getBloodType()
    {
        return m_bloodType;
    }

    int getHp()
    {
        return m_hp;
    }

    void setHp(int hp)
    {
        m_hp = hp;
    }

    int getHpMax()
    {
        return m_hpMax;
    }

    void setHpMax(int hp)
    {
        m_hpMax = hp;
    }

    int getMp()
    {
        return m_mp;
    }

    void setMp(int mp)
    {
        m_mp = mp;
    }

    int getMpMax()
    {
        return m_mpMax;
    }

    void setMpMax(int mp)
    {
        m_mpMax = mp;
    }

    int getLevel()
    {
        return m_level;
    }

    void setLevel(int level)
    {
        m_level = level;
    }

    int getMagicLevel()
    {
        return m_magicLevel;
    }

    void setMagicLevel(int magicLevel)
    {
        m_magicLevel = magicLevel;
    }

    unsigned int getExp()
    {
        return m_exp;
    }

    void setExp(unsigned int exp)
    {
        m_exp = exp;
    }

    int getCap()
    {
        return m_cap;
    }

    void setCap(int cap)
    {
        m_cap = cap;
    }

    bool hasOutfit()
    {
        return m_hasOutfit;
    }

    void setHasOutfit(bool b)
    {
        m_hasOutfit = b;
    }

    int getOutfitHead()
    {
        return m_outfit[0];
    }

    void setOutfitHead(int head)
    {
        m_outfit[0] = head;
    }

    int getOutfitBody()
    {
        return m_outfit[1];
    }

    void setOutfitBody(int body)
    {
        m_outfit[1] = body;
    }

    int getOutfitLegs()
    {
        return m_outfit[2];
    }

    void setOutfitLegs(int legs)
    {
        m_outfit[2] = legs;
    }

    int getOutfitFeet()
    {
        return m_outfit[3];
    }

    void setOutfitFeet(int feet)
    {
        m_outfit[3] = feet;
    }

    tb::Sprite* getSpriteOutfitHead()
    {
        return &m_spriteOutfit[0];
    }

    tb::Sprite* getSpriteOutfitBody()
    {
        return &m_spriteOutfit[1];
    }

    tb::Sprite* getSpriteOutfitLegs()
    {
        return &m_spriteOutfit[2];
    }

    tb::Sprite* getSpriteOutfitFeet()
    {
        return &m_spriteOutfit[3];
    }

    sf::Clock* getClockMovement()
    {
        return &m_clockMovement;
    }

    sf::Clock* getClockLogic()
    {
        return &m_clockLogic;
    }

    sf::Clock* getClockSpeech()
    {
        return &m_clockSpeech;
    }

    sf::Clock* getClockCorpse()
    {
        return &m_clockCorpse;
    }

    sf::Clock* getClockDead()
    {
        return &m_clockDead;
    }

    sf::Clock* getClockAnimation()
    {
        return &m_clockAnimation;
    }

    tb::Creature::StatusEffectList* getStatusEffectList()
    {
        return &m_statusEffectList;
    }

    tb::Container* getInventory()
    {
        return &m_inventory;
    }

    tb::Container* getInventoryDepot()
    {
        return &m_inventoryDepot;
    }

    std::vector<int>* getSpritesList()
    {
        return &m_spritesList;
    }

private:

    int m_tileOffset;

    bool m_isPlayer;

    int m_type;

    int m_size;

    int m_corpseSize;

    int m_bloodType;

    int m_numAnimations;
    int m_currentAnimation;

    std::string m_name;

    bool m_hasCustomName;

    int m_direction;

    bool m_isMovementReady;
    bool m_isLogicReady;
    bool m_isSpeechReady;

    float m_movementSpeed;

    int m_team;

    int m_vocation;

    int m_hp;
    int m_hpMax;

    int m_mp;
    int m_mpMax;

    int m_gold;
    int m_platinum;

    unsigned int m_exp; // experience points

    int m_level;
    int m_magicLevel;

    int m_cap;

    bool m_isDead;

    bool m_isSleeping;

    sf::Clock m_clockAnimation;
    sf::Time m_timeAnimation;

    sf::Clock m_clockCorpse;

    sf::Clock m_clockDead;

    std::vector<int> m_spritesList;
    std::vector<int> m_spritesCorpseList;

    tb::Sprite m_sprite[tb::NUM_CREATURE_SPRITES];
    tb::Sprite m_spriteCorpse[tb::NUM_CREATURE_SPRITES];

    bool m_hasOutfit;

    // head, body, legs, feet
    int m_outfit[tb::NUM_CREATURE_SPRITES];

    tb::Sprite m_spriteOutfit[tb::NUM_CREATURE_SPRITES];

    sf::Clock m_clockMovement;
    sf::Clock m_clockLogic;
    sf::Clock m_clockSpeech;

    tb::Creature::Ptr m_lastAttacker;

    tb::Creature::StatusEffectList m_statusEffectList;

    tb::Container m_inventory;
    tb::Container m_inventoryDepot;

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

};

}
