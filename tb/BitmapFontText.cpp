#include "tb/BitmapFontText.h"

namespace tb
{

BitmapFontText::BitmapFontText()
{
    //
}

BitmapFontText::~BitmapFontText()
{
    //
}

bool BitmapFontText::setText(tb::BitmapFont* bitmapFont, const std::string& text, const sf::Color& color)
{
    if (bitmapFont == nullptr)
    {
        g_Log.write("ERROR: bitmapFont == nullptr\n");
        return false;
    }

    m_bitmapFont = bitmapFont;

    m_text = text;

    m_color = color;

    m_vertexList.clear();
    m_vertexList.reserve(text.size() * 4);

    const unsigned int textureSizeX = bitmapFont->getTexture()->getSize().x;

    const unsigned int glyphSizeX = bitmapFont->getGlyphSize().x;
    const unsigned int glyphSizeY = bitmapFont->getGlyphSize().y;

    const int characterSpace = bitmapFont->getCharacterSpace();
    const int characterHeight = bitmapFont->getCharacterHeight();

    unsigned int textX = 0;
    unsigned int textY = 0;

    unsigned int textXMax = 0;
    unsigned int textYMax = 0;

    for (std::size_t i = 0; i < text.size(); i++)
    {
        // new line
        if (text[i] == '\n')
        {
            textX = 0;
            textY += characterHeight + m_paddingY;

            if (textYMax < textY)
            {
                textYMax = textY;
            }

            continue;
        }

        unsigned int asciiValue = static_cast<unsigned char>(text[i]);

        // skip unused characters
        if (asciiValue < 32 || asciiValue > 127)
        {
            continue;
        }

        // first 32 ascii characters skipped, need to offset the value
        asciiValue = asciiValue - 32;

        const unsigned int u = asciiValue % (textureSizeX / glyphSizeX);
        const unsigned int v = asciiValue / (textureSizeX / glyphSizeX);

        sf::Vertex vertex[4];

        vertex[0].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY));
        vertex[1].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY));
        vertex[2].position = static_cast<sf::Vector2f>(sf::Vector2u(textX + glyphSizeX, textY + glyphSizeY));
        vertex[3].position = static_cast<sf::Vector2f>(sf::Vector2u(textX,              textY + glyphSizeY));

        vertex[0].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, v       * glyphSizeY));
        vertex[1].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, v       * glyphSizeY));
        vertex[2].texCoords = static_cast<sf::Vector2f>(sf::Vector2u((u + 1) * glyphSizeX, (v + 1) * glyphSizeY));
        vertex[3].texCoords = static_cast<sf::Vector2f>(sf::Vector2u(u       * glyphSizeX, (v + 1) * glyphSizeY));

        vertex[0].color = color;
        vertex[1].color = color;
        vertex[2].color = color;
        vertex[3].color = color;

        m_vertexList.push_back(vertex[0]);
        m_vertexList.push_back(vertex[1]);
        m_vertexList.push_back(vertex[2]);
        m_vertexList.push_back(vertex[3]);

        const int characterWidth = bitmapFont->getCharacterWidthList()->at(asciiValue);

        textX += characterWidth + characterSpace;

        if (textXMax < textX)
        {
            textXMax = textX;
        }
    }

    const float textWidth = static_cast<float>(textXMax);
    const float textHeight = static_cast<float>(textYMax);

    sf::Vector2f position = getPosition();

    m_rect.left   = position.x;
    m_rect.top    = position.y;
    m_rect.width  = textWidth;
    m_rect.height = textHeight;

    return true;
}

tb::BitmapFont* BitmapFontText::getBitmapFont()
{
    return m_bitmapFont;
}

std::vector<sf::Vertex>* BitmapFontText::getVertexList()
{
    return &m_vertexList;
}

sf::FloatRect BitmapFontText::getRect()
{
    return m_rect;
}

std::string* BitmapFontText::getText()
{
    return &m_text;
}

sf::Color BitmapFontText::getColor()
{
    return m_color;
}

int BitmapFontText::getPaddingY()
{
    return m_paddingY;
}

void BitmapFontText::setPaddingY(int paddingY)
{
    m_paddingY = paddingY;
}

void BitmapFontText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = m_bitmapFont->getTexture();

    target.draw(&m_vertexList[0], m_vertexList.size(), sf::Quads, states);
}

}
