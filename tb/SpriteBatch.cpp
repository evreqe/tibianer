#include "tb/SpriteBatch.h"

namespace tb
{

SpriteBatch::SpriteBatch()
{
    m_vertexList.resize(m_maxVertices);

    m_numSprites = 0;
}

SpriteBatch::~SpriteBatch()
{
    //
}

bool SpriteBatch::addSprite(tb::Sprite* sprite, bool applyTileWidthAndHeightOffset)
{
    if (sprite == nullptr)
    {
        g_Log.write("ERROR: sprite == nullptr\n");
        return false;
    }

    sf::Vector2f spritePosition = sprite->getPosition();

    sf::FloatRect spriteRect = static_cast<sf::FloatRect>(sprite->getTextureRect());

    sf::Color spriteColor = sprite->getColor();

    float spriteTileWidth  = static_cast<float>(tb::Constants::TileSize * sprite->getTileWidth());
    float spriteTileHeight = static_cast<float>(tb::Constants::TileSize * sprite->getTileHeight());

    // big sprites
    if (applyTileWidthAndHeightOffset == true)
    {
        spritePosition.x -= (spriteTileWidth  - tb::Constants::TileSizeAsFloat);
        spritePosition.y -= (spriteTileHeight - tb::Constants::TileSizeAsFloat);
    }

    sf::Vertex* vertex = &m_vertexList[m_numSprites * 4];

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

        m_vertexList.resize(m_maxVertices);

        printDebugText();
    }

    return true;
}

void SpriteBatch::clear()
{
    m_vertexList.clear();

    m_numSprites = 0;
}

void SpriteBatch::printDebugText()
{
    g_Log.write("SpriteBatch Debug Text\n");

    g_Log.write("----> Max Sprites:  {}\n", m_maxSprites);
    g_Log.write("----> Max Vertices: {}\n", m_maxVertices);

    g_Log.write("----> Vertex List Size: {}\n", m_vertexList.size());

    g_Log.write("----> Num Sprites:  {}\n", m_numSprites);
}

void SpriteBatch::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
{
    renderTarget.draw(&m_vertexList[0], m_vertexList.size(), sf::Quads, renderStates);
}

std::uint32_t SpriteBatch::getNumSprites()
{
    return m_numSprites;
}

}
