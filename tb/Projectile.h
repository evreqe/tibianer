#pragma once

/*
#ifndef TIBIA_PROJECTILE_HPP
#define TIBIA_PROJECTILE_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

#include "tb/Tibia.hpp"
#include "tb/Utility.hpp"
#include "tb/Thing.hpp"
#include "tb/Sprite.hpp"
#include "tb/Creature.hpp"

namespace tb
{

class Projectile : public tb::Thing
{

public:

    typedef std::shared_ptr<tb::Projectile> Ptr;
    typedef std::vector<tb::Projectile::Ptr> List;

    Projectile::Projectile(int type, int direction, sf::Vector2f origin, sf::Vector2f destination, bool isPrecise = false, bool isChild = false)
    {
        m_type = type;

        m_modifyHpType = tb::ModifyHpTypes::blood;

        m_direction = direction;

        m_isPrecise = isPrecise;
        m_isChild   = isChild;

        m_range  = tb::ProjectileRanges::default;
        m_damage = tb::ProjectileDamages::default;
        m_speed  = tb::ProjectileSpeeds::default;

        m_distanceTravelled     = 0;
        m_tileDistanceTravelled = 0;

        m_spriteTileX = origin.x;
        m_spriteTileY = origin.y;

        m_vectorOrigin      = origin;
        m_vectorDestination = destination;

        m_vectorMovement = tb::Utility::getNormalByVectors(origin, destination);

        if (m_isPrecise == true)
        {
            m_direction = tb::Utility::getDirectionByVector(m_vectorMovement);
        }

        setPropertiesByType(m_type);

        setId(m_id);

        m_sprite.setId(m_id);

        setPosition(origin.x, origin.y);
    }

    void setPropertiesByType(int type)
    {
        switch (type)
        {
            case tb::ProjectileTypes::spellBlue:
                m_id           = tb::Projectiles::spellBlue;
                m_modifyHpType = tb::ModifyHpTypes::spellBlue;
                break;

            case tb::ProjectileTypes::spellBlack:
                m_id           = tb::Projectiles::spellBlack;
                m_modifyHpType = tb::ModifyHpTypes::spellBlack;
                break;

            case tb::ProjectileTypes::spellCacodemon:
                m_id           = tb::Projectiles::spellCacodemon;
                m_modifyHpType = tb::ModifyHpTypes::electricity;
                break;

            case tb::ProjectileTypes::spellFire:
                m_id           = tb::Projectiles::spellFire[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::fire;
                break;

            case tb::ProjectileTypes::throwingKnife:
                m_id           = tb::Projectiles::throwingKnife[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;

            case tb::ProjectileTypes::spear:
                m_id           = tb::Projectiles::spear[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;

            case tb::ProjectileTypes::bolt:
                m_id          = tb::Projectiles::bolt[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;

            case tb::ProjectileTypes::powerBolt:
                m_id           = tb::Projectiles::powerBolt[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;

            case tb::ProjectileTypes::arrow:
                m_id           = tb::Projectiles::arrow[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;

            case tb::ProjectileTypes::burstArrow:
                m_id           = tb::Projectiles::burstArrow[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;

            case tb::ProjectileTypes::poisonArrow:
                m_id           = tb::Projectiles::poisonArrow[m_direction];
                m_modifyHpType = tb::ModifyHpTypes::blood;
                break;
        }
    }

    void doMovement(sf::Time timeDelta)
    {
        float moveX = m_vectorMovement.x;
        float moveY = m_vectorMovement.y;

        //std::cout << "timeDelta: " << timeDelta.asSeconds() << std::endl;

        float moveSpeed = m_speed * timeDelta.asSeconds();

        moveSpeed = std::roundf(moveSpeed);

        //std::cout << "moveSpeed: " << moveSpeed << std::endl;

        m_sprite.move(moveX * moveSpeed, moveY * moveSpeed);

        m_distanceTravelled += moveSpeed;

        //std::cout << "m_distanceTravelled: " << m_distanceTravelled << std::endl;

        m_distanceTravelledRoundedToTileSize = m_distanceTravelled - (m_distanceTravelled % tb::TILE_SIZE);

        if (m_distanceTravelledRoundedToTileSize == m_distanceTravelledPrevious)
        {
            return;
        }

        m_distanceTravelledPrevious = m_distanceTravelledRoundedToTileSize;

        //std::cout << "m_distanceTravelledRoundedToTileSize: " << m_distanceTravelledRoundedToTileSize << std::endl;

        if (m_distanceTravelledRoundedToTileSize > 0 && m_distanceTravelledRoundedToTileSize % tb::TILE_SIZE == 0)
        {
            m_spriteTileX = m_spriteTileX + (moveX * tb::TILE_SIZE);
            m_spriteTileY = m_spriteTileY + (moveY * tb::TILE_SIZE);

            m_tileDistanceTravelled += 1;

            //std::cout << "m_tileDistanceTravelled: " << m_tileDistanceTravelled << std::endl;
        }
    }

    void update(sf::Time timeDelta)
    {
        //updateTileCoords();

        //int drawOffset = getDrawOffset() * tb::THING_DRAW_OFFSET;

        //setPosition(getTileX() - drawOffset, getTileY() - drawOffset);

        doMovement(timeDelta);

        setTileCoords(getSpriteTilePosition().x, getSpriteTilePosition().y);

        updateTileNumber();
    }

    void setId(int id)
    {
        m_id = id;

        m_flags = tb::UMaps::spriteFlags[m_id];
    }

    int getId()
    {
        return m_id;
    }

    void setType(int type)
    {
        m_type = type;
    }

    int getType()
    {
        return m_type;
    }

    int getModifyHpType()
    {
        return m_modifyHpType;
    }

    tb::SpriteFlags_t getFlags()
    {
        return m_flags;
    }

    void setFlags(tb::SpriteFlags_t flags)
    {
        m_flags = flags;
    }

    void setRange(int range)
    {
        m_range = range;
    }

    int getRange()
    {
        return m_range;
    }

    void setDamage(int damage)
    {
        m_damage = damage;
    }

    int getDamage()
    {
        return m_damage;
    }

    float setSpeed(float speed)
    {
        m_speed = speed;
    }

    float getSpeed()
    {
        return m_speed;
    }

    int getDirection()
    {
        return m_direction;
    }

    void setDistanceTravelled(int distance)
    {
        m_distanceTravelled = distance;
    }

    int getDistanceTravelled()
    {
        return m_distanceTravelled;
    }

    int getDistanceTravelledRoundedToTileSize()
    {
        return m_distanceTravelledRoundedToTileSize;
    }

    int getDistanceTravelledPrevious()
    {
        return m_distanceTravelledPrevious;
    }

    int getTileDistanceTravelled()
    {
        return m_tileDistanceTravelled;
    }

    void setTileDistanceTravelledPrevious(int distance)
    {
        m_tileDistanceTravelledPrevious = distance;
    }

    int getTileDistanceTravelledPrevious()
    {
        return m_tileDistanceTravelledPrevious;
    }

    sf::Vector2f getVectorOrigin()
    {
        return m_vectorOrigin;
    }

    sf::Vector2f getVectorDestination()
    {
        return m_vectorDestination;
    }

    sf::Vector2f getVectorMovement()
    {
        return m_vectorMovement;
    }

    sf::Sprite* getSprite()
    {
        return &m_sprite;
    }

    sf::Vector2f getSpritePosition()
    {
        return m_sprite.getPosition();
    }

    sf::Vector2u getSpriteTilePosition()
    {
        float integralX;
        float fractionalX = std::modf(m_spriteTileX, &integralX);

        float integralY;
        float fractionalY = std::modf(m_spriteTileY, &integralY);

        int x = integralX;
        int y = integralY;

        if (m_vectorMovement.x < 0 && m_vectorMovement.y > 0)
        {
            x += tb::TILE_SIZE;
        }
        else if (m_vectorMovement.x > 0 && m_vectorMovement.y < 0)
        {
            y += tb::TILE_SIZE;
        }
        else if (m_vectorMovement.x < 0 && m_vectorMovement.y < 0)
        {
            x += tb::TILE_SIZE;
            y += tb::TILE_SIZE;
        }

        // round down to nearest multiple of tile size
        x = x - (x % tb::TILE_SIZE);
        y = y - (y % tb::TILE_SIZE);

        return sf::Vector2u(x, y);
    }

    tb::Creature::Ptr getCreatureOwner()
    {
        return m_creatureOwner;
    }

    void setCreatureOwner(tb::Creature::Ptr creature)
    {
        m_creatureOwner = creature;
    }

    bool isPrecise()
    {
        return m_isPrecise;
    }

    void setIsPrecise(bool b)
    {
        m_isPrecise = b;
    }

    bool isChild()
    {
        return m_isChild;
    }

    void setIsChild(bool b)
    {
        m_isChild = b;
    }

private:

    int m_id;

    int m_type;
    int m_modifyHpType;

    tb::SpriteFlags_t m_flags;

    float m_spriteTileX;
    float m_spriteTileY;

    int m_direction;
    int m_range;
    int m_damage;
    float m_speed;

    int m_distanceTravelled;
    int m_distanceTravelledRoundedToTileSize;
    int m_distanceTravelledPrevious;

    int m_tileDistanceTravelled;
    int m_tileDistanceTravelledPrevious;

    bool m_isPrecise;
    bool m_isChild;

    sf::Vector2f m_vectorOrigin;
    sf::Vector2f m_vectorDestination;
    sf::Vector2f m_vectorMovement;

    tb::Sprite m_sprite;

    tb::Creature::Ptr m_creatureOwner;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        target.draw(m_sprite, states);
    }

};

} // namespace tb

#endif // TIBIA_PROJECTILE_HPP
*/