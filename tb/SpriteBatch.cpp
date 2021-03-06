#include "tb/SpriteBatch.h"

namespace tb
{

SpriteBatch::SpriteBatch()
{
    m_vertexArray.clear();
    m_vertexArray.setPrimitiveType(sf::Quads);
    m_vertexArray.resize(m_maxVertices);

    m_numSprites = 0;
}

void SpriteBatch::addSprite(tb::Sprite& sprite, bool applyTileOffset)
{
    sf::Vector2f spritePosition = sprite.getPosition();

    sf::FloatRect spriteRect = (sf::FloatRect)sprite.getTextureRect();

    sf::Color spriteColor = sprite.getColor();

    float spriteTileWidth = tb::Constants::TileSizeFloat * sprite.getTileWidth();
    float spriteTileHeight = tb::Constants::TileSizeFloat * sprite.getTileHeight();

    if (applyTileOffset == true)
    {
        spritePosition.x -= (spriteTileWidth - tb::Constants::TileSizeFloat);
        spritePosition.y -= (spriteTileHeight - tb::Constants::TileSizeFloat);
    }

    sf::Vertex* vertex = &m_vertexArray[m_numSprites * 4];

    // top left, top right, bottom right, bottom left
    vertex[0].position = sf::Vector2f(spritePosition.x, spritePosition.y);
    vertex[1].position = sf::Vector2f(spritePosition.x + spriteTileWidth, spritePosition.y);
    vertex[2].position = sf::Vector2f(spritePosition.x + spriteTileWidth, spritePosition.y + spriteTileHeight);
    vertex[3].position = sf::Vector2f(spritePosition.x, spritePosition.y + spriteTileHeight);

    vertex[0].texCoords = sf::Vector2f(spriteRect.left, spriteRect.top);
    vertex[1].texCoords = sf::Vector2f(spriteRect.left + spriteRect.width, spriteRect.top);
    vertex[2].texCoords = sf::Vector2f(spriteRect.left + spriteRect.width, spriteRect.top + spriteRect.height);
    vertex[3].texCoords = sf::Vector2f(spriteRect.left, spriteRect.top + spriteRect.height);

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

void SpriteBatch::clear()
{
    m_vertexArray.clear();
    m_vertexArray.resize(m_maxVertices);

    m_numSprites = 0;
}

void SpriteBatch::printDebugText()
{
    tb::print("SpriteBatch Debug Text\n");

    tb::print("    Max Sprites:  {}\n", m_maxSprites);
    tb::print("    Max Vertices: {}\n", m_maxVertices);

    tb::print("    Vertex Count: {}\n", m_vertexArray.getVertexCount());

    tb::print("    Num Sprites:  {}\n", m_numSprites);
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();

    states.texture = &tb::Textures::Sprites;

    target.draw(m_vertexArray, states);
}

}
