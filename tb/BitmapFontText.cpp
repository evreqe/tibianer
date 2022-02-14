#include "tb/BitmapFontText.h"

namespace tb
{

BitmapFontText::BitmapFontText()
{
    m_vertexArray.setPrimitiveType(sf::Quads);
}

void BitmapFontText::setText(tb::BitmapFont* bf, std::string text, sf::Color textColor, bool isCentered)
{
    m_bitmapFont = bf;

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

        const unsigned int tu = asciiValue % (bf->getTexture()->getSize().x / bf->getGlyphSize()->x);
        const unsigned int tv = asciiValue / (bf->getTexture()->getSize().x / bf->getGlyphSize()->x);

        sf::Vertex* quad = &m_vertexArray[i * 4];

        quad[0].position = sf::Vector2f(x, y);
        quad[1].position = sf::Vector2f(x + bf->getGlyphSize()->x, y);
        quad[2].position = sf::Vector2f(x + bf->getGlyphSize()->x, y + bf->getGlyphSize()->y);
        quad[3].position = sf::Vector2f(x, y + bf->getGlyphSize()->y);

        quad[0].texCoords = sf::Vector2f(tu * bf->getGlyphSize()->x, tv * bf->getGlyphSize()->y);
        quad[1].texCoords = sf::Vector2f((tu + 1.0f) * bf->getGlyphSize()->x, tv * bf->getGlyphSize()->y);
        quad[2].texCoords = sf::Vector2f((tu + 1.0f) * bf->getGlyphSize()->x, (tv + 1.0f) * bf->getGlyphSize()->y);
        quad[3].texCoords = sf::Vector2f(tu * bf->getGlyphSize()->x, (tv + 1.0f) * bf->getGlyphSize()->y);

        quad[0].color = textColor;
        quad[1].color = textColor;
        quad[2].color = textColor;
        quad[3].color = textColor;

        const unsigned int glyphWidth = bf->getGlyphWidthList()->at(asciiValue); //bf->getGlyphSize()->x;

        x += glyphWidth + bf->getGlyphSpace();

        textWidth += glyphWidth + bf->getGlyphSpace();
    }

    if (isCentered == true)
    {
        if (textWidth > 0)
        {
            for (std::size_t i = 0; i < m_vertexArray.getVertexCount(); i++)
            {
                m_vertexArray[i].position.x = m_vertexArray[i].position.x - (static_cast<float>(textWidth) / 2.0f);
            }
        }
    }
}

sf::VertexArray* BitmapFontText::getVertexArray()
{
    return &m_vertexArray;
}

void BitmapFontText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_bitmapFont->getTexture();

    target.draw(m_vertexArray, states);
}

}
