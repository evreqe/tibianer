#pragma once

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Utility.hpp"

namespace tb
{

class Sprite : public sf::Sprite
{

public:

    Sprite()
    {
        setTexture(tb::Textures::Sprites);

        setID(tb::Constants::SpriteIDDefault);
    }

    Sprite(tb::SpriteID_t id)
    {
        setTexture(tb::Textures::Sprites);

        setID(id);
    }

    void setID(tb::SpriteID_t id)
    {
        m_id = id;

        if (m_useWidthAndHeight == true)
        {
            if (id == 1808)
            {
                m_tileWidth = 2;
                m_tileHeight = 2;
            }
            else if (id == 1242)
            {
                m_tileWidth = 3;
                m_tileHeight = 2;
            }
        }

        const sf::IntRect rect = tb::Utility::GetSpriteRectByID(id, m_tileWidth, m_tileHeight);

        setTextureRect(rect);
    }

    tb::SpriteID_t getID() const
    {
        return m_id;
    }

    uint8_t getTileWidth() const
    {
        return m_tileWidth;
    }

    void setTileWidth(uint8_t tileWidth)
    {
        m_tileWidth = tileWidth;
    }

    uint8_t getTileHeight() const
    {
        return m_tileHeight;
    }

    void setTileHeight(uint8_t tileHeight)
    {
        m_tileHeight = tileHeight;
    }

    void setUseWidthAndHeight(bool b)
    {
        m_useWidthAndHeight = b;
    }

private:

    tb::SpriteID_t m_id = tb::Constants::SpriteIDDefault;

    uint8_t m_tileWidth = 1;
    uint8_t m_tileHeight = 1;

    bool m_useWidthAndHeight = true;
};

}
