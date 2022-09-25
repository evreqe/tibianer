#include "tb/Sprite.h"

namespace tb
{

Sprite::Sprite()
{
    setTexture(tb::Textures::Sprites);

    setID(tb::Constants::SpriteIDDefault);
}

Sprite::~Sprite()
{
    //
}

Sprite::Sprite(tb::SpriteID_t id)
{
    setTexture(tb::Textures::Sprites);

    setID(id);
}

tb::SpriteID_t Sprite::getID()
{
    return m_id;
}

void Sprite::setID(tb::SpriteID_t id)
{
    m_id = id;

    tb::SpriteData::Data* data = &g_SpriteData.getDataList()->at(m_id);
    if (data == nullptr)
    {
        g_Log.write("ERROR: nullptr\n");
        return;
    }

    setTileHeight(data->TileWidth);
    setTileWidth(data->TileHeight);

    updateTextureRect();
}

void Sprite::updateTextureRect()
{
    sf::IntRect rect = tb::Utility::getSpriteRectByID(m_id, m_tileWidth, m_tileHeight);

    setTextureRect(rect);
}

uint8_t Sprite::getTileWidth()
{
    return m_tileWidth;
}

void Sprite::setTileWidth(uint8_t tileWidth)
{
    m_tileWidth = tileWidth;

    updateTextureRect();
}

uint8_t Sprite::getTileHeight()
{
    return m_tileHeight;
}

void Sprite::setTileHeight(uint8_t tileHeight)
{
    m_tileHeight = tileHeight;

    updateTextureRect();
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
