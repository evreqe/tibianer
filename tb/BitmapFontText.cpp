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

        const unsigned int tu = asciiValue % (textureSizeX / glyphSizeX);
        const unsigned int tv = asciiValue / (textureSizeX / glyphSizeX);

        sf::Vertex* quad = &m_vertexArray[i * 4];

        quad[0].position = sf::Vector2f(x,              y);
        quad[1].position = sf::Vector2f(x + glyphSizeX, y);
        quad[2].position = sf::Vector2f(x + glyphSizeX, y + glyphSizeY);
        quad[3].position = sf::Vector2f(x,              y + glyphSizeY);

        quad[0].texCoords = sf::Vector2f(tu          * glyphSizeX, tv          * glyphSizeY);
        quad[1].texCoords = sf::Vector2f((tu + 1.0f) * glyphSizeX, tv          * glyphSizeY);
        quad[2].texCoords = sf::Vector2f((tu + 1.0f) * glyphSizeX, (tv + 1.0f) * glyphSizeY);
        quad[3].texCoords = sf::Vector2f(tu          * glyphSizeX, (tv + 1.0f) * glyphSizeY);

        quad[0].color = textColor;
        quad[1].color = textColor;
        quad[2].color = textColor;
        quad[3].color = textColor;

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
                m_vertexArray[i].position.x = m_vertexArray[i].position.x - (static_cast<float>(textWidth) / 2.0f);
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
