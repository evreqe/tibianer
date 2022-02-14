#include "tb/Sprite.h"

namespace tb
{

Sprite::Sprite()
{
    setTexture(tb::Textures::Sprites);

    setID(tb::Constants::SpriteIDDefault);
}

Sprite::Sprite(tb::SpriteID_t id)
{
    setTexture(tb::Textures::Sprites);

    setID(id);
}

void Sprite::setID(tb::SpriteID_t id)
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

    sf::IntRect rect = tb::Utility::GetSpriteRectByID(id, m_tileWidth, m_tileHeight);

    setTextureRect(rect);
}

tb::SpriteID_t Sprite::getID()
{
    return m_id;
}

uint8_t Sprite::getTileWidth()
{
    return m_tileWidth;
}

void Sprite::setTileWidth(uint8_t tileWidth)
{
    m_tileWidth = tileWidth;
}

uint8_t Sprite::getTileHeight()
{
    return m_tileHeight;
}

void Sprite::setTileHeight(uint8_t tileHeight)
{
    m_tileHeight = tileHeight;
}

bool Sprite::getUseWidthAndHeight()
{
    return m_useWidthAndHeight;
}

void Sprite::setUseWidthAndHeight(bool b)
{
    m_useWidthAndHeight = b;
}

}
