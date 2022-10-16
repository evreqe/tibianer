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
    if (g_SpriteData.isLoaded() == false)
    {
        g_Log.write("ERROR: Sprite data is not loaded\n");
        return;
    }

    tb::SpriteData::Data* spriteData = &g_SpriteData.getDataList()->at(spriteID);
    if (spriteData == nullptr)
    {
        g_Log.write("ERROR: spriteData == nullptr\n");
        return;
    }

    m_tileWidth = spriteData->TileWidth;
    m_tileHeight = spriteData->TileHeight;

    updateTextureRect();
}

sf::IntRect Sprite::getTextureRectByID(tb::SpriteID_t spriteID, uint8_t tileWidth, uint8_t tileHeight)
{
    // index in the spritesheet starts at 1
    spriteID = spriteID - 1;

    int u = (spriteID % (tb::Textures::Sprites.getSize().x / tb::Constants::TileSize)) * tb::Constants::TileSize;
    int v = (spriteID / (tb::Textures::Sprites.getSize().y / tb::Constants::TileSize)) * tb::Constants::TileSize;

    u = u - ((tileWidth - 1) * tb::Constants::TileSize);
    v = v - ((tileHeight - 1) * tb::Constants::TileSize);

    return sf::IntRect(u, v, (tileWidth * tb::Constants::TileSize), (tileHeight * tb::Constants::TileSize));
}

void Sprite::updateTextureRect()
{
    sf::IntRect rect = getTextureRectByID(m_spriteID, m_tileWidth, m_tileHeight);

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

}
