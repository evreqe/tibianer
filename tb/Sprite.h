#pragma once

#include "common.h"

#include "tb/Constants.h"
#include "tb/Utility.h"
#include "Tb/Log.h"

#include "tb/SpriteData.h"

namespace tb
{

class Sprite : public sf::Sprite
{

public:

    Sprite();
    ~Sprite();

    using List = std::vector<tb::Sprite>;

    tb::SpriteID_t getID();
    void setID(tb::SpriteID_t spriteID);

    void setTileWidthAndHeightByID(tb::SpriteID_t spriteID);

    sf::IntRect getTextureRectByID(tb::SpriteID_t spriteID, uint8_t tileWidth, uint8_t tileHeight);
    void updateTextureRect();

    uint8_t getTileWidth();
    void setTileWidth(uint8_t tileWidth);

    uint8_t getTileHeight();
    void setTileHeight(uint8_t tileHeight);

private:

    tb::SpriteID_t m_spriteID = tb::Constants::SpriteIDDefault;

    uint8_t m_tileWidth = 1;
    uint8_t m_tileHeight = 1;

};

}
