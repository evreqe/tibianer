#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "tb/Constants.h"

#include "tb/Sprite.h"

namespace tb
{

class SpriteBatch : public sf::Drawable, public sf::Transformable
{

public:

    SpriteBatch();

    void addSprite(tb::Sprite& sprite, bool applyTileOffset = false);
    void clear();
    void printDebugText();

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states);

    sf::VertexArray m_vertexArray;

    uint32_t m_numSprites = 0;

    uint32_t m_maxVertices = 65535; // 16384 * 4 = 65535

    uint32_t m_maxSprites = 16384; // 4096 * 4 = 16384
};

}
