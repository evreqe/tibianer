#include "tb/BitmapFont.h"

namespace tb
{

BitmapFont::BitmapFont()
{
    m_vertexArray.setPrimitiveType(sf::Quads);
}

BitmapFont::~BitmapFont()
{
    //
}

bool BitmapFont::load(const std::string& fileName, const sf::Vector2u& glyphSize, const std::vector<unsigned int>* glyphWidthList, unsigned int glyphSpace)
{
    if (m_texture.loadFromFile(fileName) == false)
    {
        g_Log.write("ERROR: Failed to load texture file: {}\n", fileName);
        return false;
    }

    m_vertexArray.clear();
    m_vertexArray.resize(m_numGlyphs * 4);

    m_glyphSize = glyphSize;

    m_glyphWidthList = *glyphWidthList;

    m_glyphSpace = glyphSpace;

    const unsigned int textureSizeX = m_texture.getSize().x;
    const unsigned int textureSizeY = m_texture.getSize().y;

    if (textureSizeX == 0 || textureSizeY == 0)
    {
        g_Log.write("ERROR: Texture width or height cannot be zero\n");
        return false;
    }

    const unsigned int glyphSizeX = glyphSize.x;
    const unsigned int glyphSizeY = glyphSize.y;

    for (unsigned int i = 0; i < m_numGlyphs; i++)
    {
        const unsigned int tu = i % (textureSizeX / glyphSizeX);
        const unsigned int tv = i / (textureSizeX / glyphSizeX);

        sf::Vertex* quad = &m_vertexArray[i * 4];

        quad[0].position = sf::Vector2f(i          * glyphSizeX, 1.0f          * glyphSizeY);
        quad[1].position = sf::Vector2f((i + 1.0f) * glyphSizeX, 1.0f          * glyphSizeY);
        quad[2].position = sf::Vector2f((i + 1.0f) * glyphSizeX, 2.0f          * glyphSizeY);
        quad[3].position = sf::Vector2f(i          * glyphSizeX, 2.0f          * glyphSizeY);

        quad[0].texCoords = sf::Vector2f(tu          * glyphSizeX, tv          * glyphSizeY);
        quad[1].texCoords = sf::Vector2f((tu + 1.0f) * glyphSizeX, tv          * glyphSizeY);
        quad[2].texCoords = sf::Vector2f((tu + 1.0f) * glyphSizeX, (tv + 1.0f) * glyphSizeY);
        quad[3].texCoords = sf::Vector2f(tu          * glyphSizeX, (tv + 1.0f) * glyphSizeY);
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

sf::Vector2u BitmapFont::getGlyphSize()
{
    return m_glyphSize;
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
