#pragma once

#include "common.h"

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
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates);

    std::uint32_t getNumSprites();

private:

    std::vector<sf::Vertex> m_vertexList;

    std::uint32_t m_numSprites = 0;

    std::uint32_t m_maxVertices = 65535; // 16384 * 4 = 65535

    std::uint32_t m_maxSprites = 16384; // 4096 * 4 = 16384
};

}
