#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "tb/Constants.hpp"
#include "tb/Sprite.hpp"

namespace tb
{

class SpriteBatch : public sf::Drawable, public sf::Transformable
{

public:

    SpriteBatch()
    {
        m_vertexArray.clear();
        m_vertexArray.setPrimitiveType(sf::Quads);
        m_vertexArray.resize(m_maxVertices); 

        m_numSprites = 0;
    }

    void addSprite(tb::Sprite& sprite, bool applyTileOffset = false)
    {
        sf::Vector2f spritePosition = sprite.getPosition();

        sf::FloatRect spriteRect = (sf::FloatRect)sprite.getTextureRect();

        sf::Color spriteColor = sprite.getColor();

        float spriteTileWidth  = tb::Constants::TileSizeF * sprite.getTileWidth();
        float spriteTileHeight = tb::Constants::TileSizeF * sprite.getTileHeight();

        if (applyTileOffset == true)
        {
            spritePosition.x -= (spriteTileWidth  - tb::Constants::TileSizeF);
            spritePosition.y -= (spriteTileHeight - tb::Constants::TileSizeF);
        }

        sf::Vertex* vertex = &m_vertexArray[m_numSprites * 4];

        // top left, top right, bottom right, bottom left
        vertex[0].position = sf::Vector2f(spritePosition.x,                   spritePosition.y);
        vertex[1].position = sf::Vector2f(spritePosition.x + spriteTileWidth, spritePosition.y);
        vertex[2].position = sf::Vector2f(spritePosition.x + spriteTileWidth, spritePosition.y + spriteTileHeight);
        vertex[3].position = sf::Vector2f(spritePosition.x,                   spritePosition.y + spriteTileHeight);

        vertex[0].texCoords = sf::Vector2f(spriteRect.left,                    spriteRect.top);
        vertex[1].texCoords = sf::Vector2f(spriteRect.left + spriteRect.width, spriteRect.top);
        vertex[2].texCoords = sf::Vector2f(spriteRect.left + spriteRect.width, spriteRect.top + spriteRect.height);
        vertex[3].texCoords = sf::Vector2f(spriteRect.left,                    spriteRect.top + spriteRect.height);

        vertex[0].color = spriteColor;
        vertex[1].color = spriteColor;
        vertex[2].color = spriteColor;
        vertex[3].color = spriteColor;

        m_numSprites++;

        if (m_numSprites >= m_maxSprites)
        {
            m_maxSprites = m_maxSprites * 2;
            m_maxVertices = m_maxSprites * 4;

            m_vertexArray.resize(m_maxVertices);

            this->printDebugText();
        }
    }

    void clear()
    {
        m_vertexArray.clear();
        m_vertexArray.resize(m_maxVertices);

        m_numSprites = 0;
    }

    void printDebugText()
    {
        std::cout << "SpriteBatch Debug Text\n";

        std::cout << "    Max Sprites:  " << m_maxSprites << "\n";
        std::cout << "    Max Vertices: " << m_maxVertices << "\n";

        std::cout << "    Vertex Count: " << m_vertexArray.getVertexCount() << "\n";

        std::cout << "    Num Sprites:  " << m_numSprites << "\n";
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &tb::Textures::Sprites;

        target.draw(m_vertexArray, states);
    }

    sf::VertexArray m_vertexArray;

    uint32_t m_numSprites = 0;

    uint32_t m_maxVertices = 65535; // 16384 * 4 = 65535

    uint32_t m_maxSprites = 16384; // 4096 * 4 = 16384
};

}
