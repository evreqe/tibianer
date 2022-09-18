#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Utility.h"

namespace tb
{

class Sprite : public sf::Sprite
{

public:

    Sprite();
    ~Sprite();
    Sprite(tb::SpriteID_t id);

    tb::SpriteID_t getID();
    void setID(tb::SpriteID_t id);

    void updateTextureRect();

    uint8_t getTileWidth();
    void setTileWidth(uint8_t tileWidth);

    uint8_t getTileHeight();
    void setTileHeight(uint8_t tileHeight);

    bool getUseWidthAndHeight();
    void setUseWidthAndHeight(bool b);

private:

    tb::SpriteID_t m_id = tb::Constants::SpriteIDDefault;

    uint8_t m_tileWidth = 1;
    uint8_t m_tileHeight = 1;

    bool m_useWidthAndHeight = true;
};

}
