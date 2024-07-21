#include "tb/Sprite.h"

namespace tb
{

Sprite::Sprite()
{
    setTexture(tb::Textures::Sprites);
}

Sprite::~Sprite()
{
    //
}

tb::SpriteID_t Sprite::getID()
{
    return m_spriteID;
}

void Sprite::setID(tb::SpriteID_t spriteID)
{
    m_spriteID = spriteID;

    updateTextureRect();
}

void Sprite::setTileWidthAndHeightByID(tb::SpriteID_t spriteID)
{
    tb::SpriteData::Data* spriteData = &g_SpriteData.getDataList()->at(spriteID);

    m_tileWidth = spriteData->TileWidth;
    m_tileHeight = spriteData->TileHeight;

    updateTextureRect();
}

sf::IntRect Sprite::getTextureRectByID(tb::SpriteID_t spriteID, std::uint8_t tileWidth, std::uint8_t tileHeight)
{
    // index in the spritesheet starts at 1
    spriteID = spriteID - 1;

    sf::Vector2u spritesTextureSize = tb::Textures::Sprites.getSize();

    const std::uint32_t tileSize = tb::Constants::TileSize;

    std::int32_t u = (spriteID % (spritesTextureSize.x / tileSize)) * tileSize;
    std::int32_t v = (spriteID / (spritesTextureSize.y / tileSize)) * tileSize;

    u = u - ((tileWidth  - 1) * tileSize);
    v = v - ((tileHeight - 1) * tileSize);

    return sf::IntRect(u, v, (tileWidth * tileSize), (tileHeight * tileSize));
}

void Sprite::updateTextureRect()
{
    sf::IntRect rect = getTextureRectByID(m_spriteID, m_tileWidth, m_tileHeight);

    setTextureRect(rect);
}

std::uint8_t Sprite::getTileWidth()
{
    return m_tileWidth;
}

void Sprite::setTileWidth(std::uint8_t tileWidth)
{
    m_tileWidth = tileWidth;

    updateTextureRect();
}

std::uint8_t Sprite::getTileHeight()
{
    return m_tileHeight;
}

void Sprite::setTileHeight(std::uint8_t tileHeight)
{
    m_tileHeight = tileHeight;

    updateTextureRect();
}

}
