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

bool BitmapFont::load(const std::string& fileName, const sf::Vector2u& glyphSize, const float textHeight, const std::vector<unsigned int>* glyphWidthList, unsigned int glyphSpace)
{
    if (std::filesystem::exists(fileName) == false)
    {
        g_Log.write("ERROR: File does not exist: {}\n", fileName);
        return false;
    }

    if (m_texture.loadFromFile(fileName) == false)
    {
        g_Log.write("ERROR: Failed to load texture file: {}\n", fileName);
        return false;
    }

    m_vertexArray.clear();
    m_vertexArray.resize(m_numGlyphs * 4);

    m_glyphSize = glyphSize;

    m_textHeight = textHeight;

    m_glyphWidthList = *glyphWidthList;

    m_glyphSpace = glyphSpace;

    const unsigned int textureSizeX = m_texture.getSize().x;
    const unsigned int textureSizeY = m_texture.getSize().y;

    if (textureSizeX == 0 || textureSizeY == 0)
    {
        g_Log.write("ERROR: Texture width or height is zero\n");
        return false;
    }

    const unsigned int glyphSizeX = glyphSize.x;
    const unsigned int glyphSizeY = glyphSize.y;

    if (glyphSizeX == 0 || glyphSizeY == 0)
    {
        g_Log.write("ERROR: Glyph width or height is zero\n");
        return false;
    }

    for (unsigned int i = 0; i < m_numGlyphs; i++)
    {
        const unsigned int u = i % (textureSizeX / glyphSizeX);
        const unsigned int v = i / (textureSizeX / glyphSizeX);

        sf::Vertex* vertex = &m_vertexArray[i * 4];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2u(i       * glyphSizeX, 1 * glyphSizeY));
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2u((i + 1) * glyphSizeX, 1 * glyphSizeY));
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2u((i + 1) * glyphSizeX, 2 * glyphSizeY));
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2u(i       * glyphSizeX, 2 * glyphSizeY));

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, v       * glyphSizeY));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, v       * glyphSizeY));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, (v + 1) * glyphSizeY));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, (v + 1) * glyphSizeY));
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

float BitmapFont::getTextHeight()
{
    return m_textHeight;
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
