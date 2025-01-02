#include "tb/BitmapFont.h"

namespace tb
{

BitmapFont::BitmapFont()
{
    m_vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
}

BitmapFont::~BitmapFont()
{
    //
}

bool BitmapFont::load(const std::string& fileName, const sf::Vector2u& glyphSize, std::int32_t characterSpace, std::int32_t characterHeight, std::vector<std::int32_t>* characterWidthList)
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

    const std::uint32_t numGlyphs = tb::Constants::BitmapFonts::NumGlyphs;

    m_vertexArray.clear();
    m_vertexArray.resize(numGlyphs * m_numVertexPerGlyph);

    m_glyphSize = glyphSize;

    m_characterSpace = characterSpace;

    m_characterHeight = characterHeight;

    m_characterWidthList = *characterWidthList;

    const std::uint32_t textureSizeX = m_texture.getSize().x;
    const std::uint32_t textureSizeY = m_texture.getSize().y;

    if (textureSizeX == 0 || textureSizeY == 0)
    {
        g_Log.write("ERROR: Texture width or height is zero\n");
        return false;
    }

    const std::uint32_t glyphSizeX = glyphSize.x;
    const std::uint32_t glyphSizeY = glyphSize.y;

    if (glyphSizeX == 0 || glyphSizeY == 0)
    {
        g_Log.write("ERROR: Glyph width or height is zero\n");
        return false;
    }

    for (std::uint32_t i = 0; i < numGlyphs; i++)
    {
        const std::uint32_t u = i % (textureSizeX / glyphSizeX);
        const std::uint32_t v = i / (textureSizeX / glyphSizeX);

        sf::Vertex* vertex = &m_vertexArray[i * m_numVertexPerGlyph];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2u(i       * glyphSizeX, 1 * glyphSizeY)); // top left
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2u((i + 1) * glyphSizeX, 1 * glyphSizeY)); // top right
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2u(i       * glyphSizeX, 2 * glyphSizeY)); // bottom left
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2u(i       * glyphSizeX, 2 * glyphSizeY)); // bottom left
        vertex[4].position = static_cast<sf::Vector2f>(sf::Vector2u((i + 1) * glyphSizeX, 1 * glyphSizeY)); // top right
        vertex[5].position = static_cast<sf::Vector2f>(sf::Vector2u((i + 1) * glyphSizeX, 2 * glyphSizeY)); // bottom right

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, v       * glyphSizeY)); // top left
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, v       * glyphSizeY)); // top right
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, (v + 1) * glyphSizeY)); // bottom left
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, (v + 1) * glyphSizeY)); // bottom left
        vertex[4].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, v       * glyphSizeY)); // top right
        vertex[5].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, (v + 1) * glyphSizeY)); // bottom right
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

std::int32_t BitmapFont::getCharacterSpace()
{
    return m_characterSpace;
}

std::int32_t BitmapFont::getCharacterHeight()
{
    return m_characterHeight;
}

std::vector<std::int32_t>* BitmapFont::getCharacterWidthList()
{
    return &m_characterWidthList;
}

}
