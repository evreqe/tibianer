#include "tb/BitmapFont.h"

namespace tb
{

BitmapFont::BitmapFont()
{
    m_vertexArray.setPrimitiveType(sf::Quads);
    m_vertexArray.resize(m_numGlyphs * 4);
}

BitmapFont::~BitmapFont()
{
    //
}

bool BitmapFont::load(const std::string& texture, sf::Vector2u glyphSize, const std::vector<unsigned int>* glyphWidthList, unsigned int glyphSpace)
{
    if (m_texture.loadFromFile(texture) == false)
    {
        fmt::print("ERROR: Failed to load texture file: {}\n", texture);
        return false;
    }

    m_glyphSize = glyphSize;

    m_glyphWidthList = *glyphWidthList;

    m_glyphSpace = glyphSpace;

    for (unsigned int i = 0; i < m_numGlyphs; i++)
    {
        const unsigned int tu = i % (m_texture.getSize().x / glyphSize.x);
        const unsigned int tv = i / (m_texture.getSize().x / glyphSize.x);

        sf::Vertex* quad = &m_vertexArray[i * 4];

        quad[0].position = sf::Vector2f(i * glyphSize.x, 1.0f * glyphSize.y);
        quad[1].position = sf::Vector2f((i + 1.0f) * glyphSize.x, 1.0f * glyphSize.y);
        quad[2].position = sf::Vector2f((i + 1.0f) * glyphSize.x, (1.0f + 1.0f) * glyphSize.y);
        quad[3].position = sf::Vector2f(i * glyphSize.x, (1.0f + 1.0f) * glyphSize.y);

        quad[0].texCoords = sf::Vector2f(tu * glyphSize.x, tv * glyphSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1.0f) * glyphSize.x, tv * glyphSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1.0f) * glyphSize.x, (tv + 1.0f) * glyphSize.y);
        quad[3].texCoords = sf::Vector2f(tu * glyphSize.x, (tv + 1.0f) * glyphSize.y);
    }

    return true;
}

sf::VertexArray* BitmapFont::getVertexArray()
{
    return &m_vertexArray;
}

sf::Texture* BitmapFont::getTexture()
{
    return &m_texture;
}

sf::Vector2u* BitmapFont::getGlyphSize()
{
    return &m_glyphSize;
}

std::vector<unsigned int>* BitmapFont::getGlyphWidthList()
{
    return &m_glyphWidthList;
}

unsigned int BitmapFont::getGlyphSpace()
{
    return m_glyphSpace;
}

}
