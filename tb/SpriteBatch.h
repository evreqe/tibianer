#pragma once

#include "common.h"

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"
#include "tb/Log.h"

#include "tb/Sprite.h"

namespace tb
{

class SpriteBatch
{

public:

    SpriteBatch();
    ~SpriteBatch();

    bool addSprite(tb::Sprite* sprite, bool applyTileWidthAndHeightOffset = false);
    void clear();
    void printDebugText();
    void draw(sf::RenderTarget& target, sf::RenderStates states);

    uint32_t getNumSprites();

private:

    sf::VertexArray m_vertexArray;

    uint32_t m_numSprites = 0;

    uint32_t m_maxVertices = 65535; // 16384 * 4 = 65535

    uint32_t m_maxSprites = 16384; // 4096 * 4 = 16384
};

}
