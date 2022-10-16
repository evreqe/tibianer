#include "tb/BitmapFontText.h"

namespace tb
{

BitmapFontText::BitmapFontText()
{
    m_vertexArray.setPrimitiveType(sf::Quads);
}

BitmapFontText::~BitmapFontText()
{
    //
}

bool BitmapFontText::setText(tb::BitmapFont* bitmapFont, const std::string& text, const sf::Color& textColor, bool isCentered)
{
    if (bitmapFont == nullptr)
    {
        g_Log.write("ERROR: nullptr\n");
        return false;
    }

    m_bitmapFont = bitmapFont;

    m_vertexArray.clear();
    m_vertexArray.resize(text.size() * 4);

    unsigned int x = 0;
    unsigned int y = 0;

    unsigned int textWidth = 0;

    for (std::size_t i = 0; i < text.size(); i++)
    {
        unsigned int asciiValue = static_cast<unsigned char>(text[i]);

        // skip unused characters
        if (asciiValue < 32 || asciiValue > 127)
        {
            continue;
        }

        // first 32 ascii characters skipped, need to offset the value
        asciiValue = asciiValue - 32;

        const unsigned int textureSizeX = bitmapFont->getTexture()->getSize().x;

        const unsigned int glyphSizeX = bitmapFont->getGlyphSize().x;
        const unsigned int glyphSizeY = bitmapFont->getGlyphSize().y;

        const unsigned int u = asciiValue % (textureSizeX / glyphSizeX);
        const unsigned int v = asciiValue / (textureSizeX / glyphSizeX);

        sf::Vertex* vertex = &m_vertexArray[i * 4];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2u(x,              y));
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2u(x + glyphSizeX, y));
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2u(x + glyphSizeX, y + glyphSizeY));
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2u(x,              y + glyphSizeY));

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, v       * glyphSizeY));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, v       * glyphSizeY));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, (v + 1) * glyphSizeY));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, (v + 1) * glyphSizeY));

        vertex[0].color = textColor;
        vertex[1].color = textColor;
        vertex[2].color = textColor;
        vertex[3].color = textColor;

        const unsigned int glyphWidth = bitmapFont->getGlyphWidthList()->at(asciiValue); //bitmapFont->getGlyphSize()->x;

        const unsigned int glyphSpace = bitmapFont->getGlyphSpace();

        x += glyphWidth + glyphSpace;

        textWidth += glyphWidth + glyphSpace;
    }

    if (isCentered == true)
    {
        if (textWidth != 0)
        {
            for (std::size_t i = 0; i < m_vertexArray.getVertexCount(); i++)
            {
                m_vertexArray[i].position.x = m_vertexArray[i].position.x - static_cast<float>(textWidth / 2);
            }
        }
    }

    return true;
}

sf::VertexArray* BitmapFontText::getVertexArray()
{
    return &m_vertexArray;
}

tb::BitmapFont* BitmapFontText::getBitmapFont()
{
    return m_bitmapFont;
}

void BitmapFontText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_bitmapFont->getTexture();

    target.draw(m_vertexArray, states);
}

}
